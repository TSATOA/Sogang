#include <stdio.h>
#include <string.h>
#include <syscall.h>

/*additional.c script*/

// 문자열을 숫자로 바꾸는 함수
int str_to_int(char *str){
	int result = 0;
	while(*str != '\0'){
		result = result * 10 + (*str -'0');
		str++;
	}
	return result;
}

// fibonacci와 max_of_four_int 결과 출력
int main(int argc, char **argv){
	if(argc!=5){
		printf("Insufficient number of input");
		return EXIT_FAILURE;
	}
	int a = str_to_int(argv[1]);
	int b = str_to_int(argv[2]);
	int c = str_to_int(argv[3]);
	int d = str_to_int(argv[4]);
	printf("%d ",fibonacci(a));
	printf("%d\n",max_of_four_int(a,b,c,d));
	return EXIT_SUCCESS;
}


