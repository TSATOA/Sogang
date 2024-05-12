#include<stdio.h>
#include<stdlib.h>

int main()
{
	int n,m,i,j,sum=0;
	int x1,x2,y1,y2;
	int **arr;
	scanf("%d%d",&n,&m);
	arr=(int**)malloc(sizeof(int*)*n);
	for(i=0;i<n;i++)
		arr[i]=(int*)malloc(sizeof(int)*m);
	for(i=0;i<n;i++){
		for(j=0;j<m;j++){
			scanf("%d",&arr[i][j]);
		}
	}
	scanf("%d%d%d%d",&y1,&x1,&y2,&x2);

	for(i=y1-1;i<=y2-1;i++){
		for(j=x1-1;j<=x2-1;j++){
			sum+=arr[i][j];	
		
		}
	}
	free(arr);
	printf("%d\n",sum);
}


