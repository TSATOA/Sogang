#include<stdio.h>
#include<string.h>

void split_string(char *str,char *string_1,char *string_2);

int main()
{
	char str[50],string_1[50],string_2[50];
	printf("Input str : ");
	scanf("%s",str);
	split_string(str,string_1,string_2);
	printf("[%s] > [%s] [%s]\n",str,string_1,string_2);
	return 0;
}

void split_string(char *str,char *string_1,char *string_2){
	int d,i;
	d=strlen(str);
	for(i=0;i<d/2;i++){
		string_1[i]=str[i];
		string_2[i]=str[i+d/2];
	}
	string_1[d/2]='\0';
	string_2[d/2]='\0';
}
