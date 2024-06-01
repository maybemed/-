#include<iostream>
#include<graphics.h>
#include<string>
#include<windows.h>
#include"chess.h"
#include"functions.h"
#include"parameter.h"

HWND main_game;
Chess chess;
struct maxScorePoint {
	int row;
	int col;
};
int main() {
	GraphChange(chess);
	initgraph(MAX_X, MAX_Y, EX_SHOWCONSOLE);
	DrawBackground();
	main_game = GetHWnd();
	SetWindowText(main_game, L"五子棋对战");
	setbkcolor(RGB(255, 205, 150));
	cleardevice();
	DrawBackground();
	BeginBatchDraw();
	int winner = 0;
	//1表示人人对战，0表示人机对战
	while (true) {
		//cleardevice();
		//DrawBackground();
		chess.DrawLandChess();
		//人人对战
		if (chess.mode == 1) {
			FlushBatchDraw();
			ExMessage m;
			m = getmessage(EM_MOUSE);
			DrawBackground();
			chess.DrawLandChess();
			
			if (m.message == WM_LBUTTONDOWN && chess.CheckClick(m)) {
				
				chess.DrawOneChess(m.x, m.y);
				FlushBatchDraw();
				//标记上一个落子
				chess.ShowLastLand();
				winner = chess.WinCheck(m.x, m.y);
				if (winner == 1 || winner == 2) {
					if (!GameAgain(winner))
						break;
				}
			}
		}
		//人机对战，玩家先手
		else if (chess.mode == 2) {
			/*BeginBatchDraw();
			FlushBatchDraw();
			ExMessage m;
			DrawBackground();
			chess.DrawLandChess();

			int depth = 2;

			if (!chess.CheckNextBlack()) {
				chess.AIPlayNew(depth);
				winner = chess.WinCheck(chess.AI_x * BLOCK_WIDTH + MARGIN, chess.AI_y * BLOCK_WIDTH + MARGIN);
			}
			else {
				m = getmessage(EM_MOUSE);
				if (m.message == WM_LBUTTONDOWN && chess.CheckClick(m)) {
					chess.DrawOneChess(m.x, m.y);
					FlushBatchDraw();
					winner = chess.WinCheck(m.x, m.y);
				}
				if (winner == 1 || winner == 2) {
					if (!GameAgain(winner))
						break;
				}
			}*/
		}
		//人机对战，默认ai先手
		else if (chess.mode == 3) {
			BeginBatchDraw();
			FlushBatchDraw();
			ExMessage m;
			DrawBackground();
			chess.DrawLandChess();

			int depth = 2;

			if (chess.CheckNextBlack()) {
				chess.AIPlayNew(depth);
				winner = chess.WinCheck(chess.AI_x * BLOCK_WIDTH + MARGIN, chess.AI_y * BLOCK_WIDTH + MARGIN);
				//标记上一个落子
				chess.ShowLastLand();
			}
			else {
				m = getmessage(EM_MOUSE);
				if (m.message == WM_LBUTTONDOWN && chess.CheckClick(m)) {
					chess.DrawOneChess(m.x, m.y);
					FlushBatchDraw();
					winner = chess.WinCheck(m.x, m.y);
					//标记上一个落子
					chess.ShowLastLand();
				}
				if (winner == 1 || winner == 2) {
					if (!GameAgain(winner))
						break;
				}
			}
		}
	}
	EndBatchDraw();
	return 0;
}