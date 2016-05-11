#include <iostream>
#include "Conscientia.h"
using namespace std;

/*=====>>>>>-----TEXT-----<<<<<=====*/

int main() {
	Conscientia::initilizeConscientia();
	Conscientia::createWindow("Main", 2, 2, 50, 10, true, true);
	Conscientia::print(1, "NOOOOOOOOOOOOOOOOOOOOOOOOOOOOO");
	Conscientia::update();
	while (1);
	return(1);
}