#ifndef CHESS
#define CHESS
#include<graphics.h>
struct Point {
	int row;
	int col;
};
class Chess {
	int next_color = 1;//next���ӵ���ɫ,1Black��2White
	int land_chess[16][16] = { 0 };//����Ѿ����������,һά��ʾ�ж�ά��ʾ�У�1BLACK,2WHITE
	int human, ai;
	int scoreMap[15][15] = {
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,1,1,1,1,1,1,1,1,1,1,1,1,1,0},
	{0,1,2,2,2,2,2,2,2,2,2,2,2,1,0},
	{0,1,2,3,3,3,3,3,3,3,3,3,2,1,0},
	{0,1,2,3,4,4,4,4,4,4,4,3,2,1,0},
	{0,1,2,3,4,5,5,5,5,5,4,3,2,1,0},
	{0,1,2,3,4,5,6,6,6,5,4,3,2,1,0},
	{0,1,2,3,4,5,6,7,6,5,4,3,2,1,0},
	{0,1,2,3,4,5,6,6,6,5,4,3,2,1,0},
	{0,1,2,3,4,5,5,5,5,5,4,3,2,1,0},
	{0,1,2,3,4,4,4,4,4,4,4,3,2,1,0},
	{0,1,2,3,3,3,3,3,3,3,3,3,2,1,0},
	{0,1,2,2,2,2,2,2,2,2,2,2,2,1,0},
	{0,1,1,1,1,1,1,1,1,1,1,1,1,1,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	};
	int human_score[15][15];
	int AI_score[15][15];
	int human_color = 2;
	int AI_color = 1;
	Point last_land{};//��һ�����ӵ�����
public:
	Chess() { last_land.col = -1; last_land.row = -1; }
	int winner = 0;
	bool empty = true;
	int mode = 3;//1-��Ҷ�ս,2-�˻�-��ִ�ڣ�3-�˻�-��ִ��
	int AI_x, AI_y;//AI�����µ�����x��y

	void init();//ȫ����ʼ�������¿�ʼ��Ϸ
	void DrawOneChess(int x, int y);//����һ������
	void DrawLandChess();//���������Ѿ����������
	bool CheckClick(ExMessage msg);//�ж��Ƿ�����߽磬�жϵ�ǰλ���Ƿ��Ѿ���������
	int WinCheck(int x, int y);//�ж��Ƿ�ʤ��������Ƿ���ʤ����������ɫ�����򷵻�0
	void AIPlay();//ai����
	void AIPlayNew(int depth);
	void CaculateScore();//�������ӵ÷�
	int CaculateScore(int row, int col,int type);
	bool CheckNextBlack();//�ж��Ƿ�Ӧ��AI����
	int EvaluateValue(int row, int col);//����AI_score - human-score;
	int MinValue(int row,int col,int depth);//���ص�ǰ�����ָ������µ���Сvalue
	int MaxValue(int row, int col, int depth);//���ص�ǰ�����ָ������µ����value
	void GetMinMaxEvaluate(int depth);//����ai�����λ��
	void ShowLastLand();//�ر���ʾ��һ������
};
#endif