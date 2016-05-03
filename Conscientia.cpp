#include <ncurses.h>
#include <vector>
#include "Conscientia.h"
using namespace std;
/*>--Conscientia Declarations--<*/
struct windowPoint{
  string name;
  WINDOW * pointer;
  int cursorX, cursorY;
  int scrollSetting;
};
vector<windowPoint> windows;
int currentWindowIndex = -1;
bool autoRefresh = false;


/*>--Conscientia Funcitons--<*/
/*CORE*/
void Conscientia::initilizeNcurses(){
    initscr();
    keypad(stdscr, TRUE);
    windowPoint declaration;
    declaration.name = "stdscr";
    declaration.pointer = stdscr;
    declaration.scrollSetting = 1;
    declaration.cursorX = 1;
    declaration.cursorY = 1;
    windows.push_back(declaration);
}
void Conscientia::initilizeColors(){
    start_color();
}
void Conscientia::terminateNcurses(){
    endwin();
}
/*Settings*/
void Conscientia::setCursor(bool setting){
    curs_set(setting);
}
void Conscientia::setEcho(bool setting){
    if(setting == true){
        echo();
    }
    else{
        noecho();
    }
}
void Conscientia::setRaw(bool setting){
    if(setting == true){
        raw();
    }
    else{
        noraw();
    }
}
/*Windows*/
void Conscientia::newWindow(int sizeX, int sizeY, int posX, int posY, bool border, string name, int scrollSetting){
    WINDOW *local;
    local = newwin(sizeY, sizeX, posY, posX);
    keypad(local, TRUE);
    if(border == true){
        box(local, 0, 0);
    }
    wrefresh(local);
    windowPoint declaration;
    declaration.name = name;
    declaration.pointer = local;
    declaration.scrollSetting = scrollSetting;
    declaration.cursorX = 1;
    declaration.cursorY = 1;
    windows.push_back(declaration);
}
void Conscientia::terminateWindow(WINDOW *local){
    wborder(local, ' ', ' ', ' ', ' ', ' ', ' ', ' ' , ' ');
    wrefresh(local);
    delwin(local);
}
/*USER*/
/*Output*/
/*any window*/
void Conscientia::print(int pointer, string output){
  mvwprintw(windows[pointer].pointer, windows[pointer].cursorY, windows[pointer].cursorX, output.c_str());
  if(autoRefresh == true){
    wrefresh(windows[pointer].pointer);
  }
}
/*current window*/
void Conscientia::cprint(string output){
  print(currentWindowIndex, output);
}
/*window search*/
void Conscientia::fprint(string name, string output){
  print(findWindow(name), output);
}
/*Input*/
/*Window Control*/
void Conscientia::setAutoRefresh(bool setting){
  autoRefresh = setting;
}
int Conscientia::findWindow(string name){
  for(unsigned a = 0; a < windows.size(); a++){
    if(windows[a].name == name){
      return(a);
    }
  }
  return(-1);
}
/*ADVANCED*/
/*Menu*/
/*File Explorer*/
/*Side Bars*/
/*Data Reading*/
