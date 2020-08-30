#include <iostream>
#include "Option.h"
using namespace std;

bool Option::opt_ghost = true;
bool Option::opt_save = true;
double Option::opt_fallingspeed = 0.8;

Option::Option() {
	controller_.SetController(KEY_ESC, KEY_RIGHT, KEY_LEFT, KEY_UP, KEY_DOWN, KEY_SPACE, 0);
	
	point_[0].SetX(18);	//1번 위치 초기화
	point_[0].SetY(18);

	point_[1].SetX(18);	//2번 위치 초기화
	point_[1].SetY(19);

	point_[2].SetX(18);	//3번 위치 초기화
	point_[2].SetY(20);

	point_[3].SetX(18);	//4번 위치 초기화
	point_[3].SetY(21);

	point_[4].SetX(18);	//5번 위치 초기화
	point_[4].SetY(22);

	opt_str[0] = "Ghost block";
	opt_str[1] = "Save block";
	opt_str[2] = "Falling speed";
	opt_str[3] = "exit";
}

int Option::show_main()
{
	system("cls");
	int key, curval = 0;

	cout << "┌─────────────────────────────┐" << '\n';
	cout << "│┌──┐ ┌──┐  ┌──┐  ┌──┐   ┌──┐  ┌──┐│" << '\n';
	cout << "│└┐┌┘ │┌─┘  └┐┌┘  │┌┐│   └┐┌┘  │┌─┘│" << '\n';
	cout << "│  ││   │└─┐    ││    │└┘│     ││    │└─┐│" << '\n';
	cout << "│  ││   │┌─┘    ││    │┌┐│     ││    └─┐││" << '\n';
	cout << "│  ││   │└─┐    ││    ││ ＼＼  ┌┘└┐  ┌─┘││" << '\n';
	cout << "│  └┘   └──┘    └┘    └┘   ￣  └──┘  └──┘│" << '\n';
	cout << "└──────────┐              ┌──────────┘" << '\n';
	cout << "                      │              │" << '\n';
	cout << "                      │              │	" << '\n';
	cout << "                      │              │" << '\n';
	cout << "                      │              │	" << '\n';
	cout << "                      │              │	" << '\n';
	cout << "                      │              │	" << '\n';
	cout << "                      │              │	" << '\n';
	cout << "                      │              │" << '\n';
	cout << "                      │              │	" << '\n';
	cout << "                      └───────┘" << '\n';

	cout << "                     " << "1P" << '\n';
	cout << "                     " << "1P vs 2P" << '\n';
	cout << "                     " << "Ranking" << '\n';
	cout << "                     " << "Option" << '\n';
	cout << "                     " << "나가기" << '\n';

	Point::GotoXY(point_[curval]);
	cout << "▶";
	Point::GotoXY(point_[curval]);

	while (1) {
		key = Controller::GetKey();

		if (key == controller_.Getkey_esc())
		{
			cout << "exit the game\n";
			return 0;
		}
		else if (key == controller_.Getkey_rotate())//up key
		{
			if (curval >= 1) {
				cout << "  ";
				Point::GotoXY(point_[--curval]);
				cout <<"▶";
				Point::GotoXY(point_[curval]);
			}
		}
		else if (key == controller_.Getkey_down())	
		{
			if (curval <= 3) {
				cout << "  ";
				Point::GotoXY(point_[++curval]);
				cout << "▶";
				Point::GotoXY(point_[curval]);
			}
		}
		else if (key == controller_.Getkey_space() || key == KEY_ENTER)
		{
			break;
		}
	}	
		return curval + 1;
}

void Option::show_option()
{
	system("cls");
	int key, curval = 0;
	cout << "Option\n";
	Point::GotoXY(point_[curval++]);
	cout << "    " << opt_str[0] << "\t";
	if(opt_ghost)
		cout <<"ON" <<'\n';
	else
		cout << "OFF" << '\n';
	Point::GotoXY(point_[curval++]);
	cout << "    " << opt_str[1] << "\t";
	if (opt_save)
		cout << "ON" << '\n';
	else
		cout << "OFF" << '\n';
	Point::GotoXY(point_[curval++]);
	cout << "    " << opt_str[2] << "\t";
	cout << opt_fallingspeed <<"s" << '\n';
	Point::GotoXY(point_[curval++]);
	cout << "    " << opt_str[3] <<'\n';
	
	curval = 0;
	Point::GotoXY(point_[curval]);
	cout << "▶";
	Point::GotoXY(point_[curval]);

	while (1) {
		key = Controller::GetKey();

		if (key == controller_.Getkey_esc())
		{
			break;
		}
		else if (key == controller_.Getkey_rotate())//up key
		{
			if (curval >= 1) {
				cout << "  ";
				Point::GotoXY(point_[--curval]);
				cout <<"▶";
				Point::GotoXY(point_[curval]);
			}
		}
		else if (key == controller_.Getkey_down())	
		{
			if (curval <= 2) {
				cout << "  ";
				Point::GotoXY(point_[++curval]);
				cout << "▶";
				Point::GotoXY(point_[curval]);
			}
		}
		else if (key == controller_.Getkey_left())
		{
			if (curval == 0)
			{
				Point::GotoXY(point_[curval]);
				if (Option ::opt_ghost) {
					Option ::opt_ghost = false;
					cout << "▶  " << opt_str[0] << "\tOFF" << '\n';
				}
				else {
					Option :: opt_ghost = true;
					cout << "▶  " << opt_str[0] << "\tON  " << '\n';
				}
				Point::GotoXY(point_[curval]);
			}
			if (curval == 1)
			{
				Point::GotoXY(point_[curval]);
				if (Option :: opt_save) {
					Option :: opt_save = false;
					cout << "▶  " << opt_str[1] << "\tOFF" << '\n';
				}
				else {
					Option :: opt_save = true;
					cout << "▶  " << opt_str[1] << "\tON  " << '\n';
				}
				Point::GotoXY(point_[curval]);
			}
			if (curval == 2)
			{
				Point::GotoXY(point_[curval]);
				if (Option :: opt_fallingspeed >= 0.2)
				{
					Option :: opt_fallingspeed -= 0.1;
					cout << "▶  " << opt_str[2] << "\t" << opt_fallingspeed << '\n';
				}
				Point::GotoXY(point_[curval]);
			}
		}
		else if (key == controller_.Getkey_right())
		{
			if (curval == 0)
			{
				Point::GotoXY(point_[curval]);
				if (Option :: opt_ghost) {
					Option :: opt_ghost = false;
					cout << "▶  " << opt_str[0] << "\tOFF" << '\n';
				}
				else {
					Option :: opt_ghost = true;
					cout << "▶  " << opt_str[0] << "\tON  " << '\n';
				}
				Point::GotoXY(point_[curval]);
			}
			if (curval == 1)
			{
				Point::GotoXY(point_[curval]);
				if (Option :: opt_save) {
					Option :: opt_save = false;
					cout << "▶  " << opt_str[1] << "\tOFF" << '\n';
				}
				else {
					Option :: opt_save = true;
					cout << "▶  " << opt_str[1] << "\tON  " << '\n';
				}
				Point::GotoXY(point_[curval]);
			}
			if (curval == 2)
			{
				Point::GotoXY(point_[curval]);
				if (Option :: opt_fallingspeed <= 0.8)
				{
					Option :: opt_fallingspeed += 0.1;
					cout << "▶  " << opt_str[2] << "\t" << Option :: opt_fallingspeed << '\n';
				}
				Point::GotoXY(point_[curval]);
			}
		}
		else if (key == controller_.Getkey_space() || key == KEY_ENTER)
		{
			if( curval == 3)
				break;
		}
	}	
	return;
}