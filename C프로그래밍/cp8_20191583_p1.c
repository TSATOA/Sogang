#include<stdio.h>
#include<stdlib.h>

char* triple_concatenate(char* str1,char* str2,char* str3,int a,int b, int c);

int main()
{
	char *str1,*str2,*str3,*str4;
	int a,b,c;
	int i;
	printf("Input size of str1: ");
	scanf("%d",&a);
	printf("Input str1: ");
	str1=(char *)malloc(a*sizeof(char));
	getchar();
	for(i=0;i<a;i++){
		scanf("%c",&str1[i]);
	}
	printf("Input size of sir2: ");
	scanf("%d",&b);
	printf("Input str2: ");
	str2=(char *)malloc(b*sizeof(char));
	getchar();
	for(i=0;i<b;i++){
		scanf("%c",&str2[i]);
	}
	printf("Input size of str3: ");
	scanf("%d",&c);
	printf("Input str3: ");
	str3=(char *)malloc(c*sizeof(char));
	getchar();
	for(i=0;i<c;i++){
		scanf("%c",&str3[i]);
	}
	printf("\n\nResult: ");
	str4=triple_concatenate(str1,str2,str3,a,b,c);
	printf("%s",str4);

}

char* triple_concatenate(char* str1,char* str2,char* str3,int a, int b, int c){
	int i,j,k,z=0;
	char *str4;
	str4=(char *)malloc((a+b+c)*sizeof(char));
	for(i=0;i<a-1;i++){
		str4[i]=str1[z];
		z++;
	}
	z=0;
	str4[i]=' ';
	i++;
	for(j=i;j<a+b-1;j++){
		str4[j]=str2[z];
		z++;
	}
	z=0;
	str4[j]=' ';
	j++;
	for(k=j;k<a+b+c;k++){
		str4[k]=str3[z];
		z++;
	}
	str4[k]='\0';
	return str4;
}
