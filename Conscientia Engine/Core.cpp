#include <iostream>
#include "Conscientia.h"

#include <ctime>
using namespace std;

int main() {
	int barPointer;
	CONSCIENTIA::initilizeConscientia();
	CONSCIENTIA::initilizeLoadingBar("Initialization");
	CONSCIENTIA::update();
	int a = 0;
	while (a <= 1000) {
		a++;
		CONSCIENTIA::loadingBar(0, (double)a / (double)1000);
	}
	CONSCIENTIA::terminateLoadingBar(0);
	CONSCIENTIA::terminateConscientia();
	return(1);
}