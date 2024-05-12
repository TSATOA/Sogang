#ifndef __ARRAY__
#define __ARRAY__

#include <cstdlib>
#include <iostream>

using namespace std;

//Array class 선언
template<class T>
class Array{
	protected:
		T *data;
		int len;
	public:
		Array(int size);
		~Array();

		int length() const;

		T& operator[](int i);
		T operator[](int i)const;

		void print();
};


template<class T>
Array<T>::Array(int size)
{
	//사이즈를 확인하고 양수이면 new를 사용하여 배열 data를 할당, len값 초기화
	if(size<0)
	{
		cout << "Array bound error!" << endl;
	}
	else
	{
		len = size;
		data = new T[size];
	}
}

template<class T>
Array<T>::~Array()
{
	// 소멸자; 할당된 메모리 해제
	delete[] data;
}

template<class T>
int Array<T>::length() const
{
	// 배열의 크기 리턴
	return len;
}

// 배열에 원소를 대입하거나 값을 반환하는 부분으로 []연산자의 오버로딩이다
template<class T>
T& Array<T>::operator[](int i) // 배열에 원소 삽입
{
	static T tmp;

	// 배열의 인덱스가 범위 내에 있으면 값 리턴, 그렇지 않으면 에러메세지 출력하고 tmp리턴
	if(i >= 0 && i < len)
	{
		return data[i];
	}
	else
	{
		cout << "Array bound error!" << endl;
		return tmp;
	}
}

template<class T>
T Array<T>::operator[](int i) const // 배열의 원소값 반환
{
	//배열의 인덱스가 범위 내에 잇으면 값을 리턴, 그렇지 않으면 에러메세지 출력하고 0을 리턴
	if(i >= 0 && i<len)
	{
		return data[i];
	}
	else
	{
		cout << "Array bound error!" << endl;
		return 0;
	}
}

template<class T>
void Array<T>::print() //배열의 모든 내용을 출력해주는 함수
{
	int i;
	cout<<"[";
	for(i=0;i<len-1;i++) cout << data[i]<< " ";
	cout << data[len-1];
	cout<<"]";
	cout<<endl;
}

#endif

