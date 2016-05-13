#include <iostream>
#include "Conscientia.h"
using namespace std;

/*=====>>>>>-----TEXT-----<<<<<=====*/

int main() {
	Conscientia::initilizeConscientia();
	Conscientia::createWindow("Main", 2, 2, 50, 10, true, true);
	Conscientia::print(1, "NOOOOOOOOOOOOOOOOOOOOOOOOOOOOO");
	Conscientia::setOutputAttribues(FOREGROUND_RED | FOREGROUND_INTENSITY | BACKGROUND_BLUE | COMMON_LVB_UNDERSCORE, 10, 0, 0);
	Conscientia::update();
	while (1);
	return(1);
}