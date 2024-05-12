#define _CRT_SECURE_NO_WARNINGS 
#include <cstdio>
#include <memory>
#include <queue>
#include <utility>
#include <cmath>

// SegmentTree1D �����ϼ���. ���� ��ũ��ġ�� ���� �����ϼŵ� �����մϴ�.
// ���� ���� return ���ִ� sum �Լ��� ���� ������ ���� modify �Լ� ����

class Node {
public:
    Node(int left, int right) {

        this->left = left;
        this->right = right;
        mid = (left + right) >> 1;
        sum = 0;
        leftNode = NULL;
        rightNode = NULL;

    }
    int left, right, mid, sum;
    Node* leftNode, * rightNode;
};
typedef std::pair<int, int> pairi2; //int �� �� ��ü�� ���� ��ü�� ó�� ����

class SegmentTree1D {

public:
    SegmentTree1D(int n) {
        //n�� ������ ��ŭ �Ҵ�
        this->n = n;
        m = 1;
        int temp = n;
        while (temp) {
            m <<= 1;
            temp >>= 1;
        }

        array = new int[n];
        cum_array = new int[n];
        root = new Node(0, n - 1);
        
    }

    // �ʱ�ȭ
    void initialize() {
        int sum = 0;
        for (int i = 0; i < n; i++) {
            sum += array[i];
            cum_array[i] = sum;
        }
        makeSeg(root, 0, n - 1);


    }
    void makeSeg(Node *node,int x, int y) {
        if (x == y) {
            node->sum = array[x];
            
        }
        else {
            
            Node *leftN = new Node(x, node->mid);
            Node* rightN = new Node(node->mid + 1, y);
            
            makeSeg(leftN, x, node->mid);
            makeSeg(rightN, node->mid + 1, y);
            
            node->leftNode = leftN;
            node->rightNode = rightN;
            node->sum = leftN->sum + rightN->sum;

            
        }
    }
    
    int sum(int x, int y) {
        /*
            x���� y ������ ��
        */
        return segSum(*root, x, y);
        
    }
    int segSum(Node node, int x, int y) {
        if (x > node.right || y < node.left) return 0;
        if (x <= node.left && node.right <= y) return node.sum;
        int leftResult = segSum(*node.leftNode, x, node.mid);
        int rightResult = segSum(*node.leftNode, node.mid + 1, y);
        return leftResult + rightResult;
    }

    void modify(int idx, int num) {
        /*
            idx�� ��ġ�� ���Ҹ� num���� ��ü
        */
        int ch = num-array[idx];
        Node* node = root;
        
        while (1) {
            if (node->left == node->right) break;

            if (node->left <= idx && node->right >= idx) {
                node->sum += ch;
            }
            if (node->mid < idx) {
                node = node->rightNode;
            }
            else {
                node = node->leftNode;
            }
        }


    }




    int n;
    int m;
    int* array;
    int* cum_array;
    Node* root;
};

int main() {

    int n, m;
    FILE* in = fopen("input_assignment1.txt", "r");
    
    fscanf(in, "%d", &n);
    SegmentTree1D A(n);

    int temp;
    for (int i = 0; i < n; i++) {
        fscanf(in, "%d", &temp);
        printf("%d ", temp);
        A.array[i] = temp;
    }
    printf("\n");

    A.initialize();

    fscanf(in, "%d", &m);
    for (int i = 0; i < m; i++) {

        fscanf(in, "%d\n", &temp);

        if (temp == 0) {
            int st, ed;
            fscanf(in, "%d %d", &st, &ed);
            printf("sum (%d,%d): %d\n", st, ed, A.sum(st, ed));

        }
        else {
            int idx, num;
            fscanf(in, "%d %d", &idx, &num);
            printf("change %dth elem with %d\n", idx + 1, num);
            A.modify(idx, num);
        }
    }

    return 0;

}