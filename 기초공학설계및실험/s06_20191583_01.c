#include<stdio.h>

float calc_x(int,int,int,int);
float calc_y(int,int,float);

int main()
{
	int a, b, c, d;
	printf("1st equation: y = ax - b, input 'a' and 'b'\n");
	printf("a = ");
	scanf("%d", &a);
	printf("b = ");
	scanf("%d", &b);
	printf("2nd equation: y = cx - d, input 'c' and 'd'\n");
	printf("c = ");
	scanf("%d", &c);
	printf("d = ");
	scanf("%d", &d);
	printf("result:\n");
	printf("x is %f\n", calc_x(a,b,c,d));
	printf("y is %f\n", calc_y(a,b,calc_x(a,b,c,d)));
	return 0;
}

float calc_x(int a, int b, int c, int d){
	float x, y;
	x=(float)(b-d)/(float)(a-c);
	return x;
}

float calc_y(int a, int b, float calc_x){
	float y;
	y=(float)a*calc_x-(float)b;
	return y;
}

