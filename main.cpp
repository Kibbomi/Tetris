#include <iostream>
#include <cstdlib>
#include <ctime>
#include <conio.h>
using namespace std;
#include "Tetris.h"

int main()
{
	srand(time(NULL));		// 난수 발생기 초기화
	int input;

	while (1)
	{
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

		cout << "                     " << "1. 1P" << '\n';
		cout << "                     " << "2. 1P vs 2P" << '\n';
		cout << "                     " << "3. 랭킹정보" << '\n';
		cout << "                     " << "4. 나가기" << '\n';
		cout << ">> 1인용, 2인용 선택 : ";
		cin >> input;

		system("cls");

		if (input == 1)         // 1인용 
		{
			Tetris tetris(Point(0, 0));
			tetris.Run();
		}
		else if (input == 2)              // 2인용
		{
			Tetris tetris1(Point(0, 0), KEY_ESC, 'd', 'a', 'w', 's');
			Tetris tetris2(Point(38, 0), 'p');

			while (tetris1.IsRunning() || tetris2.IsRunning())
			{
				bool key1 = false;
				bool key2 = false;

				if (_kbhit())    // 키 입력이 있다면 
				{
					int key = Controller::GetKey();
					if (tetris1.IsRunning())
						key1 = tetris1.KeyHandler(key);
					if (tetris2.IsRunning() && !key1)
						key2 = tetris2.KeyHandler(key);
				}

				if (tetris1.IsRunning() && !key1)
					tetris1.NormalStep();
				if (tetris2.IsRunning() && !key2)
					tetris2.NormalStep();
			}
		}
		else if (input == 3)
		{
			system("cls");
			Score::ReadRanking();
			_getch();
			system("cls");
		}
		else
		{
			break;
			//return 0;
		}
	}
	

    return 0;
}

/*
int main()
{
	srand(time(NULL));
	Tetris tetris;
	tetris.Run();

    return 0;
}
*/