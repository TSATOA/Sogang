#include<stdio.h>
#include<string.h>
#include<stdlib.h>

char *my_strncpy(char *a,char *b,int n);
void initialization(char *a,int n);

int main()
{
	char str[20];
	char *str1;
	int d,i=0;
	printf("input str : ");
	scanf("%[^\n]s",str);
	d=strlen(str);
	str1=(char *)malloc(sizeof(char)*d);
	for(i=0;i<d;i++) str1[i]=str[i];
	for(i=0;i<d+1;i++){
		initialization(str,d);
		my_strncpy(str,str1,i);
		printf("%s\n",str);
	}
}

void initialization(char *a,int n){
	int i;
	for(i=0;i<n;i++) a[i]='*';
}

char *my_strncpy(char *a,char *b,int n){
	int i;
	for(i=0;i<n;i++) a[i]=b[i];
}


