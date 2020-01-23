#include <iostream>
#include <windows.h>
#include <MMSystem.h>
#include "Board.h"
#pragma comment(lib,"winmm.lib")

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
#define WHITE		SetConsoleTextAttribute(COL,0x00ff);//����+�ش����

MCI_OPEN_PARMS mciOpen;  // MCI_OPEN_PARAMS ����ü ���� , ������ �ε�
MCI_PLAY_PARMS mciPlay;		//������ ���
int dwID;

using namespace std;

void Board::OpenBackgroundSound(void)
{
	mciOpen.lpstrElementName = L"backgroundsound.mp3"; // �����̸�
	mciOpen.lpstrDeviceType = L"mpegvideo";  // mpegvideo : mp3, waveaudio : wav, avivideo : avi

	mciSendCommand(NULL, MCI_OPEN, MCI_OPEN_ELEMENT | MCI_OPEN_TYPE, (DWORD)(LPVOID)&mciOpen);  //���� open

	dwID = mciOpen.wDeviceID;

	mciSendCommand(dwID, MCI_PLAY, MCI_NOTIFY | 0x00010000L, (DWORD)(LPVOID)&mciPlay);
	//0x00010000L == MCI_DGV_PLAY_REPEAT ������ݺ�
	/*#ifndef MCI_DGV_PLAY_REPEAT
	#define MCI_DGV_PLAY_REPEAT 0x00010000L
	#endif ������ �����ص� ��*/
}
void Board::CloseBackgroundSound(void)
{
	mciSendCommand(dwID, MCI_CLOSE, 0, NULL);
}
Board::Board()
{
	int i, j;

	for (i = 0; i < 10; i++) 
    {
		for (j = 0; j < 20; j++)
			board_[i][j] = EMPTY;
	}
}

int Board::GetState(Point pos)
{ 
	return board_[pos.GetX()][pos.GetY()]; 
}

void Board::SetState(Point pos, int state) 
{ 
	board_[pos.GetX()][pos.GetY()] = state;	
}

int Board::CheckLineFull(Point reference_pos)
{
	int count = 0, erased_line = 0, exp_score = 2;//exp_score�� �������� ���ÿ� ������ �߰��� ������ ����
	int line = 0;

	int sero, garo, temp_garo;
	for (sero = 0; sero < 19; sero++) //��
	{
		for (garo = 0; garo < 10; garo++)//ĭ
		{
			if (board_[garo][sero] == EMPTY)	//sero���� ���������� �ʴٸ�
				break;
		}

		//sero��°���� �������ִٸ�..
		if (garo == 10)
		{

			PlaySound(TEXT("block.wav"), NULL, SND_ASYNC);
			for (int k = 0; k < 10; k++)//garo������ ����� �ϴ� ����k
			{
				for (line = 0; line + sero <19; line++)//i��° �� ���� �� ��ĭ�� ������ �ϹǷ� ���� line ���
				{
					board_[k][line + sero] = board_[k][line + sero + 1];

					if (board_[k][line + sero + 1] != EMPTY)	//����ĭ�� ��ĭ�̾ƴ϶�� �׷���
					{
						Point::GotoXY(reference_pos + Point::GetScrPosFromCurPos(Point(k, sero + line)));
						if (board_[k][line + sero] == 0) SHY_BLUE
						else if (board_[k][line + sero] == 1) BLUE
						else if (board_[k][line + sero] == 2) GOLD
						else if (board_[k][line + sero] == 3) GREEN
						else if (board_[k][line + sero] == 4) HIGH_GREEN
						else if (board_[k][line + sero] == 5) PURPLE
						else if (board_[k][line + sero] == 6) RED
							cout << "��";
						BLACK
					}
					else
					{
						Point::GotoXY(reference_pos + Point::GetScrPosFromCurPos(Point(k, sero + line)));
						cout << "  ";

					}
				}
			}
			count = 100;	//�����̶� ����Եȴٸ� count�� 100������ �ʱ�ȭ
			erased_line++;//�ѹ��� ������ ���� ����
						  //2���̻� ���ﶧ �ʿ���

			for (temp_garo = 0; temp_garo < 10; temp_garo++)
			{
				if (board_[garo][sero + 1] == EMPTY)
					break;
			}
			if (temp_garo == 10)
				sero--;			//�ǹ�ĭ�� ���������� ������ sero--����
		}
	}

	//�������� �������� ���ʽ�����
	if (erased_line != 1)
		for (int temp = 0; temp < erased_line; temp++)
			count *= exp_score;

	return count;
}