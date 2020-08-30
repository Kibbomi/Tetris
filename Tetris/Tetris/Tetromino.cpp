#include "Tetromino.h"
#include <iostream>
#include <windows.h>
using namespace std;

Point g_tetromino_pattern[7][4][4] =
{
	{ { Point(0, 1), Point(0, 0), Point(0, -1), Point(0, -2) },{ Point(-2, 0), Point(-1, 0), Point(0, 0), Point(1, 0) },
	{ Point(0, 1), Point(0, 0), Point(0, -1), Point(0, -2) },{ Point(-2, 0), Point(-1, 0), Point(0, 0), Point(1, 0) } },  // I
	{ { Point(0, 1), Point(0, 0), Point(0, -1), Point(-1, -1) },{ Point(-1, 0), Point(0, 0), Point(1, 0), Point(-1, 1) },
	{ Point(0, 1), Point(0, 0), Point(1, 1), Point(0, -1) },{ Point(-1, 0), Point(0, 0), Point(1, 0), Point(1, -1) } },  // J
	{ { Point(-1, 1), Point(0, 1), Point(0, 0), Point(0, -1) },{ Point(1, 1), Point(-1, 0), Point(0, 0), Point(1, 0) },
	{ Point(0, 1), Point(0, 0), Point(0, -1), Point(1, -1) },{ Point(-1, 0), Point(0, 0), Point(1, 0), Point(-1, -1) } }, // L
	{ { Point(-1, 0), Point(0, 0), Point(-1, -1), Point(0, -1) },{ Point(-1, 0), Point(0, 0), Point(-1, -1), Point(0, -1) },
	{ Point(-1, 0), Point(0, 0), Point(-1, -1), Point(0, -1) },{ Point(-1, 0), Point(0, 0), Point(-1, -1), Point(0, -1) } },  // O
	{ { Point(0, 1), Point(0, 0), Point(1, 0), Point(1, -1) },{ Point(0, 0), Point(1, 0), Point(-1, -1), Point(0, -1) },
	{ Point(0, 1), Point(0, 0), Point(1, 0), Point(1, -1) },{ Point(0, 0), Point(1, 0), Point(-1, -1), Point(0, -1) } },  // S
	{ { Point(0, 1), Point(-1, 0), Point(0, 0), Point(0, -1) },{ Point(0, 1), Point(-1, 0), Point(0, 0), Point(1, 0) },
	{ Point(0, 1), Point(0, 0), Point(1, 0), Point(0, -1) },{ Point(-1, 0), Point(0, 0), Point(1, 0), Point(0, -1) } },  // T
	{ { Point(1, 1), Point(0, 0), Point(1, 0), Point(0, -1) },{ Point(-1, 0), Point(0, 0), Point(0, -1), Point(1, -1) },
	{ Point(1, 1), Point(0, 0), Point(1, 0), Point(0, -1) },{ Point(-1, 0), Point(0, 0), Point(0, -1), Point(1, -1) } }  // Z
};

Tetromino::Tetromino(Board *board, TETROMINO_TYPE type) : board_(board), type_(type)
{
	rotate_ = 0;
}

void Tetromino::Draw(Point reference_pos)
{
	for (int i = 0; i < 4; i++)
	{
		if ((center_pos_ + g_tetromino_pattern[type_][rotate_][i]).GetY() >= reference_pos.GetY() + 0 && (center_pos_ + g_tetromino_pattern[type_][rotate_][i]).GetY()<reference_pos.GetY() + 20)
		{
			Point::GotoXY(reference_pos + Point::GetScrPosFromCurPos(center_pos_ + g_tetromino_pattern[type_][rotate_][i]));
			if (type_ == 0) SHY_BLUE
			else if (type_ == 1) BLUE
			else if (type_ == 2) GOLD
			else if (type_ == 3) GREEN
			else if (type_ == 4) HIGH_GREEN
			else if (type_ == 5) PURPLE
			else if (type_ == 6) RED
				cout << "■";
		}
	}
	BLACK
}

void Tetromino::Erase(Point reference_pos)
{
	for (int i = 0; i < 4; i++)
	{
		if ((center_pos_ + g_tetromino_pattern[type_][rotate_][i]).GetY() >= reference_pos.GetY() + 0 && (center_pos_ + g_tetromino_pattern[type_][rotate_][i]).GetY()<reference_pos.GetY() + 20)
		{
			Point::GotoXY(reference_pos + Point::GetScrPosFromCurPos(center_pos_ + g_tetromino_pattern[type_][rotate_][i]));//
			cout << "  ";
		}
	}
}

void Tetromino::SetCenterPos(Point pos)
{
	center_pos_ = pos;
}

bool Tetromino::MoveDown(Point reference_pos)
{
	center_pos_.SetY(center_pos_.GetY() - 1);
	if (CheckValidPos())
	{
		center_pos_.SetY(center_pos_.GetY() + 1);
		Erase(reference_pos);
		center_pos_.SetY(center_pos_.GetY() - 1);
		ShadowDraw(reference_pos, Shadowtetromino(reference_pos));
		Draw(reference_pos);
		return true;
	}
	else
	{
		center_pos_.SetY(center_pos_.GetY() + 1);
		return false;
	}
}

void Tetromino::MoveRight(Point reference_pos)
{
	center_pos_.SetX(center_pos_.GetX() + 1);

	if (CheckValidPos())
	{
		center_pos_.SetX(center_pos_.GetX() - 1);
		ShadowErase(reference_pos, Shadowtetromino(reference_pos));
		Erase(reference_pos);

		center_pos_.SetX(center_pos_.GetX() + 1);
		ShadowDraw(reference_pos, Shadowtetromino(reference_pos));
		Draw(reference_pos);
	}
	else
	{
		center_pos_.SetX(center_pos_.GetX() - 1);
	}
}

void Tetromino::MoveLeft(Point reference_pos)
{
	center_pos_.SetX(center_pos_.GetX() - 1);

	if (CheckValidPos())
	{
		center_pos_.SetX(center_pos_.GetX() + 1);
		ShadowErase(reference_pos, Shadowtetromino(reference_pos));
		Erase(reference_pos);

		center_pos_.SetX(center_pos_.GetX() - 1);
		ShadowDraw(reference_pos, Shadowtetromino(reference_pos));
		Draw(reference_pos);
	}
	else
	{
		center_pos_.SetX(center_pos_.GetX() + 1);
	}
}

void Tetromino::Rotate(Point reference_pos)
{
	int rotate_temp = rotate_;
	rotate_ = (rotate_ + 1) % 4;//유효하지않을때 즉,4->0이되었다가 0->4가되어야하는데 불가능하므로 미리 temp변수에 저장..

	if (CheckValidPos())
	{
		rotate_ = rotate_temp;//원래로 돌아가서 지운다음,..		
		ShadowErase(reference_pos, Shadowtetromino(reference_pos));
		Erase(reference_pos);
		rotate_ = (rotate_ + 1) % 4;
		ShadowDraw(reference_pos, Shadowtetromino(reference_pos));
		Draw(reference_pos);
	}
	else
	{
		rotate_ = rotate_temp;
	}
}

void Tetromino::GoBottom(Point reference_pos)
{
	while (MoveDown(reference_pos))
	{
		//Sleep(10); //Sleep(100);
	}
}

bool Tetromino::CheckValidPos(void)
{
	for (int i = 0; i < 4; i++)
	{
		Point cur_pos(center_pos_.GetX() + g_tetromino_pattern[type_][rotate_][i].GetX(), center_pos_.GetY() + g_tetromino_pattern[type_][rotate_][i].GetY());

		if (cur_pos.GetX() < 0 || cur_pos.GetX() > 9)
			return false;
		if (cur_pos.GetY() < 0)
			return false;
		if (cur_pos.GetY() <= 19 && board_->GetState(cur_pos) != EMPTY)
			return false;
	}

	return true;
}

void Tetromino::MarkCurTetrominoPos(Point reference_pos)// board_ 2차원 배열에서 테트로미노의 4개의 각 점 위치를 mark하기
{
	for (int i = 0; i < 4; i++)
	{
		board_->Board::SetState(center_pos_ + g_tetromino_pattern[type_][rotate_][i], type_);
	}
}

bool Tetromino::CheckEndCondition(void)
{
	for (int i = 0; i < 9; i++)
		if (board_->Board::GetState(Point(i, 19)) != EMPTY)	//해당좌표가 비어있지않다면
			return true;	//끝날조건이다
		
	return false;
}
bool Tetromino::ShadowtetrominoCheck(Point temp)
{
	for (int i = 0; i < 4; i++)
	{
		Point cur_pos(temp.GetX() + g_tetromino_pattern[type_][rotate_][i].GetX(), temp.GetY() + g_tetromino_pattern[type_][rotate_][i].GetY());

		if (cur_pos.GetX() < 0 || cur_pos.GetX() > 9)
			return false;
		if (cur_pos.GetY() < 0)
			return false;
		if (cur_pos.GetY() <= 19 && board_->GetState(cur_pos) != EMPTY)
			return false;
	}
	return true;
}
Point Tetromino::Shadowtetromino(Point reference_pos)
{
	Point temp;
	temp = center_pos_;	
	while (ShadowtetrominoCheck(temp))
	{
		temp.SetY(temp.GetY() - 1);
	}
	temp.SetY(temp.GetY() + 1);
	return temp;
}

void Tetromino::ShadowDraw(Point reference_pos, Point temp)
{
	if (!Option::opt_ghost)
		return;
	for (int i = 0; i < 4; i++)
	{
		if ((temp + g_tetromino_pattern[type_][rotate_][i]).GetY() >= reference_pos.GetY() + 0 && (temp + g_tetromino_pattern[type_][rotate_][i]).GetY()<reference_pos.GetY() + 20)
		{
			Point::GotoXY(reference_pos + Point::GetScrPosFromCurPos(temp + g_tetromino_pattern[type_][rotate_][i]));
			cout << "■";
		}
	}
}

void Tetromino::ShadowErase(Point reference_pos, Point temp)
{
	if (!Option::opt_ghost)
		return;
	for (int i = 0; i < 4; i++)
	{
		if ((temp + g_tetromino_pattern[type_][rotate_][i]).GetY() >= reference_pos.GetY() + 0 && (temp + g_tetromino_pattern[type_][rotate_][i]).GetY()<reference_pos.GetY() + 20)
		{
			Point::GotoXY(reference_pos + Point::GetScrPosFromCurPos(temp + g_tetromino_pattern[type_][rotate_][i]));//
			cout << "  ";
		}
	}
}

void Tetromino::SaveDraw(Point reference_pos)
{
	for (int i = 0; i < 4; i++)
	{
		Point::GotoXY(reference_pos + Point::GetScrPosFromCurPos(Point(4, 20) + g_tetromino_pattern[type_][rotate_][i]));
		if (type_ == 0) SHY_BLUE
		else if (type_ == 1) BLUE
		else if (type_ == 2) GOLD
		else if (type_ == 3) GREEN
		else if (type_ == 4) HIGH_GREEN
		else if (type_ == 5) PURPLE
		else if (type_ == 6) RED
			cout << "■";
	}

	BLACK
}
void Tetromino::SaveErase(Point reference_pos)
{
	for (int i = 0; i < 4; i++)
	{
		Point::GotoXY(reference_pos + Point::GetScrPosFromCurPos(Point(4, 20) + g_tetromino_pattern[type_][rotate_][i]));//
		cout << "  ";
	}

}