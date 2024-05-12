#include "userprog/syscall.h"
#include <stdio.h>
#include <syscall-nr.h>
#include "threads/interrupt.h"
#include "threads/thread.h"
#include "devices/shutdown.h"
#include "userprog/process.h"
#include "devices/input.h"
#include "threads/vaddr.h"

static void syscall_handler (struct intr_frame *);

void
syscall_init (void) 
{
  intr_register_int (0x30, 3, INTR_ON, syscall_handler, "syscall");
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
      f->eax = exec(*(uint32_t *)(f->esp+4));
      break;
    case SYS_WAIT:
      if(!is_user_vaddr(f->esp+4))
        exit(-1);
      f->eax = wait((pid_t)*(uint32_t *)(f->esp+4));
      break;
    case SYS_CREATE:
      break;
    case SYS_REMOVE:
      break;
    case SYS_OPEN:
      break;
    case SYS_FILESIZE:
      break;
    case SYS_READ:
      if(!is_user_vaddr(f->esp+20))
        exit(-1);
      if(!is_user_vaddr(f->esp+24))
        exit(-1);
      if(!is_user_vaddr(f->esp+28))
        exit(-1);
      read((int)*(uint32_t*)(f->esp+20),(void*)*(uint32_t*)(f->esp+24),(unsigned)*((uint32_t*)(f->esp+28)));
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
      break;
    case SYS_TELL:
      break;
    case SYS_CLOSE:
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
  thread_exit();
}

pid_t exec(const char *cmd_line){
  return process_execute(cmd_line);
}

int wait(pid_t pid){
  return process_wait(pid);
}

int read (int fd, void *buffer, unsigned size){
  if (fd == 0) {
    return input_getc();
  }
  return -1;
}

int write(int fd, const void *buffer, unsigned size){
  if(fd ==1){
    putbuf((const void*)buffer, size);
    return size;
  }else{
    return -1;
  }
}
/**************************************/
// Fibonacci 정의
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
// Max_Of_Four_int 정의
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