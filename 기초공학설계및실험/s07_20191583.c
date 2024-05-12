#include<stdio.h>

void divideRemainder(int *a, int *b);

int main()
{
	int a,b;
	int divide;
	int remainder;
	printf("Input woo Number : ");
	scanf("%d%d", &a, &b);
	printf("----------------------------------------------------\n");
	divideRemainder(&a,&b);
	printf("OUTPUT : divide [%d] remainder [%d]\n", a, b);
	return 0;
}

void divideRemainder(int *a_adr, int *b_adr){
	int abc;
	abc=*a_adr;
	*a_adr=*a_adr / *b_adr;
	*b_adr=abc % *b_adr;
}




