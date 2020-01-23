#include "Tetris.h"
#include "Controller.h"
#include "Tetromino.h"
//#include "GhostTetromino.h"
#include <conio.h>
#include <cstdlib>
#include <iostream>
#include <windows.h>
#include <iomanip>
#include <MMSystem.h> 
#pragma comment(lib,"winmm") 

using namespace std;

Tetris::Tetris(Point reference_pos, int key_esc, int key_right, int key_left, int key_rotate, int key_down, int key_space, int key_savetetromino, int player) : reference_pos_(reference_pos), player_(player)
{
	running_ = true;
	cur_tetromino_ = NULL;
	next_tetromino_ = NULL;
	save_tetromino_ = NULL;
	start_time_ = clock();
	falling_speed_ = 0.8;
	SetCursorInvisible();
	controller_.SetController(key_esc, key_right, key_left, key_rotate, key_down, key_space, key_savetetromino);
	DrawBoard();
	GenerateNextTetromino();
	GetCurTetrominoFromNext();
	GenerateNextTetromino();
	cur_tetromino_->Draw(reference_pos_);	cur_tetromino_->ShadowDraw(reference_pos_, cur_tetromino_->Shadowtetromino(reference_pos_));
	next_tetromino_->Draw(reference_pos_);
	score_.Print(reference_pos_);
}

void Tetris::DrawBoard(void)
{
	int i, temp;
	board_.Board::OpenBackgroundSound();
	Point::GotoXY(reference_pos_);
	cout << "�ˢˢˢˢˢˢˢˢˢˢˢˢˢˢˢˢˢˢ�";
	for (i = 0; i < 6; i++) {
		Point::GotoXY(reference_pos_ + Point(0, i + 1));
		cout << "��                    ��            ��";
	}
	Point::GotoXY(reference_pos_ + Point(0, (i++) + 1));
	cout << "��                    �ˢˢˢˢˢˢˢ�";
	temp = i;
	for (i; i < temp + 3; i++) {
		Point::GotoXY(reference_pos_ + Point(0, i + 1));
		cout << "��                    ��            ��";
	}
	Point::GotoXY(reference_pos_ + Point(0, (i++) + 1));
	cout << "��                    �ˢˢˢˢˢˢˢ�" << endl;
	temp = i;
	for (i; i < temp + 9; i++) {
		Point::GotoXY(reference_pos_ + Point(0, i + 1));
		cout << "��                    ��            ��";
	}
	Point::GotoXY(reference_pos_ + Point(0, (i++) + 1));
	cout << "�ˢˢˢˢˢˢˢˢˢˢˢˢˢˢˢˢˢˢ�";

	//�÷��̾���� �޾Ƽ� ���� �Է¿� ����Ͽ���.
	if (player_ == 1)
	{
		Point::GotoXY(reference_pos_ + Point(24, 12));
		cout << "ȸ��:" << "��";
		Point::GotoXY(reference_pos_ + Point(24, 13));
		cout << "��:" << "��";
		Point::GotoXY(reference_pos_ + Point(24, 14));
		cout << "��:" << "��";
		Point::GotoXY(reference_pos_ + Point(24, 15));
		cout << "ȸ��:" << "��";
		Point::GotoXY(reference_pos_ + Point(24, 16));
		cout << "����:" << "Space";
		Point::GotoXY(reference_pos_ + Point(24, 17));
		cout << "����:��<<��c";
		Point::GotoXY(reference_pos_ + Point(24, 18));
		cout << "sa��:";
		Point::GotoXY(reference_pos_ + Point(24, 19));
		cout << "ve��:";
	}
	else
	{
		Point::GotoXY(reference_pos_ + Point(24, 12));
		cout << "ȸ��: 8";
		Point::GotoXY(reference_pos_ + Point(24, 13));
		cout << "��: 4";
		Point::GotoXY(reference_pos_ + Point(24, 14));
		cout << "��: 6";
		Point::GotoXY(reference_pos_ + Point(24, 15));
		cout << "��: 5";
		Point::GotoXY(reference_pos_ + Point(24, 16));
		cout << "����: g";
		Point::GotoXY(reference_pos_ + Point(24, 17));
		cout << "����:��<<��h";
		Point::GotoXY(reference_pos_ + Point(24, 18));
		cout << "sa��:";
		Point::GotoXY(reference_pos_ + Point(24, 19));
		cout << "ve��:";
	}
}

void Tetris::Run(void)
{
    while (running_) 
    {
        RunStep();
    }
}

void Tetris::RunStep(void)
{
    if (_kbhit())
    {
        int key = Controller::GetKey();
        KeyHandler(key);
    }
    else 
    {
        NormalStep();		
    }
}

bool Tetris::KeyHandler(int key)
{
	if (key == controller_.Getkey_esc())
	{
		running_ = false;
		return true;
	}
	else if (key == controller_.Getkey_right())
	{
		cur_tetromino_->MoveRight(reference_pos_);
		return true;
	}
	else if (key == controller_.Getkey_left())
	{
		cur_tetromino_->MoveLeft(reference_pos_);
		return true;
	}
	else if (key == controller_.Getkey_rotate())
	{
		cur_tetromino_->Rotate(reference_pos_);
		return true;
	}
	else if (key == controller_.Getkey_down())
	{
		cur_tetromino_->MoveDown(reference_pos_);
		return true;
	}
	else if (key == controller_.Getkey_savetetromino())
	{
		SaveTetromino();
		return true;
	}
	else if (key == controller_.Getkey_space()) //down ���� space�� ����...
	{
		cur_tetromino_->GoBottom(reference_pos_);
		PrepareNextStep();
		return true;
	}
	return false;
}


void Tetris::NormalStep(void)
{
    if (GetDiffTime() >= falling_speed_) 
    {
        if (cur_tetromino_->MoveDown(reference_pos_)) 
        {
            start_time_ = clock();
        }
        else 
        {	// ������ ��������. ��ó��
            PrepareNextStep();
        }
    }
}

void Tetris::PrepareNextStep(void)
{
	cur_tetromino_->MarkCurTetrominoPos(reference_pos_);

	int EraseLineCount = board_.CheckLineFull(reference_pos_);
	if (EraseLineCount > 0)
		score_.UpdateScore(reference_pos_, EraseLineCount);
	if (cur_tetromino_->CheckEndCondition())			//������ ���� �����̸�...
	{
		running_ = false;
		Point::GotoXY(reference_pos_ + Point(10, 10));
		cout << "The game is over !!!" << endl;
		board_.Board::CloseBackgroundSound();
		PlaySound(TEXT("GameOverSound.wav"), NULL, SND_ASYNC);	//������ �뷡
		Point::GotoXY(reference_pos_ + Point(0, 11));
		cout << "Do you want to save your score?";
		Point::GotoXY(reference_pos_ + Point(0, 12));
		cout << "�� (Y)" << "�ƴϿ� (N)";
		char temp;
		cin >> temp;
		fflush(stdin);
		if (temp == 'y' || temp == 'Y')
		{
			Score score;			score.SaveRanking(reference_pos_, score_.GetScore());
		}
	}
	else//������ ���������̾ƴϸ�...
	{
		next_tetromino_->Tetromino::Erase(reference_pos_);
		GetCurTetrominoFromNext();
		cur_tetromino_->Draw(reference_pos_);
		cur_tetromino_->ShadowDraw(reference_pos_, cur_tetromino_->Shadowtetromino(reference_pos_));
		GenerateNextTetromino();
		next_tetromino_->Draw(reference_pos_);
		Changefallingspeed();
	}
	start_time_ = clock();
}

void Tetris::GenerateNextTetromino(void)
{
    TETROMINO_TYPE tetromino_type = (TETROMINO_TYPE) (rand() % TETROMINO_TYPE_COUNT);
    //if (rand() % 10 == 0)           // GhostTetromino
    //    next_tetromino_ = new GhostTetromino(&board_, tetromino_type);
    //else
    next_tetromino_ = new Tetromino(&board_, tetromino_type);
    next_tetromino_->SetCenterPos(g_next_tetromino_init_pos);
}

void Tetris::GetCurTetrominoFromNext(void)//����Һκ�...
{
	if (cur_tetromino_ != NULL) delete cur_tetromino_;
	// cur_tetromino_�� ���� NULL�� �ƴ϶�� delete
	cur_tetromino_ = next_tetromino_;
	// next_tetromino_�� ��Ʈ�ι̳븦 cur_tetromino_�� ������
	cur_tetromino_->SetCenterPos(g_cur_tetromino_init_pos);
	// cur_tetromino_�� ���� ��ġ setting    
}

double Tetris::GetDiffTime(void)
{
    clock_t CurTime;
    CurTime = clock();	//time(&CurTime);
    return ((double) (CurTime - start_time_) / CLOCKS_PER_SEC);
}

// Utility
void Tetris::SetCursorInvisible(void)	// ȭ�� Ŀ���� �� ���̰� ��
{
    CONSOLE_CURSOR_INFO ci = { 10, FALSE };
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &ci);
}
void Tetris::Changefallingspeed(void)
{
	int score;
	score = score_.GetScore();
	if (score >= 2500 && score <5000)
		falling_speed_ = 0.5;
	else if (score >= 5000 && score <7500)
		falling_speed_ = 0.3;
	else if (score >= 7500 && score <10000)
		falling_speed_ = 0.2;
	else if (score >= 10000 && score <12500)
		falling_speed_ = 0.15;
	else if (score >= 12500 && score <15000)
		falling_speed_ = 0.10;
	else if (score >= 15000 && score <17500)
		falling_speed_ = 0.08;
	else if (score >= 17500)
		falling_speed_ = 0.05;
}
void Tetris::SaveTetromino(void)
{
	if (save_tetromino_ != NULL)
	{
		Tetromino * temp = save_tetromino_;
		temp->SetCenterPos(cur_tetromino_->GetCenterPos());
		if (temp->CheckValidPos())
		{
			cur_tetromino_->Erase(reference_pos_);
			cur_tetromino_->ShadowErase(reference_pos_, cur_tetromino_->Shadowtetromino(reference_pos_));
			save_tetromino_->SaveErase(reference_pos_ + Point(22, 18));

			temp = cur_tetromino_;
			save_tetromino_->SetCenterPos(cur_tetromino_->GetCenterPos());
			cur_tetromino_ = save_tetromino_;
			cur_tetromino_->SetCenterPos(save_tetromino_->GetCenterPos());
			save_tetromino_ = temp;
			save_tetromino_->SetCenterPos(Point(22, 18));
			cur_tetromino_->Draw(reference_pos_);
			cur_tetromino_->ShadowDraw(reference_pos_, cur_tetromino_->Shadowtetromino(reference_pos_));
			save_tetromino_->SaveDraw(reference_pos_ + Point(22, 18));
			RunStep();
		}
	}
	else
	{
		cur_tetromino_->Erase(reference_pos_);
		cur_tetromino_->ShadowErase(reference_pos_, cur_tetromino_->Shadowtetromino(reference_pos_));
		save_tetromino_ = cur_tetromino_;
		save_tetromino_->SaveDraw(reference_pos_ + Point(22, 18));
		save_tetromino_->SetCenterPos(g_cur_tetromino_init_pos);
		next_tetromino_->Tetromino::Erase(reference_pos_);
		cur_tetromino_ = next_tetromino_;		cur_tetromino_->SetCenterPos(g_cur_tetromino_init_pos);
		cur_tetromino_->Draw(reference_pos_);
		cur_tetromino_->ShadowDraw(reference_pos_, cur_tetromino_->Shadowtetromino(reference_pos_));
		GenerateNextTetromino();
		next_tetromino_->Draw(reference_pos_);
	}
}