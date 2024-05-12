#include "Str.h"
#include <string.h>
#include <iostream>

using namespace std;

int main(){
	Str a("I'm a girl"); //a 객체 생성 및 내용 입력(Str(*neyong))
	cout << a.contents(); //a의 내용(str) 출력(return str)
	a="I'm a boy\n"; // a의 내용 초기화(oprator)
	cout << a.contents(); // 바뀐 a의 내용(str) 출력(return str)
	cout << a.compare("I'm a a") << endl; // a의 내용과 strcmp 후 줄 종료
	return 0;
}
