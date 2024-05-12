#include<stdio.h>
int main(void)
{

	/* NAME : Kim Taegon */
	/* ID : 20191583 */
	char ch; //character
	int integer; //integer
	float real; //real number

	printf("Input one character, one integer, one real number : "); //write three variable
	scanf("%c %d %f", &ch, &integer, &real); //get three variable
	printf("%c %d %f\n",ch, integer, real); //output three variable

	return 0;
}
