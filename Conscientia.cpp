#include <iostream>
#include <string>
#include <sstream>
#include <ncurses.h>
#include <vector>
#include "Conscientia.h"
using namespace std;

/*=====>>>>>-----DATA-----<<<<<=====*/
struct window {
  string name;
  WINDOW * pointer;
  int startX, startY, sizeX, sizeY, endX, endY;
  int cursorX, cursorY;
  bool border, title;
};
vector<window> windows;
int currentWindowPointer = 0;
bool autoRefresh = false;
/*=====>>>>>-----ADVNACED DATA-----<<<<<=====*/
/*=====>>>>>-----Global-----<<<<<=====*/
struct luxCode {
  vector<string> lines;
};
/*>>>>>-----FUNCTIONS-----<<<<<*/
/*>>>>>-----Menu-----<<<<<*/
int firstPage = 0, firstList = 0, firstItem = 0;
/*>>>>>-----Loading Bars-----<<<<<*/
vector<int> loadingBarPointers;
namespace CONSCIENTIA
{
  /*=====>>>>>-----FUNCTIONS-----<<<<<=====*/
  /*=====>>>>>-----Initilization-----<<<<<=====*/
  void initializeConscientia(){
    initscr();
    keypad(stdscr, TRUE);
    window declaration;
    declaration.name = "stdscr";
    declaration.pointer = stdscr;
    declaration.startX = 0;
    declaration.startY = 0;
    getmaxyx(stdscr, declaration.sizeY, declaration.sizeX);
    declaration.cursorX = 0;
    declaration.cursorY = 0;
    declaration.endX = declaration.sizeX;
    declaration.endY = declaration.sizeY;
    declaration.border = false;
    declaration.title = false;
    windows.push_back(declaration);
  }
  void advancedInit(bool cursor, bool echo, bool raw){
    initializeConscientia();
    setCursor(cursor);
    setEcho(echo);
    setRaw(raw);
  }
  /*>>>>-----SETTINGS-----<<<<<*/
  void setAutoRefresh(bool setting){
    autoRefresh = setting;
  }
  /*>>>>>----NCURSES INITILIZATION-----<<<<<*/
  void initilizeColors(){
    start_color();
  }
  void setCursor(bool setting){
    curs_set(setting);
  }
  void setEcho(bool setting){
    if(setting == true){
        echo();
    }
    else{
        noecho();
    }
  }
  void setRaw(bool setting){
    if(setting == true){
        raw();
    }
    else{
        noraw();
    }
  }
  /*=====>>>>>-----Run Time-----<<<<<=====*/
  /*>>>>>-----WINDOW-----<<<<<*/
  /*>>>>>-----Initilization-----<<<<<*/
  void createWindow(string name, int posX, int posY, int sizeX, int sizeY, bool border, bool title){
    WINDOW *local;
    local = newwin(sizeY, sizeX, posY, posX);
    keypad(local, TRUE);
    if (border == true){
      box(local, 0, 0);
    }
    window declaration;
    declaration.name = name;
    declaration.pointer = local;
    declaration.startX = posX;
    declaration.startY = posY;
    declaration.sizeX = sizeX;
    declaration.sizeY = sizeY;
    declaration.endX = posX + sizeX;
    declaration.endY = posY + sizeY;
    declaration.cursorX = 0;
    declaration.cursorY = 0;
    declaration.border = border;
    declaration.title = title;
    if(border == true){
      declaration.cursorX++;
      declaration.cursorY++;
    }
    if(title == true && border == false){
      declaration.cursorY++;
    }
    if(title == true){
      drawTitle(windows.size() - 1);
    }
    windows.push_back(declaration);
  }
  /*>>>>>-----Management-----<<<<<*/
  void clearAllWindows(){
    for(unsigned a = 0; a < windows.size(); a++){
      clearWindow(a);
    }
  }
  int findWindowPointer(string name){
      for(unsigned a = 0; a < windows.size(); a++){
        if(windows[a].name == name){
          return(a);
        }
      }
      return(0);
  }
  /*-----POINTER-----*/
  void setBorder(int pointer, bool setting){
    if(windows[pointer].border != setting){
      windows[pointer].border = setting;
      if(setting == false){
        wborder(windows[pointer].pointer, ' ', ' ', ' ', ' ', ' ', ' ', ' ' , ' ');
      }
      else if(setting == true){
        box(windows[pointer].pointer, 0, 0);
      }
    }
  }
  void clearWindow(int pointer){
    wclear(windows[pointer].pointer);
  }
  void setWindowTitle(int pointer, bool setting){
    if(windows[pointer].title != setting){
      windows[pointer].title = setting;
      drawTitle(pointer);
    }
  }
  void setCurrentWindow(int pointer){
    currentWindowPointer = pointer;
  }
  /*-----CURRENT-----*/
  void csetBorder(bool setting){
    setBorder(currentWindowPointer, setting);
  }
  void cclearWindow(){
    clearWindow(currentWindowPointer);
  }
  void csetWindowTitle(bool setting){
    setWindowTitle(currentWindowPointer, setting);
  }
  /*-----FIND-----*/
  void fsetBorder(string name, bool setting){
    setBorder(findWindowPointer(name), setting);
  }
  void fclearWindow(string name){
    clearWindow(findWindowPointer(name));
  }
  void fsetWindowtitle(string name, bool setting){
    setWindowTitle(findWindowPointer(name), setting);
  }
  void setCurrentWindow(string name){
    currentWindowPointer = findWindowPointer(name);
  }
  /*-----LINUX-----*/
  void drawTitle(int pointer){
    int titleSize = windows[pointer].name.size();
    int windowSize = windows[pointer].sizeX;
    int posx;
    windowSize = windowSize / 2;
    titleSize = titleSize / 2;
    posx = windowSize - titleSize;
    mvwprintw(windows[pointer].pointer, 0, posx, windows[pointer].name.c_str());
  }
  /*>>>>>-----Termination-----<<<<<*/
  void terminateAllWindows(){
    for(unsigned a = 0; a < windows.size(); a++){
      terminateWindow(a);
    }
  }
  void terminateWindow(int pointer){
    if(windows[pointer].border == true){
      setBorder(pointer, false);
    }
    if(windows[pointer].title == true){
      setWindowTitle(pointer, false);
    }
    clearWindow(pointer);
    windows.erase(windows.begin() + pointer);
  }
  /*>>>>>-----USER INTERFACE-----<<<<<*/
  /*>>>>>-----Input-----<<<<<*/
  char gchar(){
    char in;
    in = getch();
    return(in);
  }
  int gint(){
    int in;
    in = int(getch());
    return(in);
  }
  int cint(){
    int in = 0;
    int rawin = 0;
    while(rawin != 13){
      rawin = int(getch());
      in = (in * 10) + rawin;
    }
    return(in);
  }
  string cstr(){
    string in;
    char inch;
    int rawint = 0;
    while(rawint != 13){
      rawint = int(getch());
      inch = char(rawint);
      in = in + inch;
    }
    return(in);
  }
  float cfloat(){
    string rawstr = cstr();
    string::size_type sz;
    float in;
    in = stof(rawstr, &sz);
    return(in);
  }
  /*>>>>>-----Output-----<<<<<*/
  /*-----POINTER-----*/
  void print(int pointer, string str){
    for(int a = 0; a < str.size(); a++){
      if(str[a] == '/'){
        int b = a + 1;
        if(str[b] == 'n'){
          windows[pointer].cursorY++;
          if(windows[pointer].cursorY > windows[pointer].sizeY){
            windows[pointer].cursorY = 0;
            if(windows[pointer].border == true){
              windows[pointer].cursorY++;
            }
            clearWindow(pointer);
          }
        }
      }
      else if(str[a] != '/'){
        if(windows[pointer].border == false){
          if(windows[pointer].cursorX >= windows[pointer].sizeX){
            windows[pointer].cursorX = 0;
            windows[pointer].cursorY++;
            if(windows[pointer].cursorY >= windows[pointer].sizeY){
              windows[pointer].cursorY = 0;
              if(windows[pointer].title == true){
                windows[pointer].cursorY++;
              }
              clearWindow(pointer);
            }
          }
        }
        if(windows[pointer].border == true){
          if(windows[pointer].cursorX >= windows[pointer].sizeX - 1){
            windows[pointer].cursorX = 1;
            windows[pointer].cursorY++;
            if(windows[pointer].cursorY >= windows[pointer].sizeY - 1){
              windows[pointer].cursorY = 1;
              clearWindow(pointer);
            }
          }
        }
        string character;
        stringstream sstream;
        sstream << str[a];
        sstream >> character;
        mvwprintw(windows[pointer].pointer, windows[pointer].cursorY, windows[pointer].cursorX, character.c_str());
        windows[pointer].cursorX++;
      }
    }
    if(autoRefresh == true){
      update();
    }
  }
  void mprint(int pointer, int x, int y, string str){
    windows[pointer].cursorX = x;
    windows[pointer].cursorY = y;
    print(pointer, str);
  }
  /*-----CURRENT-----*/
  void cprint(string str){
    print(currentWindowPointer, str);
  }
  void cmprint(int x, int y, string str){
    mprint(currentWindowPointer, x, y, str);
  }
  /*-----FIND-----*/
  void fprint(string name, string str){
    print(findWindowPointer(name), str);
  }
  void fmprint(string name, int x, int y, string str){
    int pointer = findWindowPointer(name);
    mprint(pointer, x, y, str);
  }
  /*>>>>>-----SYSTEM-----<<<<<*/
  /*>>>>>-----Update-----<<<<<*/
  void update(){
    for(unsigned a = 0; a < windows.size(); a++){
      wrefresh(windows[a].pointer);
    }
  }
  /*=====>>>>>-----Termination-----<<<<<=====*/
  void terminateConscientia(){
    endwin();
  }
};
