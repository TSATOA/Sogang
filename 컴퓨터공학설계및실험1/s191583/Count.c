#include "Header.h"

void count(int order, int N, int **a){
	int i,j,k;
	for(i=1;i<=N;i++){
		k=i;
		while(k!=0)
		{
			a[order][k%10]++;
			k/=10;
		}
	}
}
