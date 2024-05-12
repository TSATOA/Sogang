#include<stdio.h>

void swap(int *a,int *b);
void bubble(int *a,int *b,int *c);

int main()
{
	int a,b,c;
	printf("Input 3 numbers: ");
	scanf("%d%d%d",&a,&b,&c);
	bubble(&a,&b,&c);
	printf("After sorting: %d %d %d\n",a,b,c);
	return 0;
}

void swap(int *a,int *b){
	int k;
	k=*a;
	*a=*b;
	*b=k;
}

void bubble(int *a,int *b,int *c){
	if(*a<*b) swap(a,b);
	if(*b<*c) swap(b,c);
	if(*a<*b) swap(a,b);

}

