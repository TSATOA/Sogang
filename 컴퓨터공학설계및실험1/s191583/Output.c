#include "Header.h"

void print(int T,int **a){
	int i,j;
	for(i=0;i<T;i++){
		for(j=0;j<10;j++){
			printf("%d ", a[i][j]);
		}
		printf("\n");
	}
}
