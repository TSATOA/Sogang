#include "Str.h"
#include <string.h>
#include <iostream>

using namespace std;

/* Str.h에서 선언한 클래스 내용 선언 */

//Str 생성자, leng은 string의 길이
Str::Str(int leng){
	str = new char[leng+1];
	len = leng;
}

//Str 생성자(오버로딩), neyong은 초기화 할 내용이 들어감
Str::Str(char *neyong){
	len = strlen(neyong);
	str = new char[len+1];
	strcpy(str,neyong);
}

//Str 소멸자
Str::~Str(){
	delete(str);
}

//string의 길이를 리턴하는 함수
int Str::length(void){
	return len;
}

//string의 내용을 리턴하는 함수
char *Str::contents(void){
	return str;
}

//a의 내용과 strcmp
int Str::compare(class Str&a){
	return strcmp(str,a.contents());
}

//a의 내용과 strcmp
int Str::compare(char *a){
	return strcmp(str,a);
}

//string의 값을 대입 및 길이 지정
void Str::operator=(char *a){
	len = strlen(a);
	strcpy(str,a);
}

//Str의 내용 대입 및 길이지정
void Str::operator=(class Str&a){
	len = strlen(a.contents());
	strcpy(str,a.contents());
}
