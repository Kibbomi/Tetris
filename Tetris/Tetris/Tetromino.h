#ifndef KIBBOMI_TETROMINO
#define KIBBOMI_TETROMINO

#include "Point.h"
#include "Board.h"
#include "Option.h"	//for static members

#define COL 		GetStdHandle(STD_OUTPUT_HANDLE)
#define BLACK 		SetConsoleTextAttribute(COL,0x00f0);
#define DARK_BLUE	SetConsoleTextAttribute(COL,0x00f1);
#define GREEN 		SetConsoleTextAttribute(COL,0x00f2);
#define BLUE_GREEN 	SetConsoleTextAttribute(COL,0x00f3);
#define BLOOD 		SetConsoleTextAttribute(COL,0x00f4);
#define PURPLE 		SetConsoleTextAttribute(COL,0x00f5);
#define GOLD 		SetConsoleTextAttribute(COL,0x00f6);
#define ORIGNAL		SetConsoleTextAttribute(COL,0x00f7);
#define GRAY 		SetConsoleTextAttribute(COL,0x00f8);
#define BLUE		SetConsoleTextAttribute(COL,0x00f9);
#define HIGH_GREEN	SetConsoleTextAttribute(COL,0x00fa);
#define SHY_BLUE 	SetConsoleTextAttribute(COL,0x00fb);
#define RED 		SetConsoleTextAttribute(COL,0x00fc);
#define PLUM 		SetConsoleTextAttribute(COL,0x00fd);
#define YELLOW 		SetConsoleTextAttribute(COL,0x00fe);
#define WHITE		SetConsoleTextAttribute(COL,0x00ff);//��� ����+���� �� ������

#define TETROMINO_TYPE_COUNT 7
#define ROTATE_COUNT 4
//const Point g_next_tetromino_init_pos(29, 3);
const Point g_next_tetromino_init_pos(13, 17);
const Point g_cur_tetromino_init_pos(4, 20);

enum TETROMINO_TYPE { TETROMINO_I, TETROMINO_J, TETROMINO_L, TETROMINO_O, TETROMINO_S, TETROMINO_T, TETROMINO_Z };

class Tetromino
{
public:
	Tetromino(Board *board, TETROMINO_TYPE type);
	virtual void Draw(Point reference_pos);			        // ���� ȭ�� �߽� ��ġ�� �������� �׸���
	virtual void Erase(Point reference_pos);		        // ���� ȭ�� �߽� ��ġ�� �������� �����
	bool MoveDown(Point reference_pos);		        // �� ĭ ��������, ��ȿ�� ��ġ�� �ٽ� �׸�
	void MoveRight(Point reference_pos);	        // �� ĭ ���������� �̵�, ��ȿ�� ��ġ�� �ٽ� �׸�
	void MoveLeft(Point reference_pos);		        // �� ĭ �������� �̵�, ��ȿ�� ��ġ�� �ٽ� �׸�
	void Rotate(Point reference_pos);		        // ȸ��, ��ȿ�� ��ġ�� �ٽ� �׸�
	void GoBottom(Point reference_pos);		        // ���ϴ����� �̵�, ��ȿ�� ������ MoveDown() ����
	virtual void MarkCurTetrominoPos(Point reference_pos);	// �� �������� �� �Ŀ� board_�� ��ü�� ���� �� setting
	bool CheckEndCondition(void);					// ���� ���� �˻�, y�� �������� 20�̻�(���� ��)�̸� ����(return true)
	void SetCenterPos(Point pos);					// �߽� ��ġ ����    
	Point GetCenterPos(void) { return center_pos_; }

	Point Shadowtetromino(Point reference_pos);
	bool ShadowtetrominoCheck(Point temp);
	void ShadowDraw(Point reference_pos, Point temp);
	void ShadowErase(Point reference_pos, Point temp);

	void SaveDraw(Point reference_pos);
	void SaveErase(Point reference_pos);
	virtual bool CheckValidPos(void);	        // ���� ��Ʈ�ι̳� ��ġ�� ��ȿ���� �˻�, ���� ����� �ʰ� �ٸ� ��Ʈ�ι̳밡 �׿����� ����

protected:
	Point center_pos_;    // ���� �߽� ��ġ (���� �迭 ����)
	TETROMINO_TYPE type_;               // ��Ʈ�ι̳� Ÿ��
	int rotate_;				        // ���� ȸ�� ��ġ
	Board *board_;			 // Board ��ü ������ �˱� ���� Board ��ü�� ����    
};

#endif