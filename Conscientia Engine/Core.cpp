#include <iostream>
#include "Conscientia.h"

#include <ctime>
using namespace std;

int main() {
	int barPointer;
	CONSCIENTIA::initializeConscientia();
	CONSCIENTIA::createWindow("Main", 1, 1, 40, 10, true, false);
	CONSCIENTIA::update();
	CONSCIENTIA::loadMenuHierarchy("Test.lux");
	while (1);
	CONSCIENTIA::terminateConscientia();
	return(1);
}