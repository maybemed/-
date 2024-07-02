#ifndef CHESS
#define CHESS
#include<graphics.h>
struct Point {
	int row;
	int col;
};
class Chess {
	int next_color = 1;//next棋子的颜色,1Black、2White
	int land_chess[16][16] = { 0 };//存放已经下落的棋子,一维表示行二维表示列；1BLACK,2WHITE
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
	bool have_backed = false;//记录是否刚刚进行一次悔棋
	Point last_land{};//上一次落子的坐标
	Point second_last_land;//上上次落子坐标，用于悔棋操作
	Point third_last_land;//上上上次落子坐标，用于人机对战悔棋
	Point AIPoint{};
public:
	Point temp;//迫不得已定义，逻辑十分混乱，别再用它了
	bool special_AI_land = false;//判断AI上一次是否落在了单独写的活四/连五上，即判断AIPoint是否刚刚发挥作用,用于判断WinCheck的执行
	Chess() {
		last_land.col = -1; last_land.row = -1;
		AIPoint.row = -1; AIPoint.col = -1;
	}
	int winner = 0;
	bool empty = true;
	int mode = 0;//1-玩家对战,2-人机-简单，3-人机-困难
	int AI_x, AI_y;//AI即将下的落子x，y

	void init();//全部初始化，重新开始游戏
	void DrawOneChess(int x, int y);//接收一个棋子
	void DrawLandChess();//画出所有已经下落的棋子
	bool CheckClick(ExMessage msg);//判断是否脱离边界，判断当前位置是否已经存在棋子
	int WinCheck(int x, int y);//判断是否胜利，如果是返回胜利的棋子颜色，否则返回0
	void AIPlay();//ai落子
	void AIPlayNew(int depth);
	void CaculateScore();//计算落子得分
	int CaculateScore(int row, int col,int type);//新算法计算落子得分
	bool CheckNextBlack();//判断是否应该AI落子
	int EvaluateValue(int row, int col);//计算AI_score - human-score;
	int MinValue(int row,int col,int depth);//返回当前坐标的指定深度下的最小value
	int MaxValue(int row, int col, int depth);//返回当前坐标的指定深度下的最大value
	void GetMinMaxEvaluate(int depth);//决定ai下棋的位置
	void ShowLastLand();//特别显示上一个落子
	void BackChess(int click_x,int click_y);//判断并进行悔棋
	void DoBack();//进行悔棋操作，用在BackChess内部
};
#endif