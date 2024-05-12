#include "userprog/syscall.h"
#include <stdio.h>
#include <syscall-nr.h>
#include "threads/interrupt.h"
#include "threads/thread.h"
#include "threads/synch.h"
#include "devices/shutdown.h"
#include "userprog/process.h"
#include "devices/input.h"
#include "threads/vaddr.h"
#include "filesys/filesys.h"
#include "filesys/file.h"
#include "string.h"
#include "filesys/off_t.h"


static void syscall_handler (struct intr_frame *);
struct lock rw;

void
syscall_init (void) 
{
  intr_register_int (0x30, 3, INTR_ON, syscall_handler, "syscall");
  lock_init(&rw);
}

static void
syscall_handler (struct intr_frame *f UNUSED) 
{
  switch(*(uint32_t*)(f->esp)){
    case SYS_HALT:
      halt();
      break;
    case SYS_EXIT:
      if(!is_user_vaddr(f->esp+4))
        exit(-1);
      exit(*(uint32_t *)(f->esp+4));
      break;
    case SYS_EXEC:
      if(!is_user_vaddr(f->esp+4))
        exit(-1);
      f->eax = exec((const char*)*(uint32_t *)(f->esp+4));
      break;
    case SYS_WAIT:
      if(!is_user_vaddr(f->esp+4))
        exit(-1);
      f->eax = wait((pid_t)*(uint32_t *)(f->esp+4));
      break;
    case SYS_CREATE:
      if(!is_user_vaddr(f->esp+4))
        exit(-1);
      if(!is_user_vaddr(f->esp+8))
        exit(-1);
      f->eax = create((const char *)*(uint32_t *)(f->esp+4),(unsigned)*(uint32_t *)(f->esp+8));
      break;
    case SYS_REMOVE:
      if(!is_user_vaddr(f->esp+4))
        exit(-1);
      f->eax = remove((const char*)*(uint32_t *)(f->esp+4));
      break;
    case SYS_OPEN:
      if(!is_user_vaddr(f->esp+4))
        exit(-1);
      f->eax = open((const char*)*(uint32_t *)(f->esp+4));
      break;
    case SYS_FILESIZE:
      if(!is_user_vaddr(f->esp+4))
        exit(-1);
      f->eax = filesize((int)*(uint32_t *)(f->esp+4));
      break;
    case SYS_READ:
      if(!is_user_vaddr(f->esp+20))
        exit(-1);
      if(!is_user_vaddr(f->esp+24))
        exit(-1);
      if(!is_user_vaddr(f->esp+28))
        exit(-1);
      f->eax = read((int)*(uint32_t*)(f->esp+20),(void*)*(uint32_t*)(f->esp+24),(unsigned)*((uint32_t*)(f->esp+28)));
      break;
    case SYS_WRITE:
      if(!is_user_vaddr(f->esp+20))
        exit(-1);
      if(!is_user_vaddr(f->esp+24))
        exit(-1);
      if(!is_user_vaddr(f->esp+28))
        exit(-1);
      f->eax = write((int)*(uint32_t*)(f->esp+20),(void*)*(uint32_t*)(f->esp+24),(unsigned)*((uint32_t*)(f->esp+28)));
      break;
    case SYS_SEEK:
      if(!is_user_vaddr(f->esp+4))
        exit(-1);
      if(!is_user_vaddr(f->esp+8))
        exit(-1);
      seek((int)*(uint32_t *)(f->esp+4),(unsigned)*(uint32_t *)(f->esp+8));
      break;
    case SYS_TELL:
      if(!is_user_vaddr(f->esp+4))
        exit(-1);
      f->eax = tell((int)*(uint32_t *)(f->esp+4));
      break;
    case SYS_CLOSE:
      if(!is_user_vaddr(f->esp+4))
        exit(-1);
      close((int)*(uint32_t*)(f->esp+4));
      break;
    case SYS_MMAP:
      break;
    case SYS_MUNMAP:
      break;
    case SYS_FIBO:
      if(!is_user_vaddr(f->esp+4))
        exit(-1);
      f->eax = fibonacci((int)*(uint32_t *)(f->esp+4));
      break;
    case SYS_MOFI:
      if(!is_user_vaddr(f->esp+4))
        exit(-1);
      if(!is_user_vaddr(f->esp+8))
        exit(-1);
      if(!is_user_vaddr(f->esp+12))
        exit(-1);
      if(!is_user_vaddr(f->esp+16))
        exit(-1);
      f->eax = max_of_four_int((int)*(uint32_t *)(f->esp+4),(int)*(uint32_t *)(f->esp+8),(int)*(uint32_t *)(f->esp+12),(int)*(uint32_t *)(f->esp+16));
      break;
  }
  //thread_exit ();
}
void halt(void){
  shutdown_power_off();
}

void exit(int status){
  printf("%s: exit(%d)\n", thread_name(), status);
  thread_current() -> exit_status = status;
  for(int i=3;i<128;i++){
    if(thread_current()->fd[i] != NULL){
      close(i);
    }
  }
  thread_exit();
}

pid_t exec(const char *cmd_line){
  return process_execute(cmd_line);
}

int wait(pid_t pid){
  return process_wait(pid);
}

int read (int fd, void* buffer, unsigned size) {
  int read_res=-1;
  if(!is_user_vaddr(buffer))
    exit(-1);
  lock_acquire(&rw);
  if(fd==0){
    read_res = input_getc();
    lock_release(&rw);
    return read_res;
  }else if(fd>2){
    if (thread_current()->fd[fd] == NULL) {
      lock_release(&rw);
      exit(-1);
    }
    read_res = file_read(thread_current()->fd[fd],buffer,size);
    lock_release(&rw);
    return read_res;
  }else{
    lock_release(&rw);
    return -1;
  }
}
int write (int fd, const void *buffer, unsigned size) {
  int write_res= -1;
  if(!is_user_vaddr(buffer))
    exit(-1);
  lock_acquire(&rw);
  if (fd == 1) {
    putbuf(buffer, size);
    lock_release(&rw);
    return size;
  }
  else if(fd > 2){
    if (thread_current()->fd[fd] == NULL) {
      lock_release(&rw);
      exit(-1);
    }
    
    write_res= file_write(thread_current()->fd[fd],buffer,size);
    lock_release(&rw);  
    return write_res;
  }else{
    lock_release(&rw);  
    return -1;
  }
  
}

/**************************************/
// Fibonacci ?†ï?ùò
int fibonacci(int n){
  int a = 0, b = 1, tmp;
  if(n<=0){
    return 0;
  }else if (n==1){
    return 1;
  } else{
    for(int i=2; i<=n; i++){
      tmp = a+b;
      a = b;
      b = tmp;
    }
    return b;
  }
}
// Max_Of_Four_int ?†ï?ùò
int max_of_four_int(int a, int b, int c, int d){
  int max = a;
  if(b>max){
    max = b;
  }
  if(c>max){
    max = c;
  }
  if(d>max){
    max = d;
  }
  return max;
}
/**************************************/
bool create(const char *file,unsigned initial_size){
  if(file == NULL){
    exit(-1);
  }
  return filesys_create(file,initial_size);
}
bool remove(const char *file){
  if(file == NULL){
    exit(-1);
  }
  return filesys_remove(file);
}
int open(const char *file){
  if(file == NULL){
    exit(-1);
  }
  if(!is_user_vaddr(file))
    exit(-1);
  lock_acquire(&rw);
  struct file* fileobj = filesys_open(file);  
  if(fileobj == NULL){
    lock_release(&rw);
    return -1;
  }
  else {
    for(int i=3;i<128;i++){
      if(thread_current()->fd[i] == NULL){
        if(strcmp(thread_current()->name,file) == 0){
          file_deny_write(fileobj);
        }
        thread_current()->fd[i] = fileobj;
        lock_release(&rw);
        return i;
     }
    }
  }
  lock_release(&rw);
  return -1;
}
void close (int fd){
  struct file* fileobj;
  if (thread_current()->fd[fd] == NULL) {
      exit(-1);
  }
  fileobj = thread_current()->fd[fd];
  thread_current()->fd[fd] = NULL;
  return file_close(fileobj);
}

int filesize(int fd){
  int len;
  if (thread_current()->fd[fd] == NULL) {
      exit(-1);
  }
  len = file_length(thread_current()->fd[fd]);
  return len;
}

void seek(int fd, unsigned position){
  if (thread_current()->fd[fd] == NULL) {
      exit(-1);
  }
  return file_seek(thread_current()->fd[fd],position);
}

unsigned tell (int fd){
  if (thread_current()->fd[fd] == NULL) {
      exit(-1);
  }
  return file_tell(thread_current()->fd[fd]);
}