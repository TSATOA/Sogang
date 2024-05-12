#include<stdio.h>

int a,b;

void fourmath(int *c, int *d);
void printResult(int *c, int *d);

int main()
{
	int a,b;
	printf("Input two number: ");
	scanf("%d%d", &a, &b);
	fourmath(&a, &b);
	printResult(&a, &b);
	return 0;
}

void fourmath(int *c, int *d){
	a=*c+*d;
	b=*c-*d;
	*c=*c**d;
	*d=((a+b)/2)/((a-b)/2);
	return;
}

void printResult(int *c,int *d){
	printf("Result: a+b=%d, a-b=%d, a*b=%d, a/b=%d\n", a,b,*c,*d);
	return;
}
