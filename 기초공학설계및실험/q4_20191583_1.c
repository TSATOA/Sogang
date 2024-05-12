#include<stdio.h>

int main()
{
	int h,w,n,a,b;
	int res=0;
	scanf("%d%d%d", &h, &w, &n);
	a=n/h;
	if(n%h!=0){
	res=a+1;
	b=n-a*h;
	res=res+b*100;
	} else {
		res=a+h*100;
		
	}
	printf("%d\n",res);
}
