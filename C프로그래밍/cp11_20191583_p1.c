#include<stdio.h>

int string_length(char *st);

int main()
{
	char s[]="C is a high-level language";
	char *t="C프로그래밍";
	printf("문자열 s의 길이	: %d\n", string_length(s));//'\0'를 포함하지 않는 문자열의 길이
	printf("sizeof(s)	: %d\n",(int)sizeof(s));//'\0'까지 포함한 문자열의 길이
	printf("문자열 t의 길이	: %d\n",string_length(t));//한글의 경우 배열의 크기의 3칸을 차지하므로 영문자 1개와 한글문자 5개를 포함한 문자열의 길이
	printf("sizeof(t)	: %d\n",(int)sizeof(t));//문자형 포인터의 크기
}

int string_length(char *st){
	int i=0;
	while(st[i]!='\0'){
		i++;
	}
	return i;
}
