#include "Conscientia.h"
using namespace std;

void Conscientia::initilizeNcurses(){
  initscr();
  raw();
  keypad(stdscr, TRUE);
  noecho();
}
