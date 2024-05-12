#include<stdio.h>

int main()
{
	int n,i=1,j;
	printf("Input: ");
	scanf("%d", &n);

	while(i<=n){
		j=n-i;
		while(j>0){
			printf(" ");
			j--;
		}
		j=0;
		while(j<i*2-1){
			printf("*");
			j++;
		}
		printf("\n");
		i++;
	}

	return 0;

}
