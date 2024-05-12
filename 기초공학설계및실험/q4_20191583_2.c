#include<stdio.h>

int main()
{
	char a,b;
	int x,y,res;
	scanf("%c %c", &a, &b);
	x=a-'0';
	y=b-'0';
	res=(x*y)%26;
	a=res+'A';
	printf("%c\n",a);
	return 0;

}
