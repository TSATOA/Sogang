#include<stdio.h>

int main()
{
	int a, b, *p, *q;
	printf("input integer :");
	scanf("%d %d", &a, &b);
	p = &a;
	q = &b;
	if (*p > *q)
		printf("difference: %d\n", *p - *q);
	else
		printf("difference: %d\n", *q - *p);
	printf("input1 = %d address =%u\n", *p, p);
	printf("input2 = %d address =%u\n", *q, q);
	return 0;
}