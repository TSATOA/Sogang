#include<stdio.h>

void mat_mul(int left[100][100],int right[100][100], int result[100][100],int n);

int main()
{
	int left[100][100],right[100][100],result[100][100]={0,},n;
	int i,j;
	printf("<Input number>\n");
	scanf("%d",&n);
	printf("<Left>\n");
	for(i=0;i<n;i++){
		for(j=0;j<n;j++){
			scanf("%d",(*(left+i)+j));
		}
	}
	printf("<right>\n");
	for(i=0;i<n;i++){
		for(j=0;j<n;j++){
			scanf("%d",(*(right+i)+j));
		}
	}
	printf("<result>\n");
	mat_mul(left,right,result,n);
	return 0;
}

void mat_mul(int left[100][100],int right[100][100],int result[100][100],int n){
	int i,j,k;
	for(i=0;i<n;i++){
		for(j=0;j<n;j++){
			for(k=0;k<n;k++){
				*(*(result+i)+j)+=*(*(left+i)+k)**(*(right+k)+j);
			}
		}
	}

	for(i=0;i<n;i++){
		for(j=0;j<n;j++){
			printf("%d ",*(*(result+i)+j));
		}
		printf("\n");
	}
}
