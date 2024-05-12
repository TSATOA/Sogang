#include<stdio.h>

float ave(int,int,int,int);
float dev(int,float);

int main()
{
	int a,b,c,d;
	printf("Enter the first number : ");
	scanf("%d", &a);
	printf("Enter the second number : ");
	scanf("%d", &b);
	printf("Enter the third number : ");
	scanf("%d", &c);
	printf("Enter the fourth number : ");
	scanf("%d", &d);
	printf("******** average is %.2f ********\n", ave(a,b,c,d) );	
	printf("first number :  %10d  -- deviation : %10.2f\n", a, dev(a,ave(a,b,c,d)));
	printf("second number : %10d  -- deviation : %10.2f\n", b, dev(b,ave(a,b,c,d)));
	printf("third number :  %10d  -- deviation : %10.2f\n", c, dev(c,ave(a,b,c,d)));
	printf("fourth number : %10d  -- deviation : %10.2f\n", d, dev(d,ave(a,b,c,d)));
	return 0;
}

float ave(int a, int b, int c, int d){
	float average;
	average=(float)(a+b+c+d)/4;
	return average;
}

float dev(int a, float ave){
	float res;
	res = (float)a-ave;
	return res;
}

