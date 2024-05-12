#define _CRT_SECURE_NO_WARNINGS 
#include <cstdio>


int A[1000][1000];
int cum[1000][1000];

int main() {

    FILE* in = fopen("input2.txt", "r");

    int n, m;
    fscanf(in, "%d %d", &m, &n);

    // �迭�� 0�� ����
    for (int i = 0; i < n; i++)
        A[i + 1][0] = 0;
    for (int i = 0; i < m; i++)
        A[0][i + 1] = 0;
    A[0][0] = 0;

    //
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            int tmp;
            fscanf(in, "%d ", &tmp);
            A[i + 1][j + 1] = tmp;
        }
    }

    //start code
    /*
    A �迭�� ���� ���� ���� �� ����ؼ� cum �迭�� �ֱ�
    �����ð��� ��ȭ�� �����Ͻ� �κ� �����ϸ� ���� ���� �����մϴ�.
    */
    cum[1][1] = A[1][1];
    for (int i = 2; i <= m; i++) {
        cum[1][i] += cum[1][i - 1] + A[1][i];
    }
    for (int i = 2; i <= n; i++) {
        cum[i][1] += cum[i - 1][1] + A[i][1];
    }
    for (int i = 2; i <= n; i++) {
        for (int j = 2; j <= m; j++) {
            cum[i][j] = cum[i - 1][j] + cum[i][j - 1] - cum[i - 1][j - 1] + A[i][j];
        }
    }
    //end code
    
    /*
    //������ �迭 Ȯ�ο� �ڵ�
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= m; j++) {
            printf("%d ", cum[i][j]);
        }
        printf("\n");
    }
    */

    //Q queries
    fscanf(in, "%d", &m);

    for (int i = 0; i < m; i++) {

        // left up, right down (x, y)
        int lux, luy, rdx, rdy;
        fscanf(in, "%d %d %d %d", &lux, &luy, &rdx, &rdy);

        lux++;
        luy++;
        rdx++;
        rdy++;


        int value = 0; // value �ۼ��ϼ���.
        value = cum[rdy][rdx] - cum[luy - 1][rdx] - cum[rdy][lux - 1] + cum[luy - 1][lux - 1];
        printf("%d\n", value);

    }



    return 0;

}