#include <iostream>
#include "Conscientia.h"
using namespace std;


int main(){
  CONSCIENTIA::initializeConscientia();
  CONSCIENTIA::createWindow("Main", 5, 5, 10, 10, true, true);
  CONSCIENTIA::update();
  while(1);
}
