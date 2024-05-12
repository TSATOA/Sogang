#include<stdio.h>

void swap(int *a,int*b);

int main()
{
	int a[10];
	int i,max,min;
	printf("Input (10 numbers): ");
	for(i=0; i<10; i++){
		scanf("%d", &a[i]);
	}
	for(i=0;i<5;i++){
		swap(&a[i],&a[9-i]);
	}
	for(i=0;i<10;i++){
		printf("%d ",a[i]);
	}
	printf("\n");
	max=a[0];
	min=a[0];

	for(i=0;i<9;i++){
		if(max<a[i+1]){
			max=a[i+1];
		}
		if(min>a[i+1]){
			min=a[i+1];
		}

	}

	printf("Max: %d, Min: %d\n",max,min);

	return 0;
	


}

void swap(int *a, int *b){
	int k;
	k=*b;
	*b=*a;
	*a=k;
}



