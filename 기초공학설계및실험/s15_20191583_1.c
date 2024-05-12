#include<stdio.h>

int main()
{
	int n,i,x,a,b=0,sum=0;
	float avg;
	printf("Number of class: ");
	scanf("%d", &n);
	printf("Cutline: ");
	scanf("%d", &x);
	for(i=0; i<n; i++){
		printf("Input score #%d: ",i);
		scanf("%d", &a);
		sum=sum+a;
		if(a<x)
			b++;
	}
	avg=(float)sum/n;
	printf("Average socre: %.2f\n", avg);
	printf("Number of failures: %d\n",b);
	return 0;
}
