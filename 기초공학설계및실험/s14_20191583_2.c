#include<stdio.h>

void dec2oct(int *a,int *b,int *c,int *d,int n);
void dec2hex(char *e,char *f,char *g,int n);
char digi2hex(int n);

int main()
{
	int n;
	int a,b,c,d;
	char e,f,g;
	scanf("%4d", &n);
	printf("%04o\n",n);
	dec2oct(&a,&b,&c,&d,n);
	printf("%d%d%d%d\n", a,b,c,d);
	printf("%03X\n", n);
	dec2hex(&e,&f,&g,n);
	printf("%c%c%c\n", e,f,g);
	return 0;

}

void dec2oct(int *a,int *b,int *c,int *d,int n){
	*a=n/(8*8*8);
	*b=(n-(*a*8*8*8))/(8*8);
	*c=(n-(*a*8*8*8)-(*b*8*8))/8;
	*d=n%8;
	
}

void dec2hex(char *e, char *f, char *g, int n){
	int x;
	*e=digi2hex(n/(16*16));
	x=n/(16*16);
	x=(n-(x*16*16))/16;
	*f=digi2hex(x);
	*g=digi2hex(n%16);
	
}


char digi2hex(int n){
	char z='A';
	if(n>=10){
		n=n-10;
		for(int i=0; i<n; i++)
			z++;
	} else {
		z= n + '0';
	}
	return z;	
}
