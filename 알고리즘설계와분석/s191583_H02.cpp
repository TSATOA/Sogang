
#include "Graph_adj_array.h"

void Read_Graph_adj_array (int Vnum, vertex V[], int Enum, edge E[]) {
	// read graph information
	// V와 E의 name field는 각각 자신의 인덱스를 저장한다
	// V[].flag과 E[].flag은 반드시 false로 설정해야 한다.
	int i;
	int a, b, c;
	for (i = 0; i < Vnum; i++) {
		V[i].name = i;
		V[i].flag = false;
		V[i].f_hd = NONE;
		V[i].r_hd = NONE;
	}
	for (i = 0; i < Enum; i++) {
		E[i].fp = NONE;
		E[i].rp = NONE;
		E[i].flag = false;
		E[i].name = i;
	}

	for (i = 0; i < Enum; i++) {
		scanf("%d%d%d", &a, &b, &c);
		E[i].vf = a;
		E[i].vr = b;
		E[i].cost = c;
		
		if (V[a].f_hd != NONE) {
			E[i].fp = V[a].f_hd;
		}
		if (V[b].r_hd!=NONE) {
			E[i].rp = V[b].r_hd;
		}
		
		V[a].f_hd = i;
		V[b].r_hd = i;
	}

	// ***이 함수를 작성한다

}

int DFS_Tree_adj_array(
	int     src,   // source node index
	int     Vnum,  // number of vertices
	vertex *V,     // vertex structure array (starting index 0)
	int     Enum,  // number of edges
	edge   *E     // edge structure array (starting index 0) 
) {
	// DFS를 사용하여 DFS tree에 속하는 에지의 flag을 true로 설정한다.
	// DFS 시작 vertex는 입력 파일에서 지정된다(src).
	// DFS tree에 속한 에지의 cost 함을 return 한다(모든 각 edge cost가 1이면 unique)
	// recursive 함수로 작성해도 무방하다.

	// ***이 함수를 작성한다***
	
	int a;
	int b;
	int cnt = 0;
	V[src].flag = true;
	a = V[src].f_hd;
	while (1) {
		if (a == NONE)
			break;
		if (E[a].vf == src)
			b = E[a].vr;
		else
			b = E[a].vf;
		if (V[b].flag == false) {
			E[a].flag = true;
			cnt=cnt+E[a].cost+DFS_Tree_adj_array(b, Vnum, V, Enum, E);
		}

		a = E[a].fp;

	}
	a = V[src].r_hd;
	while (1) {
		if (a == NONE)
			break;
		if (E[a].vf == src)
			b = E[a].vr;
		else
			b = E[a].vf;
		if (V[b].flag == false) {
			E[a].flag = true;
			cnt=cnt+E[a].cost+DFS_Tree_adj_array(b, Vnum, V, Enum, E);
		}
		a = E[a].rp;
	}
	return cnt;
}
