#include <iostream>
#include "Conscientia.h"
using namespace std;


int main(){
  Conscientia::initilizeNcurses();
  Conscientia::initilizeColors();
  Conscientia::setCursor(false);
  Conscientia::setEcho(false);
  Conscientia::setAutoRefresh(true);
  //Conscientia::setRaw(true);
  Conscientia::newWindow(50, 20, 3, 3, true, "Main", 1);
  while(1){
    Conscientia::fprint("Main", "Hello World!");
  }
  Conscientia::terminateNcurses();
  return(1);
}
