#include<stdio.h>

void change(char a[10000]);

int main()
{
	char a[10000];
	int i,k;
	for(i=0; ;i++){
		k=i;
		scanf("%c",&a[i]);
		if(a[i]=='\n'){
			break;
		}
	}
	change(a);
	if(k<50){
		for(i=0;i<k;i++){
			printf("%c",a[i]);
		}
	} else{
		for(i=0;i<50;i++){
			printf("%c",a[i]);
		}
	}
	printf("\n");
}

void change(char a[10000]){
	int i;
	for(i=0;i<50;i++){
		if(a[i]!=' '&&a[i]>=97)
			a[i]=a[i]-32;
	}
	return ;
}

