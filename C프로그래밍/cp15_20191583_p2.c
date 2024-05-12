#include<stdio.h>

struct money{
	int w;
	int x;
	int y;
	int z;
};

int main(){
	int n;
	struct money a;
	printf("Change: ");
	scanf("%d",&n);
	a.w=0;
	a.x=0;
	a.y=0;
	a.z=0;
	while(n>0){
		while(n>=500) {
			n-=500;
			a.w++;
		}
		while(n>=100) {
			n-=100;
			a.x++;
		}
		while(n>=50) {
			n-=50;
			a.y++;
		}
		while(n>0){
			n-=10;
			a.z++;
		}
	}
	printf("500 : %d\n100 : %d\n50 : %d\n10 : %d\n",a.w,a.x,a.y,a.z);
}

