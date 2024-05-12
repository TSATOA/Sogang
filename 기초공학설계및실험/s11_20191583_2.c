#include<stdio.h>

int main()
{
	int n;
	char a, b, c;
	scanf("%d %c%c%c", &n, &a, &b, &c);
	n = n % 27;
	if (a + n > 'z') {
		a = a - 28;
		a = a + n - 1;
	}
	if (a + n < 'a') {
		a = a + n + 27;
	}
	if (a + n <= 'z'&&a + n >= 'a') {
		a = a + n;
	}
	if (b + n > 'z') {
		b = b - 28;
		b = b + n - 1;
	}
	if (b + n < 'a') {
		b = b + n + 27;
	}
	if (b + n <= 'z'&&b + n >= 'a') {
		b = b + n;
	}
	if (c + n > 'z') {
		c = c - 28;
		c = c + n - 1;
	}
	if (c + n < 'a') {
		c = c + n + 27;
	}
	if (c + n <= 'z'&&c + n >= 'a') {
		c = c + n;
	}
	printf("%c%c%c", a, b, c);
	return 0;

}