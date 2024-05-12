#include<stdio.h>

void swap(int *a,int *b);
void sort(int *a,int m);
void all_sort(int a[][101],int n, int m);
int binary_search(int *a,int* endPtr,int key,int **findPtr);
int all_binary_search(int a[][101],int n,int m,int key,int **findPtr);

int main(){
	int n,m,k,i,j,z;
	int *endPtr;
	int *findPtr=NULL;
	int a[101][101];
	
	scanf("%d%d%d",&n,&m,&k);
	endPtr=*a+m;
	for(i=1;i<=n;i++){
		for(j=1;j<=m;j++){
			scanf("%d",&a[i][j]);
		}
	}

	all_sort(a,n,m);
	z=all_binary_search(a,n,m,k,&findPtr);
	if(z==1)printf("%p",&findPtr);
	return 0;
}

void swap(int *a,int *b){
	int k;
	k=*a;
	*a=*b;
	*b=k;
}

void sort(int *a,int m){
	int i,j;
	for(i=1;i<=m;i++){
		for(j=1;j<=m-1;j++){
			if(*(a+j)>*(a+j+1)){
				swap(a+j,a+j+1);
			}
		}
	}
}

void all_sort(int a[][101],int n,int m){
	int i;
	for(i=1;i<=n;i++){
		sort(a[i],m);	
	}
}

int binary_search(int *a,int* endPtr,int key,int **findPtr){
	int* firstPtr;
	int* midPtr;
	int* lastPtr;

	firstPtr=a;
	lastPtr=endPtr;
	
	while(firstPtr<=lastPtr){
		midPtr=firstPtr+(lastPtr-firstPtr)/2;
		if(key>*midPtr)
			firstPtr=midPtr+1;
		else if (key<*midPtr)
			lastPtr=lastPtr-1;
		else{
			findPtr=&midPtr;
			return 1;
		}
	}
	return 0;
}

int all_binary_search(int a[][101],int n, int m, int key, int **findPtr){
	int i;
	for(i=1;i<=n;i++){
		if(binary_search(&a[i][1],&a[i][m],key,findPtr)){
			printf("1\n");
		
			return 1;
		}
	}
	printf("0");
	return 0;
}



