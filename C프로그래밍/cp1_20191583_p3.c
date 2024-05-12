#include<stdio.h>

int main()
{
	double a, b, c;
	char k;
	double *pa, *pb;
	printf("Input operand 1 :");
	scanf("%lf", &a);
	printf("Input operand 2 :");
	scanf("%lf", &b);
	pa = &a;
	pb = &b;
	printf("\n");
	printf("Input operator : ");
	k=getchar();
	k = getchar();
	if (k == '+') {
		c = *pa + *pb;
	}
	else if (k == '-') {
		c = *pa - *pb;
	}
	else if (k == '*') {
		c = *pa * *pb;
	}
	else if (k == '/') {
		c = *pa / *pb;
	}
	printf("\n");
	printf("Result : %.2f", c);
	return 0;
}