#include <iostream>
#include <string>
#include <Windows.h>
#include <vector>
#include <fstream>
#include <ctime>
using namespace std;

namespace Conscientia {
	/*=====>>>>>-----FUNCTIONS-----<<<<<=====*/
	/*=====>>>>>-----Initilization-----<<<<<=====*/
	void initilizeConscientia();
	void advancedInit(bool cursor, bool echo, bool raw);
	/*>>>>>-----SETTINGS-----<<<<<*/
	void setAutoRefresh(bool setting);
	/*>>>>>-----NCURSES INITILIZATION-----<<<<<*/
	void initilizeColors();
	void setCursor(bool setting);
	void setEcho(bool setting);
	void setRaw(bool setting);
	/*=====>>>>>-----Run Time-----<<<<<=====*/
	/*>>>>>-----WINDOW-----<<<<<*/
	/*>>>>>-----Initilization-----<<<<<*/
	void createWindow(string name, int posX, int posY, int sizeX, int sizeY, bool border, bool title);
	/*>>>>>-----Management-----<<<<<*/
	void setBorder(int pointer, bool setting);
	void clearAllWindows();
	void clearWindow(int pointer);
	int findWindowPointer(string name);
	void setWindowTitle(int pointer, bool setting);
	void drawTitle(int pointer);
	/*-----WINDOWS-----*/
	void drawBorder(int pointer);
	/*>>>>>-----Termination-----<<<<<*/
	void terminateAllWindows();
	void terminateWindow(int pointer);
	/*>>>>>-----USER INTERFACE-----<<<<<*/
	/*>>>>>-----Input-----<<<<<*/
	char gchar();
	char cchar();
	int gint();
	int cint();
	string cstr();
	float gfloat();
	/*>>>>>-----Output-----<<<<<*/
	void print(int pointer, string str);
	void cprint(string str);
	void fprint(string name, string str);
	void mprint(int pointer, int x, int y, string str);
	void cmprint(int x, int y, string str);
	void fmprint(string name, int x, int y, string str);
	void printc(int pointer, string str, int text, int background);
	void cprintc(string str, int text, int background);
	void fprintc(string name, string str, int text, int background);
	void mprintc(int pointer, int x, int y, string str, int text, int background);
	void cmprintc(int x, int y, string str, int text, int background);
	void fmprintc(string name, int x, int y, string str, int text, int background);
	/*-----SETTINGS-----*/
	void setOutputAttribues(WORD attributes, int length, int x, int y);
	/*>>>>>-----SYSTEM-----<<<<<*/
	/*>>>>>-----Update-----<<<<<*/
	void update();
	/*=====>>>>>-----Termination-----<<<<<=====*/
	void terminateConscientia();
}