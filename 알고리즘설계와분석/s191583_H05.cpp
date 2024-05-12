#include<stdio.h>
#include<string.h>
#include<stdlib.h>

/*3개 중 최소값 구하기*/
int min(int x, int y, int z) {
	if (x <= y && x <= z)
		return x;
	else if (y <= x && y <= z)
		return y;
	else
		return z;
}

/*Edit Distance 함수*/
void Edit_Distance(
	// inputs
	char *SS,		// Source string array
	char *TS,		// Edited string array
	int ins_cost, int del_cost, int sub_cost,
	// insertion, deletion, substitution cost
// outputs
int **Table,    // Cost Table Calculated (2-d array (|SS|+1) x (|TS|+1) will be set)
char **SR,		// Source string with insertion to T marks '*'
char **OP,		// Operation sequence('i', 'd', 's', or '.' (nop))
char **TR,       // Edited string with deletion form S mark '*'
				// NOTE: ST, OP, TR must be allocated inside the function as needed(minimum as possible)
	int  *Mem_Allocated
) {
	int SN, TN;
	int i, j, cnt = 0,k;
	int a=0, b=0, c=0, d=0;
	int ss,tt;
	int subs = sub_cost;
	SN = (int)strlen(SS);
	TN = (int)strlen(TS);
	//초기 graph
	for (i = 0; i <= SN; i++) Table[i][0] = i*del_cost;
	for (i = 0; i <= TN; i++) Table[0][i] = i*ins_cost;

	//graph 생성
	for (i = 1; i <= SN; i++) {
		for (j = 1; j <= TN; j++) {
			if (SS[i-1] == TS[j-1]) {
				subs = 0;
			}
			else {
				subs = sub_cost;
			}
			Table[i][j] = min(Table[i][j - 1] + ins_cost, Table[i - 1][j] + del_cost, Table[i - 1][j - 1] + subs);
		}
	}
	
	i = SN;
	j = TN;
	//OP의 요소 구하기(a:del, b:inp, c:sub, d:., cnt:OP의 길이)
	while (true) {
		if (ins_cost <= del_cost) {
			if (Table[i][j - 1] < Table[i][j]) {
				a++;
				j--;
			}
			else if (Table[i - 1][j] < Table[i][j]) {
				b++;
				i--;
			}
			else {
				if (Table[i - 1][j - 1] < Table[i][j]) {
					c++;
				}
				else {
					d++;
				}
				i--;
				j--;
			}
			cnt++;
		}
		else {
			if (Table[i - 1][j] < Table[i][j]) {
				b++;
				i--;
			}
			else if (Table[i][j - 1] < Table[i][j]) {
				a++;
				j--;
			}
			else {
				if (Table[i - 1][j - 1] < Table[i][j]) {
					c++;
				}
				else {
					d++;
				}
				i--;
				j--;
			}
			cnt++;
		}
		if (i == 0 || j == 0) break;
	}
	if (i != 0) {
		while (true) {
			b++;
			i--;
			cnt++;
			if (i == 0) break;
		}
	}
	if (j != 0) {
		while (true) {
			a++;
			j--;
			cnt++;
			if (j == 0) break;
		}
	}
	//OP,SR,TR동적할당 및 초기화
	*OP = new char[cnt + 1]{};
	*SR = new char[a + SN + 1]{};
	*TR = new char[b + TN + 1]{};
	//메모리 크기
	*Mem_Allocated = _msize(*OP) + _msize(*SR) + _msize(*TR);

	i = SN;
	j = TN;
	cnt--;
	ss = SN-1;
	tt = TN-1;
	//OP,SR,TR에 대입(뒤에서부터 대입)
	while (i != 0 && j != 0) {
		if (ins_cost <= del_cost) {
			if (Table[i][j - 1] < Table[i][j]) {
				(*OP)[cnt] = 'i';
				(*SR)[cnt] = '*';
				(*TR)[cnt] = TS[tt];
				tt--;
				j--;
			}
			else if (Table[i - 1][j] < Table[i][j]) {
				(*OP)[cnt] = 'd';
				(*SR)[cnt] = SS[ss];
				(*TR)[cnt] = '*';
				ss--;
				i--;
			}
			else {
				if (Table[i - 1][j - 1] < Table[i][j]) {
					(*OP)[cnt] = 's';
				}
				else {
					(*OP)[cnt] = '.';
				}
				(*SR)[cnt] = SS[ss];
				(*TR)[cnt] = TS[tt];
				ss--;
				tt--;
				i--;
				j--;
			}
			
		}
		else {
			if (Table[i - 1][j] < Table[i][j]) {
				(*OP)[cnt] = 'd';
				(*SR)[cnt] = SS[ss];
				(*TR)[cnt] = '*';
				ss--;
				i--;
			}
			else if (Table[i][j - 1] < Table[i][j]) {
				(*OP)[cnt] = 'i';
				(*SR)[cnt] = '*';
				(*TR)[cnt] = TS[tt];
				tt--;
				j--;
			}
			else {
				if (Table[i - 1][j - 1] < Table[i][j]) {
					(*OP)[cnt] = 's';
				}
				else {
					(*OP)[cnt] = '.';
				}
				(*SR)[cnt] = SS[ss];
				(*TR)[cnt] = TS[tt];
				ss--;
				tt--;
				i--;
				j--;
			}
		}
		cnt--;
	}
	if (i != 0) {
		while (true) {
			
			(*OP)[cnt] = 'd';
			(*SR)[cnt] = SS[ss];
			(*TR)[cnt] = '*';

			i--;
			cnt--;
			ss--;
			if (i == 0) break;
		}
	}
	if (j != 0) {
		while (true) {
			(*OP)[cnt] = 'i';
			(*SR)[cnt] = '*';
			(*TR)[cnt] = TS[tt];

			j--;
			cnt--;
			ss--;
			if (j == 0) break;
		}
	}

}
