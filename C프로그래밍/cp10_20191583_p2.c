#include<stdio.h>
#include<stdlib.h>

int main()
{
	int n,m,i,j,**arr;
	scanf("%d%d",&n,&m);
	arr=(int**)malloc(sizeof(int*)*n);
	for(i=0;i<n;i++)
		arr[i]=(int*)malloc(sizeof(int)*m);
	for(i=0;i<n;i++)
		for(j=0;j<m;j++)
			scanf("%d",&arr[i][j]);
	j=0;
	for(i=0;i<n-1;i++){
		while(1){
			if(arr[i][j]==0&&arr[i+1][j]==0) break;
			j++;
			if(j==m) break;
		}
		if(j==m) break;
	}
	free(arr);
	printf("%d\n",j+1);
}
