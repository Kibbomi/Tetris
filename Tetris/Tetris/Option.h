#ifndef KIBBOMI_OPTION
#define KIBBOMI_OPTION

#include "Controller.h"
#include "Point.h"
#include <string>
using namespace std;

class Option {
	public:
		Option();
		int show_main();	//선택 값 반환
		void show_option();
		static bool opt_ghost, opt_save;
		static double opt_fallingspeed;
	private:
		Controller controller_;
		Point point_[5];
		string opt_str[4];
};

#endif