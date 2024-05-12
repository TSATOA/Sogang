#include<stdio.h>

int main()
{
	int a;
	int b;
	double c,d;
	printf("Price : ");
	scanf("%d", &a);
	printf("----------------output---------------\n");
	printf("Month		:%10d%10d\n",3,6);
	b=a*1.05*1.05*1.05;
	printf("Payment		:%10d%10d\n", a,b);	
	printf("-------------------------------------\n");
	c=(double)a/3;
	d=(double)b/6;
	printf("Pay/month	:%10.2lf%10.2lf\n", c,d);	
	return 0;
}
