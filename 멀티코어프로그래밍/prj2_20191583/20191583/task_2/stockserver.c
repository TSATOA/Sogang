#include "csapp.h"
#define SBUFSIZE 20
#define NTHREADS 100

typedef struct
{
    int *buf;
    int n;
    int front;
    int rear;
    sem_t mutex;
    sem_t slots;
    sem_t items;
} sbuf_t;

struct item
{
    int ID;
    int left_stock;
    int price;
    int readcnt;
    sem_t mutex;
    struct item *left;
    struct item *right;
};

sbuf_t sbuf;
struct item *root;
static sem_t mutex;
static sem_t w;
int byte_cnt = 0;

void sbuf_init(sbuf_t *sp, int n)
{
    sp->buf = Calloc(n, sizeof(int));
    sp->n = n;
    sp->front = sp->rear = 0;
    Sem_init(&sp->mutex, 0, 1);
    Sem_init(&sp->slots, 0, n);
    Sem_init(&sp->items, 0, 0);
}

void sbuf_deinit(sbuf_t *sp)
{
    Free(sp->buf);
}

void sbuf_insert(sbuf_t *sp, int item)
{
    P(&sp->slots);
    P(&sp->mutex);
    sp->buf[(++sp->rear) % (sp->n)] = item;
    V(&sp->mutex);
    V(&sp->items);
}

int sbuf_remove(sbuf_t *sp)
{
    int item;
    P(&sp->items);
    P(&sp->mutex);
    item = sp->buf[(++sp->front) % (sp->n)];
    V(&sp->mutex);
    V(&sp->slots);
    return item;
}

struct item * insert(struct item *node, int ID, int stock, int price) {
    if(node == NULL) {
        struct item *temp;
        temp = (struct item *)malloc(sizeof(struct item));
        temp->ID = ID;
        temp->left_stock = stock;
        temp->price = price;
        temp->readcnt = 0;
        temp->left = temp->right = NULL;
        Sem_init(&temp->mutex, 0, 1);
        return temp;
    }

    if(ID < (node->ID)) {
        node->left = insert(node->left, ID, stock, price);
    }
    else if(ID > (node->ID)) {
        node->right = insert(node->right, ID, stock, price);
    }

    return node;
}

struct item* find_id(struct item *node, int ID) {
    if(node == NULL) return NULL;

    if(ID < node->ID) return find_id(node->left, ID);
    else if(ID > node->ID) return find_id(node->right, ID);

    return node;
}

void show(struct item *node, char buf[]) {
    char tmp[MAXLINE];

    if(node != NULL) {
        
        
        P(&node->mutex);
        node->readcnt++;
        if(node->readcnt==1)
            P(&w);
        V(&node->mutex);

        sprintf(tmp, "%d %d %d\n", node->ID, node->left_stock, node->price);
        strcat(buf, tmp);
        
        P(&node->mutex);
        node->readcnt--;
        if(node->readcnt==0)
            V(&w);
        V(&node->mutex);
        show(node->left, buf);
        show(node->right, buf);
        
        
    }
}

static void init_echo_cnt(void)
{
    Sem_init(&mutex, 0, 1);
    Sem_init(&w, 0, 1);
    byte_cnt = 0;
}

void echo_cnt(int connfd)
{
    int n, st_id_num, st_cnt_num;
    char buf[MAXLINE];
    rio_t rio;
    static pthread_once_t once = PTHREAD_ONCE_INIT;
    char cmd[100], st_id[100], st_cnt[100], serprint[MAXLINE];

    Pthread_once(&once, init_echo_cnt);
    Rio_readinitb(&rio, connfd);
    while ((n = Rio_readlineb(&rio, buf, MAXLINE)) != 0)
    {
        printf("server received %d bytes on fd %d\n", n, connfd);
        memset(serprint, 0, sizeof(serprint));
        sscanf(buf, "%s", cmd);
        if (!strcmp(cmd, "show"))
        {
            show(root, serprint);
        }
        else if (!strcmp(cmd, "exit"))
        {
            break;
        }
        else
        {
            sscanf(buf, "%s %s %s", cmd, st_id, st_cnt);
            st_id_num = atoi(st_id);
            st_cnt_num = atoi(st_cnt);

            struct item *target = find_id(root, st_id_num);

            if (!strcmp(cmd, "buy"))
            {
                P(&w);
                if (target && target->left_stock >= st_cnt_num)
                {
                    target->left_stock -= st_cnt_num;
                    strcpy(serprint, "[buy] success\n");
                }
                else
                {
                    strcpy(serprint, "Not enough left stock\n");
                }
                V(&w);
            }
            else if (!strcmp(cmd, "sell"))
            {
                P(&w);
                if (target)
                {
                    target->left_stock += st_cnt_num;
                    strcpy(serprint,"[sell] success\n");
                }
                
                V(&w);
            }
        }

        Rio_writen(connfd, serprint, MAXLINE);
    }
}

void *thread(void *vargp)
{
    Pthread_detach(pthread_self());
    while (1)
    {
        int connfd = sbuf_remove(&sbuf);
        echo_cnt(connfd);
        Close(connfd);
    }
}

void sigint_handler(int signum)
{
    char writefile[MAXLINE];
    FILE *file = fopen("stock.txt", "w");
    memset(writefile, 0, sizeof(writefile));
    show(root, writefile);
    Fputs(writefile, file);
    fclose(file);
    exit(1);
}

int main(int argc, char **argv)
{
    Signal(SIGINT, sigint_handler);
    int i, listenfd, connfd;
    socklen_t clientlen;
    struct sockaddr_storage clientaddr;
    pthread_t tid;

    if (argc != 2)
    {
        fprintf(stderr, "usage: %s <port>\n", argv[0]);
        exit(0);
    }

    root = NULL;

    FILE *file = fopen("stock.txt", "r");
    int ID, stock, price;
    while (fscanf(file, "%d %d %d", &ID, &stock, &price) == 3)
    {
        root = insert(root, ID, stock, price);
    }
    fclose(file);

    listenfd = Open_listenfd(argv[1]);
    sbuf_init(&sbuf, SBUFSIZE);

    for (i = 0; i < NTHREADS; i++) /* Create worker threads */
        Pthread_create(&tid, NULL, thread, NULL);
    while (1)
    {
        clientlen = sizeof(struct sockaddr_storage);
        connfd = Accept(listenfd, (SA *)&clientaddr, &clientlen);
        sbuf_insert(&sbuf, connfd); /* Insert connfd in buffer */
    }
}

