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
void Chess::AIPlay() {
	CaculateScore();
	DrawOneChess(AI_x * BLOCK_WIDTH + MARGIN, AI_y * BLOCK_WIDTH + MARGIN);
}