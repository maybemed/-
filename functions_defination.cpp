#include<iostream>
#include<graphics.h>
#include<string>
#include<windows.h>
#include<tchar.h>
#include<chrono>
#include<conio.h>
#include<stdlib.h>
#include"chess.h"
#include"functions.h"
#include"parameter.h"


extern HWND main_game;
extern Chess chess;

using namespace std;

void DrawBackground() {
	setbkcolor(RGB(255, 205, 150));
	setlinecolor(BLACK);
	for (int i = 0; i < 15; i++) {
		line(MARGIN + i * BLOCK_WIDTH, MARGIN, MARGIN + i * BLOCK_WIDTH, MAX_Y - MARGIN);
		line(MARGIN, MARGIN + i * BLOCK_WIDTH, MAX_X - MARGIN, MARGIN + i * BLOCK_WIDTH);
		string str = to_string(i);
		char numChar = 'A' + i; // 将数字转换为字符

		// 将字符转换为字符串
		char c[2];
		sprintf_s(c, "%c", numChar);
		wstring wideStr2(c, c + strlen(c));
		LPCTSTR lpctstr2 = wideStr2.c_str();
		wstring wideStr(str.begin(), str.end());
		LPCTSTR lpctstr = wideStr.c_str();
		outtextxy(MARGIN - 15, MARGIN + i * BLOCK_WIDTH - 10, lpctstr2);//手动添加微小的偏移，使其对其棋盘
		outtextxy(MARGIN + i * BLOCK_WIDTH - 3, MARGIN - 15, lpctstr);
	}
	setfillcolor(BLACK);
	solidcircle(MARGIN + 3 * BLOCK_WIDTH, MARGIN + 3 * BLOCK_WIDTH, 5);
	solidcircle(MARGIN + 3 * BLOCK_WIDTH, MARGIN + 11 * BLOCK_WIDTH, 5);
	solidcircle(MARGIN + 11 * BLOCK_WIDTH, MARGIN + 3 * BLOCK_WIDTH, 5);
	solidcircle(MARGIN + 11 * BLOCK_WIDTH, MARGIN + 11 * BLOCK_WIDTH, 5);
	solidcircle(MARGIN + 7 * BLOCK_WIDTH, MARGIN + 7 * BLOCK_WIDTH, 5);

	setbkmode(TRANSPARENT);
}

void Chess::DrawOneChess(int x, int y) {
	//判断应该画在哪一行哪一列
	int left_column;//左边那个是第几列
	int up_row;//上边那个是第几行
	int this_column, this_row;//应该画在几行几列
	left_column = (x - MARGIN) / BLOCK_WIDTH;
	up_row = (y - MARGIN) / BLOCK_WIDTH;
	this_column = (x - left_column * BLOCK_WIDTH - MARGIN > (left_column + 1) * BLOCK_WIDTH + MARGIN - x) ? left_column + 1 : left_column;
	this_row = (y - up_row * BLOCK_WIDTH - MARGIN > (up_row + 1) * BLOCK_WIDTH + MARGIN - y) ? up_row + 1 : up_row;
	int next_draw_color = (next_color == 1) ? BLACK : WHITE;
	setfillcolor(next_draw_color);
	solidcircle(this_column * BLOCK_WIDTH + MARGIN, this_row * BLOCK_WIDTH + MARGIN, R);
	land_chess[this_row][this_column] = next_color;
	next_color = (next_color == 1) ? 2 : 1;  // 切换颜色
	last_land.col = this_column;
	last_land.row = this_row;
}

bool Chess::CheckClick(ExMessage m) {
	if (m.x >= MARGIN + BLOCK_WIDTH*14 || m.y > MARGIN + BLOCK_WIDTH*14||m.x<MARGIN||m.y<MARGIN)
		return false;
	int x = m.x;
	int y = m.y;
	int left_column;//左边那个是第几列
	int up_row;//上边那个是第几行
	int this_column, this_row;//应该画在几行几列
	left_column = (x - MARGIN) / BLOCK_WIDTH;
	up_row = (y - MARGIN) / BLOCK_WIDTH;
	this_column = (x - left_column * BLOCK_WIDTH - MARGIN > (left_column + 1) * BLOCK_WIDTH + MARGIN - x) ? left_column + 1 : left_column;
	this_row = (y - up_row * BLOCK_WIDTH - MARGIN > (up_row + 1) * BLOCK_WIDTH + MARGIN - y) ? up_row + 1 : up_row;
	if (land_chess[this_row][this_column] != 0) {
		cout << "不能落在这里" << endl;
		return false;
	}
	return true;
}

void Chess::DrawLandChess() {
	for (int i = 0; i < 15; i++)
		for (int j = 0; j < 15; j++) {
			if (land_chess[i][j] != 0) {
				int next_draw_color = (next_color == 0) ? BLACK : WHITE;
				setfillcolor(land_chess[i][j] == 1 ? BLACK : WHITE);
				solidcircle(j * BLOCK_WIDTH + MARGIN, i * BLOCK_WIDTH + MARGIN, R);

			}

		}

}

int Chess::WinCheck(int x, int y) {
	int left_column;//左边那个是第几列
	int up_row;//上边那个是第几行
	int this_column, this_row;//应该画在几行几列
	left_column = (x - MARGIN) / BLOCK_WIDTH;
	up_row = (y - MARGIN) / BLOCK_WIDTH;
	this_column = (x - left_column * BLOCK_WIDTH - MARGIN > (left_column + 1) * BLOCK_WIDTH + MARGIN - x) ? left_column + 1 : left_column;
	this_row = (y - up_row * BLOCK_WIDTH - MARGIN > (up_row + 1) * BLOCK_WIDTH + MARGIN - y) ? up_row + 1 : up_row;
	x = this_column;
	y = this_row;//注意xy此时是从0开始
#ifdef debug
	cout << x << "," << y << endl;
#endif
	int left_thiscolor = 0;
	int right_thiscolor = 0;//左右边紧邻的该颜色棋子数量
	int this_color = next_color == 1 ? 2 : 1;
	//判断左边有几个
	for (int left = 1; left <= 4; left++) {
		if (x - left < 0)
			break;
		else if (land_chess[y][x - left] == this_color)
			left_thiscolor++;
		else
			break;
	}
	//判断右边有几个
	for (int right = 1; right <= 4; right++) {
		if (x + right > 15)
			break;
		else if (land_chess[y][x + right] == this_color)
			right_thiscolor++;
		else
			break;
	}
#ifdef debug
	cout << "左边有" << left_thiscolor << "个，右边有" << right_thiscolor << "个" << endl;
#endif
	if (left_thiscolor + right_thiscolor >= 4) {
		return this_color;
#ifdef debug
		cout << "over" << endl;
#endif
	}

	int up_thiscolor = 0;
	int down_thiscolor = 0;//左右边紧邻的该颜色棋子数量
	//判断上边有几个
	for (int up = 1; up <= 4; up++) {
		if (y - up < 0)
			break;
		else if (land_chess[y - up][x] == this_color)
			up_thiscolor++;
		else
			break;
	}
	//判断下边有几个
	for (int down = 1; down <= 4; down++) {
		if (y + down > 15)
			break;
		else if (land_chess[y + down][x] == this_color)
			down_thiscolor++;
		else
			break;
	}
	if (up_thiscolor + down_thiscolor >= 4) {
		return this_color;
	}

	int leftup_thiscolor = 0;
	int rightdown_thiscolor = 0;//左右边紧邻的该颜色棋子数量
	//判断左上边有几个
	for (int leftup = 1; leftup <= 4; leftup++) {
		if (y - leftup < 0 || x - leftup < 0)
			break;
		else if (land_chess[y - leftup][x - leftup] == this_color)
			leftup_thiscolor++;
		else
			break;
	}
	//判断右下边有几个
	for (int rightdown = 1; rightdown <= 4; rightdown++) {
		if (y + rightdown > 15 || x + rightdown > 15)
			break;
		else if (land_chess[y + rightdown][x + rightdown] == this_color)
			rightdown_thiscolor++;
		else
			break;
	}
	if (leftup_thiscolor + rightdown_thiscolor >= 4) {
		return this_color;
	}

	int rightup_thiscolor = 0;
	int leftdown_thiscolor = 0;//左右边紧邻的该颜色棋子数量
	//判断右上边有几个
	for (int rightup = 1; rightup <= 4; rightup++) {
		if (y - rightup < 0 || x + rightup > 15)
			break;
		else if (land_chess[y - rightup][x + rightup] == this_color)
			rightup_thiscolor++;
		else
			break;
	}
	//判断左下边有几个
	for (int leftdown = 1; leftdown <= 4; leftdown++) {
		if (y + leftdown > 15 || x - leftdown < 0)
			break;
		else if (land_chess[y + leftdown][x - leftdown] == this_color)
			leftdown_thiscolor++;
		else
			break;
	}
	if (rightup_thiscolor + leftdown_thiscolor >= 4) {
		return this_color;
	}
	return 0;
}

void Chess::init() {
	next_color = 1;
	memset(land_chess, 0, sizeof(land_chess));
}

bool GameAgain(int& winner) {
	int ret = 0;
	if (winner == 1)
		ret = MessageBox(main_game, L"黑棋获胜\n,想要再来一局吗", L"游戏结束", MB_YESNO | MB_ICONQUESTION);
	else
		ret = MessageBox(main_game, L"白棋获胜\n,想要再来一局吗", L"游戏结束", MB_YESNO | MB_ICONQUESTION);
	if (ret == IDYES) {
		cleardevice();
		chess.init();
		winner = 0;
		return true;
	}
	else
		return false;
}

void Chess::CaculateScore() {
	int human_num = 0;
	int AI_num = 0;
	int empty_num = 0;
	int directs[4][2] = { {1,0},{1,1},{0,1},{-1,1} };

	memset(human_score, 0, sizeof(human_score));
	memset(AI_score, 0, sizeof(AI_score));
	for (int row = 0; row < N; row++) {
		for (int col = 0; col < N; col++) {
			human_score[row][col] = scoreMap[row][col];
			AI_score[row][col] = scoreMap[row][col];
			if (land_chess[row][col] == 0) {
				for (int k = 0; k < 4; k++) {
					int x = directs[k][0];
					int y = directs[k][1];
					//reset
					human_num = 0;
					AI_num = 0;
					empty_num = 0;

					//Calculate human score. (Forward)
					//假定人为白棋，所以玩家的棋子颜色为2
					for (int i = 1; i <= 4; i++) {
						if (row + i * y > 14 || col + i * x > 14)
							break;
						if (land_chess[row + i * y][col + i * x] == 2) {//Human chess point.
							human_num++;
						}
						else if (land_chess[row + i * y][col + i * x] == 0) {//Empty points.
							empty_num++;
							break;
						}
						else  //AI chess point.
							break;
					}
					//Calculate human score. (Backward)
					for (int i = 1; i <= 4; i++) {
						if (row - i * y < 0 || col - i * x < 0)
							break;
						if (land_chess[row - i * y][col - i * x] == 2) {//Human chess point.
							human_num++;
						}
						else if (land_chess[row - i * y][col - i * x] == 0) {//Empty points.
							empty_num++;
							break;
						}
						else  //AI chess point.
							break;
					}

					//Check which type of chess is it.
					if (human_num == 1) {//两子相连				
						if (empty_num == 1) { //眠二
#ifdef debug
							cout << "玩家有眠二" << endl;
#endif
							human_score[row][col] += (3 - 1);
						}
						else if (empty_num == 2) {//活二
							human_score[row][col] += (5 - 1);
#ifdef debug
							cout << "玩家有活二" << endl;
#endif
						}

					}
					else if (human_num == 2) {
						if (empty_num == 1) {//眠三
							human_score[row][col] += (50 - 1);
#ifdef debug
							cout << "玩家有眠三" << endl;
#endif
						}
						else if (empty_num == 2) {//活三
							human_score[row][col] += (200 - 1);
#ifdef debug
							cout << "玩家有活三" << endl;
#endif
						}
					}
					else if (human_num == 3) {
						if (empty_num == 1) {//冲四
							human_score[row][col] += (500 - 1);
#ifdef debug
							cout << "玩家有冲四" << endl;
#endif
						}
						else if (empty_num == 2) {//活四
							human_score[row][col] += (10000 - 1);
#ifdef debug
							cout << "玩家有活四" << endl;
#endif
						}
					}
					else if (human_num == 4) {//连五
						human_score[row][col] += (100000 - 1);
#ifdef debug
						cout << "玩家有活五" << endl;
#endif

					}
					else {
						human_score[row][col] += 1;
					}


					empty_num = 0;
					//Calculate AI score. (Forward)
					for (int i = 1; i <= 4; i++) {
						if (row + i * y > 14 || col + i * x > 14)
							break;
						if (land_chess[row + i * y][col + i * x] == 1) {//Ai chess point.
							AI_num++;
						}
						else if (land_chess[row + i * y][col + i * x] == 0) {//Empty points.
							empty_num++;
							break;
						}
						else  //human chess point.
							break;
					}


					//Calculate AI score. (Backward)
					for (int i = 1; i <= 4; i++) {
						if (row - i * y < 0 || col - i * x < 0)
							break;
						if (land_chess[row - i * y][col - i * x] == 1) {//AI chess point.
							AI_num++;
						}
						else if (land_chess[row - i * y][col - i * x] == 0) {//Empty points.
							empty_num++;
							break;
						}
						else  //Human chess point.
							break;
					}

					//Check which type of chess is it.
					if (AI_num == 1) {//两子相连				
						if (empty_num == 1) { //眠二
							AI_score[row][col] += 3;
#ifdef debug
							cout << "AI有眠二" << endl;
#endif
						}
						else if (empty_num == 2) {//活二
							AI_score[row][col] += 5;
#ifdef debug
							cout << "AI有活二" << endl;
#endif
						}

					}
					else if (AI_num == 2) {
						if (empty_num == 1) {//眠三
							AI_score[row][col] += 50;
#ifdef debug
							cout << "AI有眠三" << endl;
#endif
						}
						else if (empty_num == 2) {//活三
							AI_score[row][col] += 200;
#ifdef debug
							cout << "AI有活三" << endl;
#endif
						}
					}
					else if (AI_num == 3) {
						if (empty_num == 1) {//冲四
							AI_score[row][col] += 500;
#ifdef debug
							cout << "AI有冲四" << endl;
#endif
						}
						else if (empty_num == 2) {//活四
							AI_score[row][col] += 10000;
#ifdef debug
							cout << "AI有活四" << endl;
#endif
						}
					}
					else if (AI_num == 4) {//连五
						AI_score[row][col] += 100000;
#ifdef debug
						cout << "AI有连五" << endl;
#endif

					}
					else {
						AI_score[row][col] += 1;
					}
				}
			}
		}
	}
	int result_x, result_y;
	int max_score = 0;
	int flag;
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++) {
			if (AI_score[i][j] > max_score && land_chess[i][j] == 0) {
				max_score = AI_score[i][j];
				result_x = j;
				result_y = i;
#ifdef debug
				flag = 1;//表示是human的最高分
#endif // 

			}
		}
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++) {
			if (human_score[i][j] > max_score && land_chess[i][j] == 0) {
				max_score = human_score[i][j];
				result_x = j;
				result_y = i;
#ifdef debug
				flag = 0;//表示是AI的最高分
#endif // 
			}
		}
#ifdef debug
	if (flag == 1)
		cout << "human的最高分, ";
	else if (flag == 0)
		cout << "AI的最高分, ";
	cout << "最大处的分值为： " << max_score << endl;
#endif
	AI_x = result_x;
	AI_y = result_y;
}

int Chess::CaculateScore(int row, int col, int type) {//0表示AI，1表示玩家
	int human_num = 0;
	int AI_num = 0;
	int empty_num = 0;
	int directs[4][2] = { {1,0},{1,1},{0,1},{-1,1} };

	int human_score = scoreMap[row][col];
	int AI_score = scoreMap[row][col];
	for (int k = 0; k < 4; k++) {
		int x = directs[k][0];
		int y = directs[k][1];
		//reset
		human_num = 0;
		AI_num = 0;
		empty_num = 0;

		//Calculate human score. (Forward)
		//假定人为白棋，所以玩家的棋子颜色为2
		for (int i = 1; i <= 4; i++) {
			if (row + i * y > 14 || col + i * x > 14)
				break;
			if (land_chess[row + i * y][col + i * x] == 2) {//Human chess point.
				human_num++;
			}
			else if (land_chess[row + i * y][col + i * x] == 0) {//Empty points.
				empty_num++;
				break;
			}
			else  //AI chess point.
				break;
		}
		//Calculate human score. (Backward)
		for (int i = 1; i <= 4; i++) {
			if (row - i * y < 0 || col - i * x < 0)
				break;
			if (land_chess[row - i * y][col - i * x] == 2) {//Human chess point.
				human_num++;
			}
			else if (land_chess[row - i * y][col - i * x] == 0) {//Empty points.
				empty_num++;
				break;
			}
			else  //AI chess point.
				break;
		}

		//Check which type of chess is it.
		if (human_num == 1) {//两子相连				
			if (empty_num == 1) { //眠二
				human_score += (3 - 1);
			}
			else if (empty_num == 2) {//活二
				human_score += (5 - 1);
			}

		}
		else if (human_num == 2) {
			if (empty_num == 1) {//眠三
				human_score += (50 - 1);
			}
			else if (empty_num == 2) {//活三
				human_score += (200 - 1);
			}
		}
		else if (human_num == 3) {
			if (empty_num == 1) {//冲四
				human_score += (500 - 1);
			}
			else if (empty_num == 2) {//活四
				human_score += (10000 - 1);
			}
		}
		else if (human_num == 4) {//连五
			human_score += (100000 - 1);

		}
		else {
			human_score += 1;
		}

		empty_num = 0;
		//Calculate AI score. (Forward)
		for (int i = 1; i <= 4; i++) {
			if (row + i * y > 14 || col + i * x > 14)
				break;
			if (land_chess[row + i * y][col + i * x] == 1) {//Ai chess point.
				AI_num++;
			}
			else if (land_chess[row + i * y][col + i * x] == 0) {//Empty points.
				empty_num++;
				break;
			}
			else  //human chess point.
				break;
		}


		//Calculate AI score. (Backward)
		for (int i = 1; i <= 4; i++) {
			if (row - i * y < 0 || col - i * x < 0)
				break;
			if (land_chess[row - i * y][col - i * x] == 1) {//AI chess point.
				AI_num++;
			}
			else if (land_chess[row - i * y][col - i * x] == 0) {//Empty points.
				empty_num++;
				break;
			}
			else  //Human chess point.
				break;
		}

		//Check which type of chess is it.
		if (AI_num == 1) {//两子相连				
			if (empty_num == 1) { //眠二
				AI_score += 3;
			}
			else if (empty_num == 2) {//活二
				AI_score += 5;
			}

		}
		else if (AI_num == 2) {
			if (empty_num == 1) {//眠三
				AI_score += 50;
			}
			else if (empty_num == 2) {//活三
				AI_score += 200;
			}
		}
		else if (AI_num == 3) {
			if (empty_num == 1) {//冲四
				AI_score += 500;
			}
			else if (empty_num == 2) {//活四
				AI_score += 10000;
			}
		}
		else if (AI_num == 4) {//连五
			AI_score += 100000;

		}
		else {
			AI_score += 1;
		}
	}
	if (type == 1)
		return human_score;
	else if (type == 0)
		return AI_score;
}



void Chess::AIPlay() {
	CaculateScore();
	DrawOneChess(AI_x * BLOCK_WIDTH + MARGIN, AI_y * BLOCK_WIDTH + MARGIN);
}

//old CheckAiPlay
bool Chess::CheckNextBlack() {
	if (next_color == 1)
		return true;
	return false;
}

void ShowStartPage() {
	int circlex = 180, circley = 220;
	settextcolor(BLACK);
	setbkmode(TRANSPARENT);
	settextstyle(48, 60, _T("宋体"));
	outtextxy(200, 200, _T("开始游戏"));
	outtextxy(200, 350, _T("模式选择"));

	settextstyle(24, 20, _T("宋体"));
	outtextxy(350, 800, _T("按o键确定"));
	settextstyle(48, 60, _T("宋体"));
}

void GraphChange(Chess&c) {
	initgraph(MAX_X, MAX_Y);
	cleardevice();
	setbkcolor(WHITE);
	ShowStartPage();
	int flag = 1;//选择的选项
	setfillcolor(BLACK);
	int circlex = 180, circley = 220;
	BeginBatchDraw();

	while (true) {
		cleardevice();
		ShowStartPage();
		solidcircle(circlex, circley, 20);
		FlushBatchDraw();
		char input = _getch();
		if (input == 'w' && flag != 1) {
			flag--;
			circley -= 150;
			cleardevice();
			ShowStartPage();
			FlushBatchDraw();
		}
		else if (input == 's' && flag != 2) {
			flag++;
			circley += 150;
			cleardevice();
			ShowStartPage();
			solidcircle(circlex, circley, 20);
			FlushBatchDraw();
		}
		else if (input == 'o') {
			if (flag == 2)
				ChooseMode(c);
			else if (flag == 1)
				break;
		}
		EndBatchDraw();
	}
}
void ChooseMode(Chess &c) {
	cleardevice();
	setbkcolor(WHITE);
	BeginBatchDraw();
	int flag = 1;
	int circlex = 80, circley = 220;
	settextstyle(28, 24, _T("宋体"));
	outtextxy(100, 200, _T("玩家对战"));
	outtextxy(100, 350, _T("人机对战（玩家执黑）"));
	outtextxy(100, 500, _T("人机对战（玩家执白）"));
	solidcircle(circlex, circley, 20);
	FlushBatchDraw();
	while (true) {
		cleardevice();
		outtextxy(100, 200, _T("玩家对战"));
		outtextxy(100, 350, _T("人机对战（玩家执黑）"));
		outtextxy(100, 500, _T("人机对战（玩家执白）"));
		char input = _getch();
		if (input == 'w' && flag != 1) {
			flag--;
			circley -= 150;
			outtextxy(100, 200, _T("玩家对战"));
			outtextxy(100, 350, _T("人机对战（玩家执黑）"));
			outtextxy(100, 500, _T("人机对战（玩家执白）"));
			solidcircle(circlex, circley, 20);
			FlushBatchDraw();
		}
		else if (input == 's' && flag != 3) {
			flag++;
			circley += 150;
			outtextxy(100, 200, _T("玩家对战"));
			outtextxy(100, 350, _T("人机对战（玩家执黑）"));
			outtextxy(100, 500, _T("人机对战（玩家执白）"));
			solidcircle(circlex, circley, 20);
			FlushBatchDraw();
		}
		else if (input == 'o') {
			c.mode = flag;
			break;
		}
	}
};

int Chess::EvaluateValue(int row,int col) {
	return CaculateScore(row, col, AI_PLAYER) - CaculateScore(row, col, HUMAN_PLAYER);
}

int Chess::MinValue(int row, int col, int depth) {
	int value = -EvaluateValue(row, col);
	if (depth <= 0)
		return value;
	int min_value = INT_MAX;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (land_chess[i][j] != 0)
				continue;
			land_chess[i][j] = human_color;
			int temp = MaxValue(i, j, depth - 1);
			if (temp < min_value)
				min_value = temp;
			land_chess[i][j] = 0;
		}
	}
	return min_value;
}

int Chess::MaxValue(int row, int col, int depth) {
	int value = EvaluateValue(row, col);
	if (depth <= 0)
		return value;
	int max_value = INT_MIN;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (land_chess[i][j] != 0)
				continue;
			land_chess[i][j] = AI_color;
			int temp = MinValue(i, j, depth - 1);
			if (temp > max_value)
				max_value = temp;
			land_chess[i][j] = 0;
		}
	}
	return max_value;
}

void Chess::GetMinMaxEvaluate(int depth) {
	Point max_point[N * N] = { 0 };
	int max_value = INT_MIN;
	int k = 0;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (land_chess[i][j] != 0)
				continue;
			land_chess[i][j] = AI_color;
			int temp = MinValue(i, j, depth - 1);
			if (temp == max_value) {
				max_point[k].row = i;
				max_point[k].col = j;
				k++;
			}
			if (temp > max_value) {
				k = 0;
				memset(max_point, 0, sizeof(max_point));
				max_value = temp;
				max_point[k].row = i;
				max_point[k].col = j;
				k++;
			}
			land_chess[i][j] = 0;
		}
	}
	int index = (int)(rand() % k);
	AI_x = max_point[index].col;
	AI_y = max_point[index].row;
}

void Chess::AIPlayNew(int depth) {
	if (empty) {
		DrawOneChess(7 * BLOCK_WIDTH + MARGIN, 7 * BLOCK_WIDTH + MARGIN);
		empty = false;
	}
	else {
		GetMinMaxEvaluate(depth);
		DrawOneChess(AI_x * BLOCK_WIDTH + MARGIN, AI_y * BLOCK_WIDTH + MARGIN);
	}
}

//void PVP(Chess chess) {
//	FlushBatchDraw();
//	ExMessage m;
//	m = getmessage(EM_MOUSE);
//	DrawBackground();
//	chess.DrawLandChess();
//	if (m.message == WM_LBUTTONDOWN && chess.CheckClick(m)) {
//		chess.DrawOneChess(m.x, m.y);
//		FlushBatchDraw();
//		chess.winner = chess.WinCheck(m.x, m.y);
//		
//	}
//}

void Chess::ShowLastLand() {
	if (last_land.col == -1)
		return;
	cleardevice();
	DrawBackground();
	chess.DrawLandChess();
	setlinecolor(BLUE);
	int mar = 5;
	int r = R + 2;//画在外围
	//上方
	line(last_land.col * BLOCK_WIDTH + MARGIN - r, last_land.row * BLOCK_WIDTH + MARGIN - r,
		last_land.col * BLOCK_WIDTH + MARGIN - mar, last_land.row * BLOCK_WIDTH + MARGIN - r );
	line(last_land.col * BLOCK_WIDTH + MARGIN + mar, last_land.row * BLOCK_WIDTH + MARGIN - r,
		last_land.col * BLOCK_WIDTH + MARGIN + r, last_land.row * BLOCK_WIDTH + MARGIN - r);
	//下方(左右)
	line(last_land.col * BLOCK_WIDTH + MARGIN - r, last_land.row * BLOCK_WIDTH + MARGIN + r,
		last_land.col * BLOCK_WIDTH + MARGIN - mar, last_land.row * BLOCK_WIDTH + MARGIN + r);
	line(last_land.col * BLOCK_WIDTH + MARGIN + mar, last_land.row * BLOCK_WIDTH + MARGIN + r,
		last_land.col * BLOCK_WIDTH + MARGIN + r, last_land.row * BLOCK_WIDTH + MARGIN + r );
	//左方(上下)
	line(last_land.col * BLOCK_WIDTH + MARGIN - r, last_land.row * BLOCK_WIDTH + MARGIN - r,
		last_land.col * BLOCK_WIDTH + MARGIN - r, last_land.row * BLOCK_WIDTH + MARGIN - mar);
	line(last_land.col * BLOCK_WIDTH + MARGIN - r, last_land.row * BLOCK_WIDTH + MARGIN + mar,
		last_land.col * BLOCK_WIDTH + MARGIN - r, last_land.row * BLOCK_WIDTH + MARGIN + r);
	//右方(上下)
	line(last_land.col * BLOCK_WIDTH + MARGIN + r, last_land.row * BLOCK_WIDTH + MARGIN - r,
		last_land.col * BLOCK_WIDTH + MARGIN + r, last_land.row * BLOCK_WIDTH + MARGIN - mar);
	line(last_land.col * BLOCK_WIDTH + MARGIN + r, last_land.row * BLOCK_WIDTH + MARGIN + mar ,
		last_land.col * BLOCK_WIDTH + MARGIN + r, last_land.row * BLOCK_WIDTH + MARGIN + r);
}
