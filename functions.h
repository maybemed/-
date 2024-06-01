#include"chess.h"
void DrawBackground();
bool GameAgain(int& winner);//判断是否再来一局
void GraphChange(Chess&c);//起始页面
void ChooseMode(Chess&c);//模式选择
void ShowStartPage();
void PVP(Chess chess);
void AI_HumanWhite(Chess chess);
void AI_HumanBlack(Chess chess);