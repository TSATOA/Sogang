#include<stdio.h>
#include<stdlib.h>

int *get_next_process(int *prepo, int size);
int big(int *prepo,int size);

int main()
{
	int size,nextsize;
	int *prepo,*nextpo;
	int i,j,k;
	scanf("%d",&size);
	prepo=(int *)malloc(size*sizeof(int));
	for(i=0;i<size;i++){
		scanf("%d",&prepo[i]);
	}
	if(size%2!=1) j=size/2;
	else j=size/2+1;
	
	for(i=0;i<j;i++){
		nextpo=get_next_process(prepo,size);
		if(size%2==1){
			nextsize=size/2+1;
			size=nextsize;
		} else{
			nextsize=size/2;
			size=nextsize;
		}
		free(prepo);
		prepo=nextpo;
		for(k=0;k<size;k++)
			printf("%d ",prepo[k]);
		
		
		printf("\n");
		if(size==1) break;

	}


}

int big(int *prepo,int size){
	int a=-1;
	int i;
	for(i=0;i<size;i++){
		if(a<prepo[i]){
			a=prepo[i];
		}
	}
	for(i=0;i<size;i++){
		if(prepo[i]==a){
			prepo[i]=-1;
			break;
		}
	}
	return a;
}


int *get_next_process(int *prepo, int size){
	int next_size;
	int *next_pointer;
	if(size%2==1) next_size=size/2+1;
	else next_size=size/2;
	next_pointer=(int *)malloc(next_size*sizeof(int));
	int i;
	int a,b;
	for(i=0;i<size/2;i++){
		a=big(prepo,size);
		b=big(prepo,size);
		next_pointer[i]=a+b;
	}
	if(size%2==1){
		next_pointer[i]=big(prepo,size);
	}

	return next_pointer;
}
