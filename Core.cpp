#include <iostream>
#include "Conscientia.h"
using namespace std;


int main(){
  Conscientia::initilizeConscientia();
  Conscientia::createWindow("Main", 5, 5, 10, 10, true);
  Conscientia::update();
  while(1);
}
