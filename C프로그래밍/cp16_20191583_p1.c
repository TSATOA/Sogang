#include<stdio.h>
#include<math.h>
#include<stdlib.h>


typedef float* Vector_Comp;
typedef float Comp;

struct Vector{
	Vector_Comp comps;
	int vec_size;
};

float Distance_DistVector(struct Vector v1,struct Vector v2);
float Scalar_innerProduct(struct Vector v1,struct Vector v2);
float Size_vectorSize(struct Vector v);

int main()
{
	struct Vector v1;
	struct Vector v2;
	int i;
	scanf("%d",&v1.vec_size);
	v1.comps=(Vector_Comp)malloc(sizeof(Comp)*v1.vec_size);
	for(i=0;i<v1.vec_size;i++){
		scanf("%f",&v1.comps[i]);
	}
	scanf("%d",&v2.vec_size);
	v2.comps=(Vector_Comp)malloc(sizeof(Comp)*v2.vec_size);
	for(i=0;i<v2.vec_size;i++){
		scanf("%f",&v2.comps[i]);
	}
	if(v1.vec_size==v2.vec_size){
		printf("Size : %.2f\n", Size_vectorSize(v1));
		printf("Size : %.2f\n", Size_vectorSize(v2));
		printf("Dist : %.2f\n", Distance_DistVector(v1,v2));
		printf("Inner : %.2f\n", Scalar_innerProduct(v1,v2));
	} else{
		printf("Size : %.2f\n", Size_vectorSize(v1));
		printf("Size : %.2f\n", Size_vectorSize(v2));
	}
	return 0;

}

float Distance_DistVector(struct Vector v1,struct Vector v2){
	float d=0;
	int i;
	float a[30];
	float res;
	for(i=0;i<v1.vec_size;i++){
		a[i]=(v1.comps[i]-v2.comps[i])*(v1.comps[i]-v2.comps[i]);
		d+=a[i];
	}
	res=sqrt(d);
	return res;
}

float Scalar_innerProduct(struct Vector v1,struct Vector v2){
	float d=0;
	int i;
	for(i=0;i<v1.vec_size;i++){
		d+=v1.comps[i]*v2.comps[i];
	}
	return d;
}

float Size_vectorSize(struct Vector v){
	float d=0;
	int i;
	for(i=0;i<v.vec_size;i++){
		d+=v.comps[i]*v.comps[i];
	}
	d=sqrt(d);
	return d;
}
