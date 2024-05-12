#include<stdio.h>

int main()
{
	char str[20];
	char a[20];
	char c;
	int i=0,j=0;
	scanf("%16s",str);
	while(str[i]!='\0'){
		if(str[i]>='0'&&str[i]<='9'){
			a[j]=str[i];
			j++;
		}
		i++;
	}
	if(j/4==1) c='K';
	if(j/7==1) c='M';
	if(j/11==1) c='G';
	if(i!=j) printf("%s\n",str);
	else {
		if(c=='K') {
			for(i=0;i<j-3;i++) printf("%c",a[i]);
			printf("%c\n",c);
		}
		if(c=='M'){
			for(i=0;i<j-6;i++) printf("%c",a[i]);
			printf("%c\n",c);
		}
		if(c=='G'){
			for(i=0;i<j-9;i++) printf("%c",a[i]);
			printf("%c\n",c);
		}
	}
	return 0;
}
