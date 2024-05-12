#include<stdio.h>

const float e=2.7182818;
float approx_exfunc(float x);
int giveme_factorial(int n);

int main()
{
	float x;
	scanf("%f", &x);
	printf("%f\n", approx_exfunc(x));
	return 0;
	
}

float approx_exfunc(float x){
	int i,j;
	float a;
	float res=1;
	a=x;
	for(i=1; i<10000; i++){

		for(j=0;j<i-1;j++){
			x=x*x;
		}

		res=res+x/(float)giveme_factorial(i);
		if(x*a/giveme_factorial(i+1)<0.0000001){
			break;
		}
	}
	return res;

}

int giveme_factorial(int n){
	int i, res=1;
	for(i=1; i<=n; i++){
		res=res*i;
	}
	return res;
}
