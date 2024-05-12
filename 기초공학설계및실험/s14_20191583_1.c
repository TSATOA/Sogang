#include<stdio.h>

float avgFunc(float, float, float);
void gradeFunc(float);

int main()
{
	float a,b,c,avg;
	printf("input: ");
	scanf("%f%f%f",&a, &b, &c);
	avg=avgFunc(a,b,c);
	gradeFunc(avg);
}

float avgFunc(float a, float b, float c){
	float av;
	av=(a+b+c)/3;
	return av;
}

void gradeFunc(float avg){
	if(avg>=90)
		printf("Grade: A\n");

	if(avg>=80){
		if(avg<90){
			printf("Grade: B\n");
		}
	}

	if(avg>=70){
		if(avg<80){
			printf("Grade: C\n");
		}
	}

	if(avg>=50){
		if(avg<70){
			printf("Grade: D\n");
		}
	}

	if(avg<50)
		printf("Grade: F\n");

}
