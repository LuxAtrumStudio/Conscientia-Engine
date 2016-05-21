#include <iostream>
#include "Conscientia.h"
using namespace std;

int main() {
	int barPointer;
	CONSCIENTIA::initializeConscientia();
	CONSCIENTIA::menu("Test.lux", 1, 1, 118, 28);
	CONSCIENTIA::terminateConscientia();
	return(1);
}