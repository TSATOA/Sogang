#include "Header.h"

int main()
{
	//변수 선언 T:테스트케이스 개수, N[i]:i번째 페이지 수, arr[i][j]:i번째 페이지일 때 j숫자의 개수(0<=j;j<=9)
	int i,j,T;
	int *N;
	int **arr;

	scanf("%d",&T);//T입력
	
	//T만큼의 페이지수 공간 생성 및 입력
	N = (int *)malloc(sizeof(int)*T);
	for(i=0;i<T;i++) scanf("%d",&N[i]);

	//T만큼의 숫자0~9 공간 생성
	arr = (int**)malloc(sizeof(int)*T);
	for(i=0;i<T;i++) arr[i]=(int*)malloc(sizeof(int)*10);
	
	for(i=0;i<T;i++){
		for(j=0;j<10;j++){
			arr[i][j]=0;
		}
	}


	//T번만큼 페이지의 숫자개수세기
	for(i=0;i<T;i++) count(i,N[i],arr);
	//출력
	print(T,arr);
	

	//동적할당 초기화
	for(i=0;i<T;i++) free(arr[i]);
	free(arr);
	free(N);
}
