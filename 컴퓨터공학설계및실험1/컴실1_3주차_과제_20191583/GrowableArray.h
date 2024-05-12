#ifndef __GROWABLEARRAY__
#define __GROWABLEARRAY__

#include "Array.h"
#include<cstdlib>
#include<iostream>

using namespace std;

template<class T>
class GrowableArray : public Array<T>{
	protected:
		T *a;
	public:
		GrowableArray(int size);
		~GrowableArray();
		T&operator[](int i);
		T operator[](int i)const;
};


template<class T>
GrowableArray<T>::GrowableArray(int size):Array<T>(size){
}

template<class T>
GrowableArray<T>::~GrowableArray(){
}

template<class T>
T&GrowableArray<T>::operator[](int i){
	int j;
	if(i>=this->len){
		a=new T[this->len];
		for(j=0;j<this->len;j++)
			a[j]=this->data[j];
	
		delete[] this->data;

		this->data=new T[2*i];
		for(j=0;j<this->len;j++)
			this->data[j]=a[j];
		for(j=this->len;j<2*i;j++)
			this->data[j]=0;
		delete[] a;
		this->len=i*2;
	}
	return Array<T>::operator[](i);
	
}

template<class T>
T GrowableArray<T>::operator[](int i)const{
	return Array<T>::operator[](i);
}

#endif

