#include<stdio.h>
int main()
{
	FILE *ifp, *ofp, *sfp;
	char name1[20],name2[20];
	char a,b,a1,b1,n;
	int i,cnt=0,scnt=0;
	float per;
	
	printf("Input first file name: ");
	scanf("%s", name1);
	printf("Input second file name: ");
	scanf("%s", name2);

	ifp=fopen(name1,"r");
	ofp=fopen(name2,"r");
	sfp=fopen("output", "w");	
	
	
	while(1){
		while(1){
			a=fscanf(ifp,"%c",&a1);
			if(a1!=' '&&a1!='\n'&&a1!='\t') break;
			if(a==EOF) break;
		}
	
		while(1){
			b=fscanf(ofp,"%c",&b1);
			if(b==EOF) break;
			if(b1!=' '&&b1!='\n'&&b1!='\t') break;
		}
		if(a1==EOF||b==EOF) break;
		cnt++;
		if(a1==b1) scnt++;
	
	}

	per=(float)scnt/cnt*100;

	fclose(ifp);
	fclose(ofp);

	fprintf(sfp,"Total character: %d\n", cnt);
	fprintf(sfp,"Same character: %d\n", scnt);
	fprintf(sfp,"%.3f%%\n",per);
}
