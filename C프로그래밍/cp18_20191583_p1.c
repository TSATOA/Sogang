#include<stdio.h>
#include<stdlib.h>

enum Sex{Male,Female};

typedef struct{
	float mid;
	float fin;
	float pro;
}points;

typedef struct{
	int studentid;
	char name[40];
	enum Sex sex;
	points subject;
	char grade[3];
}student;


int main()
{
	student *std;
	student asdf;
	char x[10];
	int n,i,j;
	float *res;
	float k;

	scanf("%d",&n);	
	std=(student*)malloc(sizeof(student)*n);
	for(i=0;i<n;i++){
		scanf("%d %*c %40[^/] %*c %s %*c %f %*c %f %*c %f",&std[i].studentid,std[i].name,x,&std[i].subject.mid,&std[i].subject.fin,&std[i].subject.pro);
		if(x[0]=='F') std[i].sex=1;
		else std[i].sex=0;
	}
	res=(float*)malloc(sizeof(float)*n);
	for(i=0;i<n;i++) res[i]=std[i].subject.mid*0.3+std[i].subject.fin*0.3+std[i].subject.pro*0.4;
	for(i=0;i<n;i++){
		for(j=0;j<n-1;j++){
			if(res[j]<res[j+1]){
				k=res[j];
				res[j]=res[j+1];
				res[j+1]=k;
				asdf=std[j];
				std[j]=std[j+1];
				std[j+1]=asdf;
			}
		}
	}
	printf("--Studnet List--\n");
	for(i=0;i<n;i++){
		printf("id : %d\n",std[i].studentid);
		printf("Name : %s",std[i].name);
		if(std[i].sex==0) printf("(Male)\n");
		else printf("(Female)\n");
		printf("Grade(mid) : %.2f\n",std[i].subject.mid);
		printf("Grade(final) : %.2f\n",std[i].subject.fin);
		printf("Grade(project) : %.2f\n",std[i].subject.pro);
		if(res[i]<50) {
			printf("Grade : F(%.2f %d)\n\n",res[i],i);
		}else{
			if(i<(float)n*0.3) printf("Grade : A+(%.2f %d)\n\n",res[i],i);
			else if(i>(float)n*0.3&&i<(float)n*0.7) printf("Grade : B+(%.2f %d)\n\n",res[i],i);
			else printf("Grade : C+(%.2f %d)\n\n",res[i],i);
		}
	}
}

