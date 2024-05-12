#include<stdio.h>

void selsort(int data_array[][8],int n);

int main()
{
	int i,j,n;
	int data_array[4][8]={{838,758,113,515,51,627,10,419},
		{212,86,749,767,84,60,225,543},
		{89,183,137,566,966,978,495,311},
		{367,54,31,145,882,736,524,505}
	};
	printf("Before sortiong\n");
	for(i=0;i<4;i++){
		for(j=0;j<8;j++){
			printf("%3d ",data_array[i][j]);
		}
		printf("\n");
	}

	printf("\n\nEnter the row index <0~3> : ");
	scanf("%d",&n);
	selsort(data_array,n);
	printf("\n\nAfter sorting\n");
	for(i=0;i<4;i++){
		for(j=0;j<8;j++){
			printf("%3d ",data_array[i][j]);
		}
		printf("\n");
	}
}

void selsort(int data_array[][8],int n){
	int i,j,k;
	for(i=0;i<8;i++){
		for(j=0;j<7;j++){
			if(data_array[n][j]>data_array[n][j+1]){
				k=data_array[n][j];
				data_array[n][j]=data_array[n][j+1];
				data_array[n][j+1]=k;
			}
		}
	}

}
