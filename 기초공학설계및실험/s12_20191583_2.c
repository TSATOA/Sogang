#include<stdio.h>

float check(float c1, float c2, float c3, float c4);

int main()
{
	float c1, c2, c3, c4;
	scanf("%f%f%f%f", &c1, &c2, &c3, &c4);
	printf("%.1f", check(c1, c2, c3, c4));
	return 0;

}

float check(float c1, float c2, float c3, float c4) {
	float res, res1, res2, res3;
	res1 = (c2 - ((c1 + c2) / 2)) * 2 + (c4 - ((c3 + c4) / 2)) * 2;
	res2 = (c3 - (c1 + c3) / 2) * 2;
	res3 = (c4 - (c2 + c4) / 2) * 2;
	if (res1 < res2&&res1<res3) {
			res = res1;
	}
	if (res2 < res3&&res2<res1) {
			res = res2;
	}
	if (res3 < res1&&res3<res2) {
			res = res3;
	}
	return res;

}