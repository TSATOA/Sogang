#include "Graph_adj_list.h"
#include <queue>
using namespace std;

extern void errorExit(const char *s);

SLList2 pool;
unsigned long UsedMemoryForArray = 0;

void Read_Graph_adj_list(int Vnum, vertex *V, int Enum, edge *E) {
	// ���Ͽ��� �׷��� ������ �о� V�� E �迭�� �����Ѵ�.
	// V[ ].name�� E[ ].name�� ������ �ʿ䰡 ������ ���ǻ� �� �迭������
	//   index�� �����Ѵ�.
	// V[ ].S�� adjacent list header�� ���� ����ε� ���ȴ�.
	// ���� edge (i,j)�� ������ V[i].S�� edge index k�� push�ϰ�
	//  ���������� V[j].S�� k�� push�Ѵ�.
	// V[].flag�� E[].flag�� �ݵ�� false�� �����ؾ� �Ѵ�.

	int i,a,b,c;
	
	for (i = 0; i < Vnum; i++) {
		V[i].name = i;
		V[i].flag = false;
	}
	for (i = 0; i < Enum; i++) {
		scanf("%d%d%d", &a, &b, &c);
		E[i].vf = a;
		E[i].vr = b;
		E[i].cost = c;
		E[i].name = i;
		E[i].flag = false;

		SLL *p = pool.allocSLL();
		p->i = i;
		V[a].S.push(p);
		p = pool.allocSLL();
		p->i = i;
		V[b].S.push(p);
		
	}


	// ***�� �Լ��� �ۼ��Ѵ�

}

void Free_Graph_adj_list(int Vnum, vertex *V) {
	// V �迭�� adjacency list�� ���Ҹ� pop()�� ����Ͽ�
	// ���  pool�� �ǵ��� �ش�
	int k;
	for (k = 0; k < Vnum; k++) {
		while (!(V[k].S.empty())) {
			SLL *p = V[k].S.pop();
			pool.freeSLL(p);
		}
	}
	// ***�� �Լ��� �ۼ��Ѵ�

}

int BFS_Tree_adj_list(
	int     src,   // source node index
	int     Vnum,  // number of vertices
	vertex *V,     // vertex structure array (starting index 0)
	int     Enum,  // number of edges
	edge   *E     // edge structure array (starting index 0)
) {
	// BFS�� ����Ͽ� BFS tree�� ���ϴ� ������ flag�� true�� �����Ѵ�.
	// BFS ���� vertex�� �Է� ���Ͽ��� �����ȴ�(src).
	// V[]�� adjacent list Ž���� .top() ��� �Լ��� ����Ͽ�
	//  adj list ����� ��� �̸� ���󰡸� ���� vertex�� Ž���Ѵ�.
	// BFS tree�� ���� ������ cost ���� return �Ѵ�
	//   (not unique but ��� �� edge cost�� 1�̸� unique)
	// -- �Լ��� ��� parameter�� ���� �ʿ�� ����.
	// -- BFS�� ���� queue�� �ʿ��ϸ� STL�� queue�� ����ص� ����

	// ***�� �Լ��� �ۼ��Ѵ�
	int i;
	int a;
	int cnt=0;
	SLL *p;
	queue <int> q;

	V[src].flag = true;
	q.push(src);
	while (!q.empty()) {
		a = q.front();
		q.pop();
		p = V[a].S.top();

		while (p!=NULL) {
			if (V[E[p->i].vf].flag == false) {
				V[E[p->i].vf].flag = true;
				q.push(E[p->i].vf);
				E[p->i].flag = true;
				cnt += E[p->i].cost;
			}
			if (V[E[p->i].vr].flag == false) {
				V[E[p->i].vr].flag = true;
				q.push(E[p->i].vr);
				E[p->i].flag = true;
				cnt+=E[p->i].cost;
			}
			p = p->p;
		}
	}
	
	return cnt;
}

// SLL management functions
// �Ʒ� �Լ����� 02_04_CSE3081_CPrg&DataStructure_�߰��ڷ�.pdf��
//   �����Ͽ� �� �Լ����� ä�� ����.
// ���ø� �ʿ��ϹǷ� ť�� ��� �Լ��� �Ʒ� �Լ� ����Ʈ�� ����

// stack member fuctions
void sllStack2::push(SLL *p) {
	// insert p to the top of stack ST
	p->p = ST;
	ST = p;
}

SLL *sllStack2::pop(void) {
	// remove and return p at the top of ST
	SLL *p = ST;
	if (ST->p == NULL)
		ST = NULL;
	else
		ST = ST->p;
	return p;
	// ***�� �Լ��� �ۼ��Ѵ�

}

SLL *sllStack2::top(void) {
	// return p at the top of ST
	return ST;
}

bool sllStack2::empty(void) {
	// return true if empty
	if (ST == NULL)
		return true;
	else
		return false;
}

// SLList2 member functions
SLL *SLList2::allocSLL(void) {		// allocate an SLL element
	SLL *p;
	if (SLL_pool == NULL) {
		p = (SLL *)malloc(sizeof(SLL));
		if (p == NULL)
			errorExit("Memory allocation error(allocSLL)");
		UsedMemoryForSLLs += sizeof(SLL);
		p->i = NONE;
	}
	else {
		p = SLL_pool;
		SLL_pool = p->p;
	}
	p->p = NULL;
	++SLL_cnt;
	// ***�� �Լ��� �ۼ��Ѵ�

	return(p);
}

void SLList2::freeSLL(SLL *p) {		// free *p (move it to SLL_pool
	if (p->i == NONE) {
		errorExit("This is already freed(freeSLL).");
	}
	p->i = NONE;
	p->p = SLL_pool;
	SLL_pool = p;
	--SLL_cnt;
	// ***�� �Լ��� �ۼ��Ѵ�

}

void SLList2::freeSLL_pool(void) {	// clear SLL_pool
	SLL *p = SLL_pool;
	while (p != NULL) {
		SLL_pool = p->p;
		free(p);
		UsedMemoryForSLLs -= sizeof(SLL);
		p = SLL_pool;
	}
	// ***�� �Լ��� �ۼ��Ѵ�

	if (SLL_cnt != 0) {
		errorExit("Non-zero SLL_cnt after cleanup.");
	}
}