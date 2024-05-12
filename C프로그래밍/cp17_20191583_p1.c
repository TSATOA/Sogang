#include<stdio.h>
#include<stdlib.h>

typedef struct{
	int numer;
	int denom;
}fraction;

void multfr(fraction* pfrl,fraction* pfr2,fraction* pres);

int main()
{
	fraction *pfr1;
	fraction *pfr2;
	fraction *pres;
	pfr1=(fraction*)malloc(sizeof(fraction));
	pfr2=(fraction*)malloc(sizeof(fraction));
	pres=(fraction*)malloc(sizeof(fraction));
	printf("x/y : ");
	scanf("%d/%d",&(*pfr1).numer,&(*pfr1).denom);
	printf("x/y : ");
	scanf("%d/%d",&(*pfr2).numer,&(*pfr2).denom);
	printf("\n");
	printf("%d/%d * %d/%d = ",(*pfr1).numer,(*pfr1).denom,(*pfr2).numer,(*pfr2).denom);
	multfr(pfr1,pfr2,pres);
	printf("%d/%d\n",(*pres).numer,(*pres).denom);
}

void multfr(fraction* pfr1,fraction* pfr2,fraction* pres){
	int k;
	int i;
	(*pres).numer=(*pfr1).numer*(*pfr2).numer;
	(*pres).denom=(*pfr1).denom*(*pfr2).denom;
	if((*pres).numer>(*pres).denom) k=(*pres).denom;
	else k=(*pres).numer;
	for(i=2;i<=k;i++){
		if((*pres).numer%i==0&&(*pres).denom%i==0){
			(*pres).numer=(*pres).numer/i;
			(*pres).denom=(*pres).denom/i;
		}
	}
}
