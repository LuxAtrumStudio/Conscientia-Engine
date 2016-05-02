#include <iostream>
#include "Conscientia.h"
using namespace std;


int main(){
  Conscientia::initilizeNcurses();
  Conscientia::initilizeColors();
  Conscientia::newWindow(10, 10, 3, 3, true);
  while(1);
  Conscientia::terminateNcurses();
  return(1);
}
