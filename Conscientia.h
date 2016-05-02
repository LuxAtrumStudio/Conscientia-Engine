#include <iostream>
#include <vector>
#include <ncurses.h>

namespace Conscientia
{
  /*INITILIZATION*/
  void initilizeNcurses();
  void initilizeColors();
  void terminateNcurses();
  /*Settings*/
  void setCursor(bool setting);
  void setEcho(bool setting);
  void setRaw(bool setting);
  /*Windows*/
  void newWindow(int sizeX, int sizeY, int posX, int posY, bool border);
}
