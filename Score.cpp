#include <iostream>
#include <iomanip>
#include <fstream>

#include "Score.h"

using namespace std;


Score::Score()
{
	score_ = 0;
	score_pos_ = Point(28, 9);
}

void Score::Print(Point reference_pos)
{
	Point::GotoXY(reference_pos + score_pos_);
	cout << "    ";
	Point::GotoXY(reference_pos + score_pos_);
	cout << setw(5) << score_;
}

void Score::UpdateScore(Point reference_pos, int increment)
{
	score_ += increment;
	Print(reference_pos);
}
void Score::ReadRanking(void)
{
	ifstream Ranking("TetrisRanking.txt");

	if (!Ranking)
	{
		cout << "���� ���� ����" << endl;
		return;
	}
	cout << "  �̸�  " << "  ����  " << endl;
	while (!Ranking.eof())
	{
		char temp[100] = { 0 };
		Ranking.getline(temp, 100);
		cout << temp << endl;
	}


	Ranking.close();
}

void Score::SaveRanking(Point reference_pos, int score_)
{
	ofstream Ranking;
	Ranking.open("TetrisRanking.txt", ios_base::app);	//�������� ��� ������..
	if (!Ranking)
	{
		cout << "���� ���� ����" << endl;
		return;
	}
	char name[15] = { 0 };
	Point::GotoXY(reference_pos + Point(0, 13));
	cout << "�̸��� �Է��ϼ��� :";
	cin >> name;
	fflush(stdin);//Ȥ�� 12�����̻� �Է½�..or ���๮��

	Ranking << name << "  " << score_ << endl;

	Ranking.close();
}