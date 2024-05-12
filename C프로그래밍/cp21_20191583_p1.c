#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct _Node{
	int id;
	char name[30];
	struct _Node *link;
}Node;

Node *head=NULL;

void create(int id, char *name);

int main()
{
	int n,i;
	Node *k;
	k=head;
	scanf("%d",&n);
	for(i=0;i<n;i++){
		int id;
		char name[30];
		scanf("%d %*c %30[^\n]",&id,name);
		create(id,name);
		//
	}
	for(k=head; k->link != NULL; k = k->link){
		printf("%d / %s\n",k->id,k->name);
	}
}

void create(int id, char *name){
	Node *new;
	Node *a;

	new=(Node *)malloc(sizeof(Node));
	new->id=id;
	strcpy(new->name,name);
	if(head==NULL){
		head=new;
	} else{
		a=head;
		while (a->link!=NULL){
			a=a->link;
		}
		a->link = new;
	}
}
 
