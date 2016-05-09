#include <iostream>
#include <string>
#include <ncurses.h>
#include <vector>
#include "Conscientia.h"
using namespace std;

/*=====>>>>>-----DATA-----<<<<<=====*/
struct window {
  string name;
  WINDOW * pointer;
  int posX, posY, sizeX, sizeY;
  int cursorX, cursorY;
  int colorPointer;
  bool border;
};
vector<window> windows;
int currentWindowPointer = 0;
bool autoRefresh = false;

namespace Conscientia
{
  /*=====>>>>>-----FUNCTIONS-----<<<<<=====*/
  /*=====>>>>>-----Initilization-----<<<<<=====*/
  void initilizeConscientia(){
    initscr();
    keypad(stdscr, TRUE);
    window declaration;
    declaration.name = "stdscr";
    declaration.pointer = stdscr;
    declaration.posX = 0;
    declaration.posY = 0;
    getmaxyx(stdscr, declaration.sizeY, declaration.sizeX);
    declaration.cursorX = 0;
    declaration.cursorY = 0;
    declaration.border = false;
    windows.push_back(declaration);
    initilizeColors();
  }
  void advancedInit(bool cursor, bool echo, bool raw){
    initilizeConscientia();
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
  void createWindow(string name, int posX, int posY, int sizeX, int sizeY, bool border){
    WINDOW *local;
    local = newwin(sizeY, sizeX, posY, posX);
    keypad(local, TRUE);
    if (border == true){
      box(local, 0, 0);
    }
    window declaration;
    declaration.name = name;
    declaration.pointer = local;
    declaration.posX = posX;
    declaration.posY = posY;
    declaration.sizeX = sizeX;
    declaration.sizeY = sizeY;
    declaration.cursorX = 0;
    declaration.cursorY = 0;
    declaration.border = border;
    windows.push_back(declaration);
  }
  /*>>>>>-----Management-----<<<<<*/
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
  void clearAllWindows(){
    for(unsigned a = 0; a < windows.size(); a++){
      clearWindow(a);
    }
  }
  void clearWindow(int pointer){
    wclear(windows[pointer].pointer);
  }
  int findWindowPointer(string name){
    for(unsigned a = 0; a < windows.size(); a++){
      if(windows[a].name == name){
        return(a);
      }
    }
    return(0);
  }
  void setWindowColor(int pointer, int text, int background){

  }
  void clearWindowColor(int pointer){

  }
  /*>>>>>-----Termination-----<<<<<*/
  void terminateAllWindows(){
    for(unsigned a = 0; a < windows.size(); a++){
      terminateWindow(a);
    }
  }
  void terminateWindow(int pointer){
    clearWindow(pointer);
  }
  /*>>>>>-----USER INTERFACE-----<<<<<*/
  /*>>>>>-----Input-----<<<<<*/
  char gchar(){

  }
  char cchar(){

  }
  int gint(){

  }
  int cint(){

  }
  string cstr(){

  }
  float gfloat(){

  }
  /*>>>>>-----Output-----<<<<<*/
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
        string character = "" + str[a];
        mvwprintw(windows[pointer].pointer, windows[pointer].cursorY, windows[pointer].cursorX, character.c_str());
        windows[pointer].cursorX++;
        if(windows[pointer].cursorX > windows[pointer].sizeX){
          windows[pointer].cursorX = 0;
          if(windows[pointer].border == true){
            windows[pointer].cursorX++;
          }
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
    }
    if(autoRefresh == true){
      updateWindow(pointer);
    }
  }
  void cprint(string str){
    print(currentWindowPointer, str);
  }
  void fprint(string name, string str){
    print(findWindowPointer(name), str);
  }
  void mprint(int pointer, int x, int y, string str){
    windows[pointer].cursorX = x;
    windows[pointer].cursorY = y;
    print(pointer, str);
  }
  void cmprint(int x, int y, string str){
    mprint(currentWindowPointer, x, y, str);
  }
  void fmprint(string name, int x, int y, string str){
    int pointer = findWindowPointer(name);
    mprint(pointer, x, y, str);
  }
  /*>>>>>-----SYSTEM-----<<<<<*/
  /*>>>>>-----Update-----<<<<<*/
  void update(){
    updateAllWindows();
  }
  /*-----NCURSES-----*/
  void updateAllWindows(){
    for(unsigned a = 0; a < windows.size(); a++){
      updateWindow(a);
    }
  }
  void updateWindow(int pointer){
    wrefresh(windows[pointer].pointer);
  }
  /*=====>>>>>-----Termination-----<<<<<=====*/
  void terminateConscientia(){
    endwin();
  }
};
