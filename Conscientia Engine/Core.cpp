#include <iostream>
#include "Conscientia.h"

#include <ctime>
using namespace std;

int main() {
	int barPointer;
	CONSCIENTIA::initializeConscientia();
	CONSCIENTIA::update();
	CONSCIENTIA::menu("Test.lux", 1, 1, 118, 28);
	CONSCIENTIA::terminateConscientia();
	while (1);
	return(1);
}