/* 
 * stockserver.c - A simple stock management server
 */ 

#include "csapp.h"

struct item {
    int ID;
    int left_stock;
    int price;
    int readcnt;
    struct item *left_item;
    struct item *right_item;
};

struct item *root = NULL;

struct item *create_item(int ID, int left_stock, int price) {
    struct item *new_item = (struct item *)malloc(sizeof(struct item));
    new_item->ID = ID;
    new_item->left_stock = left_stock;
    new_item->price = price;
    new_item->readcnt = 0;
    new_item->left_item = NULL;
    new_item->right_item = NULL;
    return new_item;
}

struct item *insert(struct item *root, int ID, int left_stock, int price) {
    if (root == NULL) {
        return create_item(ID, left_stock, price);
    }

    if (ID < root->ID) {
        root->left_item = insert(root->left_item, ID, left_stock, price);
    } else if (ID > root->ID) {
        root->right_item = insert(root->right_item, ID, left_stock, price);
    }

    return root;
}

void show(struct item *root, char buf[]) {
    char tmp[MAXLINE];
    if (root != NULL) {
        show(root->left_item, buf);
        sprintf(tmp, "%d %d %d\n", root->ID, root->left_stock, root->price);
        strcat(buf, tmp);
        show(root->right_item, buf);
    }
}

struct item *search(struct item *root, int ID) {
    if (root == NULL || root->ID == ID) {
        return root;
    }

    if (ID < root->ID) {
        return search(root->left_item, ID);
    } else {
        return search(root->right_item, ID);
    }
}

void sigint_handler(int signum) {
    char writefile[MAXLINE];
    FILE *file = fopen("stock.txt", "w");
    memset(writefile, 0, sizeof(writefile));
    show(root, writefile);
    Fputs(writefile, file);
    fclose(file);
    exit(1);
}

typedef struct {
    int maxfd;
    fd_set read_set;
    fd_set ready_set;
    int nready;
    int maxi;
    int clientfd[FD_SETSIZE];
    rio_t clientrio[FD_SETSIZE];
} pool;

void init_pool(int listenfd, pool *p) {
    int i;
    p->maxi = -1;
    for (i = 0; i < FD_SETSIZE; i++)
        p->clientfd[i] = -1;

    p->maxfd = listenfd;
    FD_ZERO(&p->read_set);
    FD_SET(listenfd, &p->read_set);
}

void add_client(int connfd, pool *p) {
    int i;
    p->nready--;
    for (i = 0; i < FD_SETSIZE; i++)
        if (p->clientfd[i] < 0) {
            p->clientfd[i] = connfd;
            Rio_readinitb(&p->clientrio[i], connfd);

            FD_SET(connfd, &p->read_set);

            if (connfd > p->maxfd)
                p->maxfd = connfd;
            if (i > p->maxi)
                p->maxi = i;
            break;
        }
    if (i == FD_SETSIZE)
        app_error("add_client error: Too many clients");
}

void check_clients(pool *p) {
    int i, connfd, n, st_id_num, st_cnt_num;
    char buf[MAXLINE], cmd[100], st_id[100], st_cnt[100], serprint[MAXLINE];

    rio_t rio;

    for (i = 0; (i <= p->maxi) && (p->nready > 0); i++) {
        connfd = p->clientfd[i];
        rio = p->clientrio[i];

        if ((connfd > 0) && (FD_ISSET(connfd, &p->ready_set))) {
            p->nready--;
            if ((n = Rio_readlineb(&rio, buf, MAXLINE)) != 0) {
                printf("server received %d bytes on fd %d\n", n, connfd);
                memset(serprint, 0, sizeof(serprint));
                sscanf(buf, "%s", cmd);
                if (!strcmp(cmd, "show")) {
                    char buff[MAXLINE];
                    memset(buff, 0, sizeof(buff));
                    show(root, buff);
                    Rio_writen(connfd, buff, MAXLINE);
                } else if (!strcmp(cmd, "exit")) {
                    Close(connfd);
                    FD_CLR(connfd, &p->read_set);
                    p->clientfd[i] = -1;
                } else {
                    sscanf(buf, "%s %s %s", cmd, st_id, st_cnt);
                    st_id_num = atoi(st_id);
                    st_cnt_num = atoi(st_cnt);
                    if (!strcmp(cmd, "buy")) {
                        struct item *target_item = search(root, st_id_num);
                        if (target_item != NULL) {
                            if (target_item->left_stock >= st_cnt_num) {
                                target_item->left_stock -= st_cnt_num;
                                strcpy(serprint, "[buy] success\n");
                            } else {
                                strcpy(serprint, "Not enough left stock\n");
                            }
                        } 
                    } else if (!strcmp(cmd, "sell")) {
                        struct item *target_item = search(root, st_id_num);
                        if (target_item != NULL) {
                            target_item->left_stock += st_cnt_num;
                            strcpy(serprint, "[sell] success\n");
                        } 
                    }
                    Rio_writen(connfd, serprint, MAXLINE);
                }

            } else {
                Close(connfd);
                FD_CLR(connfd, &p->read_set);
                p->clientfd[i] = -1;
            }
        }
    }
}

int main(int argc, char **argv) {
    Signal(SIGINT, sigint_handler);

    int listenfd, connfd;
    socklen_t clientlen;
    struct sockaddr_storage clientaddr; /* Enough space for any address */
    char client_hostname[MAXLINE], client_port[MAXLINE];
    static pool pool;

    FILE *file = fopen("stock.txt", "r");
    int ID, stock, price;
    while (fscanf(file, "%d %d %d", &ID, &stock, &price) == 3) {
        root = insert(root, ID, stock, price);
    }
    fclose(file);

    listenfd = Open_listenfd(argv[1]);
    init_pool(listenfd, &pool);

    while (1) {
        pool.ready_set = pool.read_set;
        pool.nready = Select(pool.maxfd + 1, &pool.ready_set, NULL, NULL, NULL);

        if (FD_ISSET(listenfd, &pool.ready_set)) {
            clientlen = sizeof(struct sockaddr_storage);
            connfd = Accept(listenfd, (SA *)&clientaddr, &clientlen);
            add_client(connfd, &pool);

            Getnameinfo((SA *)&clientaddr, clientlen, client_hostname, MAXLINE,
                client_port, MAXLINE, 0);
            printf("Connected to (%s, %s)\n", client_hostname, client_port);
        }
        check_clients(&pool);
    }
    exit(0);
}
