#include<stdio.h>

void f(void *h,void*m,void*s,int t);

int main()
{
	int h,m,s,t;
	void *ph,*pm,*ps;
	scanf("%d%d%d%d",&h,&m,&s,&t);
	ph=&h;
	pm=&m;
	ps=&s;
	f(ph,pm,ps,t);
	printf("%02d:%02d:%02d\n",h,m,s);
	return 0;
}

void f(void *h,void*m,void*s,int t){
	int a,b,c,res;
	a=*(int*)h;
	b=*(int*)m;
	c=*(int*)s;
	res=c+b*60+a*3600+t;
	a=res/3600;
	res=res-a*3600;
	b=res/60;
	c=res%60;
	if(a==24) a=0;
	*(int*)h=a;
	*(int*)m=b;
	*(int*)s=c;
}
