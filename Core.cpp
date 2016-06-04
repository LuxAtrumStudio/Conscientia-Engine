#include <iostream>
#include "Conscientia.h"
using namespace std;


int main(){
  CONSCIENTIA::initializeConscientia();
  CONSCIENTIA::menu("Test.lux", 1, 1, 120, 30);
  CONSCIENTIA::update();
  while(1);
}
