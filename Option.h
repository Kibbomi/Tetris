#ifndef KIBBOMI_OPTION
#define KIBBOMI_OPTION

#include "Controller.h"
#include "Point.h"

class Option {
	public:
		Option();
		int show_main();	//선택 값 반환
	private:
		Controller controller_;
		Point point_[4];
};

#endif