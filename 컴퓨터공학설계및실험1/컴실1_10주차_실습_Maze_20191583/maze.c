#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

void sync(int **maze, char **frame, int xa, int ya);
int x, y, z = 1;

int main() {
	int **maze;
	char **frame;
	int i, j;
	int cnt = 0;
	int combine_rand, inc_rand;
	FILE *fp;
	fp = fopen("maze.maz", "w");
	scanf("%d%d", &x, &y);
	maze = (int **)malloc(sizeof(int *)*y);
	for (i = 0; i < y; i++)
		maze[i] = (int *)malloc(sizeof(int)*x);
	frame = (char **)malloc(sizeof(char *)*(y * 2 + 1));
	for (i = 0; i < y * 2 + 1; i++)
		frame[i] = (char *)malloc(sizeof(char)*(x * 2 + 1));

	srand((unsigned)time(NULL));

	//초기 설정
	for (i = 0; i < x; i++) {
		maze[0][i] = z;
		z++;
	}
	for (i = 0; i < x * 2 + 1; i++) {
		if (i % 2 == 0) {
			frame[0][i] = '+';
		}
		else {
			frame[0][i] = '-';
		}
	}
	for (i = 0; i < x * 2 + 1; i++) {
		if (i % 2 == 0) {
			frame[1][i] = '|';
		}
		else {
			frame[1][i] = ' ';
		}
	}
	for (i = 0; i < x * 2 + 1; i++) {
		if (i % 2 == 0) {
			frame[2][i] = '+';
		}
		else {
			frame[2][i] = '-';
		}
	}

	for (i = 0; i < y - 1; i++) {
		//중간1 벽제거
		for (j = 0; j < x - 1; j++) {
			combine_rand = rand() % 2;
			if (combine_rand == 1) {
				frame[i*2+1][j * 2 + 2] = ' ';
			}
		}
		//중간2 합치기(동기화)
		for (j = 0; j < x; j++) {
			sync(maze, frame, j, i);
		}
		//중간3 늘리기
		cnt = 0;
		for (j = 0; j < x; j++) {
			inc_rand = rand() % 2;
			if (inc_rand == 1) {
				maze[i + 1][j] = maze[i][j];
				cnt++;
			}
			else {
				if (cnt == 0 && j == x - 1) {
					maze[i + 1][j] = maze[i][j];
					cnt = 0;
				}
				else if (cnt == 0 && maze[i][j] != maze[i][j + 1] && j != x - 1) {
					maze[i + 1][j] = maze[i][j];
					cnt = 0;
				}
				else {
					maze[i + 1][j] = z;
					z++;
				}
			}
			if (j != x - 1 && maze[i][j] != maze[i][j + 1]) cnt = 0;
		}
		//중간4 아래벽깨기
		for (j = 0; j < x; j++) {
			if (maze[i][j] == maze[i + 1][j]) {
				frame[i * 2 + 2][j * 2 + 1] = ' ';
			}
		}
		//중간5 벽만들기
		//옆벽
		for (j = 0; j < x * 2 + 1; j++) {
			if (j % 2 == 0) {
				if (j == 0 || j == x * 2) {
					frame[i * 2 + 3][j] = '|';
				}
				else {
					if (maze[i + 1][j / 2 - 1] == maze[i + 1][j / 2]) {
						frame[i * 2 + 3][j] = ' ';
					}
					else {
						frame[i * 2 + 3][j] = '|';
					}
				}

			}
			else {
				frame[i * 2 + 3][j] = ' ';
			}
		}
		//아래벽
		for (j = 0; j < x * 2 + 1; j++) {
			if (j % 2 == 0) {
				frame[i * 2 + 4][j] = '+';
			}
			else {
				frame[i * 2 + 4][j] = '-';
			}
		}
	}

	//끝 옆벽 깨기
	for (i = 0; i < x - 1; i++) {
		if (maze[y - 1][i] != maze[y - 1][i + 1]) {
			frame[y * 2 - 1][i * 2 + 2] = ' ';
			sync(maze, frame, i, y - 1);
		}
	}

	


	for (i = 0; i < y * 2 + 1; i++) {
		for (j = 0; j < x * 2 + 1; j++) {
			fprintf(fp,"%c", frame[i][j]);
		}
		fprintf(fp,"\n");
	}
	fclose(fp);
}


void sync(int **maze, char **frame, int xa, int ya) {
	//왼쪽 벽이 없는 경우
	if (frame[ya * 2 + 1][xa * 2] == ' ') {
		if (maze[ya][xa - 1] != maze[ya][xa]) {
			maze[ya][xa - 1] = maze[ya][xa];
			sync(maze, frame, xa - 1, ya);
		}
	}
	//오른쪽에 벽이 없는 경우
	if (frame[ya * 2 + 1][xa * 2 + 2] == ' ') {
		if (maze[ya][xa + 1] != maze[ya][xa]) {
			maze[ya][xa + 1] = maze[ya][xa];
			sync(maze, frame, xa + 1, ya);
		}
	}
	//위쪽에 벽이 없는 경우
	if (frame[ya * 2][xa * 2 + 1] == ' ') {
		if (maze[ya - 1][xa] != maze[ya][xa]) {
			maze[ya - 1][xa] = maze[ya][xa];
			sync(maze, frame, xa, ya - 1);
		}
	}
	//아래쪽에 벽이 없는 경우
	if (frame[ya * 2 + 2][xa * 2 + 1] == ' ') {
		if (maze[ya + 1][xa] != maze[ya][xa]) {
			maze[ya + 1][xa] = maze[ya][xa];
			sync(maze, frame, xa, ya + 1);
		}
	}

}