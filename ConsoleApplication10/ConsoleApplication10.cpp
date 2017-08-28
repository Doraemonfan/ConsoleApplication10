#include "stdafx.h"
#include <graphics.h>
#include <conio.h>
#include <string.h>
#include <time.h>
#define WIDTH 640      
#define HIGH 480
#define GAME_WIDTH 15    //游戏区横列格子数
#define GAME_HIGH 28   //游戏区竖排格子数
#define BOX_WIDTH 15     //一个格子的宽度
#define BOX_HIGH 15     //一个格子的长度

void startup();  //初始化
void show();     //图像显示
void gameover();  //游戏结束设置
void fourKinds(int four[4][4], int kind); // 新的形状图形
void updateWithInput();
void updateWithoutInput();
void transformation();

int board[GAME_WIDTH + 2][GAME_HIGH + 2];
int nowFour[4][4];
int nextFour[4][4];
int nowKind;
int nextKind;
int four_x, four_y;  //图形位置
int pre_x, pre_y;   //预告位置
char scoreC[10];
int score;
int beginWidth, beginHigh;  //游戏区开始

// 获取新的形状图形，各种图形在 4 X 4 表格中的显示
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

//变形
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

//初始化
void startup() {
	memset(board, 0, sizeof(board));   //游戏区数组初始化为0
	beginWidth = WIDTH / 6;           //游戏区位置
	beginHigh = HIGH / 18;
	score = 0;               //分数

	srand((unsigned)time(NULL));

	nowKind = (rand() % 5) * 10 + rand() % 4;
	fourKinds(nowFour, nowKind);          //随机开始图形
	nextKind = (rand() % 5) * 10 + rand() % 4;
	fourKinds(nextFour, nextKind);        //随机下一个图形

	four_x = rand() % (GAME_WIDTH - 6) + 2;   //随机图形区初始位置
	four_y = -3;    

	pre_x = beginWidth + (GAME_WIDTH + 4) * BOX_WIDTH;
	pre_y = beginHigh + BOX_WIDTH;

	initgraph(WIDTH, HIGH);
	BeginBatchDraw();

}

//显示
void show() {
	//游戏区显示
	for (int i = 0; i < GAME_WIDTH + 2; i++) {
		for (int j = 0; j < GAME_HIGH + 2; j++) {
			int begin_i = i * BOX_WIDTH + beginWidth;
			int end_i = (i + 1) * BOX_WIDTH + beginWidth;
			int begin_j = j * BOX_HIGH + beginHigh;
			int end_j = (j + 1) * BOX_HIGH + beginHigh;

			if (i == 0 || i == GAME_WIDTH + 1) {    //左右边界
				board[i][j] = 2;   //左右边界为2
				setcolor(WHITE);
				setfillcolor(GREEN);
				fillrectangle(begin_i - 1, begin_j, end_i - 1, end_j);
			}
			else if (j == 0) {    //上边界
				board[i][j] = 0;    //上边界为4
				setcolor(WHITE);
				setfillcolor(GREEN);
				fillrectangle(begin_i, begin_j, end_i, end_j);
			}
			else if(j == GAME_HIGH + 1) {   //下边界
				board[i][j] = 3;    //下边界为3
				setcolor(WHITE);
				setfillcolor(GREEN);
				fillrectangle(begin_i, begin_j, end_i, end_j);
			}
			else if (board[i][j] == 3) {
				setcolor(BLUE);             //沉积区
				setfillcolor(RED);
				fillrectangle(begin_i, begin_j, end_i, end_j);
			}
			else if (board[i][j] == 1) {             //实区
				setcolor(BLUE);
				setfillcolor(WHITE);
				fillrectangle(begin_i, begin_j, end_i, end_j);
			}
			else if (board[i][j] == 0) {       //空区
				setcolor(RGB(50, 50, 50));
				setfillcolor(BLACK);
				fillrectangle(begin_i, begin_j, end_i, end_j);
			}
		}
	}

	//下一个图形预知
	settextcolor(WHITE);
	settextstyle(20, 0, _T("黑体"));

	outtextxy(pre_x, pre_y, _T("下一个:"));

	for (int i = 0; i < 4; i++) {             //4 X 4 表格
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

	//得分
	settextcolor(WHITE);
	settextstyle(20, 0, _T("黑体"));
	int score_x = pre_x;
	int score_y = pre_y + BOX_HIGH * 8;
	outtextxy(score_x, score_y, _T("得分:"));
	sprintf_s(scoreC, "%5d", score);
	outtextxy(score_x + 60, score_y, scoreC);

	//nowFour[4][4]当前图形显示
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
	
	//擦去原位置图形
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

//无输入更新
void updateWithoutInput() {
	bool isHit = false;    //判断是否沉积
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (nowFour[i][j] == 1) {
				int next_i = four_x + i;
				int next_j = four_y + j + 1;  //实形下为实形则冻结为沉积区
				if (board[next_i][next_j] == 3 && four_y + j > 0) {
					isHit = true;  //沉积
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

		memcpy(nowFour, nextFour, sizeof(int) * 16);  //预告图形变为现时图形
		nowKind = nextKind;

		//擦去预告图形
		for (int i = 0; i < 4; i++) {             //4 X 4 表格
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
		fourKinds(nextFour, nextKind);   //随机预告新图形
		four_x = rand() % (GAME_WIDTH - 6) + 2;   //随机图形区初始位置
		four_y = -3;
		isHit = false;
	}

	//消去满行,分数增加
	
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

	//堆满失败
	for(int i = 1; i <= GAME_WIDTH; i++)
		if (board[i][0] == 3) {
			settextcolor(BLUE);
			settextstyle(64, 0, _T("黑体"));
			outtextxy(WIDTH / 4, HIGH / 3, _T("Game over!"));
			FlushBatchDraw();
			_getch();
			exit(0);
		}

	four_y += 1;
}

//有输入更新
void updateWithInput() {
	CHAR input;
	if (_kbhit()) {
		bool isLeftBar = false;    //判断是否为边界
		bool isRightBar = false;
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				if (nowFour[i][j] == 1) {
					int left_i = four_x + i - 1;  //左
					int left_j = four_y + j;  
					int right_i = four_x + i + 1;  //右
					int right_j = four_y + j;
					if ((board[left_i][left_j] == 2 || board[left_i][left_j] == 3) && four_y + j > 0) {
						isLeftBar = true;  //左有实物
					}
					if ((board[right_i][right_j] == 2 || board[right_i][right_j] == 3) && four_y + j > 0) {
						isRightBar = true;  //右有实物
					}
				}
			}
		}
		input = _getch();
		if (input == 'a' && !isLeftBar) four_x--;   //左移
		else if (input == 'd' && !isRightBar) four_x++;  //右移
		else if (input == 's') while (four_y != -2) updateWithoutInput();   //一落到地
		else if (input == 'w') transformation();   // 变形
	}
}

//游戏结束设置
void gameover() {
	_getch();
	EndBatchDraw();
	closegraph();
}

//主函数
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