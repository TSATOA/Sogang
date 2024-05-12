/*

	ofxWinMenu basic example - ofApp.h

	Copyright (C) 2016-2017 Lynn Jarvis.

	http://www.spout.zeal.co

	=========================================================================
	This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
	=========================================================================
*/

	#pragma once

#include "ofMain.h"
#include "ofxWinMenu.h" // Menu addon


//dsf���� ����� ���� ����Ʈ�� �����ϱ� ���� ��� ����
typedef struct _Node {
	int vertex;
	int cnt;
	struct _Node *next;
}Node;

class ofApp : public ofBaseApp {

	public:
		//�⺻���� ���� �Լ�
		void setup();
		void update();
		void draw();

		void keyPressed(int key); // Traps escape key if exit disabled
		void keyReleased(int key);
		void mouseMoved(int x, int y);
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);


		void freeMemory(); //�Ҵ�� �޸� �ʱ�ȭ �Լ�
		void makemaze1(); //�̷�1�� ����� �Լ�
		void makemaze2(); //�̷�2�� ����� �Լ�
		void makelist(); // dfs�� ����� ��������Ʈ�� ����� �Լ�(�������迭���� ��������Ʈ�� ����)
		void sync(int **maze, char **frame, int xa, int ya); // dfs���� ����ȭ�ϴ� �۾�(maze�� ������ ���� ����ȭ)
		void DFS1(); // �̷� 1�� dfs �Լ�
		void DFS2(); // �̷� 2�� dfs �Լ�
		void dfsdraw(); //�̷�1�� �̷�2�� dfs��� �׸��� �Լ�
		void ENDP(); // ���α׷��� ������ �� �����ϴ� �Լ�

		int HEIGHT;//�̷��� ����
		int WIDTH;//�̷��� �ʺ�
		double timeresult; //�ɸ� �ð�
		//�� �̷��� ����
		char** frame1;//�̷� ���� ������ �迭
		char** frame2;
		//DFS�� ���� �ڷᱸ��
		Node **mazelist1;
		Node **mazelist2;
		//DFS
		int* visited1; //�湮���θ� ������ ������
		int* visited2;
		int* stack1; // �ִ� ��θ� �����ϴ� ������
		int* stack2;
		int* path1; // �ٳ�� ��θ� �����ϴ� ������
		int* path2;
		int top1 = -1; // dfs���� stack�� ���� ����
		int ptop1 = -1; // dfs���� path�� ���� ����
		int top2 = -1;
		int ptop2 = -1;
		//������� ��ġ
		int maze_y=0;//�̷�ĭ�� ���� �ε����� ����Ų��.
		int maze_x=0;//�̷�ĭ�� ���� �ε����� ����Ų��.
		int midstart, midend; //�������� ������ �̷ΰ� �̵� ���
		int page = 0; //�̷��� ��ġ�� ��Ÿ���� ����(maze1�� maze2)
		int k=0; //���α׷��� ���� �ܰ迡�� �Լ��� �ѹ��� �����Ű�� ���� ������ ����
		time_t start, end; //���α׷��� �۵��� �� �ð��� �����ϴ� ����
		int isOpen=0; //���α׷��� ������ ��Ÿ����.
		int isDFS=0;//DFS�Լ��� ������״��� �Ǵ��ϴ� ����. 0�̸� ������߰� 1�̸� �����ߴ�.
		int isBFS;//BFS�Լ��� ������״��� �Ǵ��ϴ� ����. 0�̸� ������߰� 1�̸� �����ߴ�.
		int isEND = 0; //���α׷��� ���Ḧ �Ǵ��ϴ� ����

		// Menu
		ofxWinMenu * menu; // Menu object
		void appMenuFunction(string title, bool bChecked); // Menu return function

		// Used by example app
		ofTrueTypeFont myFont;
        ofImage myImage;
		float windowWidth, windowHeight;
		HWND hWnd; // Application window
		HWND hWndForeground; // current foreground window

		// Example menu variables
		bool bShowInfo;
		bool bFullscreen;
		bool bTopmost;
		bool isdfs;
		// Example functions
 		void doFullScreen(bool bFull);
		void doTopmost(bool bTop);

};
