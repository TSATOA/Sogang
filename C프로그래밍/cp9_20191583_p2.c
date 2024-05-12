#include<stdio.h>
#include<stdlib.h>

void double_double(int **a,int *size);

int main()
{
	int* a;
	int n,i;
	scanf("%d",&n);
	a=(int*)calloc(n,sizeof(int)*n);
	for(i=0;i<n;i++) scanf("%d",&a[i]);
	double_double(&a,&n);
	for(i=0;i<n*2;i++) printf("%d ",a[i]);
	printf("\n");
	free(a);
}

void double_double(int **a,int *size){
	int j=0,i,k;
	*a=(int*)realloc(*a,*size*2*sizeof(int));
	for(i=*size;i<*size*2;i++){
		a[0][i]=a[0][j]*2;
		j++;
	}
	for(i=0;i<*size*2;i++){
		for(j=0;j<*size*2-1;j++){
			if(a[0][j]>a[0][j+1]){
				k=a[0][j];
				a[0][j]=a[0][j+1];
				a[0][j+1]=k;
			}
		}
	}
}
