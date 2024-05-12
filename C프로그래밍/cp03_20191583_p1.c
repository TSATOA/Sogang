#include<stdio.h>

void swap(char **a,char **b);

int main()
{
	printf("Before swapping\n\n");
	char *str1="she can do, he can do";
	char *str2="why not me?";
	printf("str1 = %s\n",str1);
	printf("str2 = %s\n\n",str2);
	swap(&str1,&str2);
	printf("After swapping\n\n");
	printf("str1 = %s\n",str1);
	printf("str2 = %s\n", str2);
}

void swap(char **a,char **b){
	char *k;
	k=*a;
	*a=*b;
	*b=k;
}
