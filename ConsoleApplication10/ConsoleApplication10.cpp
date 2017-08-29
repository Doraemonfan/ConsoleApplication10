#include "stdafx.h"
#include <graphics.h>
#include <conio.h>
#include <string.h>
#include <math.h>
#include <time.h>
#pragma comment(lib, "winmm.lib")
#define WIDTH 640      
#define HIGH 480
#define GAME_WIDTH 15    //��Ϸ�����и�����
#define GAME_HIGH 28   //��Ϸ�����Ÿ�����
#define BOX_WIDTH 15     //һ�����ӵĿ��
#define BOX_HIGH 15     //һ�����ӵĳ���

//��������
void startup();  //��ʼ��
void show();     //ͼ����ʾ
void gameover();  //��Ϸ��������
void fourKinds(int four[4][4], int kind); // �µ���״ͼ��
void updateWithInput();   //���������
void updateWithoutInput();  //���������
void transformation();  //����
void startMenu();    //��ʼ�˵�
void pauseStart();    //��ͣ�˵�
void playMusicOnce(CHAR *musicName);  //������Чһ��
void readRecord();  //����
void writeRecord();  //�浵

//ȫ�ֱ���
int GAME_CONDITION = 1; // ��Ϸ״̬��1Ϊ��ʼ�˵��� 0Ϊ�˳��� 2 Ϊ��ʽ��Ϸ

int board[GAME_WIDTH + 2][GAME_HIGH + 2];  //��Ϸ��
int nowFour[4][4];       //����ͼ��
int nextFour[4][4];     // ��һ��ͼ��
int nowKind;            //����ͼ������
int nextKind;          //��һ��ͼ������
int four_x, four_y;  //ͼ��λ��
COLORREF color;        //ͼ����ɫ
int pre_x, pre_y;   //Ԥ��λ��
int score;           //������������ʽ��
int levelUp;    //�ȼ�
int beginWidth, beginHigh;  //��Ϸ����ʼ
bool isFail;   //��Ϸʧ��
int isPause;  //��Ϸ��ͣ
int isMedi;  //��Ϸ�ж�
IMAGE img_bk;   //����ͼƬ
MOUSEMSG m;    //������
int mouse_x, mouse_y;
int choice;  //���ѡ��

//��������
// ������Чһ��
void playMusicOnce(CHAR * musicName) {
	CHAR playMusic[50] = "open ";
	strcat_s(playMusic, musicName);
	strcat_s(playMusic, " alias tempMusic");
	mciSendString("close tempMusic", NULL, 0, NULL);
	mciSendString(playMusic, NULL, 0, NULL);
	mciSendString("play tempMusic", NULL, 0, NULL);
}

//����
void readRecord() {
	startup();
	FILE *fp;
	fopen_s(&fp, "record.txt", "r");
	int n;
	fscanf_s(fp, "%d", &n);
	if (n == -1) {
		fscanf_s(fp, "%d %d %d %d %d %d", &score, &isFail, &four_x, &four_y, &nowKind, &nextKind);
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
				fscanf_s(fp, "%d ", &nowFour[i][j]);
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
				fscanf_s(fp, "%d ", &nextFour[i][j]);
		for (int i = 1; i <= GAME_WIDTH; i++)
			for (int j = 1; j <= GAME_HIGH; j++)
				fscanf_s(fp, "%d ", &board[i][j]);
		GAME_CONDITION = 2;
	}
	fclose(fp);
}

//�浵
void writeRecord() {
	FILE * fp;
	fopen_s(&fp, "record.txt", "w");
	fprintf_s(fp, "%d\n\n", -1);
	fprintf_s(fp, "%d %d %d %d %d %d\n\n", score, isFail, four_x, four_y, nowKind, nextKind);
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++)
			fprintf_s(fp, "%d ", nowFour[i][j]);
		fprintf_s(fp, "\n");
	}
	fprintf_s(fp, "\n");
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++)
			fprintf_s(fp, "%d ", nextFour[i][j]);
		fprintf_s(fp, "\n");
	}
	fprintf_s(fp, "\n");
	for (int i = 1; i <= GAME_WIDTH; i++) {
		for (int j = 1; j <= GAME_HIGH; j++)
			fprintf_s(fp, "%d ", board[i][j]);
		fprintf_s(fp, "\n");
	}
	fclose(fp);
}

//��ʼ�˵�
void startMenu() {
	putimage(0, 0, &img_bk);
	setbkmode(TRANSPARENT);

	settextcolor(GREEN);
	settextstyle(64, 0, _T("��������"));
	outtextxy(WIDTH * 0.25, HIGH * 0.1, _T("����˹����"));

	setcolor(BLUE);
	setfillcolor(RGB(200,200,200));
	fillrectangle(WIDTH * 0.39, HIGH * 0.33, WIDTH * 0.61, HIGH * 0.43);
	fillrectangle(WIDTH * 0.39, HIGH * 0.48, WIDTH * 0.61, HIGH * 0.58);
	fillrectangle(WIDTH * 0.39, HIGH * 0.63, WIDTH * 0.61, HIGH * 0.73); 
	fillrectangle(WIDTH * 0.39, HIGH * 0.78, WIDTH * 0.61, HIGH * 0.88);

	if (MouseHit()) {
		m = GetMouseMsg();   // ��ȡ�����Ϣ
		mouse_x = m.x;
		mouse_y = m.y;	
		if (m.uMsg == WM_LBUTTONUP) {
			if (choice == 1) { 
				GAME_CONDITION = 2;
				playMusicOnce(".\\music\\mouse.wav");
				Sleep(500);
				playMusicOnce(".\\music\\game_start.wav");
			}
			else if (choice == 2) { readRecord(); playMusicOnce(".\\music\\mouse.wav"); }
			else if (choice == 3) { writeRecord(); playMusicOnce(".\\music\\mouse.wav"); }
			else if (choice == 4) { playMusicOnce(".\\music\\mouse.wav"); Sleep(100); gameover(); }
		}
	}

	choice = 0;
	settextcolor(BLUE);	
	if (mouse_x >= WIDTH * 0.39 && mouse_x <= WIDTH * 0.61 && mouse_y >= HIGH * 0.33 && mouse_y <= HIGH * 0.43) {
		settextstyle(32, 0, _T("����"));
		choice = 1;
	}
	else settextstyle(32, 0, _T("���Ĳ���"));
	if(isMedi) outtextxy(WIDTH * 0.4, HIGH * 0.35, _T("������Ϸ"));
	else outtextxy(WIDTH * 0.4, HIGH * 0.35, _T("��ʼ��Ϸ"));

	if (mouse_x >= WIDTH * 0.39 && mouse_x<= WIDTH * 0.61 && mouse_y >= HIGH * 0.48 && mouse_y <= HIGH * 0.58) {
		settextstyle(32, 0, _T("����"));
		choice = 2;
	}
	else 	settextstyle(32, 0, _T("���Ĳ���"));
	outtextxy(WIDTH * 0.4, HIGH * 0.50, _T("�������"));

	if (mouse_x >= WIDTH * 0.39 && mouse_x <= WIDTH * 0.61 && mouse_y >= HIGH * 0.63 && mouse_y <= HIGH * 0.73) {
		settextstyle(32, 0, _T("����"));
		choice = 3;
	}
	else settextstyle(32, 0, _T("���Ĳ���"));
	outtextxy(WIDTH * 0.4, HIGH * 0.65, _T("�������"));

	if (mouse_x >= WIDTH * 0.39 && mouse_x <= WIDTH * 0.61 && mouse_y >= HIGH * 0.78 && mouse_y <= HIGH * 0.88) {
		settextstyle(32, 0, _T("����"));
		choice = 4;
	}
	else settextstyle(32, 0, _T("���Ĳ���"));
	outtextxy(WIDTH * 0.45, HIGH * 0.80, _T("�˳�"));

	FlushBatchDraw();
	clearrectangle(0, 0, WIDTH - 1, HIGH - 1);
}

// ��ȡ�µ���״ͼ�Σ�����ͼ���� 4 X 4 ����е���ʾ
void fourKinds(int four[4][4], int kind) {
	if (kind == 0) { int temp[4][4] = { {0,1,0,0},{0,1,0,0},{0,1,0,0},{0,1,0,0} }; memcpy(four, temp, sizeof(int) * 16); }
	else if (kind == 1) { int temp[4][4] = { {0,0,0,0},{1,1,1,1},{0,0,0,0},{0,0,0,0} }; memcpy(four, temp, sizeof(int) * 16); }
	else if (kind == 2) { int temp[4][4] = { {0,0,1,0},{0,0,1,0},{0,0,1,0},{0,0,1,0} }; memcpy(four, temp, sizeof(int) * 16); }
	else if (kind == 3) { int temp[4][4] = { {0,0,0,0},{0,0,0,0},{1,1,1,1},{0,0,0,0} }; memcpy(four, temp, sizeof(int) * 16); }

	else if (kind == 10) { int temp[4][4] = { { 0,0,0,0 },{ 0,1,1,0 },{ 0,1,1,0 },{ 0,0,0,0 } }; memcpy(four, temp, sizeof(int) * 16); }
	else if (kind == 11) { int temp[4][4] = { { 0,0,0,0 },{ 0,1,1,0 },{ 0,1,1,0 },{ 0,0,0,0 } }; memcpy(four, temp, sizeof(int) * 16); }
	else if (kind == 12) { int temp[4][4] = { { 0,0,0,0 },{ 0,1,1,0 },{ 0,1,1,0 },{ 0,0,0,0 } }; memcpy(four, temp, sizeof(int) * 16); }
	else if (kind == 13) { int temp[4][4] = { { 0,0,0,0 },{ 0,1,1,0 },{ 0,1,1,0 },{ 0,0,0,0 } }; memcpy(four, temp, sizeof(int) * 16); }

	else if (kind == 20) { int temp[4][4] = { { 0,0,0,0 },{ 0,1,1,0 },{ 0,0,1,0 },{ 0,0,1,0 } }; memcpy(four, temp, sizeof(int) * 16); }
	else if (kind == 21) { int temp[4][4] = { { 0,0,0,0 },{ 0,1,1,1 },{ 0,1,0,0 },{ 0,0,0,0 } }; memcpy(four, temp, sizeof(int) * 16); }
	else if (kind == 22) { int temp[4][4] = { { 0,1,0,0 },{ 0,1,0,0 },{ 0,1,1,0 },{ 0,0,0,0 } }; memcpy(four, temp, sizeof(int) * 16); }
	else if (kind == 23) { int temp[4][4] = { { 0,0,0,0 },{ 0,0,1,0 },{ 1,1,1,0 },{ 0,0,0,0 } }; memcpy(four, temp, sizeof(int) * 16); }

	else if (kind == 30) { int temp[4][4] = { { 0,0,0,0 },{ 0,1,1,0 },{ 0,1,0,0 },{ 0,1,0,0 } }; memcpy(four, temp, sizeof(int) * 16); }
	else if (kind == 31) { int temp[4][4] = { { 0,0,0,0 },{ 1,1,1,0 },{ 0,0,1,0 },{ 0,0,0,0 } }; memcpy(four, temp, sizeof(int) * 16); }
	else if (kind == 32) { int temp[4][4] = { { 0,0,1,0 },{ 0,0,1,0 },{ 0,1,1,0 },{ 0,0,0,0 } }; memcpy(four, temp, sizeof(int) * 16); }
	else if (kind == 33) { int temp[4][4] = { { 0,0,0,0 },{ 0,1,0,0 },{ 0,1,1,1 },{ 0,0,0,0 } }; memcpy(four, temp, sizeof(int) * 16); }

	else if (kind == 40) { int temp[4][4] = { { 0,0,0,0 },{ 0,1,0,0 },{ 1,1,1,0 },{ 0,0,0,0 } }; memcpy(four, temp, sizeof(int) * 16); }
	else if (kind == 41) { int temp[4][4] = { { 0,0,1,0 },{ 0,1,1,0 },{ 0,0,1,0 },{ 0,0,0,0 } }; memcpy(four, temp, sizeof(int) * 16); }
	else if (kind == 42) { int temp[4][4] = { { 1,1,1,0 },{ 0,1,0,0 },{ 0,0,0,0 },{ 0,0,0,0 } }; memcpy(four, temp, sizeof(int) * 16); }
	else if (kind == 43) { int temp[4][4] = { { 1,0,0,0 },{ 1,1,0,0 },{ 1,0,0,0 },{ 0,0,0,0 } }; memcpy(four, temp, sizeof(int) * 16); }

	else if (kind == 50) { int temp[4][4] = { { 0,1,0,0 },{ 0,1,1,0 },{ 0,0,1,0 },{ 0,0,0,0 } }; memcpy(four, temp, sizeof(int) * 16); }
	else if (kind == 51) { int temp[4][4] = { { 0,0,0,0 },{ 0,0,1,1 },{ 0,1,1,0 },{ 0,0,0,0 } }; memcpy(four, temp, sizeof(int) * 16); }
	else if (kind == 52) { int temp[4][4] = { { 0,1,0,0 },{ 0,1,1,0 },{ 0,0,1,0 },{ 0,0,0,0 } }; memcpy(four, temp, sizeof(int) * 16); }
	else if (kind == 53) { int temp[4][4] = { { 0,0,0,0 },{ 0,0,1,1 },{ 0,1,1,0 },{ 0,0,0,0 } }; memcpy(four, temp, sizeof(int) * 16); }

	else if (kind == 60) { int temp[4][4] = { { 0,0,0,0 },{ 0,0,1,0 },{ 0,1,1,0 },{ 0,1,0,0 } }; memcpy(four, temp, sizeof(int) * 16); }
	else if (kind == 61) { int temp[4][4] = { { 0,0,0,0 },{ 0,1,1,0 },{ 0,0,1,1 },{ 0,0,0,0 } }; memcpy(four, temp, sizeof(int) * 16); }
	else if (kind == 62) { int temp[4][4] = { { 0,0,0,0 },{ 0,0,1,0 },{ 0,1,1,0 },{ 0,1,0,0 } }; memcpy(four, temp, sizeof(int) * 16); }
	else if (kind == 63) { int temp[4][4] = { { 0,0,0,0 },{ 0,1,1,0 },{ 0,0,1,1 },{ 0,0,0,0 } }; memcpy(four, temp, sizeof(int) * 16); }
}

//����
void transformation() {
	int tempKind = nowKind;
	int tempFour[4][4];
	bool isTrans = true;

	if (tempKind % 10 == 3) tempKind = (tempKind / 10) * 10;
	else tempKind++;

	fourKinds(tempFour, tempKind);

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (tempFour[i][j] == 1) {
				int trans_i = four_x + i;
				int trans_j = four_y + j;
				if (board[trans_i][trans_j] == 2 || board[trans_i][trans_j] == 3) {
					isTrans = false;
					break;
				}
			}
		}
		if (!isTrans) break;
	}

	if (isTrans) {
		memcpy(nowFour, tempFour, sizeof(int) * 16);
		nowKind = tempKind;
		playMusicOnce(".\\music\\trans.wav");
	}
}

//��ʼ��
void startup() {
	memset(board, 0, sizeof(board));   //��Ϸ�������ʼ��Ϊ0
	beginWidth = WIDTH / 6;           //��Ϸ��λ��
	beginHigh = HIGH / 18;
	score = 0;               //����
	levelUp = 1;

	srand((unsigned)time(NULL));

	nowKind = (rand() % 7) * 10 + rand() % 4;
	fourKinds(nowFour, nowKind);          //�����ʼͼ��
	nextKind = (rand() % 7) * 10 + rand() % 4;
	fourKinds(nextFour, nextKind);        //�����һ��ͼ��

	four_x = rand() % (GAME_WIDTH - 6) + 2;   //���ͼ������ʼλ��
	four_y = -3;    
	color = RGB(rand() % 255, rand() % 255, rand() % 255);

	pre_x = beginWidth + (GAME_WIDTH + 4) * BOX_WIDTH;  //����һ��������λ��
	pre_y = beginHigh + BOX_WIDTH;

	isFail = false;   //ʧ��
	isPause = false;   //��ͣ
	isMedi = false;    // �ж�

	loadimage(&img_bk, ".\\picture\\bk.jpg");  //����ͼƬ

	mouse_x = 0;  //��ʼ���λ��Ϊ��0��0��
	mouse_y = 0;

	choice = 0;

	initgraph(WIDTH, HIGH);
	BeginBatchDraw();

	/*mciSendString("open .\\music\\bk.wma alias bkMusic", NULL, 0, NULL);
	mciSendString("play bkMusic repeat", NULL, 0, NULL);*/
}

//��ʾ
void show() {
	while (GAME_CONDITION == 1) startMenu(); // ���뿪ʼ�˵�

	putimage(0, 0, &img_bk);
	setbkmode(TRANSPARENT);

	//��Ϸ����ʾ
	for (int i = 0; i < GAME_WIDTH + 2; i++) {
		for (int j = 0; j < GAME_HIGH + 2; j++) {
			int begin_i = i * BOX_WIDTH + beginWidth;
			int end_i = (i + 1) * BOX_WIDTH + beginWidth;
			int begin_j = j * BOX_HIGH + beginHigh;
			int end_j = (j + 1) * BOX_HIGH + beginHigh;

			if (i == 0 || i == GAME_WIDTH + 1) {    //���ұ߽�
				board[i][j] = 2;   //���ұ߽�Ϊ2
				setcolor(WHITE);
				setfillcolor(GREEN);
				fillrectangle(begin_i - 1, begin_j, end_i - 1, end_j);
			}
			else if (j == 0) {    //�ϱ߽�
				board[i][j] = 0;    //�ϱ߽�Ϊ4
				setcolor(WHITE);
				setfillcolor(GREEN);
				fillrectangle(begin_i, begin_j, end_i, end_j);
			}
			else if(j == GAME_HIGH + 1) {   //�±߽�
				board[i][j] = 3;    //�±߽�Ϊ3
				setcolor(WHITE);
				setfillcolor(GREEN);
				fillrectangle(begin_i, begin_j, end_i, end_j);
			}
			else if (board[i][j] == 3) {
				setcolor(BLUE);             //������
				setfillcolor(RED);
				fillrectangle(begin_i, begin_j, end_i, end_j);
			}
			else if (board[i][j] == 1) {             //ʵ��
				setcolor(BLUE);
				setfillcolor(WHITE);
				fillrectangle(begin_i, begin_j, end_i, end_j);
			}
			else if (board[i][j] == 0) {       //����
				setcolor(RGB(50, 50, 50));
				setfillcolor(BLACK);
				fillrectangle(begin_i, begin_j, end_i, end_j);
			}
		}
	}

	//��һ��ͼ��Ԥ֪
	settextcolor(WHITE);
	settextstyle(20, 0, _T("����"));

	outtextxy(pre_x, pre_y, _T("��һ��:"));

	for (int i = 0; i < 4; i++) {             //4 X 4 ���
		for (int j = 0; j < 4; j++) {	
			if (nextFour[i][j] == 1) {
				int begin_i = i * BOX_WIDTH + pre_x + 100;
				int end_i = (i + 1) * BOX_WIDTH + pre_x + 100;
				int begin_j = j * BOX_HIGH + pre_y;
				int end_j = (j + 1) * BOX_HIGH + pre_y;
				setcolor(BLUE);
				setfillcolor(WHITE);
				fillrectangle(begin_i, begin_j, end_i, end_j);
			}
		}
	}

	//�÷�
	settextcolor(WHITE);
	settextstyle(20, 0, _T("����"));
	int score_x = pre_x;
	int score_y = pre_y + BOX_HIGH * 8;
	outtextxy(score_x, score_y, _T("�÷�:"));
	char scoreC[10];   //�������ַ���ʽ��
	sprintf_s(scoreC, "%5d", score);
	outtextxy(score_x + 60, score_y, scoreC);

	int level_x = pre_x;
	int level_y = score_y + BOX_HIGH * 4;
	outtextxy(level_x, level_y, _T("�ȼ���"));
	char levelC[10];
	sprintf_s(levelC, "%5d", levelUp);
	outtextxy(level_x + 60, level_y, levelC);

	//nowFour[4][4]��ǰͼ����ʾ
	
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (nowFour[i][j] == 1 && four_y + j > 0) {
				int begin_i = (four_x + i) * BOX_WIDTH + beginWidth;
				int end_i = (four_x + i + 1) * BOX_WIDTH + beginWidth;
				int begin_j = (four_y + j) * BOX_HIGH + beginHigh;
				int end_j = (four_y + j + 1) * BOX_HIGH + beginHigh;
				setcolor(BLUE);
				
				setfillcolor(color);
				fillrectangle(begin_i, begin_j, end_i, end_j);
			}
		}
	}

	//ʧ����ʾ
	if (isFail) {
		settextcolor(BLUE);
		settextstyle(64, 0, _T("����"));
		outtextxy(WIDTH / 4, HIGH / 3, _T("Game over!"));
		FlushBatchDraw();
		GAME_CONDITION = 1;
		Sleep(8000);
		isFail = 0;
	}

	setcolor(BLUE);
	setfillcolor(RGB(200, 200, 200));
	fillrectangle(pre_x + 80, pre_y + 280, pre_x + 160, pre_y + 320);
	fillrectangle(pre_x + 30, pre_y + 360, pre_x + 210, pre_y + 400);

	choice = 0;
	settextcolor(BLUE);
	if (mouse_x >= pre_x + 80 && mouse_x <= pre_x + 160 && mouse_y >= pre_y + 280 && mouse_y <= pre_y + 320) {
		settextstyle(32, 0, _T("����"));
		choice = 1;
	}
	else settextstyle(32, 0, _T("���Ĳ���"));
	if (isPause) outtextxy(pre_x + 88, pre_y + 285, _T("����"));
	else outtextxy(pre_x + 88, pre_y + 285, _T("��ͣ"));

	if (mouse_x >= pre_x + 30 && mouse_x <= pre_x + 210 && mouse_y >= pre_y + 360 && mouse_y <= pre_y + 400) {
		settextstyle(32, 0, _T("����"));
		choice = 2;
	}
	else 	settextstyle(32, 0, _T("���Ĳ���"));
	outtextxy(pre_x + 38, pre_y + 365, _T("�������˵�"));

	FlushBatchDraw();   //���ҳ��
	Sleep(200 - levelUp * 20);
	clearrectangle(0, 0, WIDTH - 1, HIGH - 1);
}

//���������
void updateWithoutInput() {
	bool isHit = false;    //�ж��Ƿ����
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (nowFour[i][j] == 1) {
				int next_i = four_x + i;
				int next_j = four_y + j + 1;  //ʵ����Ϊʵ���򶳽�Ϊ������
				if (board[next_i][next_j] == 3 && four_y + j > 0) {
					isHit = true;  //����
					break;
				}
			}
		}
		if (isHit) break;
	}

	//����
	if (isHit) {
		playMusicOnce(".\\music\\down.wav");
		for (int i = 0; i < 4; i++ ) {
			for (int j = 0; j < 4; j++) {
				if (nowFour[i][j] == 1) {
					board[four_x + i][four_y + j] = 3;
				}
			}
		}

		memcpy(nowFour, nextFour, sizeof(int) * 16);  //Ԥ��ͼ�α�Ϊ��ʱͼ��
		nowKind = nextKind;

		//��ȥԤ��ͼ��
		for (int i = 0; i < 4; i++) {             //4 X 4 ���
			for (int j = 0; j < 4; j++) {
				if (nextFour[i][j] == 1) {
					int begin_i = i * BOX_WIDTH + pre_x + 100;
					int end_i = (i + 1) * BOX_WIDTH + pre_x + 100;
					int begin_j = j * BOX_HIGH + pre_y;
					int end_j = (j + 1) * BOX_HIGH + pre_y;
					setcolor(BLACK);
					setfillcolor(BLACK);
					fillrectangle(begin_i, begin_j, end_i, end_j);
				}
			}
		}
		nextKind = (rand() % 7) * 10 + rand() % 4;
		fourKinds(nextFour, nextKind);   //���Ԥ����ͼ��
		four_x = rand() % (GAME_WIDTH - 6) + 2;   //���ͼ������ʼλ��
		four_y = -3;
		color = RGB(rand() % 255, rand() % 255, rand() % 255);
		isHit = false;
	}

	//��ȥ����,��������
	for (int j = 1; j <= GAME_HIGH; j++) {
		int tempSum = 0;
		for (int i = 1; i <= GAME_WIDTH; i++)
			tempSum += board[i][j];
		if (tempSum == 3 * GAME_WIDTH) {
			score++; 
			playMusicOnce(".\\music\\full.wav");
			for (int k = j; k > 0; k--)
				for (int i = 1; i <= GAME_WIDTH; i++)
					board[i][k] = board[i][k - 1];
		}
	}

	//���ݷ�������ȼ�
	int temp = score / 5 + 1;
	if (temp - levelUp == 1) {
		playMusicOnce(".\\music\\level_up.wav");
		levelUp++;
	}

	//����ʧ��
	for(int i = 1; i <= GAME_WIDTH; i++)
		if (board[i][0] == 3) {
			isFail = true;
			playMusicOnce(".\\music\\fail2.wav");
		}
	// ͼ�������ƶ�
	four_y += 1;
}

//���������
void updateWithInput() {
	CHAR input;
	if (_kbhit()) {  //���ƶ���������
		bool isLeftBar = false;    //�ж��Ƿ�Ϊ�߽�
		bool isRightBar = false;
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				if (nowFour[i][j] == 1) {
					int left_i = four_x + i - 1;  //��
					int left_j = four_y + j;  
					int right_i = four_x + i + 1;  //��
					int right_j = four_y + j;
					if ((board[left_i][left_j] == 2 || board[left_i][left_j] == 3) && four_y + j > 0) {
						isLeftBar = true;  //����ʵ��
					}
					if ((board[right_i][right_j] == 2 || board[right_i][right_j] == 3) && four_y + j > 0) {
						isRightBar = true;  //����ʵ��
					}
				}
			}
		}
		input = _getch();
		if (input == 'a' && !isLeftBar) four_x--;   //����
		else if (input == 'd' && !isRightBar) four_x++;  //����
		else if (input == 's') while (four_y != -2) updateWithoutInput();   //һ�䵽��
		else if (input == 'w') transformation();   // ����
	}

	while (MouseHit()) {  //������������
		m = GetMouseMsg();  //��������Ϣ
		mouse_x = m.x;
		mouse_y = m.y;
		if (m.uMsg == WM_LBUTTONUP) {   //�������
			if (choice == 2) {
				GAME_CONDITION = 1;   //�жϣ��������˵�
				isMedi = true;
				playMusicOnce(".\\music\\mouse.wav");
			}
			if (choice == 1) {    //��ͣ
				isPause = true;
				playMusicOnce(".\\music\\pause.wav");
			}
		}
	}
	while (isPause) {    //��ͣ״̬����갴��������������Ϸ
		show();
		while (MouseHit()) {
			m = GetMouseMsg();
			mouse_x = m.x;
			mouse_y = m.y;
			if (m.uMsg == WM_LBUTTONUP) {
				if (choice == 2) {
					GAME_CONDITION = 1;
					isMedi = true;
					playMusicOnce(".\\music\\mouse.wav");
				}
				else if (choice == 1) {
					isPause = false;
					playMusicOnce(".\\music\\pause.wav");
				}
			}
		}
	}
}

//��Ϸ��������
void gameover() {
	EndBatchDraw();
	closegraph();
	exit(0);
}

//������
int main() {
	startup();
	for (;;) {
		show();
		updateWithoutInput();
		updateWithInput();
	}
	gameover();
	return 0;
}