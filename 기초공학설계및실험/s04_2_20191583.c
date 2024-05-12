#include<stdio.h>

int main()
{
	int a,b;
	printf("Birthday : ");
	scanf("%d", &a);
	printf("Your birthday is %d / %d / %d\n", a/10000, a%10000/100, a%100);
	printf("Year : ");	
	scanf("%d", &b);
	printf("In %d, your age is %d\n", b, b-a/10000+1);
	return 0;

}	

