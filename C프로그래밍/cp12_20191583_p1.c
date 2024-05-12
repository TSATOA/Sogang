#include<stdio.h>

int main()
{
	char str[1000];
	char a[1000];
	int i=0,cnt=0,j=0,k=0;
	printf("Input : ");
	fgets(str,sizeof(str),stdin);
	while(str[i]!='\n'){
		if(str[i]!=' '){
			a[j]=str[i];
			j++;
		}
		i++;
	}
	
	i=0;
	while(str[i]!='\n'){
		while(str[i]!=a[k]) i++;
		while(str[i]==a[k]){
			i++;
			k++;
		}
		cnt++;
		if(k==j) break;
		

	}
	printf("%d\n",cnt);

}
