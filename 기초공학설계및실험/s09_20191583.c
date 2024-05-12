#include<stdio.h>
#include<stdlib.h>

void area(int *x1,int *y1,int *x2,int *y2,int *x3,int *y3, float *result);

int main()
{
	int x1,x2,x3,y1,y2,y3;
	float result;
	scanf("%d%d%d%d%d%d", &x1, &y1, &x2, &y2, &x3, &y3);
	area(&x1,&y1,&x2,&y2,&x3,&y3,&result);
	printf("%.2f\n", result);
	return 0;
}

void area(int *x1,int *y1,int *x2,int *y2,int *x3,int *y3,float *result){
	*result=0.5*(float)abs((*x1)*(*y2)+(*x2)*(*y3)+(*x3)*(*y1)-(*x2)*(*y1)-(*x3)*(*y2)-(*x1)*(*y3));
	return ;
}
