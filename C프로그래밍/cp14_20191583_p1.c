#include<stdio.h>
#include<string.h>

void change(char *str1,char *str2);

int main()
{
	char k[10];
	char st[30],s[7];
	char str[100][100];
	char res[100][100];
	char name[100][30],sex[100][7];
	int score[100];
	int n;
	double sum=0;
	int i,j,x;
	fgets(k,sizeof(k),stdin);
	sscanf(k,"%d",&n);
	for(i=0;i<n;i++) fgets(str[i],sizeof(str),stdin);
	for(i=0;i<n;i++) sscanf(str[i],"%30[^/] %*c %s %*c %d %*c",name[i],sex[i],&score[i]);
	
	for(i=0;i<n;i++){
		for(j=0;j<n-1;j++){
			if(strcmp(name[j],name[j+1])>0){
				change(name[j],name[j+1]);
				change(sex[j],sex[j+1]);
				x=score[j];
				score[j]=score[j+1];
				score[j+1]=x;
			}
		}
	}
	printf("-----Student List-----\n");
	for(i=0;i<n;i++) sprintf(res[i],"2019%04d / %s / %s / %d\n", i+1, name[i], sex[i], score[i]);
	for(i=0;i<n;i++) printf("%s",res[i]);
	printf("---------------------\n");
	for(i=0;i<n;i++) sum+=score[i];
	printf("average=%f\n",sum/n);
	
	return 0;
}

void change(char *str1,char *str2){
	char ex[100];
	strcpy(ex,str1);
	strcpy(str1,str2);
	strcpy(str2,ex);
}	
