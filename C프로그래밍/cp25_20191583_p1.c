#include<stdio.h>
#include<stdlib.h>

typedef struct node{
	int data;
	struct node* next;
} QUEUE_NODE;

typedef struct{
	QUEUE_NODE *front;
	int count;
	QUEUE_NODE *rear;
} QUEUE;

void Exit(QUEUE *queue);
void Enqueue(QUEUE *queue);
void PrintAll(QUEUE *queue);
void Dequeue(QUEUE *queue);

int main(){
	QUEUE *queue;
	queue->count=0;
	int n;
	printf("****** Menu ******\n");
	printf("0 : Exit	 *\n");
	printf("1 : Enqueue	 *\n");
	printf("2 : Dequeue	 *\n");
	printf("3 : Print All	 *\n");
	printf("******************\n");
	while(1){
		printf("Select > ");
		scanf("%d",&n);
		if(n==1){
			Enqueue(queue);
		} else if(n==2){
			Dequeue(queue);
		} else if(n==3){
			PrintAll(queue);
		} else{
			Exit(queue);
			break;
		}
	}

}

void Exit(QUEUE *queue){
	QUEUE_NODE *a;
	a=queue->front;
	if(queue->count==0) return ;

	while(a->next!=NULL){
		queue->front=queue->front->next;
		free(a);
		a=queue->front;
	}
	free(queue->front);

}

void Enqueue(QUEUE *queue){
	QUEUE_NODE *new;
	int n;
	new=(QUEUE_NODE*)malloc(sizeof(QUEUE_NODE));
	printf("Input Data > ");
	scanf("%d",&n);
	new->data=n;
	new->next=NULL;
	if(queue->count==0){
		queue->front=new;
	} else{
		queue->rear->next=new;
	}
	queue->rear=new;
	queue->count++;
}

void Dequeue(QUEUE *queue){
	QUEUE_NODE *del;
	int k;
	if(queue->count==0){
		printf("NO DATA\n");
		return ;
	}
	k=queue->front->data;
	del=queue->front;
	if(queue->count==1){
		queue->rear=NULL;
		queue->front=NULL;
	} else{
		queue->front=queue->front->next;
	}
	queue->count--;
	printf("Dequeue %d\n",k);
	free(del);
}

void PrintAll(QUEUE *queue){
	QUEUE_NODE *a;
	a=queue->front;
	while(a!=NULL){
		printf("%d ",a->data);
		a=a->next;
	}
	printf("\nQueue Level : %d\n",queue->count);
}
