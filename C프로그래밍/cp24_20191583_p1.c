#include<stdio.h>
#include<stdlib.h>

typedef struct node *sptr;

typedef struct{
	int count;
	sptr link;
}stack;

typedef struct node{
	int data;
	sptr link;
}stack_node;

void Exit(stack*);
void Push(stack*);
void Pop(stack*);
void Printall(stack*);

int main()
{
	stack *top;
	top->count=0;
	int n;	
	printf("****** Menu ******\n");
	printf("* 0 : Exit	 *\n");
	printf("* 1 : Push	 *\n");
	printf("* 2 : Pop	 *\n");
	printf("* 3 : Print All	 *\n");
	printf("******************\n");
	while(1){
		printf("Select > ");
		scanf("%d",&n);
		if(n==1){
			Push(top);
		} else if(n==2){
			Pop(top);
		} else if(n==3){
			Printall(top);
		} else{
			Exit(top);
			break;
		}
	}
	
}

void Exit(stack *top){
	stack_node *a;
	a=top->link;
	if(top->count==0) return ;

	while(a->link!=NULL){
		top->link=top->link->link;
		free(a);
		a=top->link;
	}
	free(top->link);

}

void Push(stack *top){
	stack_node *new;
	new=(stack_node *)malloc(sizeof(stack_node));
	printf("Input Data > ");
	scanf("%d",&(new->data));
	new->link=top->link;
	top->link=new;
	top->count++;
}

void Pop(stack *top){
	stack_node *del;
	if(top->count!=0){
		del=top->link;
		del->data=top->link->data;
		top->link=(top->link)->link;
		top->count--;
		printf("Pop %d\n",del->data);
		free(del);
		
	}else{
		printf("Stack is Empty\n");
	}
}

void Printall(stack *top){
	stack_node *a;
	a=top->link;
	if(top->count==0){
		printf("Stack is Empty!\n");
		return ;
	} else{
		for(int i=0;i<top->count;i++){
			printf("%d ",a->data);
			a=a->link;
		}
		printf("\nStack Level : %d\n",top->count);
	}
}

