#include <iostream>
#include <string>
#include <sstream>
#include <Windows.h>
#include <vector>
#include <fstream>
#include <ctime>
#include <conio.h>
#include "Conscientia.h"
/*=====>>>>>-----BASIC DATA-----<<<<<=====*/
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

/*=====>>>>>-----ADVANCED DATA-----<<<<<=====*/
/*=====>>>>>-----Global-----<<<<<=====*/
struct luxCode {
	vector<string> lines;
};
/*>>>>>-----FUNCTIONS-----<<<<<*/
/*>>>>>-----Menu-----<<<<<*/

/*>>>>>-----Loading Bars-----<<<<<*/
vector<int> loadingBarPointers;

namespace CONSCIENTIA {
	/*=====>>>>>-----FUNCTIONS-----<<<<<=====*/
	/*=====>>>>>-----Initilization-----<<<<<=====*/
	void initializeConscientia() {
		autoRefresh = false;
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
		initializeConscientia();
	}
	/*>>>>>-----SETTINGS-----<<<<<*/
	void setAutoRefresh(bool setting) {
		autoRefresh = setting;
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
	void clearAllWindows() {
		for (unsigned a = 0; a < windows.size(); a++) {
			clearWindow(a);
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
	/*-----POINTER-----*/
	void setBorder(int pointer, bool setting) {
		if (windows[pointer].border != setting) {
			windows[pointer].border = setting;
			drawBorder(pointer);
		}
	}
	void clearWindow(int pointer) {
		string clear = "";
		int charCount, x, y;
		windows[pointer].cursorX = 0;
		windows[pointer].cursorY = 0;
		if (windows[pointer].border == true || windows[pointer].title == true) {
			windows[pointer].cursorY++;
		}
		if (windows[pointer].border == true) {
			windows[pointer].cursorX++;
		}
		x = windows[pointer].sizeX;
		y = windows[pointer].sizeY;
		if (windows[pointer].border == true) {
			x -= 2;
			y -= 2;
		}
		if (windows[pointer].title == true && windows[pointer].border == false) {
			x--;
		}
		charCount = x;
		for (int a = 0; a < charCount; a++) {
			clear = clear + char(0);
		}
		for (int a = 0; a < y; a++) {
			print(pointer, clear);
		}
		clear = "";
		windows[pointer].cursorX = 0;
		windows[pointer].cursorY = 0;
		if (windows[pointer].border == true || windows[pointer].title == true) {
			windows[pointer].cursorY++;
		}
		if (windows[pointer].border == true) {
			windows[pointer].cursorX++;
		}
	}
	void setWindowTitle(int pointer, bool setting) {
		if (windows[pointer].title != setting) {
			windows[pointer].title = setting;
			drawTitle(pointer);
		}
	}
	void setCurrentWindow(int pointer) {
		currentWindowPointer = pointer;
	}
	/*-----CURRENT-----*/
	void csetBorder(bool setting) {
		setBorder(currentWindowPointer, setting);
	}
	void cclearWindow() {
		clearWindow(currentWindowPointer);
	}
	void csetWindowTitle(bool setting) {
		setWindowTitle(currentWindowPointer, setting);
	}
	/*-----FIND-----*/
	void fsetBorder(string name, bool setting) {
		setBorder(findWindowPointer(name), setting);
	}
	void fclearWindow(string name) {
		clearWindow(findWindowPointer(name));
	}
	void fsetWindowTitle(string name, bool setting) {
		setWindowTitle(findWindowPointer(name), setting);
	}
	void fsetCurrentWindow(string name) {
		currentWindowPointer = findWindowPointer(name);
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
		if (windows[pointer].title == true) {
			setWindowTitle(pointer, false);
		}
		clearWindow(pointer);
		windows.erase(windows.begin() + pointer);
	}
	/*>>>>>-----USER INTERFACE-----<<<<<*/
	/*>>>>>-----Input-----<<<<<*/
	char gchar() {
		char in;
		in = _getch();
		return(in);
	}
	int gint() {
		int in;
		in = _getch();
		return(in);
	}
	int cint() {
		int in = 0;
		int rawin = 0;
		while (rawin != 13) {
			rawin = _getch();
			in = (in * 10) + rawin;
		}
		return(in);
	}
	string cstr() {
		string in;
		char inch;
		int rawint = 0;
		while (rawint != 13) {
			rawint = _getch();
			inch = char(rawint);
			in = in + inch;
		}
		return(in);
	}
	float gfloat() {
		string rawstr = cstr();
		string::size_type sz;
		float in;
		in = stof(rawstr, &sz);
		return(in);
	}
	/*>>>>>-----Output-----<<<<<*/
	/*-----POINTER-----*/
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
				string character;
				stringstream sstream;
				sstream << str[a];
				sstream >> character;
				COORD pos = { windows[pointer].cursorX + windows[pointer].startX, windows[pointer].cursorY + windows[pointer].startY };
				DWORD dwBytesWritten = 0;
				WriteConsoleOutputCharacter(loadBuffer, character.c_str(), character.size(), pos, &dwBytesWritten);
				windows[pointer].cursorX++;
			}
		}
		if (autoRefresh == true) {
			update();
		}
	}
	void mprint(int pointer, int x, int y, string str) {
		windows[pointer].cursorX = x;
		windows[pointer].cursorY = y;
		print(pointer, str);
	}
	/*-----CURRENT-----*/
	void cprint(string str) {
		print(currentWindowPointer, str);
	}
	void cmprint(int x, int y, string str) {
		mprint(currentWindowPointer, x, y, str);
	}
	/*-----FIND-----*/
	void fprint(string name, string str) {
		print(findWindowPointer(name), str);
	}
	void fmprint(string name, int x, int y, string str) {
		mprint(findWindowPointer(name), x, y, str);
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

	/*=====>>>>>-----ADVANCED FUNCITONS-----<<<<<=====*/
	/*=====>>>>>-----Output Funcitons-----<<<<<=====*/
	/*>>>>>-----INTERACTIVE-----<<<<<*/
	/*>>>>>-----Menu-----<<<<<*/
	string menu(string menuFileDirectory, int posX, int posY, int sizeX, int sizeY) {
		menuHierarchy menu;
		menu = loadMenuHierarchy(menuFileDirectory);
		int windowPointer = windows.size();
		int pageWidth, listWidth;
		int currentPage = 0, currentList = 0, currentItem = 0;
		createWindow(menu.name, posX, posY, sizeX, sizeY, true, true);
		setCurrentWindow(windowPointer);
		return("");
	}
	menuHierarchy loadMenuHierarchy(string menuFileDirectory) {
		string line;
		luxCode rawCode;
		int lineCount = 0, totalLines;
		int loadBar = -1;
		ifstream load(menuFileDirectory.c_str());
		if (load.is_open()) {
			load >> lineCount;
			totalLines = lineCount;
			if (lineCount >= 50) {
				loadBar = initializeLoadingBar("Loading Menu");
			}
			lineCount = 0;
			getline(load, line);
			while (getline(load, line)) {
				rawCode.lines.push_back(line);
				lineCount++;
				if (loadBar != -1 && (lineCount % 10) == 0) {
					loadingBar(loadBar, ((double)lineCount / (double)totalLines) * 100);
				}
			}
			load.close();
			if (loadBar != -1) {
				terminateLoadingBar(loadBar);
			}
		}
		string cleanLine;
		bool tabSpace;
		for (unsigned a = 0; a < rawCode.lines.size(); a++) {
			line = rawCode.lines[a];
			cleanLine = "";
			tabSpace = true;
			for (unsigned b = 0; b < line.size(); b++) {
				if (tabSpace == true && line[b] != '	') {
					tabSpace = false;
				}
				if (tabSpace == false) {
					cleanLine = cleanLine + line[b];
				}
			}
			rawCode.lines[a] = cleanLine;
		}
		menuHierarchy newHierarchy;
		menuPage newPage;
		menuList newList;
		int currentLevel = 0;
		string currentLine = "";
		string codeLine = "";
		for (unsigned a = 0; a < rawCode.lines.size(); a++) {
			currentLine = rawCode.lines[a];
			codeLine = "";
			if (currentLine[0] == '[') {
				for (unsigned b = 1; b < currentLine.size() && currentLine[b] != ']'; b++) {
					codeLine = codeLine + currentLine[b];
				}
				if (currentLevel == 0) {
				}
				if (currentLevel == 1) {
				}
				if (currentLevel == 2) {
				}
			}
			if (currentLine[currentLine.size() - 1] == '{') {
				if (currentLevel == 0) {
					newHierarchy.name = codeLine;
				}
				if (currentLevel == 1) {
					newPage.lists.clear();
					newPage.name = codeLine;
				}
				if (currentLevel == 2) {
					newList.items.clear();
					newList.name = codeLine;
				}
				currentLevel++;
			}
			if (currentLine[currentLine.size() - 1] == '}') {
				currentLevel--;
				if (currentLevel == 0) {
				}
				if (currentLevel == 1) {
					newHierarchy.pages.push_back(newPage);
				}
				if (currentLevel == 2) {
					newPage.lists.push_back(newList);
				}
			}
			if (currentLine[0] != '[') {
				newList.items.push_back(currentLine);
			}
		}
		return(newHierarchy);
	}
	void displayMenu(menuHierarchy menu, int x, int y, int z) {
		int sizeX, sizeY;
		sizeX = windows[currentWindowPointer].sizeX - 2;
		sizeY = windows[currentWindowPointer].sizeY - 2;
		int pageWidth, listWidth;
		pageWidth = sizeX / menu.pages.size();
		if (pageWidth < sizeX / 6) {
			pageWidth = sizeX / 5;
		}
		listWidth = sizeX / menu.pages[z].lists.size();
		if (listWidth < sizeX / 9) {
			listWidth = sizeX / 8;
		}
	}
	int findTextStart(string str, int space) {
		space = space / 2;
		int strSize = str.size();
		strSize / 2;
		int strStart = space - strSize;
		return(strStart);
	}
	/*>>>>>-----DISPLAY-----<<<<<*/
	/*>>>>>-----Loading Bars-----<<<<<*/
	int initializeLoadingBar(string process) {
		loadingBarPointers.push_back(windows.size());
		createWindow(process, (windows[0].sizeX / 2) - (windows[0].sizeX / 4), (windows[0].sizeY / 2) - 1, (windows[0].sizeX / 2), 3, true, true);
		return(loadingBarPointers.size() - 1);
	}
	void loadingBar(int index, double percent) {
		char block = char(219);
		int loadingBarPointer = loadingBarPointers[index];
		int size = windows[loadingBarPointer].sizeX - 2;
		double blockWorth = (double)100 / (double)size;
		clearWindow(loadingBarPointer);
		string bar = "";
		while (percent > blockWorth) {
			bar = bar + block;
			percent = percent - blockWorth;
		}
		print(loadingBarPointer, bar);
	}
	void terminateLoadingBar(int index) {
		terminateWindow(loadingBarPointers[index]);
		loadingBarPointers.erase(loadingBarPointers.begin() + index);
	}
	/*=====>>>>>-----Input Funcitons-----<<<<<=====*/
	/*=====>>>>>-----System Funcitons-----<<<<<=====*/
}