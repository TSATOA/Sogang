#include<stdio.h>

int fib(int n);

int main()
{
	int n;
	scanf("%d", &n);
	printf("%d\n", fib(n));
}

int fib(int n){
	int i,a=1,b=1,c,res;
	if(n<3){
		c=1;
	}else{
		for(i=0; i<n-2; i++){
			c=a+b;
			a=b;
			b=c;
		}
	}
	return c;
}
