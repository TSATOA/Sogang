#include<stdio.h>
int main()
{
	FILE *ifp,*ofp;

	int a,b;
	float c;
	float z;
	int x,y;
	char k;

	ifp=fopen("input32.txt","r");
	ofp=fopen("output32.txt","w");

	while(1){
		x=fscanf(ifp,"%d %c %d = %f", &a,&k,&b,&c);
		if(x==EOF) break;
		
		if(k=='+') z=a+b;
		if(k=='-') z=a-b;
		if(k=='*') z=a*b;
		if(k=='/') z=(float)a/b;
		if(k=='%') z=a%b;
		if(z==c){
			fprintf(ofp,"%.2f %c %.2f = %.2f correct\n",(float)a,k,(float)b,c);
		} else{
			fprintf(ofp,"%.2f %c %.2f = %.2f incorrect\n",(float)a,k,(float)b,c);
		}
			
	}
	
	fclose(ifp);
	fclose(ofp);
}
