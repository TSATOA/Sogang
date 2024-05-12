#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct{
	char dept_name[25];
	int dept_no;
}dept;

enum Gender {male=0,female};

typedef struct{
	int employee_id;
	char name[25];
	enum Gender gender;
	dept department;
	double salary;
}employee_data;

int search(employee_data *e,int num,int keyword);
void update(employee_data *e,int n);

int main()
{
	int n,i,id,res,no,keyword;
	char gen[10];
	char a;
	employee_data *em;
	FILE *file = fopen("19_input.txt","r");
	fscanf(file,"%d",&n);
	em=(employee_data*)malloc(sizeof(employee_data)*n);
	for(i=0;i<n;i++){
		fscanf(file,"%d %*c %25[^/] %*c %s %*c %25[^/] %*c %d %*c %lf",&em[i].employee_id,em[i].name,gen,em[i].department.dept_name,&em[i].department.dept_no,&em[i].salary);
		if(gen[0]=='M') em[i].gender=0;
		else em[i].gender=1;
	}
	while(1){
		printf("Employee ID : ");
		scanf("%d",&id);
		res=search(em,n,id);
		if(res<n){
			printf("------Employee Data------\n");
			printf("%d / %s/ ",em[res].employee_id,em[res].name);
			if(em[res].gender==0) printf("Male / ");
			else printf("Female / ");
			printf("%s / %d / %.2f\n",em[res].department.dept_name,em[res].department.dept_no,em[res].salary);
			printf("------Update information------\n");
			printf("Input the department Number : ");
			scanf("%d",&no);
			printf("%d / %s/ ",em[res].employee_id,em[res].name);
			if(em[res].gender==0) printf("Male / ");
			else printf("Female / ");
			em[res].department.dept_no=no;
			update(&em[res],no);
			
			printf("%s / %d / %.2f\n",em[res].department.dept_name,em[res].department.dept_no,em[res].salary);
		} else{
			printf("No employee\n");
		}
			printf("Continue? (y/n) : ");
			scanf("%*c%c",&a);
			if(a=='y') continue;
			else break;
	}
	fclose(file);
}

void update(employee_data *e,int n){
	int i=0;	
	for(i=0;i<25;i++) (*e).department.dept_name[i]='\0';
	if(n==1) strcpy((*e).department.dept_name,"FINACE");
	else if(n==2) strcpy((*e).department.dept_name,"SALES");
	else if(n==3) strcpy((*e).department.dept_name,"RESEARCH");
	else if(n==4) strcpy((*e).department.dept_name,"PLANNING");
}

int search(employee_data *e,int num,int keyword){
	int res;
	int i;
	for(i=0;i<num;i++) {
		if(e[i].employee_id==keyword) break;
	}
	res=i;
	return res;

}
