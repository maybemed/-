#include"chess.h"
void DrawBackground();
bool GameAgain(int& winner);//判断是否再来一局
void GraphChange(Chess&c);//起始页面
void ChooseMode(Chess&c);//模式选择
void ShowStartPage();
void PVP(Chess chess);
void AI_HumanWhite(Chess chess);
void AI_HumanBlack(Chess chess);
void ShowBackArea();//绘制悔棋区域
void Introduction();//规则介绍
// 载入PNG图并去透明部分
void drawAlpha(IMAGE* picture, int  picture_x, int picture_y); //x为载入图片的X坐标，y为Y坐标