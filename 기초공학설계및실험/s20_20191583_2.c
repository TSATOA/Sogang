#include<stdio.h>

int main()
{
	FILE *ifp,*ofp;
	
	int i=0,k;
	char name[20];
	float ave[10000];
	float tave=0;
	float a,b;
	int x,y;

	ifp=fopen("student.txt","r");
	ofp=fopen("output33.txt","w");

	while(1){
		
		x=fscanf(ifp,"%s %f %f", name,&a,&b);
		if(x==EOF) break;
		ave[i]=(a+b)/2;
		i++;
	}
	k=i;
	for(i=0;i<k;i++){
		tave+=ave[i];
	}
	tave=tave/k;
	i=0;
	fclose(ifp);
	ifp=fopen("student.txt","r");
	fprintf(ofp,"student		average	grade\n");
	while(1){
		x=fscanf(ifp,"%s %f %f", name,&a,&b);
		if(x==EOF) break;
		if(ave[i]>=tave){
			fprintf(ofp,"%s		%.2f	p\n", name,ave[i]);
		} else{
			fprintf(ofp,"%s		%.2f 	f\n", name,ave[i]);
		}
		i++;
	}
	fprintf(ofp,"total avg : %.2f\n",tave);

	fclose(ifp);
	fclose(ofp);
}
