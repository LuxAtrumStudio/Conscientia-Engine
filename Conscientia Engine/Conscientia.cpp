#include <iostream>
#include <string>
#include <Windows.h>
#include <vector>
#include <fstream>
#include <ctime>
#include "Conscientia.h"
/*=====>>>>>-----DATA-----<<<<<=====*/
/*=====>>>>>-----Global-----<<<<<=====*/
struct window {
	string name;
	int startX, startY, sizeX, sizeY, endX, endY;
	int cursorX, cursorY;
	bool border;
};
vector<window> windows;
int currentWindowPointer = 0;
bool autoRefresh = false;
/*=====>>>>>-----Windows-----<<<<<=====*/
HANDLE loadBuffer, displayBuffer;
_CONSOLE_SCREEN_BUFFER_INFO consoleInfo;

namespace Conscientia {
	/*=====>>>>>-----FUNCTIONS-----<<<<<=====*/
	/*=====>>>>>-----Initilization-----<<<<<=====*/
	void initilizeConscientia() {
		loadBuffer = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
		displayBuffer = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
		SetConsoleActiveScreenBuffer(displayBuffer);
		GetConsoleScreenBufferInfo(displayBuffer, &consoleInfo);
		window declaration;
		declaration.name = "stdscr";
		declaration.startX = 0;
		declaration.startY = 0;
		declaration.sizeX = consoleInfo.dwSize.X;
		declaration.sizeY = consoleInfo.dwSize.Y;
		declaration.endX = consoleInfo.dwSize.X;
		declaration.endY = consoleInfo.dwSize.Y;
		declaration.cursorX = 0;
		declaration.cursorY = 0;
		declaration.border = false;
		windows.push_back(declaration);
	}
	void advancedInit(bool cursor, bool echo, bool raw) {
		initilizeConscientia();
		Conscientia::setCursor(cursor);
		Conscientia::setEcho(echo);
		Conscientia::setRaw(raw);
	}
	/*>>>>>-----SETTINGS-----<<<<<*/
	void setAutoRefresh(bool setting) {
		autoRefresh = setting;
	}
	/*>>>>>-----NCURSES INITILIZATION-----<<<<<*/
	void initilizeColors() {

	}
	void setCursor(bool setting) {

	}
	void setEcho(bool setting) {

	}
	void setRaw(bool setting) {

	}
	/*=====>>>>>-----Run Time-----<<<<<=====*/
	/*>>>>>-----WINDOW-----<<<<<*/
	/*>>>>>-----Initilization-----<<<<<*/
	void createWindow(string name, int posX, int posY, int sizeX, int sizeY, bool border) {
		window declaration;
		declaration.name = name;
		declaration.startX = posX;
		declaration.startY = posY;
		declaration.sizeX = sizeX;
		declaration.sizeY = sizeY;
		declaration.endX = posX + sizeX;
		declaration.endY = posY + sizeY;
		declaration.cursorX = 0;
		declaration.cursorY = 0;
		declaration.border = border;
		if (border == true) {
			declaration.cursorX++;
			declaration.cursorY++;
		}
		windows.push_back(declaration);
	}
	/*>>>>>-----Management-----<<<<<*/
	void setBorder(int pointer, bool setting) {
		if (windows[pointer].border != setting) {
			Conscientia::drawBorder(pointer, setting);
		}
	}
	void clearAllWindows() {
		for (unsigned a = 0; a < windows.size(); a++) {
			clearWindow(a);
		}
	}
	void clearWindow(int pointer) {
		windows[pointer].cursorX = 0;
		windows[pointer].cursorY = 0;
		if (windows[pointer].border == true) {
			windows[pointer].cursorX++;
			windows[pointer].cursorY++;
		}
		string blank = "";
		if (windows[pointer].border == false) {
			for (int a = 0; a < windows[pointer].sizeX; a++) {
				blank = blank + " ";
			}
			for (int a = 0; a < windows[pointer].sizeY; a++) {
				print(pointer, blank);
			}
		}
		else if (windows[pointer].border == true) {
			for (int a = 0; a < windows[pointer].sizeX - 1; a++) {
				blank = blank + " ";
			}
			for (int a = 0; a < windows[pointer].sizeY - 1; a++) {
				print(pointer, blank);
			}
		}
	}
	int findWindowPointer(string name) {
		for (unsigned a = 0; a < windows.size(); a++) {
			if (windows[a].name == name) {
				return(a);
			}
		}
		return(0);
	}
	/*-----WINDOWS-----*/
	void drawBorder(int pointer, bool setting) {

	}
	/*>>>>>-----Termination-----<<<<<*/
	void terminateAllWindows() {
		for (unsigned a = 1; a < windows.size(); a++) {
			terminateWindow(a);
		}
	}
	void terminateWindow(int pointer) {
		if (windows[pointer].border == true) {
			setBorder(pointer, false);
		}
		clearWindow(pointer);
		windows.erase(windows.begin() + pointer);
	}
	/*>>>>>-----USER INTERFACE-----<<<<<*/
	/*>>>>>-----Input-----<<<<<*/
	char gchar() {

	}
	char cchar() {

	}
	int gint() {

	}
	int cint() {

	}
	string cstr() {

	}
	float gfloat() {

	}
	/*>>>>>-----Output-----<<<<<*/
	void print(int pointer, string str) {

	}
	void cprint(string str) {

	}
	void fprint(string name, string str) {

	}
	void mprint(int pointer, int x, int y, string str) {

	}
	void cmprint(int x, int y, string str) {

	}
	void fmprint(string name, int x, int y, string str) {

	}
	void printc(int pointer, string str, int text, int background) {

	}
	void cprintc(string str, int text, int background) {

	}
	void fprintc(string name, string str, int text, int background) {

	}
	void mprintc(int pointer, int x, int y, string str, int text, int background) {

	}
	void cmprintc(int x, int y, string str, int text, int background) {

	}
	void fmprintc(string name, int x, int y, string str, int text, int background) {

	}
	/*>>>>>-----SYSTEM-----<<<<<*/
	/*>>>>>-----Update-----<<<<<*/
	void update() {
		displayBuffer = loadBuffer;
		SetConsoleActiveScreenBuffer(displayBuffer);
	}
	/*=====>>>>>-----Termination-----<<<<<=====*/
	void terminateConscientia() {

	}
}
