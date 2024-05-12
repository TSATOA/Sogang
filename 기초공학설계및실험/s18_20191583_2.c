#include<stdio.h>

float func(int a[101][101], int k, int n);

int main(){
	int i,j,n,k,a[101][101];
	scanf("%d", &n);
	for(i=0;i<n;i++){
		for(j=0;j<n;j++){
			scanf("%d", &a[i][j]);
		}
	}
	for(k=0;k<n;k++){
		printf("%.2f ", func(a,k,n));
	}
	printf("\n");
	return 0;



}

float func(int a[101][101], int k, int n){
	int i,sum=0;
	int res;
	for(i=0;i<n;i++){
		sum+=a[i][k];
	}
	res=(float)sum/n;
	return res;
}
