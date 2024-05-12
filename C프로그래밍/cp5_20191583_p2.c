#include<stdio.h>

void swap(int *a,int *b);
void sort(int *a,int n);
void print_array(int *a,int n);

int main()
{
	int arr[1001],n,i;
	printf("Length of array : ");
	scanf("%d",&n);
	printf("\n");
	printf("Before : ");
	for(i=0;i<n;i++) scanf("%d",&arr[i]);
	printf("\n");
	sort(arr,n);
	print_array(arr,n);
	return 0;

}

void swap(int *a,int *b){
	int k;
	k=*a;
	*a=*b;
	*b=k;
}

void sort(int *a,int n){
	int i,j;
	for(i=0;i<n;i++){
		for(j=0;j<n-1;j++){
			if(*(a+j)>*(a+j+1)){
				swap(a+j,(a+j+1));
			}
		}
	}
}

void print_array(int *a,int n){
	int i;
	printf("AfterSort: ");
	for(i=0;i<n;i++){
		printf("%d ",*(a+i));
	}
	printf("\n");
}
