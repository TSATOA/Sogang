#include<stdio.h>

void sqr(int);
void printOne(int);


int main()
{
	int a;
	int result;
	printf("Input: ");
	scanf("%d", &a);
	sqr(a);
}


void printOne(int a)
{
	printf("Result: %d\n", a);
	return;
}	


void  sqr(int a){
	int result;
	result=a*a;
	printOne(result);
	return;
}






