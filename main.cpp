#include<iostream>
#include<graphics.h>
#include<string>
#include<windows.h>
#include<mmsystem.h>//���ǰ�����ý���豸�ӿ�ͷ�ļ�
#pragma comment(lib,"winmm.lib")//���ؾ�̬��
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
	SetWindowText(main_game, L"�������ս");
	FlushBatchDraw();
	cleardevice();
	DrawBackground();
	int winner = 0;
	m = getmessage(EX_MOUSE);
	//1��ʾ���˶�ս��0��ʾ�˻���ս
	while (true) {

		chess.DrawLandChess();
		//���ƻ�������
		ShowBackArea();
		//���˶�ս
		if (chess.mode == 1) {
			FlushBatchDraw();
			
			m = getmessage(EM_MOUSE);
			
			if (m.message == WM_LBUTTONDOWN) {
				//�жϽ��л���
				chess.BackChess(m.x,m.y);
				//������������
				if (chess.CheckClick(m)) 
					chess.DrawOneChess(m.x, m.y);
				FlushBatchDraw();
				//�����һ������
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
		//�˻���ս������
		else if (chess.mode == 3) {
			BeginBatchDraw();
			FlushBatchDraw();

			if (chess.CheckNextBlack()) {
				chess.AIPlay();
				winner = chess.WinCheck(chess.AI_x * BLOCK_WIDTH + MARGIN, chess.AI_y * BLOCK_WIDTH + MARGIN);
				//�����һ������
				chess.ShowLastLand();
			}
			else {
				m = getmessage(EM_MOUSE);
				if (m.message == WM_LBUTTONDOWN) {
					//�жϽ��л���
					chess.BackChess(m.x, m.y);
					//������������
					if (chess.CheckClick(m)) {
						chess.DrawOneChess(m.x, m.y);
						FlushBatchDraw();
						winner = chess.WinCheck(m.x, m.y);
					}
						//�����һ������
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
		//�˻���ս����
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
				//�����һ������
				chess.ShowLastLand();
			}
			else {
				m = getmessage(EM_MOUSE);
				if (m.message == WM_LBUTTONDOWN) {
					//�жϽ��л���
					chess.BackChess(m.x, m.y);
					//������������
					if (chess.CheckClick(m))
						chess.DrawOneChess(m.x, m.y);
					FlushBatchDraw();
					winner = chess.WinCheck(m.x, m.y);
					//�����һ������
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