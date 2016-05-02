#include <ncurses.h>
#include <vector>
#include "Conscientia.h"
using namespace std;
/*>--Conscientia Declarations--<*/
vector<WINDOW *> windows;
int currentWindowIndex = -1;


/*>--Conscientia Funcitons--<*/
/*INITILIZATION*/
void Conscientia::initilizeNcurses(){
    initscr();
    keypad(stdscr, TRUE);
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
void Conscientia::newWindow(int sizeX, int sizeY, int posX, int posY, bool border){
    WINDOW *local;
    local = newwin(sizeY, sizeX, posY, posX);
    keypad(local, TRUE);
    if(border == true){
        box(local, 0, 0);
    }
    wrefresh(local);
    windows.push_back(local);
}
