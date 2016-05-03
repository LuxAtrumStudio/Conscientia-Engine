#include <iostream>
#include <vector>
#include <ncurses.h>

namespace Conscientia
{
  /*CORE*/
  void initilizeNcurses();
  void initilizeColors();
  void terminateNcurses();
  /*Settings*/
  void setCursor(bool setting);
  void setEcho(bool setting);
  void setRaw(bool setting);
  /*Windows*/
  void newWindow(int sizeX, int sizeY, int posX, int posY, bool border, std::string name, int scrollSetting);
  void terminateWindow(WINDOW *local);
  /*USER*/
  /*Output*/
  /*any window*/
  void print(int pointer, std::string output);
  /*current window*/
  void cprint(std::string output);
  /*window search*/
  void fprint(std::string name, std::string output);
  /*Input*/
  /*Window Control*/
  void setAutoRefresh(bool setting);
  int findWindow(std::string name);
  /*ADVANCED*/
  /*Menu*/
  /*File Explorer*/
  /*Side Bars*/
  /*Data Reading*/
}
