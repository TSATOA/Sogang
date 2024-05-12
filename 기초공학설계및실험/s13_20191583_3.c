#include<stdio.h>

int main()
{
	int a,b,c,d,e,f;
	int cnt=0;
	printf("Enter 2 numbers: ");
	scanf("%1d%1d%1d %1d%1d%1d", &a, &b, &c, &d, &e, &f);
	if(c+f>=10){
		cnt++;
		b++;
	}
	if(b+e>=10){
		cnt++;
		a++;
	}
	if(a+d>=10){
		cnt++;
	}
	printf("%d carry operations\n", cnt);
	return 0;
}
