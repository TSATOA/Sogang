#include<stdio.h>

void swap(int *a, int *b);
int mul(int a,int b);

int main()
{
	int a,b;
	printf("Input first number: ");
	scanf("%d",&a);
	printf("Input second number: ");
	scanf("%d",&b);
	swap(&a,&b);
	if(a<1){
		printf("Input is less than 1\n");
	}else{
		printf("Result: %d\n", mul(a,b));
	}
	return 0;
}

void swap(int *a, int *b){
	int k;
	if(*a>*b){
		k=*b;
		*b=*a;
		*a=k;
	}
}

int mul(int a, int b){
	int i;
	int sum=0;
	for(i=a; i<=b; i++){
		if(i%2==0||i%3==0)
			sum+=i;
	}
	return sum;
}



