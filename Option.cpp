#include <iostream>
#include "Option.h"
using namespace std;

Option::Option() {
	controller_.SetController(KEY_ESC, 0, 0, KEY_UP, KEY_DOWN, KEY_SPACE, 0);
	point_[0].SetX(18);	//1번 위치 초기화
	point_[0].SetY(18);

	point_[1].SetX(18);	//2번 위치 초기화
	point_[1].SetY(19);

	point_[2].SetX(18);	//3번 위치 초기화
	point_[2].SetY(20);

	point_[3].SetX(18);	//4번 위치 초기화
	point_[3].SetY(21);
}

int Option::show_main()
{
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
		cout << "                     " << "랭킹정보" << '\n';
		cout << "                     " << "나가기" << '\n';
		cout << ">> 1인용, 2인용 선택 : ";
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
				cout << curval<<"▶";
				Point::GotoXY(point_[curval]);
			}
		}
		else if (key == controller_.Getkey_down())	
		{
			if (curval <= 2) {
				cout << "  ";
				Point::GotoXY(point_[++curval]);
				cout <<curval<< "▶";
				Point::GotoXY(point_[curval]);
			}
		}
		else if (key == controller_.Getkey_space()) //down 에서 space로 변경...
		{
			break;
		}

	}	
		return curval + 1;
}