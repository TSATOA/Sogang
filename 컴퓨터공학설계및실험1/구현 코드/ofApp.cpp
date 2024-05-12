/*

	ofxWinMenu basic example - ofApp.cpp

	Example of using ofxWinMenu addon to create a menu for a Microsoft Windows application.
	
	Copyright (C) 2016-2017 Lynn Jarvis.

	https://github.com/leadedge

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

	03.11.16 - minor comment cleanup
	21.02.17 - rebuild for OF 0.9.8

*/
#include "ofApp.h"
#include <iostream>
using namespace std;
//--------------------------------------------------------------
//기본적인 설정
void ofApp::setup() {
	scanf("%d%d", &HEIGHT, &WIDTH); //미로의 높이와 너비를 입력받는다
	ofSetWindowTitle("Maze Example"); // Set the app name on the title bar
	//프레임 속도와 배경색 지정
	ofSetFrameRate(15);
	ofBackground(255, 255, 255);
	// Get the window size for image loading
	//창의 높이 너비 값 획득
	windowWidth = ofGetWidth();
	windowHeight = ofGetHeight();
	isdfs = false;
	
	// Centre on the screen
	ofSetWindowPosition((ofGetScreenWidth()-windowWidth)/2, (ofGetScreenHeight()-windowHeight)/2);

	// Load a font rather than the default
	myFont.loadFont("verdana.ttf", 12, true, true);

	// Load an image for the example
	//myImage.loadImage("lighthouse.jpg");

	// Window handle used for topmost function
	hWnd = WindowFromDC(wglGetCurrentDC());

	// Disable escape key exit so we can exit fullscreen with Escape (see keyPressed)
	ofSetEscapeQuitsApp(false);

	//
	// Create a menu using ofxWinMenu
	//

	// A new menu object with a pointer to this class
	menu = new ofxWinMenu(this, hWnd);

	// Register an ofApp function that is called when a menu item is selected.
	// The function can be called anything but must exist. 
	// See the example "appMenuFunction".
	menu->CreateMenuFunction(&ofApp::appMenuFunction);

	// Create a window menu
	HMENU hMenu = menu->CreateWindowMenu();

	//
	// Create  menu
	//
	//메뉴선택(Exit,Full screen,About .etc)
	HMENU hPopup = menu->AddPopupMenu(hMenu, "File");

	menu->AddPopupItem(hPopup, "Exit", false, false);
	bFullscreen = false; // not fullscreen yet
	menu->AddPopupItem(hPopup, "Full screen", false, false);
	
	hPopup = menu->AddPopupMenu(hMenu, "Help");
	menu->AddPopupItem(hPopup, "About", false, false); // No auto check

	// Set the menu to the window
	menu->SetWindowMenu();


	/*미로의 공간할당*/
	frame1 = (char**)malloc(sizeof(char*)*HEIGHT * 2 + 1);
	frame2 = (char**)malloc(sizeof(char*)*HEIGHT * 2 + 1);
	for (int i = 0; i < HEIGHT * 2 + 1; i++) {
		frame1[i] = (char*)malloc(sizeof(char)*WIDTH * 2 + 1);
		frame2[i] = (char*)malloc(sizeof(char)*WIDTH * 2 + 1);
	}
	//미로1,2 생성
	makemaze1();
	makemaze2();
	//생성된 미로 인접리스트로 표현
	makelist();
	
	//끝이 아니면 정상적으로 진행
	if (isEND == 0) {
		isOpen = 1;
	}
	else {
		isOpen = 0;
	}
	//미로 1,2 랜덤 연결 통로 위치
	midstart = rand() % HEIGHT;
	midend = rand() % HEIGHT;

	//깊이 우선 탐색을 통한 최단 경로
	DFS1();
	DFS2();
	//게임 시작! 시간 측정 시작!
	printf("Game Start!\n");
	start = time(NULL);
} // end Setup


//
// Menu function
//
// This function is called by ofxWinMenu when an item is selected.
// The the title and state can be checked for required action.
// 
//메뉴에 관한 함수
void ofApp::appMenuFunction(string title, bool bChecked) {

	ofFileDialogResult result;
	string filePath;
	size_t pos;

	

	if(title == "Exit") {
		ofExit(); // Quit the application
	}


	if(title == "Full screen") {
		bFullscreen = !bFullscreen; // Not auto-checked and also used in the keyPressed function
		doFullScreen(bFullscreen); // But als take action immediately
	}


	//
	// Help menu
	//
	if(title == "About") {
		ofSystemAlertDialog("ofxWinMenu\nbasic example\n\nhttp://spout.zeal.co");
	}

} // end appMenuFunction


//--------------------------------------------------------------
void ofApp::update() {

}


//--------------------------------------------------------------
//가장 많은 역할을 하는 draw함수 -> 매 프레임 마다 변화한 동작을 표현
void ofApp::draw() {


	char ti[256];
	char str[256];
	char title[256];
	//ofBackground(0, 0, 0, 0);
	ofSetColor(100);
	ofSetLineWidth(5);
	int i, j, z=0;
	Node *b;
	
	// TO DO : DRAW MAZE; 

	//높이와 너비를 정상적으로 받으면 실행
	if (isOpen==1) {
		
		ofNoFill();
		//인접 리스트로 표현한 미로를 출력
		//격자 틀 출력
		for (i = 0; i < HEIGHT; i++) {
			for (j = 0; j < WIDTH; j++) {
				ofSetColor(100);
				ofDrawRectangle(j * 40 + 100, i * 40 + 50, 40, 40);
				b = mazelist1[i*WIDTH + j];
				ofSetColor(255);
				//빈 벽 제거
				while (b->next != NULL) {
					b = b->next;
					if (b->vertex == i * WIDTH + j + 1)
						ofDrawLine(j * 40 + 40 + 100, i * 40 + 2.5 + 50, j * 40 + 40 + 100, i * 40 + 40 + 50 - 2.5);
					if (b->vertex == i * WIDTH + j - 1)
						ofDrawLine(j * 40 + 100, i * 40 + 50+2.5, j * 40 + 100, i * 40 + 40 + 50-2.5);
					if (b->vertex == i * WIDTH + j - WIDTH)
						ofDrawLine(j * 40 + 100+2.5, i * 40 + 50, j * 40 + 40 + 100-2.5, i * 40 + 50);
					if (b->vertex == i * WIDTH + j + WIDTH)
						ofDrawLine(j * 40 + 100+2.5, i * 40 + 40 + 50, j * 40 + 100 + 40 - 2.5, i * 40 + 40 + 50);
				}
			}
		}
		//위와 같은 과정으로 미로2 출력
		for (i = 0; i < HEIGHT; i++) {
			for (j = 0; j < WIDTH; j++) {
				ofSetColor(100);
				ofDrawRectangle(j * 40 + 100, i * 40 + 200 + HEIGHT*40, 40, 40);
				b = mazelist2[i*WIDTH + j];
				ofSetColor(255);
				while (b->next != NULL) {
					b = b->next;
					if (b->vertex == i * WIDTH + j + 1)
						ofDrawLine(j * 40 + 40 + 100, i * 40 + 2.5 + 200 + HEIGHT * 40, j * 40 + 40 + 100, i * 40 + 40 + 200 - 2.5 + HEIGHT * 40);
					if (b->vertex == i * WIDTH + j - 1)
						ofDrawLine(j * 40 + 100, i * 40 + 200 + 2.5 + HEIGHT * 40, j * 40 + 100, i * 40 + 40 + 200 - 2.5 + HEIGHT * 40);
					if (b->vertex == i * WIDTH + j - WIDTH)
						ofDrawLine(j * 40 + 100 + 2.5, i * 40 + 200 + HEIGHT * 40, j * 40 + 40 + 100 - 2.5, i * 40 + 200 + HEIGHT * 40);
					if (b->vertex == i * WIDTH + j + WIDTH)
						ofDrawLine(j * 40 + 100 + 2.5, i * 40 + 40 + 200 + HEIGHT * 40, j * 40 + 100 + 40 - 2.5, i * 40 + 40 + 200 + HEIGHT * 40);
				}
			}
		}
		// 연결 통로 입구와 출구 제거
		ofDrawLine(100  + WIDTH * 40, 50  + midstart * 40, 100 + WIDTH * 40, 50  + midstart * 40 + 40);
		ofDrawLine(100 , 200  + HEIGHT*40 + midend * 40, 100 , 200  + HEIGHT*40 + midend * 40 + 40);

		//시작점과 끝점 표현
		ofSetColor(0, 0, 255);
		ofDrawRectangle(120, 70, 5, 5);

		ofSetColor(0, 255, 0);
		ofDrawRectangle((WIDTH-1) * 40 + 20 + 100 -2.5, 20 + (HEIGHT - 1) * 40 + HEIGHT * 40 + 200 -2.5, 5, 5);
		
		//연결 통로 출력
		ofSetColor(100);
		ofDrawLine(100 + WIDTH * 40 - 2.5, 50 + midstart * 40, 100 + WIDTH * 40 + 80, 50 + midstart * 40);
		ofDrawLine(100 + WIDTH * 40 - 2.5, 50 + midstart * 40 + 40, 100 + WIDTH * 40 + 40, 50 + midstart * 40 + 40);
		ofDrawLine(100 + WIDTH * 40 + 80, 50 + midstart * 40, 100 + WIDTH * 40 + 80, 50 + HEIGHT * 40 + 95);
		ofDrawLine(100 + WIDTH * 40 + 40, 50 + midstart * 40 + 40, 100 + WIDTH * 40 + 40, 50 + HEIGHT * 40 + 55);
		ofDrawLine(20, 50 + HEIGHT * 40 + 55, 100 + WIDTH * 40 + 40, 50 + HEIGHT * 40 + 55);
		ofDrawLine(60, 50 + HEIGHT * 40 + 95, 100 + WIDTH * 40 + 80, 50 + HEIGHT * 40 + 95);
		ofDrawLine(20, 50 + HEIGHT * 40 + 55, 20, 200 + HEIGHT * 40 + midend * 40 + 40);
		ofDrawLine(60, 50 + HEIGHT * 40 + 95, 60, 200 + HEIGHT * 40 + midend * 40);
		ofDrawLine(20, 200 + HEIGHT * 40 + midend * 40 + 40, 100 + 2.5, 200 + HEIGHT * 40 + midend * 40 + 40);
		ofDrawLine(60, 200 + HEIGHT * 40 + midend * 40, 100 + 2.5, 200 + HEIGHT * 40 + midend * 40 );
		
		//사용자의 말(캐릭터) 표현
		//page=0은 미로1, page=1은 미로2에 있는 상태
		ofFill();
		ofSetColor(255, 0, 0);
		if (page == 0) {
			ofDrawRectangle(maze_x * 40 + 110, maze_y * 40 + 60, 20, 20);
		}
		else {
			ofDrawRectangle(maze_x * 40 + 110, maze_y * 40 + 210 + HEIGHT * 40, 20, 20);
		}
		//미로의 통로 워프
		ofSetColor(100);
		if (page==0 && maze_x == WIDTH - 1 && maze_y == midstart) {
			page = 1;
			maze_x = 0;
			maze_y = midend;
		}
		//u키를 누를 경우 isDFS=1, 방향키를 누를 경우 isDFS=0 / 최단 경로 힌트
		if (isDFS == 1) {
			dfsdraw();
		}
		//실시간 시간 출력
		end = time(NULL);
		timeresult = (double)(end - start);
		sprintf(ti, "%.0f Seconds!", timeresult);
		myFont.drawString(ti, ofGetWidth() / 2 + 150, 30);
		
	}
	//종점 도달 시 최종 시간 출력 밑 종료
	if (page == 1 && maze_x == WIDTH - 1 && maze_y == HEIGHT - 1) {
		isEND = 1;
		isOpen = 0;
		if (z == 0)
			ENDP();
		z++;

		sprintf(ti, "The time you took is %.0f Seconds!", timeresult);
		myFont.drawString(ti, ofGetWidth() / 2 - 120, ofGetHeight() / 2);
	}
	
	//사실 여기는 필요 없는 부분(지워도 된다.ㅎㅎ)
	if (isdfs)
	{
		ofSetColor(200);
		ofSetLineWidth(5);
		if (isOpen)
			dfsdraw();
		else
			cout << "You must open file first" << endl;
	}
	//제목과 컴실 프로젝트 글씨 출력
	if(bShowInfo) {
		// Show keyboard duplicates of menu functions
		sprintf(title, "%d X %d Double Race!",HEIGHT,WIDTH);
		myFont.drawString(title, ofGetWidth() / 2 - 70, 30 );
		sprintf(str, " comsil project");
		myFont.drawString(str, 15, ofGetHeight()-20);
	}
	
} // end Draw

//풀 스크린
void ofApp::doFullScreen(bool bFull)
{
	// Enter full screen
	if(bFull) {
		// Remove the menu but don't destroy it
		menu->RemoveWindowMenu();
		// hide the cursor
		ofHideCursor();
		// Set full screen
		ofSetFullscreen(true);
	}
	else { 
		// return from full screen
		ofSetFullscreen(false);
		// Restore the menu
		menu->SetWindowMenu();
		// Restore the window size allowing for the menu
		ofSetWindowShape(windowWidth, windowHeight + GetSystemMetrics(SM_CYMENU)); 
		// Centre on the screen
		ofSetWindowPosition((ofGetScreenWidth()-ofGetWidth())/2, (ofGetScreenHeight()-ofGetHeight())/2);
		// Show the cursor again
		ofShowCursor();
		// Restore topmost state
		if(bTopmost) doTopmost(true);
	}

} // end doFullScreen


void ofApp::doTopmost(bool bTop)
{
	if(bTop) {
		// get the current top window for return
		hWndForeground = GetForegroundWindow();
		// Set this window topmost
		SetWindowPos(hWnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE); 
		ShowWindow(hWnd, SW_SHOW);
	}
	else {
		SetWindowPos(hWnd, HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
		ShowWindow(hWnd, SW_SHOW);
		// Reset the window that was topmost before
		if(GetWindowLong(hWndForeground, GWL_EXSTYLE) & WS_EX_TOPMOST)
			SetWindowPos(hWndForeground, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE); 
		else
			SetWindowPos(hWndForeground, HWND_TOP, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE); 
	}
} // end doTopmost


//--------------------------------------------------------------
//키 입력
void ofApp::keyPressed(int key) {
	//영어로 설명되어 있고 이전 프로젝트에서 동일하게 제시된 곳은 생략
	// Escape key exit has been disabled but it can be checked here
	if(key == VK_ESCAPE) {
		// Disable fullscreen set, otherwise quit the application as usual
		if(bFullscreen) {
			bFullscreen = false;
			doFullScreen(false);
		}
		else {
			ofExit();
		}
	}

	// Remove or show screen info
	if(key == ' ') {
		bShowInfo = !bShowInfo;
		// Update the menu check mark because the item state has been changed here
		menu->SetPopupItem("Show DFS", bShowInfo);
	}

	if(key == 'f') {
		bFullscreen = !bFullscreen;	
		doFullScreen(bFullscreen);
		// Do not check this menu item
		// If there is no menu when you call the SetPopupItem function it will crash
	}

} // end keyPressed

//--------------------------------------------------------------
//키입력
void ofApp::keyReleased(int key){
	//오른쪽 방향키 플레이어 우측 이동
	if (key == OF_KEY_RIGHT) {
		if (page == 0) {
			if (maze_x < WIDTH - 1 && frame1[maze_y * 2 + 1][maze_x * 2 + 2] == ' ') 
				maze_x++;
		}
		else {
			if (maze_x < WIDTH - 1 && frame2[maze_y * 2 + 1][maze_x * 2 + 2] == ' ') 
				maze_x++;
		}
		isDFS = 0;
	}
	//왼쪽 방향키 플레이어 좌측 이동
	if (key == OF_KEY_LEFT) {
		if (page == 0) {
			if (maze_x > 0 && frame1[maze_y * 2 + 1][maze_x * 2 ] == ' ')
				maze_x--;
		}
		else {
			if (maze_x > 0 && frame2[maze_y * 2 + 1][maze_x * 2 ] == ' ')
				maze_x--;
		}
		isDFS = 0;
	}
	//윗쪽 방향키 플레이어 상측 이동
	if (key == OF_KEY_UP) {
		if (page == 0) {
			if (maze_y > 0 && frame1[maze_y * 2 ][maze_x * 2 + 1] == ' ')
				maze_y--;
		}
		else {
			if (maze_y >0 && frame2[maze_y * 2 ][maze_x * 2 + 1] == ' ')
				maze_y--;
		}
		isDFS = 0;
	}
	//아래쪽 방향키 플레이어 하측 이동
	if (key == OF_KEY_DOWN) {
		if (page == 0) {
			if (maze_y < HEIGHT -1 && frame1[maze_y * 2 +2][maze_x * 2 + 1] == ' ')
				maze_y++;
		}
		else {
			if (maze_y < HEIGHT -1 && frame2[maze_y * 2 +2][maze_x * 2 + 1] == ' ')
				maze_y++;
		}
		isDFS = 0;
	}
	//U키 입력시 최단경로를 보여주는 힌트 제공
	if (key == 'U' || key == 'u') {
		isDFS = 1;
	}
	//Q키 입력 시 메모리를 초기화하고 종료
	if (key == 'Q' || key == 'q') {
		//freeMemory();
		_Exit(0);
	}
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

void ofApp::freeMemory() {


	// malloc한 memory를 free해주는 함수
	int i;
	Node *prev = NULL;
	Node *cur;
	free(visited1);
	free(visited2);
	free(stack1);
	free(stack2);
	free(path1);
	free(path2);
	printf("asdf");
	for (i = 0; i < HEIGHT*2+1; i++) {
		free(frame1[i]);
		free(frame2[i]);
	}
	free(frame1);
	free(frame2);
	
	for (i = 0; i < HEIGHT*WIDTH; i++) {
		cur = mazelist1[i];
		while (cur) {
			prev = cur;
			cur = cur->next;
			free(prev);
		}
	}
	free(mazelist1);
	for (i = 0; i < HEIGHT*WIDTH; i++) {
		cur = mazelist2[i];
		while (cur) {
			prev = cur;
			cur = cur->next;
			free(prev);
		}
	}
	free(mazelist2);
}
//깊이 우선 탐색을 통한 최단 경로 추출
void ofApp::DFS1()//DFS탐색을 하는 함수
{
	//경로,최단경로,방문이력 동적할당
	visited1 = (int *)malloc(sizeof(int)*HEIGHT*WIDTH);
	stack1 = (int *)malloc(sizeof(int)*HEIGHT*WIDTH);
	path1 = (int *)malloc(sizeof(int)*((WIDTH - 1)*HEIGHT + (HEIGHT - 1)*WIDTH));
	
	int i;
	int dis = 0;
	Node *temp;
	//초기화
	for (i = 0; i < HEIGHT*WIDTH; i++) {
		visited1[i] = 0;
		stack1[i] = -1;
	}
	//처음 스택 저장
	stack1[++top1] = mazelist1[0]->vertex;
	path1[++ptop1] = mazelist1[0]->vertex;
	visited1[0] = 1;
	//깊이 우선 탐색 과정
	while (top1 != -1) {
		//maze2로 이동하는 통로 도착 시 종료
		if (stack1[top1] == WIDTH * (midstart+1) - 1) break;
		temp = mazelist1[stack1[top1]];
		dis = 0;
		for (i = 0; i < mazelist1[stack1[top1]]->cnt; i++) {
			if (visited1[temp->next->vertex] == 0) {
				temp = temp->next;
				dis = 1;
				break;
			}
			temp = temp->next;
		}
		if (dis == 0) {
			stack1[top1--] = -1;
			path1[++ptop1] = stack1[top1];
		}
		else {
			stack1[++top1] = temp->vertex;
			visited1[temp->vertex] = 1;
			path1[++ptop1] = stack1[top1];
		}

	}


	return ;
}
//maze2의 깊이우선탐색(위 과정과 매우 유사)
void ofApp::DFS2()
{
	
	visited2 = (int *)malloc(sizeof(int)*HEIGHT*WIDTH);
	stack2 = (int *)malloc(sizeof(int)*HEIGHT*WIDTH);
	path2 = (int *)malloc(sizeof(int)*((WIDTH - 1)*HEIGHT + (HEIGHT - 1)*WIDTH));
	int i;
	int dis = 0;
	Node *temp;
	for (i = 0; i < HEIGHT*WIDTH; i++) {
		visited2[i] = 0;
		stack2[i] = -1;
	}
	stack2[++top2] = mazelist2[WIDTH*midend]->vertex;
	path2[++ptop2] = mazelist2[WIDTH*midend]->vertex;
	visited2[WIDTH*midend] = 1;

	while (top2 != -1) {
		if (stack2[top2] == WIDTH * HEIGHT - 1) break;
		temp = mazelist2[stack2[top2]];
		dis = 0;
		for (i = 0; i < mazelist2[stack2[top2]]->cnt; i++) {
			if (visited2[temp->next->vertex] == 0) {
				temp = temp->next;
				dis = 1;
				break;
			}
			temp = temp->next;
		}
		if (dis == 0) {
			stack2[top2--] = -1;
			path2[++ptop2] = stack2[top2];
		}
		else {
			stack2[++top2] = temp->vertex;
			visited2[temp->vertex] = 1;
			path2[++ptop2] = stack2[top2];
		}

	}

	
	return ;
	
}

//깊이 우선 탐색 결과 출력
void ofApp::dfsdraw()
{

	int i;
	ofSetColor(0, 0, 150);
	ofSetLineWidth(5);
	for (i = 0; i < top1; i++) {
		ofDrawLine(120 +stack1[i] % WIDTH * 40, 70 + stack1[i] / WIDTH * 40, 120 + stack1[i + 1] % WIDTH * 40, 70 + stack1[i + 1] / WIDTH * 40);
	}
	
	for (i = 0; i < top2; i++) {
		ofDrawLine(120 + stack2[i] % WIDTH * 40,HEIGHT*40 + 220 + stack2[i] / WIDTH * 40, 120 + stack2[i + 1] % WIDTH * 40,HEIGHT*40 + 220 + stack2[i + 1] / WIDTH * 40);
	}

	

}
//maze1 frame1 생성(이차원 배열)
void ofApp::makemaze1()
{
	int **maze;
	int i, j;
	int z=1;
	int cnt = 0;
	int combine_rand, inc_rand;
	//미로 동적 할당
	maze = (int**)malloc(sizeof(int*)*HEIGHT);

	for (i = 0; i < HEIGHT; i++) 
		maze[i] = (int*)malloc(sizeof(int)*WIDTH);
	
	//랜덤 설정 및 이동 통로 입구 설정
	srand((unsigned)time(NULL));
	midstart = rand() % HEIGHT;
	//미로 초기(첫 줄)
	for (i = 0; i < WIDTH; i++) {
		maze[0][i] = z;
		z++;
	}
	for (i = 0; i < WIDTH * 2 + 1; i++) {
		if (i % 2 == 0) {
			frame1[0][i] = '+';
			frame1[1][i] = '|';
			frame1[2][i] = '+';
		}
		else {
			frame1[0][i] = '-';
			frame1[1][i] = ' ';
			frame1[2][i] = '-';
		}
	}
	//반복 과정 시작
	for (i = 0; i < HEIGHT - 1; i++) {
		//중간1 벽제거
		for (j = 0; j < WIDTH - 1; j++) {
			combine_rand = rand() % 2;
			if (maze[i][j] != maze[i][j + 1]) {
				if (combine_rand == 1) {
					frame1[i * 2 + 1][j * 2 + 2] = ' ';
				}
				sync(maze, frame1, j, i);
			}
		}
		//중간2 늘리기
		cnt = 0;
		for (j = 0; j < WIDTH; j++) {
			inc_rand = rand() % 2;
			if (inc_rand == 1) {
				if (j != 0 && maze[i][j] == maze[i][j - 1] && maze[i + 1][j - 1] != z - 1) {
					maze[i + 1][j] = z;
					z++;
				}
				else {
					maze[i + 1][j] = maze[i][j];
					cnt++;
				}
			}
			else {
				if (j == 0 && maze[i][j] != maze[i][j + 1]) {
					maze[i + 1][j] = maze[i][j];
					cnt = 0;
				}
				else if (j == WIDTH - 1 && cnt==0) {
					maze[i + 1][j] = maze[i][j];
					cnt = 0;
				}
				else if (j != 0 && j != WIDTH - 1 && cnt == 0 && maze[i][j] != maze[i][j + 1]) {
					maze[i + 1][j] = maze[i][j];
					cnt = 0;
				}
				else if (cnt != 0 && j != WIDTH - 1 && maze[i][j + 1] != maze[i][j]) {
					maze[i + 1][j] = z;
					z++;
					cnt = 0;
				}
				else {
					maze[i + 1][j] = z;
					z++;
				}
				
			}
			
			if (j != WIDTH - 1 && maze[i][j] != maze[i][j + 1]) cnt = 0;
		}
		//중간3 아래벽깨기
		for (j = 0; j < WIDTH; j++)
			if (maze[i][j] == maze[i + 1][j])
				frame1[i * 2 + 2][j * 2 + 1] = ' ';

		//중간4 벽만들기
		for (j = 0; j < WIDTH * 2 + 1; j++) {
			if (j % 2 == 0) {
				frame1[i * 2 + 3][j] = '|';
				frame1[i * 2 + 4][j] = '+';
			}
			else {
				frame1[i * 2 + 3][j] = ' ';
				frame1[i * 2 + 4][j] = '-';
			}
		}

	}
	//끝 옆벽깨기
	for (i = 0; i < WIDTH - 1; i++) {
		if (maze[HEIGHT - 1][i] != maze[HEIGHT - 1][i + 1]) {
			frame1[HEIGHT * 2 - 1][i * 2 + 2] = ' ';
			sync(maze, frame1, i, HEIGHT - 1);
		}
	}
	

}
//maze2 frame2 생성(위 과정과 매우 유사)
void ofApp::makemaze2()
{
	int **maze;
	int i, j;
	int z = 1;
	int cnt = 0;
	int combine_rand, inc_rand;
	maze = (int**)malloc(sizeof(int*)*HEIGHT);

	for (i = 0; i < HEIGHT; i++)
		maze[i] = (int*)malloc(sizeof(int)*WIDTH);
	//연결 통로 출구(maze2로 입장하는 입구) 지정
	midend = rand() % HEIGHT;
	//미로 초기
	for (i = 0; i < WIDTH; i++) {
		maze[0][i] = z;
		z++;
	}
	for (i = 0; i < WIDTH * 2 + 1; i++) {
		if (i % 2 == 0) {
			frame2[0][i] = '+';
			frame2[1][i] = '|';
			frame2[2][i] = '+';
		}
		else {
			frame2[0][i] = '-';
			frame2[1][i] = ' ';
			frame2[2][i] = '-';
		}
	}
	//반복 과정 시작
	for (i = 0; i < HEIGHT - 1; i++) {
		//중간1 벽제거
		for (j = 0; j < WIDTH - 1; j++) {
			combine_rand = rand() % 2;
			if (maze[i][j] != maze[i][j + 1]) {
				if (combine_rand == 1) {
					frame2[i * 2 + 1][j * 2 + 2] = ' ';
				}
				sync(maze, frame2, j, i);
			}
		}
		//중간2 늘리기
		cnt = 0;
		for (j = 0; j < WIDTH; j++) {
			inc_rand = rand() % 2;
			if (inc_rand == 1) {
				if (j != 0 && maze[i][j] == maze[i][j - 1] && maze[i + 1][j - 1] != z - 1) {
					maze[i + 1][j] = z;
					z++;
				}
				else {
					maze[i + 1][j] = maze[i][j];
					cnt++;
				}
			}
			else {
				if (j == 0 && maze[i][j] != maze[i][j + 1]) {
					maze[i + 1][j] = maze[i][j];
					cnt = 0;
				}
				else if (j == WIDTH - 1 && cnt==0) {
					maze[i + 1][j] = maze[i][j];
					cnt = 0;
				}
				else if (j != 0 && j != WIDTH - 1 && cnt == 0 && maze[i][j] != maze[i][j + 1]) {
					maze[i + 1][j] = maze[i][j];
					cnt = 0;
				}
				else if (cnt != 0 && j != WIDTH - 1 && maze[i][j + 1] != maze[i][j]) {
					maze[i + 1][j] = z;
					z++;
					cnt = 0;
				}
				else {
					maze[i + 1][j] = z;
					z++;
				}
				
			}
			
			if (j != WIDTH - 1 && maze[i][j] != maze[i][j + 1]) cnt = 0;
		}
		//중간3 아래벽깨기
		for (j = 0; j < WIDTH; j++)
			if (maze[i][j] == maze[i + 1][j])
				frame2[i * 2 + 2][j * 2 + 1] = ' ';

		//중간4 벽만들기
		for (j = 0; j < WIDTH * 2 + 1; j++) {
			if (j % 2 == 0) {
				frame2[i * 2 + 3][j] = '|';
				frame2[i * 2 + 4][j] = '+';
			}
			else {
				frame2[i * 2 + 3][j] = ' ';
				frame2[i * 2 + 4][j] = '-';
			}
		}

	}
	//끝 옆벽깨기
	for (i = 0; i < WIDTH - 1; i++) {
		if (maze[HEIGHT - 1][i] != maze[HEIGHT - 1][i + 1]) {
			frame2[HEIGHT * 2 - 1][i * 2 + 2] = ' ';
			sync(maze, frame2, i, HEIGHT - 1);
		}
	}
	
}

//깊이 우선 탐색 과정에서 사용하는 동기화 함수(maze에서 인접한 숫자 일치시키는 과정)
void ofApp::sync(int **maze, char **frame, int xa, int ya)
{
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
//위 과정에서 생성된 frame1,2를 이용하여 인접리스트 생성
void ofApp::makelist() {
	Node *a;
	int i, j;
	int v;
	//인접리스트 동적할당
	mazelist1 = (Node**)malloc(sizeof(Node*)*HEIGHT*WIDTH);
	for (i = 0; i < HEIGHT*WIDTH; i++)
		mazelist1[i] = (Node*)malloc(sizeof(Node));
	mazelist2 = (Node**)malloc(sizeof(Node*)*HEIGHT*WIDTH);
	for (i = 0; i < HEIGHT*WIDTH; i++)
		mazelist2[i] = (Node*)malloc(sizeof(Node));

	//frame1을 이용하여 mazelist1 생성
	for (i = 0; i < HEIGHT; i++) {
		for (j = 0; j < WIDTH; j++) {
			v = i * WIDTH + j;
			mazelist1[v]->vertex = v;
			mazelist1[v]->cnt = 0;
			a = mazelist1[v];

			//아래
			if (frame1[i * 2 + 2][j * 2 + 1] == ' ') {
				Node *newnode = (Node*)malloc(sizeof(Node));
				newnode->vertex = v + WIDTH;
				newnode->next = NULL;
				a->next = newnode;
				mazelist1[v]->cnt++;
				a = a->next;
			}
			//오른쪽
			if (frame1[i * 2 + 1][j * 2 + 2] == ' ') {
				Node *newnode = (Node*)malloc(sizeof(Node));
				newnode->vertex = v + 1;
				newnode->next = NULL;
				a->next = newnode;
				mazelist1[v]->cnt++;
				a = a->next;
			}
			//위
			if (frame1[i * 2][j * 2 + 1] == ' ') {
				Node *newnode = (Node*)malloc(sizeof(Node));
				newnode->vertex = v - WIDTH;
				newnode->next = NULL;
				a->next = newnode;
				mazelist1[v]->cnt++;
				a = a->next;
			}
			//왼쪽
			if (frame1[i * 2 + 1][j * 2] == ' ') {
				Node *newnode = (Node*)malloc(sizeof(Node));
				newnode->vertex = v - 1;
				newnode->next = NULL;
				a->next = newnode;
				mazelist1[v]->cnt++;
				a = a->next;
			}

		}
	}

	//frame2를 이용하여 mazelist2 생성
	for (i = 0; i < HEIGHT; i++) {
		for (j = 0; j < WIDTH; j++) {
			v = i * WIDTH + j;
			mazelist2[v]->vertex = v;
			mazelist2[v]->cnt = 0;
			a = mazelist2[v];

			//아래
			if (frame2[i * 2 + 2][j * 2 + 1] == ' ') {
				Node *newnode = (Node*)malloc(sizeof(Node));
				newnode->vertex = v + WIDTH;
				newnode->next = NULL;
				a->next = newnode;
				mazelist2[v]->cnt++;
				a = a->next;
			}
			//오른쪽
			if (frame2[i * 2 + 1][j * 2 + 2] == ' ') {
				Node *newnode = (Node*)malloc(sizeof(Node));
				newnode->vertex = v + 1;
				newnode->next = NULL;
				a->next = newnode;
				mazelist2[v]->cnt++;
				a = a->next;
			}
			//위
			if (frame2[i * 2][j * 2 + 1] == ' ') {
				Node *newnode = (Node*)malloc(sizeof(Node));
				newnode->vertex = v - WIDTH;
				newnode->next = NULL;
				a->next = newnode;
				mazelist2[v]->cnt++;
				a = a->next;
			}
			//왼쪽
			if (frame2[i * 2 + 1][j * 2] == ' ') {
				Node *newnode = (Node*)malloc(sizeof(Node));
				newnode->vertex = v - 1;
				newnode->next = NULL;
				a->next = newnode;
				mazelist2[v]->cnt++;
				a = a->next;
			}

		}
	}

}

//캐릭터가 목적지에 도달 시 종료 및 최종 시간 출력
void ofApp::ENDP() {
	
	if (isEND == 1&&k==0) {
		end = time(NULL);
		timeresult = (double)(end - start);
		k++;//한번만 실행시키기 위함
		printf("End Game!\n");
	}
	
}