#ifndef KIBBOMI_BOARD
#define KIBBOMI_BOARD

#include "Point.h"

#define EMPTY -1

class Board
{
public:
	Board();
	int GetState(Point pos);                // Pos ��ġ�� ���¸� ��ȯ�� : �ܼ��� board_[][] ���� ��ȯ�ϸ� ��
	void SetState(Point pos, int state);    // Pos ��ġ�� ���� State ������ ������
	int CheckLineFull(Point reference_pos); // Ư�� ���� ��Ʈ�ι̳�� ���� �� �ִ��� ����, ���� �� �ִٸ� �� ���� ���ε��� �� ĭ�� ����
											// ���������� ������ ���� �� ��ȯ
	void OpenBackgroundSound(void);//���� ��� 
	void CloseBackgroundSound(void);//���� ����

private:
	int board_[10][20];
};

#endif