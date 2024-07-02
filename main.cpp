#include<iostream>
#include<graphics.h>
#include<string>
#include<windows.h>
#include<mmsystem.h>//这是包含多媒体设备接口头文件
#pragma comment(lib,"winmm.lib")//加载静态库
#include"chess.h"
#include"functions.h"
#include"parameter.h"
//#define DEBUG
using namespace std;
HWND main_game;
ExMessage m;
Chess chess;
struct maxScorePoint {
	int row;
	int col;
};
int main() {
	GraphChange(chess);
	initgraph(MAX_X + 200, MAX_Y, EX_SHOWCONSOLE);
	BeginBatchDraw();
	DrawBackground();
	main_game = GetHWnd();
	SetWindowText(main_game, L"五子棋对战");
	FlushBatchDraw();
	cleardevice();
	DrawBackground();
	int winner = 0;
	m = getmessage(EX_MOUSE);
	//1表示人人对战，0表示人机对战
	while (true) {

		chess.DrawLandChess();
		//绘制悔棋区域
		ShowBackArea();
		//人人对战
		if (chess.mode == 1) {
			FlushBatchDraw();
			
			m = getmessage(EM_MOUSE);
			
			if (m.message == WM_LBUTTONDOWN) {
				//判断进行悔棋
				chess.BackChess(m.x,m.y);
				//进行正常落子
				if (chess.CheckClick(m)) 
					chess.DrawOneChess(m.x, m.y);
				FlushBatchDraw();
				//标记上一个落子
				chess.ShowLastLand();
				winner = chess.WinCheck(m.x, m.y);
				if (winner == 1 || winner == 2) {
					if (!GameAgain(winner))
						break;
					else {
						DrawBackground();
						chess.DrawLandChess();
					}
				}
			}
		}
		//人机对战，困难
		else if (chess.mode == 3) {
			BeginBatchDraw();
			FlushBatchDraw();

			if (chess.CheckNextBlack()) {
				chess.AIPlay();
				winner = chess.WinCheck(chess.AI_x * BLOCK_WIDTH + MARGIN, chess.AI_y * BLOCK_WIDTH + MARGIN);
				//标记上一个落子
				chess.ShowLastLand();
			}
			else {
				m = getmessage(EM_MOUSE);
				if (m.message == WM_LBUTTONDOWN) {
					//判断进行悔棋
					chess.BackChess(m.x, m.y);
					//进行正常落子
					if (chess.CheckClick(m)) {
						chess.DrawOneChess(m.x, m.y);
						FlushBatchDraw();
						winner = chess.WinCheck(m.x, m.y);
					}
						//标记上一个落子
						chess.ShowLastLand();
					
				}
				if (winner == 1 || winner == 2) {
					if (!GameAgain(winner))
						break;
					else
						chess.empty = true;
				}
			}
		}
		//人机对战，简单
		else if (chess.mode == 2) {
			BeginBatchDraw();
			FlushBatchDraw();

			int depth = 3;

			if (chess.CheckNextBlack()) {
				chess.AIPlayNew(depth);
				if (chess.special_AI_land == false)
					winner = chess.WinCheck(chess.AI_x * BLOCK_WIDTH + MARGIN, chess.AI_y * BLOCK_WIDTH + MARGIN);
				else
					winner = chess.WinCheck(chess.temp.col * BLOCK_WIDTH + MARGIN, chess.temp.row * BLOCK_WIDTH + MARGIN);
				//标记上一个落子
				chess.ShowLastLand();
			}
			else {
				m = getmessage(EM_MOUSE);
				if (m.message == WM_LBUTTONDOWN) {
					//判断进行悔棋
					chess.BackChess(m.x, m.y);
					//进行正常落子
					if (chess.CheckClick(m))
						chess.DrawOneChess(m.x, m.y);
					FlushBatchDraw();
					winner = chess.WinCheck(m.x, m.y);
					//标记上一个落子
					chess.ShowLastLand();
				}
				if (winner == 1 || winner == 2) {
					if (!GameAgain(winner))
						break;
					else
						chess.empty = true;
				}
			}
		}
	}
	EndBatchDraw();
	return 0;
}