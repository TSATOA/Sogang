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
void deletenodeatfront();
void deletenodeatback();


int main(){
	insertnodeatfront('n');
	insertnodeatfront('e');
	insertnodeatfront('p');
	insertnodeatback('l');
	insertnodeatfront('o');
	insertnodeatback('a');
	insertnodeatback('b');
	printlist();
	deletenodeatfront();
	deletenodeatback();
	deletenodeatback();
	deletenodeatback();
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

void deletenodeatfront(){
	NODE *a;
	a=head;
	head=head->link;
	free(a);
}

void deletenodeatback(){
	NODE *a;
	NODE *b;
	a=head;
	while(a->link!=NULL){
		b=a;
		a=a->link;
	}	
	free(a);
	b->link=NULL;
}
