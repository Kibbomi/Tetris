#include <iostream>
#include <cstdlib>
#include <ctime>
#include <conio.h>
using namespace std;
#include "Tetris.h"
#include "Option.h"

int main()
{
	srand(time(NULL));		// ���� �߻��� �ʱ�ȭ
	int input;
	Option opt_;
	
	while (1)
	{
		input = opt_.show_main();

		if (input == 1)         // 1�ο� 
		{
			system("cls");
			Tetris tetris(Point(0, 0));
			tetris.Run();
		}
		else if (input == 2)              // 2�ο�
		{
			system("cls");
			Tetris tetris1(Point(0, 0));
			//Tetris tetris2(Point(38, 0), KEY_ESC,KEY_RIGHT,KEY_LEFT,KEY_UP,KEY_DOWN,'g','h',2);
			Tetris tetris2(Point(38, 0), KEY_ESC, '6', '4', '8', '5', 'g', 'h', 2);
			while (tetris1.IsRunning() || tetris2.IsRunning())
			{
				bool key1 = false;
				bool key2 = false;

				if (_kbhit())    // Ű �Է��� �ִٸ� 
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
		else if (input == 4)
		{
			opt_.show_option();
		}
		else
		{
			break;
			//return 0;
		}
	}


	return 0;
}
