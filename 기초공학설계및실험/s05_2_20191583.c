#include<stdio.h>

int  cal(int , int);

int main()
{
	int a, b;
	printf("Input first number: ");
	scanf("%d", &a);
	printf("Input second number: ");
	scanf("%d", &b);
	printf("%d + %d = %d\n", a, b, cal(a,b));
	return 0;
}

int cal(int a, int b)
{
	int result;
	result = a+b;
	return result;
}


