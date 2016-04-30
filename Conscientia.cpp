#include <ncurses.h>
#include "Conscientia.h"
using namespace std;

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
