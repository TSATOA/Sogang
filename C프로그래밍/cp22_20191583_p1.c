#include<stdio.h>
#include<stdlib.h>

typedef struct _NODE{
	char data;
	struct _NODE *link;
}NODE;

NODE *head=NULL;

void insertnodeatfront(char a);
void insertnodeatback(char b);
void printlist();

int main(){
	insertnodeatfront('p');
	insertnodeatfront('p');
	insertnodeatfront('a');
	insertnodeatback('l');
	insertnodeatback('e');
	printlist();
	return 0;
}

void insertnodeatback(char a){
	NODE *new;
	NODE *k;
	new=(NODE *)malloc(sizeof(NODE));
	k=head;
	(*new).data=a;
	new->link=NULL;
	while(k->link!=NULL){
		k=k->link;
	}
	k->link=new;
	
}

void insertnodeatfront(char a){
	NODE *new;
	new=(NODE *)malloc(sizeof(NODE));
	(*new).data=a;
	new->link=head;
	head=new;
}

void printlist(){
	NODE *k;
	k=head;
	while(k!=NULL){
		printf("%c",(*k).data);
		k=k->link;
	}
	printf("\n");
}
