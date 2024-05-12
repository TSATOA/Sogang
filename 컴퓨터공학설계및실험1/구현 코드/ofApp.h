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


//dsf에서 사용할 인접 리스트를 구현하기 위한 노드 선언
typedef struct _Node {
	int vertex;
	int cnt;
	struct _Node *next;
}Node;

class ofApp : public ofBaseApp {

	public:
		//기본적인 설정 함수
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


		void freeMemory(); //할당된 메모리 초기화 함수
		void makemaze1(); //미로1을 만드는 함수
		void makemaze2(); //미로2를 만드는 함수
		void makelist(); // dfs에 사용할 인접리스트를 만드는 함수(이차원배열에서 인접리스트로 변경)
		void sync(int **maze, char **frame, int xa, int ya); // dfs에서 동기화하는 작업(maze의 인접한 숫자 동일화)
		void DFS1(); // 미로 1의 dfs 함수
		void DFS2(); // 미로 2의 dfs 함수
		void dfsdraw(); //미로1과 미로2의 dfs경로 그리는 함수
		void ENDP(); // 프로그램이 종료할 때 시행하는 함수

		int HEIGHT;//미로의 높이
		int WIDTH;//미로의 너비
		double timeresult; //걸린 시간
		//두 미로의 정보
		char** frame1;//미로 벽의 이차원 배열
		char** frame2;
		//DFS를 위한 자료구조
		Node **mazelist1;
		Node **mazelist2;
		//DFS
		int* visited1; //방문여부를 저장할 포인터
		int* visited2;
		int* stack1; // 최단 경로를 저장하는 포인터
		int* stack2;
		int* path1; // 다녀온 경로를 저장하는 포인터
		int* path2;
		int top1 = -1; // dfs에서 stack에 쌓인 개수
		int ptop1 = -1; // dfs에서 path에 쌓인 개수
		int top2 = -1;
		int ptop2 = -1;
		//사용자의 위치
		int maze_y=0;//미로칸의 열의 인덱스를 가리킨다.
		int maze_x=0;//미로칸의 행의 인덱스를 가리킨다.
		int midstart, midend; //랜덤으로 정해진 미로간 이동 통로
		int page = 0; //미로의 위치를 나타내는 변수(maze1과 maze2)
		int k=0; //프로그램의 종료 단계에서 함수를 한번만 실행시키기 위해 지정한 변수
		time_t start, end; //프로그램이 작동할 때 시간을 측정하는 변수
		int isOpen=0; //프로그램의 진행을 나타낸다.
		int isDFS=0;//DFS함수를 실행시켰는지 판단하는 변수. 0이면 실행안했고 1이면 실행했다.
		int isBFS;//BFS함수를 실행시켰는지 판단하는 변수. 0이면 실행안했고 1이면 실행했다.
		int isEND = 0; //프로그램의 종료를 판단하는 변수

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
