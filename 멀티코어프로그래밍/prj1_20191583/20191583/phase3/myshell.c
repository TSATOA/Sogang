/* $begin shellmain */
#include "csapp.h"
#include <errno.h>
#define MAXARGS 128

/* Function prototypes */
void eval(char *cmdline);
int parseline(char *buf, char **argv);
int builtin_command(char **argv);

void show_history(int cnt, char *cmdl, int *t); // cnt번째 history 출력. cnt<0이면 모두 출력.
void write_history(char **argv);                // 입력된 명령어 history에 저장
int check_history(char *cmdline);               // 입력된 명령어가 history관련 명령어 !!,!#인지 체크
static int child = 0;
void redir(int ofd, int nfd);
void call_pipe(char ***cmd, int p, int ifd);
void show_pipe(char **argv, char *cmdline, int checkpipe);
int check_pipe(char **argv);


char Path[MAXLINE];



int main()
{
    char cmdline[MAXLINE]; /* Command line */
    if (getcwd(Path, MAXLINE) == NULL)
    {
        perror("getcwd() error");
        return -1;
    }
    strcat(Path, "/history");

    while (1)
    {
        /* Read */
        printf("CSE4100-MP-P1> ");
        fgets(cmdline, MAXLINE, stdin);
        if (feof(stdin))
            exit(0);

        /* Evaluate */
        eval(cmdline);
    }
}
/* $end shellmain */

/* $begin eval */
/* eval - Evaluate a command line */
void eval(char *cmdline)
{
    char *argv[MAXARGS]; /* Argument list execve() */
    char buf[MAXLINE];   /* Holds modified command line */
    int bg;              /* Should the job run in bg or fg? */
    pid_t pid;           /* Process id */
    int checkhist;
    int checkpipe = -1;

    checkhist = check_history(cmdline);

    strcpy(buf, cmdline);
    bg = parseline(buf, argv);

    checkpipe = check_pipe(argv);

    if (checkhist)
        write_history(argv);

    if (argv[0] == NULL)
        return; /* Ignore empty lines */
    // pipe가 없는 경우
    if (checkpipe < 0)
    {
        // 저장된 history 범위 내에 숫자가 들어온 경우
        if (checkhist)
        {
            if (!builtin_command(argv))
            { // quit -> exit(0), & -> ignore, other -> run
                if ((pid = fork()) == 0)
                {
                    if (strcmp(argv[0], "echo") == 0)
                    {
                        int x = 1;
                        while (argv[x] != NULL)
                        {
                            char *src = argv[x];
                            char *dst = argv[x];
                            while (*src)
                            {
                                if (*src != '"')
                                {
                                    *dst++ = *src;
                                }
                                src++;
                            }
                            *dst = '\0';
                            x++;
                        }
                        x = 1;
                        while (argv[x] != NULL)
                        {
                            char *src = argv[x];
                            char *dst = argv[x];
                            while (*src)
                            {
                                if (*src != '\'')
                                {
                                    *dst++ = *src;
                                }
                                src++;
                            }
                            *dst = '\0';
                            x++;
                        }
                        if (execvp(argv[0], argv) < 0)
                        {
                            printf("%s: Command not found.\n", argv[0]);
                            exit(0);
                        }
                    }
                    else
                    {
                        if (execvp(argv[0], argv) < 0)
                        {
                            printf("%s: Command not found.\n", argv[0]);
                            exit(0);
                        }
                    }
                }

                /* Parent waits for foreground job to terminate */
                if (!bg)
                {
                    int status;
                    if (waitpid(pid, &status, 0) < 0)
                        unix_error("waitfg: waitpid error");
                }
                else // when there is backgrount process!
                    printf("%d %s", pid, cmdline);
            }
        }
    }
    // 파이프가 가장 처음에 온 경우
    else if (checkpipe == 0)
    {
        printf("-bash:systax error near unexpected token '|'\n");
    }
    // 파이프가 입력된 경우
    else
    {
        if((pid=fork())==0){
            show_pipe(argv, cmdline, checkpipe);
            exit(0);
        }
        if (!bg)
                {
                    int status;
                    if (waitpid(pid, &status, 0) < 0)
                        unix_error("waitfg: waitpid error");
                }
                else // when there is backgrount process!
                    printf("%d %s", pid, cmdline);
    }
    return;
}

/* If first arg is a builtin command, run it and return true */
int builtin_command(char **argv)
{
    if (!strcmp(argv[0], "quit")) /* quit command */
        exit(0);
    if (!strcmp(argv[0], "exit")) /* exit command */
        exit(0);
    if (!strcmp(argv[0], "&")) /* Ignore singleton & */
        return 1;
    if (!strcmp(argv[0], "cd"))
    { /* cd command */
        if (chdir(argv[1]) < 0)
        {
            printf("Error: %s\n", strerror(errno));
        }
        return 1;
    }

    if (!strcmp(argv[0], "history"))
    {
        char *s;
        int t;
        show_history(-2, s, &t);
        return 1;
    }

    return 0; /* Not a builtin command */
}
/* $end eval */

/* $begin parseline */
/* parseline - Parse the command line and build the argv array */
int parseline(char *buf, char **argv)
{
    char *delim; /* Points to first space delimiter */
    int argc;    /* Number of args */
    int bg;      /* Background job? */

    // buf[strlen(buf)-1] = ' ';  /* Replace trailing '\n' with space */
    buf[strcspn(buf, "\n")] = ' '; /* Replace trailing '\n' with space */
    while (*buf && (*buf == ' '))  /* Ignore leading spaces */
        buf++;

    /* Build the argv list */
    argc = 0;
    while ((delim = strchr(buf, ' ')))
    {
        argv[argc++] = buf;
        *delim = '\0';
        buf = delim + 1;
        while (*buf && (*buf == ' ')) /* Ignore spaces */
            buf++;
    }
    argv[argc] = NULL;

    if (argc == 0) /* Ignore blank line */
        return 1;

    /* Should the job run in the background? */
    if ((bg = (*argv[argc - 1] == '&')) != 0)
        argv[--argc] = NULL;

    return bg;
}
/* $end parseline */

void write_history(char **argv)
{
    if (argv[0] == NULL)
        return;
    FILE *fp = fopen(Path, "a+");
    int canwr = 0;
    char buf[MAXLINE];
    char *hist_argv[MAXARGS];
    // 입력했던 내용이 없으면 새로운 명령어 파일에 추가 가능
    // 입력했던 내용이 있으면 history 파일에서 내용을 꺼내오고, 현재 입력된 명령어와 비교
    fseek(fp, 0, SEEK_END);

    if (ftell(fp) == 0)
    {
        canwr = 1;
    }
    else
    {
        fseek(fp, -1, SEEK_END);
        long int pos = ftell(fp);
        int x = 0;
        while (pos - x >= 1)
        {
            x++;
            if (pos - x == 0)
            {
                fseek(fp, 0, SEEK_SET);
                break;
            }
            fseek(fp, -x - 1, SEEK_END);
            if (fgetc(fp) == '\n')
            {
                x--;
                fseek(fp, -x - 1, SEEK_END);
                break;
            }
        }
        fgets(buf, MAXLINE, fp);
        buf[strcspn(buf, "\n")] = '\0';
        parseline(buf, hist_argv);
        int k = 0;
        while (1)
        {
            if (argv[k] == NULL && hist_argv[k] == NULL)
                break;

            if (argv[k] == NULL || hist_argv[k] == NULL)
            {
                canwr = 1;
                break;
            }
            if (strncmp(argv[k], hist_argv[k], MAXLINE))
            {
                canwr = 1;
                break;
            }
            k++;
        }
    }

    if (canwr)
    {
        // 파일 출력
        int i = 0;
        fseek(fp, 0L, SEEK_END);
        while (1)
        {
            fprintf(fp, "%s", argv[i]);

            if (argv[i + 1] == NULL)
                break;
            fprintf(fp, " ");

            i++;
        }
        fprintf(fp, "\n");
    }
    fclose(fp);
}

int check_history(char *cmdline)
{
    int i = 0;
    char cmdl[MAXLINE];
    char *pos = strstr(cmdline, "!!");
    int t = 1;
    while (pos)
    {
        show_history(-1, cmdl, &t);
        memmove(pos + strlen(cmdl), pos + 2, strlen(pos + 2) + 1);
        memcpy(pos, cmdl, strlen(cmdl));
        pos = strstr(cmdline, "!!");
    }
    pos = NULL;
    pos = strstr(cmdline, "!");
    while (pos)
    {
        // "!" 다음에 오는 숫자를 파싱한다.
        int num = atoi(pos + 1);
        int lennum = 0;
        int n = num;
        while (n != 0)
        {
            n = n / 10;
            lennum++;
        }

        show_history(num, cmdl, &t);
        if (t)
        {
            memmove(pos + strlen(cmdl), pos + lennum + 1, lennum + 1);
            memcpy(pos, cmdl, strlen(cmdl));
        }
        pos = strstr(pos + 1, "!");
    }

    return t;
}

void show_history(int cnt, char *cmdl, int *t)
{
    FILE *fp = fopen(Path, "r");
    char history_command[MAXLINE];
    char c;
    int line = 0;
    *t = 1;
    while ((c = fgetc(fp)) != EOF)
        if (c == '\n')
            line++;
    fseek(fp, 0, SEEK_SET);
    if (cnt == -1)
    {
        while (fgets(history_command, MAXLINE, fp) != NULL)
        {
        }
    }
    else if (cnt == -2)
    {
        int i = 1;
        while (fgets(history_command, MAXLINE, fp) != NULL)
        {
            printf("%d %s", i, history_command);
            i++;
        }
        return;
    }
    else
    {
        if (cnt > line)
        {
            *t = 0;
            printf("-bash: !%d: event not found\n", cnt);
            return;
        }
        for (int i = 0; i < cnt; i++)
        {
            fgets(history_command, MAXLINE, fp);
        }
    }
    fclose(fp);
    history_command[strcspn(history_command, "\n")] = '\0';
    strcpy(cmdl, history_command);
}

int check_pipe(char **argv)
{
    int cnt = 0;
    if (argv[0] == NULL)
        return -1;
    for (int i = 0; argv[i] != NULL; i++)
    {
        char *p = argv[i];
        while ((p = strchr(p, '|')) != NULL)
        {
            cnt++;
            p++;
        }
    }
    char *a = argv[0];
    if (strchr(a, '|') == a)
        return 0;
    if (cnt != 0)
        return cnt;
    else
        return -1;
}

void show_pipe(char **argv, char *cmdline, int checkpipe)
{
    char cmds[checkpipe + 1][MAXARGS][MAXLINE];
    memset(cmds, 0, sizeof(cmds));
    char *token, *subtoken;
    int j = 0;
    char st[checkpipe + 1][MAXLINE];
    token = strtok(cmdline, "|");
    strcpy(st[0], token);
    for (int i = 1; i < checkpipe + 1; i++)
    {
        token = strtok(NULL, "|");
        strcpy(st[i], token);
    }

    for (int i = 0; i < checkpipe + 1; i++)
    {
        int x = 0;
        subtoken = strtok(st[i], " \n");
        while (subtoken != NULL)
        {
            strcpy(cmds[i][x], subtoken);
            x++;
            subtoken = strtok(NULL, " \n");
        }
    }
    
    int a[MAXARGS];
    

    for(int i=0;i<checkpipe+1;i++){
        int j = 0;
        while(cmds[i][j][0]!='\0'){
            char *src = cmds[i][j];
            char *dst = cmds[i][j];
            while(*src){
                if(*src != '"'){
                    *dst++ = *src;
                }
                src++;
            }
            *dst = '\0';
            j++;
        }
        a[i] = j;
        j=0;
        while(cmds[i][j][0]!='\0'){
            char *src = cmds[i][j];
            char *dst = cmds[i][j];
            while(*src){
                if(*src != '\''){
                    *dst++ = *src;
                }
                src++;
            }
            *dst = '\0';
            j++;
        }
    }



    char ***cmdd = malloc(sizeof(char**)*(checkpipe+2));
    for(int j=0;j<(checkpipe+1);j++){
        cmdd[j] = malloc(sizeof(char*)*(a[j]+1));
    }

    cmdd[checkpipe+1] = NULL;
    
    for(int i=0;i<checkpipe+1;i++){
        int j=0;
        for(j=0;j<a[i];j++){
            cmdd[i][j] = malloc(sizeof(char) * (strlen(cmds[i][j]) + 1));
            strcpy(cmdd[i][j],cmds[i][j]);
        }
        cmdd[i][j] = NULL;
    }
    call_pipe((char***)cmdd, 0 , STDIN_FILENO);
    for (int i = 0; i < checkpipe + 1; i++) {
        for (int j = 0; j < a[i]; j++) {
            free(cmdd[i][j]);
        }
        free(cmdd[i]);
    }   
    free(cmdd);

}


void redir(int ofd, int nfd)
{
    if (ofd != nfd)
    {
        if (dup2(ofd, nfd) != -1) close(ofd);
        else exit(0);
    }
}

void call_pipe(char ***cmd, int p, int ifd){
    if (cmd[p + 1] == NULL)
    {
        redir(ifd, STDIN_FILENO);
        execvp(cmd[p][0], cmd[p]);
        exit(0);
    }
    else
    {
        int fd[2];
        if (pipe(fd) == -1) exit(0);
        int fn = fork();
        if (fn == -1)
        {
            exit(0);
        }
        else if (fn == 0)
        {
            child = 1;
            close(fd[0]);
            redir(ifd, STDIN_FILENO);
            redir(fd[1], STDOUT_FILENO);
            execvp(cmd[p][0], cmd[p]);
            exit(0);
        }
        else
        {
            close(fd[1]);
            close(ifd);
            call_pipe(cmd, p + 1, fd[0]);
        }
    }
}