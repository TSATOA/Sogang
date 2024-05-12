#include<stdio.h>

void *max(void *ptr1,void *ptr2, char option);

int main()
{
	char option;
	void *ptr1,*ptr2;
	int num1,num2;
	float num3,num4;
	void *result;

	printf("Enter the type of numbers: ");
	scanf("%c",&option);
	if(option=='i'){
		printf("Enter the 1st number : ");
		scanf("%d",&num1);
		printf("Enter the 2nd number : ");
		scanf("%d",&num2);
		ptr1=&num1;
		ptr2=&num2;
		result=max(ptr1,ptr2,option);
		printf("\n\n\nmaximum value is %d\n",*(int *)result);
	} else{
		printf("Enter the 1st number : ");
		scanf("%f",&num3);
		printf("Enter the 2nd number : ");
	scanf("%f",&num4);
		ptr1=&num3;
		ptr2=&num4;
		result=max(ptr1,ptr2,option);
		printf("\n\n\nmaximum value is %f\n",*(float *)result);
	}
	
	
	return 0;

}

void *max(void *ptr1,void *ptr2, char option){
	if(option=='i'){
		if(*(int*)ptr1>*(int*)ptr2) return (int*)ptr1;
		else return (int*)ptr2;
	} else{
		if(*(float*)ptr1>*(float*)ptr2) return (float*)ptr1;
		else return (float*)ptr2;
	}
}
