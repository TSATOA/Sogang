#include<stdio.h>

int main()
{
	double a, b, c, d;
	double *pa, *pb, *pc, *pd;

	scanf("%d%d%d%d", &a, &b, &c, &d);
	pa = &a;
	pb = &b;
	pc = &c;
	pd = &d;

	if (*pa == *pc) {
		if (*pb == *pd) {
			printf("00");
		}
		else {
			printf("0");
		}
	} else {
		printf("1");
	}
	return 0;

}