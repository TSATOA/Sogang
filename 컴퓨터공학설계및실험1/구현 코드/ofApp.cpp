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
//�⺻���� ����
void ofApp::setup() {
	scanf("%d%d", &HEIGHT, &WIDTH); //�̷��� ���̿� �ʺ� �Է¹޴´�
	ofSetWindowTitle("Maze Example"); // Set the app name on the title bar
	//������ �ӵ��� ���� ����
	ofSetFrameRate(15);
	ofBackground(255, 255, 255);
	// Get the window size for image loading
	//â�� ���� �ʺ� �� ȹ��
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
	//�޴�����(Exit,Full screen,About .etc)
	HMENU hPopup = menu->AddPopupMenu(hMenu, "File");

	menu->AddPopupItem(hPopup, "Exit", false, false);
	bFullscreen = false; // not fullscreen yet
	menu->AddPopupItem(hPopup, "Full screen", false, false);
	
	hPopup = menu->AddPopupMenu(hMenu, "Help");
	menu->AddPopupItem(hPopup, "About", false, false); // No auto check

	// Set the menu to the window
	menu->SetWindowMenu();


	/*�̷��� �����Ҵ�*/
	frame1 = (char**)malloc(sizeof(char*)*HEIGHT * 2 + 1);
	frame2 = (char**)malloc(sizeof(char*)*HEIGHT * 2 + 1);
	for (int i = 0; i < HEIGHT * 2 + 1; i++) {
		frame1[i] = (char*)malloc(sizeof(char)*WIDTH * 2 + 1);
		frame2[i] = (char*)malloc(sizeof(char)*WIDTH * 2 + 1);
	}
	//�̷�1,2 ����
	makemaze1();
	makemaze2();
	//������ �̷� ��������Ʈ�� ǥ��
	makelist();
	
	//���� �ƴϸ� ���������� ����
	if (isEND == 0) {
		isOpen = 1;
	}
	else {
		isOpen = 0;
	}
	//�̷� 1,2 ���� ���� ��� ��ġ
	midstart = rand() % HEIGHT;
	midend = rand() % HEIGHT;

	//���� �켱 Ž���� ���� �ִ� ���
	DFS1();
	DFS2();
	//���� ����! �ð� ���� ����!
	printf("Game Start!\n");
	start = time(NULL);
} // end Setup


//
// Menu function
//
// This function is called by ofxWinMenu when an item is selected.
// The the title and state can be checked for required action.
// 
//�޴��� ���� �Լ�
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
//���� ���� ������ �ϴ� draw�Լ� -> �� ������ ���� ��ȭ�� ������ ǥ��
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

	//���̿� �ʺ� ���������� ������ ����
	if (isOpen==1) {
		
		ofNoFill();
		//���� ����Ʈ�� ǥ���� �̷θ� ���
		//���� Ʋ ���
		for (i = 0; i < HEIGHT; i++) {
			for (j = 0; j < WIDTH; j++) {
				ofSetColor(100);
				ofDrawRectangle(j * 40 + 100, i * 40 + 50, 40, 40);
				b = mazelist1[i*WIDTH + j];
				ofSetColor(255);
				//�� �� ����
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
		//���� ���� �������� �̷�2 ���
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
		// ���� ��� �Ա��� �ⱸ ����
		ofDrawLine(100  + WIDTH * 40, 50  + midstart * 40, 100 + WIDTH * 40, 50  + midstart * 40 + 40);
		ofDrawLine(100 , 200  + HEIGHT*40 + midend * 40, 100 , 200  + HEIGHT*40 + midend * 40 + 40);

		//�������� ���� ǥ��
		ofSetColor(0, 0, 255);
		ofDrawRectangle(120, 70, 5, 5);

		ofSetColor(0, 255, 0);
		ofDrawRectangle((WIDTH-1) * 40 + 20 + 100 -2.5, 20 + (HEIGHT - 1) * 40 + HEIGHT * 40 + 200 -2.5, 5, 5);
		
		//���� ��� ���
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
		
		//������� ��(ĳ����) ǥ��
		//page=0�� �̷�1, page=1�� �̷�2�� �ִ� ����
		ofFill();
		ofSetColor(255, 0, 0);
		if (page == 0) {
			ofDrawRectangle(maze_x * 40 + 110, maze_y * 40 + 60, 20, 20);
		}
		else {
			ofDrawRectangle(maze_x * 40 + 110, maze_y * 40 + 210 + HEIGHT * 40, 20, 20);
		}
		//�̷��� ��� ����
		ofSetColor(100);
		if (page==0 && maze_x == WIDTH - 1 && maze_y == midstart) {
			page = 1;
			maze_x = 0;
			maze_y = midend;
		}
		//uŰ�� ���� ��� isDFS=1, ����Ű�� ���� ��� isDFS=0 / �ִ� ��� ��Ʈ
		if (isDFS == 1) {
			dfsdraw();
		}
		//�ǽð� �ð� ���
		end = time(NULL);
		timeresult = (double)(end - start);
		sprintf(ti, "%.0f Seconds!", timeresult);
		myFont.drawString(ti, ofGetWidth() / 2 + 150, 30);
		
	}
	//���� ���� �� ���� �ð� ��� �� ����
	if (page == 1 && maze_x == WIDTH - 1 && maze_y == HEIGHT - 1) {
		isEND = 1;
		isOpen = 0;
		if (z == 0)
			ENDP();
		z++;

		sprintf(ti, "The time you took is %.0f Seconds!", timeresult);
		myFont.drawString(ti, ofGetWidth() / 2 - 120, ofGetHeight() / 2);
	}
	
	//��� ����� �ʿ� ���� �κ�(������ �ȴ�.����)
	if (isdfs)
	{
		ofSetColor(200);
		ofSetLineWidth(5);
		if (isOpen)
			dfsdraw();
		else
			cout << "You must open file first" << endl;
	}
	//����� �Ľ� ������Ʈ �۾� ���
	if(bShowInfo) {
		// Show keyboard duplicates of menu functions
		sprintf(title, "%d X %d Double Race!",HEIGHT,WIDTH);
		myFont.drawString(title, ofGetWidth() / 2 - 70, 30 );
		sprintf(str, " comsil project");
		myFont.drawString(str, 15, ofGetHeight()-20);
	}
	
} // end Draw

//Ǯ ��ũ��
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
//Ű �Է�
void ofApp::keyPressed(int key) {
	//����� ����Ǿ� �ְ� ���� ������Ʈ���� �����ϰ� ���õ� ���� ����
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
//Ű�Է�
void ofApp::keyReleased(int key){
	//������ ����Ű �÷��̾� ���� �̵�
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
	//���� ����Ű �÷��̾� ���� �̵�
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
	//���� ����Ű �÷��̾� ���� �̵�
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
	//�Ʒ��� ����Ű �÷��̾� ���� �̵�
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
	//UŰ �Է½� �ִܰ�θ� �����ִ� ��Ʈ ����
	if (key == 'U' || key == 'u') {
		isDFS = 1;
	}
	//QŰ �Է� �� �޸𸮸� �ʱ�ȭ�ϰ� ����
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


	// malloc�� memory�� free���ִ� �Լ�
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
//���� �켱 Ž���� ���� �ִ� ��� ����
void ofApp::DFS1()//DFSŽ���� �ϴ� �Լ�
{
	//���,�ִܰ��,�湮�̷� �����Ҵ�
	visited1 = (int *)malloc(sizeof(int)*HEIGHT*WIDTH);
	stack1 = (int *)malloc(sizeof(int)*HEIGHT*WIDTH);
	path1 = (int *)malloc(sizeof(int)*((WIDTH - 1)*HEIGHT + (HEIGHT - 1)*WIDTH));
	
	int i;
	int dis = 0;
	Node *temp;
	//�ʱ�ȭ
	for (i = 0; i < HEIGHT*WIDTH; i++) {
		visited1[i] = 0;
		stack1[i] = -1;
	}
	//ó�� ���� ����
	stack1[++top1] = mazelist1[0]->vertex;
	path1[++ptop1] = mazelist1[0]->vertex;
	visited1[0] = 1;
	//���� �켱 Ž�� ����
	while (top1 != -1) {
		//maze2�� �̵��ϴ� ��� ���� �� ����
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
//maze2�� ���̿켱Ž��(�� ������ �ſ� ����)
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

//���� �켱 Ž�� ��� ���
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
//maze1 frame1 ����(������ �迭)
void ofApp::makemaze1()
{
	int **maze;
	int i, j;
	int z=1;
	int cnt = 0;
	int combine_rand, inc_rand;
	//�̷� ���� �Ҵ�
	maze = (int**)malloc(sizeof(int*)*HEIGHT);

	for (i = 0; i < HEIGHT; i++) 
		maze[i] = (int*)malloc(sizeof(int)*WIDTH);
	
	//���� ���� �� �̵� ��� �Ա� ����
	srand((unsigned)time(NULL));
	midstart = rand() % HEIGHT;
	//�̷� �ʱ�(ù ��)
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
	//�ݺ� ���� ����
	for (i = 0; i < HEIGHT - 1; i++) {
		//�߰�1 ������
		for (j = 0; j < WIDTH - 1; j++) {
			combine_rand = rand() % 2;
			if (maze[i][j] != maze[i][j + 1]) {
				if (combine_rand == 1) {
					frame1[i * 2 + 1][j * 2 + 2] = ' ';
				}
				sync(maze, frame1, j, i);
			}
		}
		//�߰�2 �ø���
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
		//�߰�3 �Ʒ�������
		for (j = 0; j < WIDTH; j++)
			if (maze[i][j] == maze[i + 1][j])
				frame1[i * 2 + 2][j * 2 + 1] = ' ';

		//�߰�4 �������
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
	//�� ��������
	for (i = 0; i < WIDTH - 1; i++) {
		if (maze[HEIGHT - 1][i] != maze[HEIGHT - 1][i + 1]) {
			frame1[HEIGHT * 2 - 1][i * 2 + 2] = ' ';
			sync(maze, frame1, i, HEIGHT - 1);
		}
	}
	

}
//maze2 frame2 ����(�� ������ �ſ� ����)
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
	//���� ��� �ⱸ(maze2�� �����ϴ� �Ա�) ����
	midend = rand() % HEIGHT;
	//�̷� �ʱ�
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
	//�ݺ� ���� ����
	for (i = 0; i < HEIGHT - 1; i++) {
		//�߰�1 ������
		for (j = 0; j < WIDTH - 1; j++) {
			combine_rand = rand() % 2;
			if (maze[i][j] != maze[i][j + 1]) {
				if (combine_rand == 1) {
					frame2[i * 2 + 1][j * 2 + 2] = ' ';
				}
				sync(maze, frame2, j, i);
			}
		}
		//�߰�2 �ø���
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
		//�߰�3 �Ʒ�������
		for (j = 0; j < WIDTH; j++)
			if (maze[i][j] == maze[i + 1][j])
				frame2[i * 2 + 2][j * 2 + 1] = ' ';

		//�߰�4 �������
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
	//�� ��������
	for (i = 0; i < WIDTH - 1; i++) {
		if (maze[HEIGHT - 1][i] != maze[HEIGHT - 1][i + 1]) {
			frame2[HEIGHT * 2 - 1][i * 2 + 2] = ' ';
			sync(maze, frame2, i, HEIGHT - 1);
		}
	}
	
}

//���� �켱 Ž�� �������� ����ϴ� ����ȭ �Լ�(maze���� ������ ���� ��ġ��Ű�� ����)
void ofApp::sync(int **maze, char **frame, int xa, int ya)
{
	//���� ���� ���� ���
	if (frame[ya * 2 + 1][xa * 2] == ' ') {
		if (maze[ya][xa - 1] != maze[ya][xa]) {
			maze[ya][xa - 1] = maze[ya][xa];
			sync(maze, frame, xa - 1, ya);
		}
	}
	//�����ʿ� ���� ���� ���
	if (frame[ya * 2 + 1][xa * 2 + 2] == ' ') {
		if (maze[ya][xa + 1] != maze[ya][xa]) {
			maze[ya][xa + 1] = maze[ya][xa];
			sync(maze, frame, xa + 1, ya);
		}
	}
	//���ʿ� ���� ���� ���
	if (frame[ya * 2][xa * 2 + 1] == ' ') {
		if (maze[ya - 1][xa] != maze[ya][xa]) {
			maze[ya - 1][xa] = maze[ya][xa];
			sync(maze, frame, xa, ya - 1);
		}
	}
	//�Ʒ��ʿ� ���� ���� ���
	if (frame[ya * 2 + 2][xa * 2 + 1] == ' ') {
		if (maze[ya + 1][xa] != maze[ya][xa]) {
			maze[ya + 1][xa] = maze[ya][xa];
			sync(maze, frame, xa, ya + 1);
		}
	}
}
//�� �������� ������ frame1,2�� �̿��Ͽ� ��������Ʈ ����
void ofApp::makelist() {
	Node *a;
	int i, j;
	int v;
	//��������Ʈ �����Ҵ�
	mazelist1 = (Node**)malloc(sizeof(Node*)*HEIGHT*WIDTH);
	for (i = 0; i < HEIGHT*WIDTH; i++)
		mazelist1[i] = (Node*)malloc(sizeof(Node));
	mazelist2 = (Node**)malloc(sizeof(Node*)*HEIGHT*WIDTH);
	for (i = 0; i < HEIGHT*WIDTH; i++)
		mazelist2[i] = (Node*)malloc(sizeof(Node));

	//frame1�� �̿��Ͽ� mazelist1 ����
	for (i = 0; i < HEIGHT; i++) {
		for (j = 0; j < WIDTH; j++) {
			v = i * WIDTH + j;
			mazelist1[v]->vertex = v;
			mazelist1[v]->cnt = 0;
			a = mazelist1[v];

			//�Ʒ�
			if (frame1[i * 2 + 2][j * 2 + 1] == ' ') {
				Node *newnode = (Node*)malloc(sizeof(Node));
				newnode->vertex = v + WIDTH;
				newnode->next = NULL;
				a->next = newnode;
				mazelist1[v]->cnt++;
				a = a->next;
			}
			//������
			if (frame1[i * 2 + 1][j * 2 + 2] == ' ') {
				Node *newnode = (Node*)malloc(sizeof(Node));
				newnode->vertex = v + 1;
				newnode->next = NULL;
				a->next = newnode;
				mazelist1[v]->cnt++;
				a = a->next;
			}
			//��
			if (frame1[i * 2][j * 2 + 1] == ' ') {
				Node *newnode = (Node*)malloc(sizeof(Node));
				newnode->vertex = v - WIDTH;
				newnode->next = NULL;
				a->next = newnode;
				mazelist1[v]->cnt++;
				a = a->next;
			}
			//����
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

	//frame2�� �̿��Ͽ� mazelist2 ����
	for (i = 0; i < HEIGHT; i++) {
		for (j = 0; j < WIDTH; j++) {
			v = i * WIDTH + j;
			mazelist2[v]->vertex = v;
			mazelist2[v]->cnt = 0;
			a = mazelist2[v];

			//�Ʒ�
			if (frame2[i * 2 + 2][j * 2 + 1] == ' ') {
				Node *newnode = (Node*)malloc(sizeof(Node));
				newnode->vertex = v + WIDTH;
				newnode->next = NULL;
				a->next = newnode;
				mazelist2[v]->cnt++;
				a = a->next;
			}
			//������
			if (frame2[i * 2 + 1][j * 2 + 2] == ' ') {
				Node *newnode = (Node*)malloc(sizeof(Node));
				newnode->vertex = v + 1;
				newnode->next = NULL;
				a->next = newnode;
				mazelist2[v]->cnt++;
				a = a->next;
			}
			//��
			if (frame2[i * 2][j * 2 + 1] == ' ') {
				Node *newnode = (Node*)malloc(sizeof(Node));
				newnode->vertex = v - WIDTH;
				newnode->next = NULL;
				a->next = newnode;
				mazelist2[v]->cnt++;
				a = a->next;
			}
			//����
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

//ĳ���Ͱ� �������� ���� �� ���� �� ���� �ð� ���
void ofApp::ENDP() {
	
	if (isEND == 1&&k==0) {
		end = time(NULL);
		timeresult = (double)(end - start);
		k++;//�ѹ��� �����Ű�� ����
		printf("End Game!\n");
	}
	
}