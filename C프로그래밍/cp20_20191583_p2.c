#include<stdio.h>
#include<stdlib.h>
#include<string.h>

union number{
	int i;
	float f;
	double d;
};

typedef struct{
	int type;
	char name[20];
	union number num;
}doub;

void power(doub *dou);
int main()
{
	doub *dou;
	int n,i;
	printf("Number of Iterations : ");
	scanf("%d",&n);
	dou=(doub*)malloc(sizeof(doub)*n);
	for(i=0;i<n;i++){
		printf("Type [1 for int, 2 for float, 3 for double ] : ");
		scanf("%d",&dou[i].type);
		if(dou[i].type==1){
			printf("Enter an integer value : ");
			scanf("%d",&dou[i].num.i);
			strcpy(dou[i].name,"integer");
			power(&dou[i]);
		} else if(dou[i].type==2){
			printf("Enter an float value : ");
			scanf("%f",&dou[i].num.f);
			strcpy(dou[i].name,"float");
			power(&dou[i]);
		} else{
			printf("Enter an double value : ");
			scanf("%lf",&dou[i].num.d);
			strcpy(dou[i].name,"double");
			power(&dou[i]);
		}
	}
	printf("--------Result--------\n");
	for(i=0;i<n;i++){
		if(dou[i].type==1){
			printf("%s	: %d\n",dou[i].name,dou[i].num.i);
		} else if(dou[i].type==2){
			printf("%s	: %.4f\n",dou[i].name,dou[i].num.f);
		} else{
			printf("%s	: %.4lf\n",dou[i].name,dou[i].num.d);
		}
	}
}

void power(doub *dou){
	if((*dou).type==1){
		(*dou).num.i=(*dou).num.i*(*dou).num.i;
	} else if((*dou).type==2){
		(*dou).num.f=(*dou).num.f*(*dou).num.f;
	} else{
		(*dou).num.d=(*dou).num.d*(*dou).num.d;
	}
}
