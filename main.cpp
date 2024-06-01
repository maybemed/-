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
	SetWindowText(main_game, L"�������ս");
	setbkcolor(RGB(255, 205, 150));
	cleardevice();
	DrawBackground();
	BeginBatchDraw();
	int winner = 0;
	//1��ʾ���˶�ս��0��ʾ�˻���ս
	while (true) {
		//cleardevice();
		//DrawBackground();
		chess.DrawLandChess();
		//���˶�ս
		if (chess.mode == 1) {
			FlushBatchDraw();
			ExMessage m;
			m = getmessage(EM_MOUSE);
			DrawBackground();
			chess.DrawLandChess();
			
			if (m.message == WM_LBUTTONDOWN && chess.CheckClick(m)) {
				
				chess.DrawOneChess(m.x, m.y);
				FlushBatchDraw();
				//�����һ������
				chess.ShowLastLand();
				winner = chess.WinCheck(m.x, m.y);
				if (winner == 1 || winner == 2) {
					if (!GameAgain(winner))
						break;
				}
			}
		}
		//�˻���ս���������
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
		//�˻���ս��Ĭ��ai����
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
				//�����һ������
				chess.ShowLastLand();
			}
			else {
				m = getmessage(EM_MOUSE);
				if (m.message == WM_LBUTTONDOWN && chess.CheckClick(m)) {
					chess.DrawOneChess(m.x, m.y);
					FlushBatchDraw();
					winner = chess.WinCheck(m.x, m.y);
					//�����һ������
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