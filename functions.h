#include"chess.h"
void DrawBackground();
bool GameAgain(int& winner);//�ж��Ƿ�����һ��
void GraphChange(Chess&c);//��ʼҳ��
void ChooseMode(Chess&c);//ģʽѡ��
void ShowStartPage();
void PVP(Chess chess);
void AI_HumanWhite(Chess chess);
void AI_HumanBlack(Chess chess);
void ShowBackArea();//���ƻ�������
void Introduction();//�������
// ����PNGͼ��ȥ͸������
void drawAlpha(IMAGE* picture, int  picture_x, int picture_y); //xΪ����ͼƬ��X���꣬yΪY����