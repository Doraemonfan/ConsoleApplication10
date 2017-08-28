#include "stdafx.h"
#include <graphics.h>
#include <conio.h>
#include <string.h>
#include <time.h>
#define WIDTH 640      
#define HIGH 480
#define GAME_WIDTH 15    //��Ϸ�����и�����
#define GAME_HIGH 28   //��Ϸ�����Ÿ�����
#define BOX_WIDTH 15     //һ�����ӵĿ��
#define BOX_HIGH 15     //һ�����ӵĳ���

void startup();  //��ʼ��
void show();     //ͼ����ʾ
void gameover();  //��Ϸ��������
void fourKinds(int four[4][4], int kind); // �µ���״ͼ��
void updateWithInput();
void updateWithoutInput();
void transformation();

int board[GAME_WIDTH + 2][GAME_HIGH + 2];
int nowFour[4][4];
int nextFour[4][4];
int nowKind;
int nextKind;
int four_x, four_y;  //ͼ��λ��
int pre_x, pre_y;   //Ԥ��λ��
char scoreC[10];
int score;
int beginWidth, beginHigh;  //��Ϸ����ʼ

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
	}
}

//��ʼ��
void startup() {
	memset(board, 0, sizeof(board));   //��Ϸ�������ʼ��Ϊ0
	beginWidth = WIDTH / 6;           //��Ϸ��λ��
	beginHigh = HIGH / 18;
	score = 0;               //����

	srand((unsigned)time(NULL));

	nowKind = (rand() % 5) * 10 + rand() % 4;
	fourKinds(nowFour, nowKind);          //�����ʼͼ��
	nextKind = (rand() % 5) * 10 + rand() % 4;
	fourKinds(nextFour, nextKind);        //�����һ��ͼ��

	four_x = rand() % (GAME_WIDTH - 6) + 2;   //���ͼ������ʼλ��
	four_y = -3;    

	pre_x = beginWidth + (GAME_WIDTH + 4) * BOX_WIDTH;
	pre_y = beginHigh + BOX_WIDTH;

	initgraph(WIDTH, HIGH);
	BeginBatchDraw();

}

//��ʾ
void show() {
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
	sprintf_s(scoreC, "%5d", score);
	outtextxy(score_x + 60, score_y, scoreC);

	//nowFour[4][4]��ǰͼ����ʾ
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (nowFour[i][j] == 1 && four_y + j > 0) {
				int begin_i = (four_x + i) * BOX_WIDTH + beginWidth;
				int end_i = (four_x + i + 1) * BOX_WIDTH + beginWidth;
				int begin_j = (four_y + j) * BOX_HIGH + beginHigh;
				int end_j = (four_y + j + 1) * BOX_HIGH + beginHigh;
				setcolor(BLUE);
				setfillcolor(WHITE);
				fillrectangle(begin_i, begin_j, end_i, end_j);
			}
		}
	}

	FlushBatchDraw();
	Sleep(150);
	
	//��ȥԭλ��ͼ��
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (nowFour[i][j] == 1 && four_y + j > 0) {
				int begin_i = (four_x + i) * BOX_WIDTH + beginWidth;
				int end_i = (four_x + i + 1) * BOX_WIDTH + beginWidth;
				int begin_j = (four_y + j) * BOX_HIGH + beginHigh;
				int end_j = (four_y + j + 1) * BOX_HIGH + beginHigh;
				setcolor(BLACK);
				setfillcolor(BLACK);
				fillrectangle(begin_i, begin_j, end_i, end_j);
			}
		}
	}
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

	if (isHit) {
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
		nextKind = (rand() % 5) * 10 + rand() % 4;
		fourKinds(nextFour, nextKind);   //���Ԥ����ͼ��
		four_x = rand() % (GAME_WIDTH - 6) + 2;   //���ͼ������ʼλ��
		four_y = -3;
		isHit = false;
	}

	//��ȥ����,��������
	
	for (int j = 1; j <= GAME_HIGH; j++) {
		int tempSum = 0;
		for (int i = 1; i <= GAME_WIDTH; i++)
			tempSum += board[i][j];
		if (tempSum == 3 * GAME_WIDTH) {
			score++;
			for (int k = j; k > 0; k--)
				for (int i = 1; i <= GAME_WIDTH; i++)
					board[i][k] = board[i][k - 1];
		}
	}

	//����ʧ��
	for(int i = 1; i <= GAME_WIDTH; i++)
		if (board[i][0] == 3) {
			settextcolor(BLUE);
			settextstyle(64, 0, _T("����"));
			outtextxy(WIDTH / 4, HIGH / 3, _T("Game over!"));
			FlushBatchDraw();
			_getch();
			exit(0);
		}

	four_y += 1;
}

//���������
void updateWithInput() {
	CHAR input;
	if (_kbhit()) {
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
}

//��Ϸ��������
void gameover() {
	_getch();
	EndBatchDraw();
	closegraph();
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