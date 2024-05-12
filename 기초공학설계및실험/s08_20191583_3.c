#include<stdio.h>

int x=1;
void fib(int *y);

int main()
{
	int x=0;
	printf("Fibo(2): ");
	fib(&x);
	printf("Fibo(3): ");
	fib(&x);
	printf("Fibo(4): ");
        fib(&x);
	printf("Fibo(5): ");
        fib(&x);
	printf("Fibo(6): ");
        fib(&x);
	printf("Fibo(7): ");
        fib(&x);
	printf("Fibo(8): ");
        fib(&x);
	printf("Fibo(9): ");
        fib(&x);
	return 0;
}

void fib(int*y){
	x=x+*y;
	*y=x-*y;
	printf("%d\n", x);
	return ;
}
