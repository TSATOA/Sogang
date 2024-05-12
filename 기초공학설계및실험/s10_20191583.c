#include<stdio.h>

int main()
{
	float n;
	printf("Input: ");
	scanf("%f", &n);
	printf("Use \">\": %d\n", (int)(0.5+n)>n);
	printf("Use \">=\": %d\n", n-(int)n>=0.5);
	printf("Use \"==\": %d\n", (int)(0.5+n)==(int)n+1);
	printf("Use \"!=\": %d\n", (int)(0.5+n)!=(int)n);
	return 0;
}