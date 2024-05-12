#include<stdio.h>

int k=1;
int dig(int num);
int palindrome(int num,int digit);

int main(){
	int num,digit=1;
	printf("Input: ");
	scanf("%d", &num);
	if(num<0){
		printf("Input number cannot be negative.\n");
	} else if(palindrome(num,digit)==1){
		printf("%d is a palindrome number.\n", num);
	} else if(palindrome(num,digit)==0){
		printf("%d is not a palindrome number.\n",num);
	}

	return 0;
}

int dig(int num){
	if(num/10==0){
		return 1;
	}
	return 10*dig(num/10);
}

int palindrome(int num, int digit){
	if(k*k>=dig(num)){
		k=1;
		return 1;
	} else if(((num%(10*digit))-(num%digit))/digit!=((num%(10*(dig(num)/digit))-(num%(dig(num)/digit)))/(dig(num)/digit))){
		k=1;
		return 0;
	} else{
		k*=10;
		return palindrome(num,10*digit);
	}
}
		

