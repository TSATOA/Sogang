#include<stdio.h>

void checkWB(char col, int row, char *answer);

int main()
{
	char col,answer;
	int row;
	scanf("%c%d", &col, &row);
	checkWB(col, row, &answer);
	printf("%c", answer);
	return 0;
}

void checkWB(char col, int row, char *answer) {
	if (row % 2 == 0 && (col == 'a' || col == 'c' || col == 'e' || col == 'g')) {
		*answer = 'W';
	}
	if (row % 2 == 1 && (col == 'a' || col == 'c' || col == 'e' || col == 'g')) {
		*answer = 'B';
	}
	if (row % 2 == 0 && (col == 'b' || col == 'd' || col == 'f' || col == 'h')) {
		*answer = 'B';
	}
	if (row % 2 == 1 && (col == 'b' || col == 'd' || col == 'f' || col == 'h')) {
		*answer = 'W';
	}
	return;

}