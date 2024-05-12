#include<stdio.h>

double fun(char a[12]);

int main()
{
	char a[12];
	int i=0;
	while(1){
		scanf("%c", &a[i]);
		if(a[i]=='\n'){
			break;
		}
		i++;
	}

	printf("Result: %lf\n", fun(a));
	return 0;
}

double fun(char a[12]){
	double b,res=0;
	int i,j,x=0,y=0,z=0;
	for(i=0; ; i++){
		if(a[i]=='\n'){
			x=i-1;
			break;
		}
	}

	for(i=0;i<=x;i++){
		if(a[i]=='.'){
			y=i;
		}
	}
	if(y!=0){
	if(a[0]=='-'){
		for(i=1;i<y;i++){
			z=(a[y-i]-'0');
			for(j=0;j<i-1;j++){
				z=z*10;
			}
			res+=z;
		}
		for(i=y+1;i<=x;i++){
			b=(a[i]-'0');
			for(j=0;j<i-y;j++){
				b=b*0.1;
			}
			res+=b;
		}
		res=-res;
	} else {
		for(i=0;i<y;i++){
			z=(a[y-i-1]-'0');
			for(j=0;j<i;j++){
				z=z*10;
			}
			res+=z;
		}
		for(i=y+1;i<=x;i++){
			b=(a[i]-'0');
			for(j=0;j<i-y;j++){
				b=b*0.1;
			}
			res+=b;
		}
	}
	}else{
		for(i=0;i<=x;i++){
			z=a[x-i]-'0';
			for(j=0;j<i;j++){
				z=z*10;
			}
			res+=z;
		}
	}
	return res;
}
	



