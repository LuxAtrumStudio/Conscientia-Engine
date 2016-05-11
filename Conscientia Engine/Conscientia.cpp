#include <iostream>
#include <string>
#include <sstream>
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
	bool border, title;
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
		declaration.title = false;
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
	void createWindow(string name, int posX, int posY, int sizeX, int sizeY, bool border, bool title) {
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
		declaration.title = title;
		if (border == true) {
			declaration.cursorX++;
			declaration.cursorY++;
		}
		if (title == true && border == false) {
			declaration.cursorY++;
		}
		windows.push_back(declaration);
		if (border == true) {
			drawBorder(windows.size() - 1);
		}
		if (title == true) {
			drawTitle(windows.size() - 1);
		}
	}
	/*>>>>>-----Management-----<<<<<*/
	void setBorder(int pointer, bool setting) {
		if (windows[pointer].border != setting) {
			windows[pointer].border = setting;
			drawBorder(pointer);
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
	void setWindowTitle(int pointer, bool setting) {
		if (windows[pointer].title != setting) {
			windows[pointer].title = setting;
			drawTitle(pointer);
		}
	}
	void drawTitle(int pointer) {
		int titleSize = windows[pointer].name.size();
		int windowSize = windows[pointer].sizeX;
		windowSize = windowSize / 2;
		titleSize = titleSize / 2;
		COORD pos = { (windowSize - titleSize) + windows[pointer].startX, windows[pointer].startY };
		DWORD dwBytesWritten;
		string title = windows[pointer].name;
		WriteConsoleOutputCharacter(loadBuffer, title.c_str(), title.size(), pos, &dwBytesWritten);
	}
	/*-----WINDOWS-----*/
	void drawBorder(int pointer) {
		int x = 0, y = 0;
		char TL = char(218), TR = char(191), BL = char(192), BR = char(217);
		char V = char(179), H = char(196);
		string characterH;
		stringstream sstreamH;
		COORD posH;
		DWORD dwBytesWrittenH = 0;
		sstreamH << H;
		sstreamH >> characterH;
		for (x = 0; x <= windows[pointer].sizeX - 1; x++) {
			posH = { (short)x + (short)windows[pointer].startX, (short)windows[pointer].startY };
			WriteConsoleOutputCharacter(loadBuffer, characterH.c_str(), characterH.size(), posH, &dwBytesWrittenH);
			posH = { (short)x + (short)windows[pointer].startX, (short)windows[pointer].endY - 1 };
			WriteConsoleOutputCharacter(loadBuffer, characterH.c_str(), characterH.size(), posH, &dwBytesWrittenH);
		}
		string characterV;
		stringstream sstreamV;
		COORD posV;
		DWORD dwBytesWrittenV = 0;
		sstreamV << V;
		sstreamV >> characterV;
		for (y = 0; y <= windows[pointer].sizeY - 1; y++) {
			posV = { (short)windows[pointer].startX, (short)y + (short)windows[pointer].startY };
			WriteConsoleOutputCharacter(loadBuffer, characterV.c_str(), characterV.size(), posV, &dwBytesWrittenV);
			posV = { (short)windows[pointer].endX - 1, (short)y + (short)windows[pointer].startY };
			WriteConsoleOutputCharacter(loadBuffer, characterV.c_str(), characterV.size(), posV, &dwBytesWrittenV);
		}
		string character1;
		stringstream sstream1;
		COORD pos1;
		DWORD dwBytesWritten1 = 0;
		sstream1 << TL;
		sstream1 >> character1;
		pos1 = { (short)windows[pointer].startX, (short)windows[pointer].startY };
		WriteConsoleOutputCharacter(loadBuffer, character1.c_str(), character1.size(), pos1, &dwBytesWritten1);
		string character2;
		stringstream sstream2;
		COORD pos2;
		DWORD dwBytesWritten2 = 0;
		sstream2 << TR;
		sstream2 >> character2;
		pos2 = { (short)windows[pointer].endX - 1, (short)windows[pointer].startY };
		WriteConsoleOutputCharacter(loadBuffer, character2.c_str(), character2.size(), pos2, &dwBytesWritten2);
		string character3;
		stringstream sstream3;
		COORD pos3;
		DWORD dwBytesWritten3 = 0;
		sstream3 << BL;
		sstream3 >> character3;
		pos3 = { (short)windows[pointer].startX, (short)windows[pointer].endY - 1 };
		WriteConsoleOutputCharacter(loadBuffer, character3.c_str(), character3.size(), pos3, &dwBytesWritten3);
		string character4;
		stringstream sstream4;
		COORD pos4;
		DWORD dwBytesWritten4 = 0;
		sstream4 << BR;
		sstream4 >> character4;
		pos4 = { (short)windows[pointer].endX - 1, (short)windows[pointer].endY - 1 };
		WriteConsoleOutputCharacter(loadBuffer, character4.c_str(), character4.size(), pos4, &dwBytesWritten4);
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
		return('a');
	}
	char cchar() {
		return('a');
	}
	int gint() {
		return(0);
	}
	int cint() {
		return(0);
	}
	string cstr() {
		return("a");
	}
	float gfloat() {
		return(0.0f);
	}
	/*>>>>>-----Output-----<<<<<*/
	void print(int pointer, string str) {
		for (int a = 0; a < str.size(); a++) {
			if (str[a] == '/') {
				int b = a + 1;
				if (str[b] == 'n') {
					windows[pointer].cursorY++;
					if (windows[pointer].cursorY > windows[pointer].sizeY) {
						windows[pointer].cursorY = 0;
						if (windows[pointer].border == true || windows[pointer].title == true) {
							windows[pointer].cursorY++;
						}
					}
					clearWindow(pointer);
					a = a + 2;
				}
			}
			else if (str[a] != '/') {
				string character;
				stringstream sstream;
				sstream << str[a];
				sstream >> character;
				COORD pos = { windows[pointer].cursorX + windows[pointer].startX, windows[pointer].cursorY + windows[pointer].startY };
				DWORD dwBytesWritten = 0;
				WriteConsoleOutputCharacter(loadBuffer, character.c_str(), character.size(), pos, &dwBytesWritten);
				windows[pointer].cursorX++;
				if (windows[pointer].border == false) {
					if (windows[pointer].cursorX >= windows[pointer].sizeX) {
						windows[pointer].cursorX = 0;
						windows[pointer].cursorY++;
						if (windows[pointer].cursorY >= windows[pointer].sizeY) {
							windows[pointer].cursorY = 0;
							if (windows[pointer].title == true) {
								windows[pointer].cursorY++;
							}
							clearWindow(pointer);
						}
					}
				}
				if (windows[pointer].border == true) {
					if (windows[pointer].cursorX >= windows[pointer].sizeX - 1) {
						windows[pointer].cursorX = 1;
						windows[pointer].cursorY++;
						if (windows[pointer].cursorY >= windows[pointer].sizeY - 1) {
							windows[pointer].cursorY = 1;
							clearWindow(pointer);
						}
					}
				}
			}
		}
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