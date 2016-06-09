#include <iostream>
#include <string>
#include <Windows.h>
#include <vector>
#include <fstream>
#include <ctime>
using namespace std;
struct menuList {
	string name;
	vector<string> items;
};
struct menuPage {
	string name;
	vector<menuList> lists;
};
struct menuHierarchy {
	string name;
	vector<menuPage> pages;
};
namespace CONSCIENTIA {
	/*=====>>>>>-----CORE FUNCTIONS-----<<<<<=====*/
	/*=====>>>>>-----Initilization-----<<<<<=====*/
	void InitializeConscientia();
	void AdvancedInit(bool cursor, bool echo, bool raw);
	/*>>>>>-----SETTINGS-----<<<<<*/
	void SetAutoRefresh(bool setting);
	/*=====>>>>>-----Run Time-----<<<<<=====*/
	/*>>>>>-----WINDOW-----<<<<<*/
	/*>>>>>-----Initilization-----<<<<<*/
	void GenorateWindow(string name, int posX, int posY, int sizeX, int sizeY, bool border, bool title);
	/*>>>>>-----Management-----<<<<<*/
	void ClearAllWindows();
	int FindWindowPointer(string name);
	/*-----POINTER-----*/
	void SetBorder(int pointer, bool setting);
	void ClearWindow(int pointer);
	void SetWindowTitle(int pointer, bool setting);
	void SetCurrentWindow(int pointer);
	/*-----CURRENT-----*/
	void CsetBorder(bool setting);
	void CclearWindow();
	void CsetWindowTitle(bool setting);
	/*-----FIND-----*/
	void FsetBorder(string name, bool setting);
	void FclearWindow(string name);
	void FsetWindowTitle(string name, bool setting);
	void FsetCurrentWindow(string name);
	/*-----WINDOWS-----*/
	void DrawBorder(int pointer);
	void DrawTitle(int pointer);
	/*>>>>>-----Termination-----<<<<<*/
	void TerminateAllWindows();
	void TerminateWindow(int pointer);
	/*>>>>>-----USER INTERFACE-----<<<<<*/
	/*>>>>>-----Input-----<<<<<*/
	char Gchar();
	int Gint();
	int Cint();
	string Cstr();
	float Gfloat();
	/*>>>>>-----Output-----<<<<<*/
	/*-----POINTER-----*/
	void Print(int pointer, string str);
	void Mprint(int pointer, int x, int y, string str);
	/*-----CURRENT-----*/
	void Cprint(string str);
	void Cmprint(int x, int y, string str);
	/*-----FIND-----*/
	void Fprint(string name, string str);
	void Fmprint(string name, int x, int y, string str);
	/*>>>>>-----SYSTEM-----<<<<<*/
	/*>>>>>-----Update-----<<<<<*/
	void Update();
	/*>>>>>-----Console-----<<<<<*/
	void SetConsoleTitle(string title);
	/*=====>>>>>-----Termination-----<<<<<=====*/
	void TerminateConscientia();
	/*=====>>>>>-----ADVANCED FUNCITONS-----<<<<<=====*/
	/*=====>>>>>-----Output Funcitons-----<<<<<=====*/
	/*>>>>>-----INTERACTIVE-----<<<<<*/
	/*>>>>>-----Menu-----<<<<<*/
	string Menu(string menuFileDirectory, int posX, int posY, int sizeX, int sizeY);
	menuHierarchy LoadMenuHierarchy(string menuFileDirectory);
	void DisplayMenu(menuHierarchy menu, int currentPage, int currentList, int currentItem);
	int FindTextStart(string str, int space);
	/*>>>>>-----DISPLAY-----<<<<<*/
	/*>>>>>-----Loading Bars-----<<<<<*/
	int InitializeLoadingBar(string process);
	void LoadingBar(int index, double percent);
	void TerminateLoadingBar(int index);
	/*=====>>>>>-----Input Funcitons-----<<<<<=====*/
	/*=====>>>>>-----System Funcitons-----<<<<<=====*/
	bool FullStartUp();
}

namespace LOGGING {
	void InitializeLogging();
	void LogError(string log, string location);
	void LogWarning(string log, string location);
	void LogSuccess(string log, string location);
	void LogData(string log, string location);
	void Log(int code);
	void TerminateLogging();
}