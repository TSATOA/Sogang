#include<stdio.h>

int is_prime(int ***a);

int main()
{
	int a;
	int *pa;
	int**ppa;
	printf("Input number: ");
	scanf("%d",&a);
	pa=&a;
	ppa=&pa;
	a=is_prime(&ppa);
	if(a==1) printf("IS prime\n");
	else printf("IS composition\n");
}

int is_prime(int ***a){
	int i;
	int cnt=0;
	for(i=1;i<***a;i++){
		if(***a%i==0) cnt++;
	}
	if(***a==1) return 0;
	if(cnt==1) return 1;
	else return 0;
	
}
