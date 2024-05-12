#include "tetris.h"

static struct sigaction act, oact;

int main(){
	int exit=0;

	initscr();
	noecho();
	keypad(stdscr, TRUE);	

	srand((unsigned int)time(NULL));
	createRankList();
	while(!exit){
		clear();
		switch(menu()){
		case MENU_PLAY: play(); break;
		case MENU_RANK: rank(); break;
		case MENU_EXIT: exit=1; break;
		default: break;
		}
	}

	endwin();
	system("clear");
	return 0;
}

void InitTetris(){
	int i,j;
	
	for(j=0;j<HEIGHT;j++)
		for(i=0;i<WIDTH;i++)
			field[j][i]=0;
	/*
	nextBlock[0]=rand()%7;
	nextBlock[1]=rand()%7;
	nextBlock[2]=rand()%7; //과제
	*/

	for(i=0;i<VISIBLE_BLOCKS;i++) nextBlock[i]=rand()%7;
	blockRotate=0;
	blockY=-1;
	blockX=WIDTH/2-2;
	score=0;	
	gameOver=0;
	timed_out=0;

	DrawOutline();
	DrawField();
	DrawBlock(blockY,blockX,nextBlock[0],blockRotate,' ');
	DrawNextBlock(nextBlock);
	PrintScore(score);
}

void DrawOutline(){	
	int i,j;
	/* 블럭이 떨어지는 공간의 태두리를 그린다.*/
	DrawBox(0,0,HEIGHT,WIDTH);

	/* next block을 보여주는 공간의 태두리를 그린다.*/
	move(2,WIDTH+10);
	printw("NEXT BLOCK");
	DrawBox(3,WIDTH+10,4,8);

	//과제 2번째 next블록의 공간을 그려준다.
	DrawBox(9,WIDTH+10,4,8);

	/* score를 보여주는 공간의 태두리를 그린다.*/
	//과제 2번째 next블록 때문에 위치 조정
	move(16,WIDTH+10);
	printw("SCORE");
	DrawBox(17,WIDTH+10,1,8);
}

int GetCommand(){
	int command;
	command = wgetch(stdscr);
	switch(command){
	case KEY_UP:
		break;
	case KEY_DOWN:
		break;
	case KEY_LEFT:
		break;
	case KEY_RIGHT:
		break;
	case ' ':	/* space key*/
		/*fall block*/
		break;
	case 'q':
	case 'Q':
		command = QUIT;
		break;
	default:
		command = NOTHING;
		break;
	}
	return command;
}

int ProcessCommand(int command){
	int ret=1;
	int drawFlag=0;
	switch(command){
	case QUIT:
		ret = QUIT;
		break;
	case KEY_UP:
		if((drawFlag = CheckToMove(field,nextBlock[0],(blockRotate+1)%4,blockY,blockX)))
			blockRotate=(blockRotate+1)%4;
		break;
	case KEY_DOWN:
		if((drawFlag = CheckToMove(field,nextBlock[0],blockRotate,blockY+1,blockX)))
			blockY++;
		break;
	case KEY_RIGHT:
		if((drawFlag = CheckToMove(field,nextBlock[0],blockRotate,blockY,blockX+1)))
			blockX++;
		break;
	case KEY_LEFT:
		if((drawFlag = CheckToMove(field,nextBlock[0],blockRotate,blockY,blockX-1)))
			blockX--;	
		break;
	default:
		break;
	}
	if(drawFlag) DrawChange(field,command,nextBlock[0],blockRotate,blockY,blockX);
	return ret;	
}

void DrawField(){
	int i,j;
	for(j=0;j<HEIGHT;j++){
		move(j+1,1);
		for(i=0;i<WIDTH;i++){
			if(field[j][i]==1){
				attron(A_REVERSE);
				printw(" ");
				attroff(A_REVERSE);
			}
			else printw(".");
		}
	}
}


void PrintScore(int score){
	move(18,WIDTH+11);//2번째 next블록 생성때문에 11->18
	printw("%8d",score);
}
	
void DrawNextBlock(int *nextBlock){
	int i, j;
	for( i = 0; i < 4; i++ ){
		move(4+i,WIDTH+13);
		for( j = 0; j < 4; j++ ){
			if( block[nextBlock[1]][0][i][j] == 1 ){
				attron(A_REVERSE);
				printw(" ");
				attroff(A_REVERSE);
			}
			else printw(" ");
		}
	}
	//2번째 next블록 과제
	for(i=0;i<4;i++){	
		move(10+i,WIDTH+13);
		for(j=0;j<4;j++){
			if(block[nextBlock[2]][0][i][j] == 1){
				attron(A_REVERSE);
				printw(" ");
				attroff(A_REVERSE);
			}
			else printw(" ");
		}
	}

}

void DrawBlock(int y, int x, int blockID,int blockRotate,char tile){
	int i,j;
	for(i=0;i<4;i++)	
		for(j=0;j<4;j++){
			if(block[blockID][blockRotate][i][j]==1 && i+y>=0){
				move(i+y+1,j+x+1);
				attron(A_REVERSE);
				printw("%c",tile);	
				attroff(A_REVERSE);
			}
		}

	move(HEIGHT,WIDTH+10);
}

void DrawBox(int y,int x, int height, int width){
	int i,j;
	move(y,x);
	addch(ACS_ULCORNER);
	for(i=0;i<width;i++)
		addch(ACS_HLINE);
	addch(ACS_URCORNER);
	for(j=0;j<height;j++){
		move(y+j+1,x);
		addch(ACS_VLINE);
		move(y+j+1,x+width+1);
		addch(ACS_VLINE);
	}
	move(y+j+1,x);
	addch(ACS_LLCORNER);
	for(i=0;i<width;i++)
		addch(ACS_HLINE);


	addch(ACS_LRCORNER);
}

void play(){
	int command;
	clear();
	act.sa_handler = BlockDown;
	sigaction(SIGALRM,&act,&oact);
	InitTetris();
	do{
		if(timed_out==0){
			alarm(1);
			timed_out=1;
		}

		command = GetCommand();
		if(ProcessCommand(command)==QUIT){
			alarm(0);
			DrawBox(HEIGHT/2-1,WIDTH/2-5,1,10);
			move(HEIGHT/2,WIDTH/2-4);
			printw("Good-bye!!");
			refresh();
			getch();

			return;
		}
	}while(!gameOver);

	alarm(0);
	getch();
	DrawBox(HEIGHT/2-1,WIDTH/2-5,1,10);
	move(HEIGHT/2,WIDTH/2-4);
	printw("GameOver!!");
	refresh();
	getch();
	newRank(score);
}

char menu(){
	printw("1. play\n");
	printw("2. rank\n");
	printw("3. recommended play\n");
	printw("4. exit\n");
	return wgetch(stdscr);
}

//#include "Array.h"
/////////////////////////첫주차 실습에서 구현해야 할 함수/////////////////////////

int CheckToMove(char f[HEIGHT][WIDTH],int currentBlock,int blockRotate, int blockY, int blockX){
	// user code
	int i,j;
	for(i=0;i<4;i++){
		for(j=0;j<4;j++){
			if(block[currentBlock][blockRotate][i][j]==1){
				//블록을 놓는 위치에 필드상 블록이 있을 경우
				if(f[blockY+i][blockX+j]==1) return 0;
				//y>=HEIGHT, x<0, x>=WIDHT인 경우
				if(blockY+i>=HEIGHT || blockX	+j<0 || blockX+j>=WIDTH) return 0;
			}
		}
	}
	return 1;
}



void DrawChange(char f[HEIGHT][WIDTH],int command,int currentBlock,int blockRotate, int blockY, int blockX){
	// user code
	int i,j;
	int X,Y,R; // 이전 블록
	int shadowy;

	X=blockX;
	Y=blockY;
	R=blockRotate;
	shadowy=blockY;

	//1. 이전 블록 정보를 찾는다. ProcessCommand의 switch문을 참조할 것
	switch(command){
		case KEY_UP :
			R=(blockRotate+3)%4;
			break;
		case KEY_DOWN :
			Y=blockY-1;
			break;
		case KEY_RIGHT :
			X=blockX-1;
			break;
		case KEY_LEFT :
			X=blockX+1;
			break;
		default:
			break;
	}

	while(CheckToMove(f,currentBlock,R,shadowy,X)==1) shadowy++;

	//2. 이전 블록 정보를 지운다. DrawBlock함수 참조할 것.
	//이전 블록의 정보에 블록이 있고, 화면에 블록이 있을 경우 그 블록의 위치로 가 .출력 
	for(i=0;i<4;i++){
		for(j=0;j<4;j++){
			if(block[currentBlock][R][i][j]==1&&Y+i>=0){
					move(Y+i+1,j+X+1);
					printw(".");
					//그림자 제거
					move(shadowy+i,j+X+1);
					printw(".");
			}
		}
	}

	//3. 새로운 블록 정보를 그린다. 
	//DrawBlock(blockY,blockX,currentBlock,blockRotate,' ');
	DrawField();
	DrawBlockWithFeatures(blockY,blockX,currentBlock,blockRotate);
	move(HEIGHT,WIDTH+10);
}

void BlockDown(int sig){
	// user code
	int i,j,t,k;
	//강의자료 p26-27의 플로우차트를 참고한다.
	//블록이 한칸 내려갈 수 있는지 확인
	if(CheckToMove(field,nextBlock[0],blockRotate,blockY+1,blockX)==1){
		//내려갈 수 있으면 한칸 내리고 종료
		blockY++;
		DrawChange(field,KEY_DOWN,nextBlock[0],blockRotate,blockY,blockX);
	}else{
		//내려갈 수 없을 때
		//y좌표의 초기값이 0인 경우 게임 종료 flag를 TRUE로 설정
		if(blockY==-1) gameOver=1;
		//블록을 필드에 쌓는다.
		k=AddBlockToField(field,nextBlock[0],blockRotate,blockY,blockX);
		if(k!=0) score+=k;
		//완전한 line이 있을 경우 지워주고 점수를 갱신한뒤 출력한다.
		score+=DeleteLine(field);
		PrintScore(score);
		//Next블록을 현재 블록으로 만들어주고 새로운 Next블록을 랜덤하게 결정한다.
		/*
		nextBlock[0]=nextBlock[1];
		nextBlock[1]=nextBlock[2];
		nextBlock[2]=rand()%7;
		*/
		for(i=0;i<VISIBLE_BLOCKS-1;i++) nextBlock[i]=nextBlock[i+1];
		nextBlock[VISIBLE_BLOCKS-1]=rand()%7;
		
		ini();
		recommend(recRoot);
		
		DrawNextBlock(nextBlock);
		//현재 블록의 위치를 초기화하고 동작을 종료한다.
		blockRotate=0;
		blockY=-1;
		blockX=WIDTH/2-2;
		DrawField();
	}
	timed_out=0;


}

int AddBlockToField(char f[HEIGHT][WIDTH],int currentBlock,int blockRotate, int blockY, int blockX){
	// user code
	//과제 score 증가하기
	int touched=0;
	int score=0;

	//Block이 추가된 영역의 필드값을 바꾼다.
	int i,j;
	for(i=0;i<4;i++){
		for(j=0;j<4;j++){
			if(block[currentBlock][blockRotate][i][j]==1){
				field[blockY+i][blockX+j]=1;
				if(blockY+i==HEIGHT-1) touched++;
				if(f[i+blockY+1][j+blockX]==1) touched++;
			}
		}
	}
	score=touched*10;
	return score;
}

int DeleteLine(char f[HEIGHT][WIDTH]){
	// user code
	
	//1. 필드를 탐색하여, 꽉 찬 구간이 있는지 탐색한다.
	//2. 꽉 찬 구간이 있으면 해당 구간을 지운다. 즉, 해당 구간으로 필드값을 한칸씩 내린다.
	int i,j,k,cnt,delline;
	delline=0;
	for(i=0;i<HEIGHT;i++){
		cnt=0;
		for(j=0;j<WIDTH;j++){
			if(f[i][j]==1)
				cnt++;
		}
		if(cnt==WIDTH){
			delline++;
			for(j=i;j>0;j--){
				for(k=0;k<WIDTH;k++){
					f[j][k]=f[j-1][k];
				}
			}
		}
	}

	return delline*delline*100;
}

/* 과제 DrawBlockWithFeature() 함수 */
void DrawBlockWithFeatures(int y, int x, int blockID, int blockRotate){
	DrawBlock(y,x,blockID,blockRotate,' ');
	DrawShadow(y,x,blockID,blockRotate);
	DrawRecommend(maxY,maxX,blockID,maxR);
}

///////////////////////////////////////////////////////////////////////////

void DrawShadow(int y, int x, int blockID,int blockRotate){
	// user code
	while(CheckToMove(field,nextBlock[0],blockRotate,y+1,x)) y++;
	DrawBlock(y,x,blockID,blockRotate,'/');
}

void createRankList(){
	// user code
	//Open "rank.txt"
	int i;
	char name[NAMELEN];
	int sc;
	Node *newnode;
	FILE *fp;
	Node *a;
	a=list;
	fp = fopen("rank.txt","r");
	if(fp==NULL){
		return;
	}
	fscanf(fp,"%d",&member);
	if(member>0){
		for(i=0;i<member;i++){
			fscanf(fp,"%s %d",name,&sc);
			newnode = (Node*)malloc(sizeof(Node));
			strcpy(newnode->name,name);
			newnode->score = sc;
			newnode->link=NULL;
			
			if(list==NULL){
				list=newnode;
				a=list;
			} else{
				a->link=newnode;
				a=a->link;
			}
			
		}
	}
	fclose(fp);

}

void rank(){
	// user code
	int i,num;
	int x=0, y=0, count=0;
	Node *a=list;
	Node *prenode=list;
	Node *delnode;
	char na[NAMELEN];
	int rank=0;

	//rank확인을 누르면 화면 초기화 후 rank메뉴 출력
	clear();
	printw("1. list ranks from X to Y\n");
	printw("2. list ranks by a specific name\n");
	printw("3. delete a specific rank");
	num=wgetch(stdscr);
	echo();
	if(num=='1'){
		printw("\nX: ");
		scanw("%d",&x);
		printw("Y: ");
		scanw("%d",&y);
		printw("\tname\t|\tscore\n");
		printw("------------------------------\n");
		count=0;
		if((x>y&&y!=0) || x<0 || member<y || y<0){
			printw("serch failure: no rank in the list\n");
		} else if(x==0 && y==0){
			while(a!=NULL){
				printw(" %s\t\t| %d\n",a->name,a->score);
				count++;
				if(count==5) break;
				a=a->link;
			}
		} else if(x!=0 && y==0){
			count++;
			while(a!=NULL){
				if(count==x) break;
				a=a->link;
				count++;
			}
			while(a!=NULL){
				printw(" %s\t\t| %d\n",a->name,a->score);
				if(count==5) break;
				count++;
				a=a->link;
			}
		} else{
			while(a!=NULL){
				count++;
				if(count>=x && count<=y){
					printw(" %s\t\t| %d\n",a->name,a->score);
				}
				a=a->link;
			}
		}
	}
	if(num=='2'){
		printw("\ninput the name: ");
		scanw("%s",na);
		printw("\tname\t|\tscore\n");
		printw("------------------------------\n");
		count=0;
		while(a!=NULL){
			if(!strcmp(a->name,na)){
				printw(" %s\t\t| %d\n",a->name,a->score);
				count++;
			}
			a=a->link;
		}
		if(count==0) printw("\nsearch failure: no name in the list\n");
	}
	if(num=='3'){
		printw("\ninput the rank: ");
		scanw("%d",&rank);
		if(member<rank){
			printw("\nsearch failure: the rank not in the list\n");
		}else{
			while(a!=NULL){
				count++;
				delnode=a;
				if(count==rank){
					if(rank==1){
						list=list->link;
						free(delnode);
						break;
					} else{
						prenode->link=a->link;
						free(delnode);
					}
				}
				prenode=a;
				a=a->link;
				
			}

			member--;
			writeRankFile();
			printw("\nresult: the rank deleted\n");
		}
		
	}
	getch();
	noecho();
}

void writeRankFile(){
	// user code
	Node *a;
	a=list;
	int i;
	FILE *fp;
	fp = fopen("rank.txt","w");
	if(member==0){
		fprintf(fp,"0");
	} else{
		fprintf(fp,"%d\n",member);
		for(i=0;i<member;i++){
			fprintf(fp,"%s %d\n",a->name,a->score);
			a=a->link;
		}
	}
	fclose(fp);
}

void newRank(int score){
	// user code
	char name[NAMELEN];
	Node *newnode;
	newnode=(Node*)malloc(sizeof(Node));
	Node *a;
	a=list;
	Node *prenode;
	prenode=NULL;

	clear();
	printw("Input a user name : ");
	echo();
	scanw("%s",name);

	strcpy(newnode->name,name);
	newnode->score=score;
	newnode->link=NULL;

	if(list==NULL){
		list=newnode;
	}else{
		if(a->score<newnode->score){
			newnode->link = a;
			list = newnode;
		} else{
			while(a!=NULL&&a->score>newnode->score){
				prenode=a;
				a=a->link;
			}
			if(a!=NULL){
				newnode->link=a;
				prenode->link=newnode;
			}else{
				prenode->link=newnode;
			}
		}
	}
	member++;
	writeRankFile();
	noecho();
	getch();
}

void DrawRecommend(int y, int x, int blockID,int blockRotate){
	// user code
	while(CheckToMove(field,blockID,blockRotate,y+1,x)) y++;
	DrawBlock(y,x,blockID,blockRotate,'R');
}

int recommend(RecNode *root){
	int max=0; // 미리 보이는 블럭의 추천 배치까지 고려했을 때 얻을 수 있는 최대 점수
	int i,j,x=0,y=0,m,n,sc=0;
	int cnt;
	int d,t;
	int r[7]={2,4,4,4,1,2,2};
	int s[7]={17,34,34,34,9,17,17};
	// user code
	RecNode **a=root->c;
	

	a=(RecNode**)malloc(sizeof(RecNode*)*s[nextBlock[root->lv]]);
	for(i=0;i<s[nextBlock[root->lv]];i++) a[i]=(RecNode*)malloc(sizeof(RecNode));

	for(i=0;i<r[nextBlock[root->lv]];i++){
		for(j=-2;j<WIDTH+3;j++){
			if(!CheckToMove(root->f,nextBlock[root->lv],i,0,j)) continue;

			for(m=0;m<HEIGHT;m++)
				for(n=0;n<WIDTH;n++)
					a[x]->f[m][n]=root->f[m][n];

			a[x]->lv=root->lv+1;
			a[x]->score=root->score;
			y=0;
			while(CheckToMove(a[x]->f,nextBlock[root->lv],i,y+1,j)==1) y++;
			/*
			a[x]->score+=AddBlockToField(a[x]->f,nextBlock[root->lv],i,y,j);
			a[x]->score+=DeleteLine(a[x]->f);
			*/
			
			if(a[x]->lv==VISIBLE_BLOCKS){
				
			t=0;
			for(m=0;m<4;m++){
				for(n=0;n<4;n++){
					if(block[nextBlock[root->lv]][i][m][n]==1){
					//	root->f[y+m][j+n]=1;
						if(y+i==HEIGHT-1) t++;
						if(a[x]->f[y+m+1][n+j]==1) t++;
					}
				}
			}


			d=0;
			for(m=0;m<HEIGHT;m++){
				cnt=0;
				for(n=0;n<WIDTH;n++){
					if(a[x]->f[i][j]==1) cnt++;
				}
				if(cnt==WIDTH){
					d++;
				}
			}
			

		//	a[x]->score+=AddBlockToField(a[x]->f,nextBlock[root->lv],i,y,j);
		//	a[x]->score+=DeleteLine(a[x]->f);
			} else{
				a[x]->score+=recommend(a[x]);
			}
			if(max<=a[x]->score&&maxY<y){
				maxX=j;
				maxY=y;
				maxR=i;
				max=a[x]->score;
			}
			x++;
			/*	
			t=0;
			for(m=0;m<4;m++){
				for(n=0;n<4;n++){
					if(block[nextBlock[root->lv]][i][m][n]==1){
					//	root->f[y+m][j+n]=1;
						if(y+i==HEIGHT-1) t++;
						else if(a[x]->f[y+m+1][n+j]==1) t++;
					}
				}
			}


			d=0;
			for(m=0;m<HEIGHT;m++){
				cnt=0;
				for(n=0;n<WIDTH;n++){
					if(a[x]->f[i][j]==1) cnt++;
				}
				if(cnt==WIDTH){
					d++;
				}
			}

				
			a[x]->score+=t*10+d*d*100;
			if(a[x]->lv<=VISIBLE_BLOCKS) a[x]->score=recommend(a[x]);
			if(max<=a[x]->score){
				if(root->lv==0){
					maxX=j;
					maxY=y;
					maxR=i;
				}
				max=a[x]->score;
			}
			if(root->lv==0)
				free(a[x]);
			x++;
			*/
		}
	}

	


	return max;
}

void ini(){
	int i,j;
	recRoot=(RecNode*)malloc(sizeof(RecNode));
	for(i=0;i<HEIGHT;i++)
		for(j=0;j<WIDTH;j++)
			recRoot->f[i][j]=field[i][j];
	recRoot->lv=0;
	recRoot->score=0;
	maxX=0;
	maxY=0;
	maxR=0;
}

void recommendedPlay(){
	// user code
}
