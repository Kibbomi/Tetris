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
		system("cls");

		if (input == 1)         // 1�ο� 
		{
			Tetris tetris(Point(0, 0));
			tetris.Run();
		}
		else if (input == 2)              // 2�ο�
		{
			Tetris tetris1(Point(0, 0), KEY_ESC, 'd', 'a', 'w', 's');
			Tetris tetris2(Point(38, 0), 'p');

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
		else
		{
			break;
			//return 0;
		}
	}


	return 0;
}
