#include<stdio.h>

void swap(float * x,float * y);

int main()
{
	float x,y;
	printf("Input two Number\n");
	printf("	x : ");
	scanf("%f", &x);
	printf("	y : ");
	scanf("%f", &y);
	printf("----------------------------------------\n");
	printf("Before : x [%f] y [%f]\n",x,y);
	printf("----------------------------------------\n");
	swap(&x,&y);
	printf("After  : x [%f] y [%f]\n",x,y);

	return 0;
}

void swap(float * x, float * y){
	float a;
	a=*x;
	*x=*y;
	*y=a;
	return;
}
