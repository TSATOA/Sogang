#include<stdio.h>

int main()
{
	int h,w,n,num=1;
	int a[10][100];
	int i,j;
	printf("Input H W N : ");
	scanf("%d%d%d",&h,&w,&n);
	for(i=1;i<=h;i++){
		for(j=1;j<=w;j++){
			*(*(a+i)+j)=i*100+j;
		}
	}
	i=0;
	j=1;
	while(num<=n){
		i++;
		if(i>h){
			i=1;
			j++;
		}
		num++;
	}
	printf("%d\n",*(*(a+i)+j));
	return 0;
}
