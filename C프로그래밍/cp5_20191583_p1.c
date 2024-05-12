#include<stdio.h>

void delete_char(char*,char);

int main()
{
	char Arr[10]={'G','O','O','D','M','O','R','I','N','G'};
	char *p=Arr;
	char c;
	int i;
	scanf("%c",&c);
	for(i=0;i<10;i++){
		printf("%c ",*(p+i));
	}
	printf("\n");

	delete_char(p,c);
	for(i=0;i<10;i++) {
		if(*(p+i)!='\0');
		printf("%c ",*(p+i));
	}
	printf("\n");
	return 0;
}

void delete_char(char *p,char c){
	int i,j=0,cnt=0;
	char a[10];
	for(i=0;i<10;i++){
		if(*(p+i)==c){
			*(p+i)='\0';
			cnt++;
		}
	}
	for(i=0;i<10;i++){
		if(*(p+i)!='\0'){
			a[j]=*(p+i);
			j++;
		}
	}
	for(i=j;i<10;i++){
		a[i]='\0';
	}
	for(i=0;i<10;i++){
		*(p+i)=a[i];
	}
}
