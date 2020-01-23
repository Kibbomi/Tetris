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
#define WHITE		SetConsoleTextAttribute(COL,0x00ff);//흰배경+해당색깔

MCI_OPEN_PARMS mciOpen;  // MCI_OPEN_PARAMS 구조체 변수 , 파일을 로드
MCI_PLAY_PARMS mciPlay;		//파일을 재생
int dwID;

using namespace std;

void Board::OpenBackgroundSound(void)
{
	mciOpen.lpstrElementName = L"backgroundsound.mp3"; // 파일이름
	mciOpen.lpstrDeviceType = L"mpegvideo";  // mpegvideo : mp3, waveaudio : wav, avivideo : avi

	mciSendCommand(NULL, MCI_OPEN, MCI_OPEN_ELEMENT | MCI_OPEN_TYPE, (DWORD)(LPVOID)&mciOpen);  //파일 open

	dwID = mciOpen.wDeviceID;

	mciSendCommand(dwID, MCI_PLAY, MCI_NOTIFY | 0x00010000L, (DWORD)(LPVOID)&mciPlay);
	//0x00010000L == MCI_DGV_PLAY_REPEAT 배경음반복
	/*#ifndef MCI_DGV_PLAY_REPEAT
	#define MCI_DGV_PLAY_REPEAT 0x00010000L
	#endif 위에다 선언해도 됨*/
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
	int count = 0, erased_line = 0, exp_score = 2;//exp_score은 여러줄을 동시에 깼을때 추가될 점수의 배율
	int line = 0;

	int sero, garo, temp_garo;
	for (sero = 0; sero < 19; sero++) //줄
	{
		for (garo = 0; garo < 10; garo++)//칸
		{
			if (board_[garo][sero] == EMPTY)	//sero줄이 가득차있지 않다면
				break;
		}

		//sero번째줄이 가득차있다면..
		if (garo == 10)
		{

			PlaySound(TEXT("block.wav"), NULL, SND_ASYNC);
			for (int k = 0; k < 10; k++)//garo랑같은 기능을 하는 변수k
			{
				for (line = 0; line + sero <19; line++)//i번째 줄 위로 다 한칸식 내려야 하므로 변수 line 사용
				{
					board_[k][line + sero] = board_[k][line + sero + 1];

					if (board_[k][line + sero + 1] != EMPTY)	//위에칸이 빈칸이아니라면 그려라
					{
						Point::GotoXY(reference_pos + Point::GetScrPosFromCurPos(Point(k, sero + line)));
						if (board_[k][line + sero] == 0) SHY_BLUE
						else if (board_[k][line + sero] == 1) BLUE
						else if (board_[k][line + sero] == 2) GOLD
						else if (board_[k][line + sero] == 3) GREEN
						else if (board_[k][line + sero] == 4) HIGH_GREEN
						else if (board_[k][line + sero] == 5) PURPLE
						else if (board_[k][line + sero] == 6) RED
							cout << "■";
						BLACK
					}
					else
					{
						Point::GotoXY(reference_pos + Point::GetScrPosFromCurPos(Point(k, sero + line)));
						cout << "  ";

					}
				}
			}
			count = 100;	//한줄이라도 지우게된다면 count는 100점으로 초기화
			erased_line++;//한번에 지워진 줄의 개수
						  //2줄이상 지울때 필요함

			for (temp_garo = 0; temp_garo < 10; temp_garo++)
			{
				if (board_[garo][sero + 1] == EMPTY)
					break;
			}
			if (temp_garo == 10)
				sero--;			//맨밑칸이 안지워지기 때문에 sero--해줌
		}
	}

	//여러줄을 지웠을때 보너스점수
	if (erased_line != 1)
		for (int temp = 0; temp < erased_line; temp++)
			count *= exp_score;

	return count;
}