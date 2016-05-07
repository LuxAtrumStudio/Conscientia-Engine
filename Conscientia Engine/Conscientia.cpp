#include <iostream>
#include <string>
#include <Windows.h>
#include <vector>
#include <fstream>
#include <ctime>
#include "Conscientia.h"
/*=====>>>>>-----DATA-----<<<<<=====*/
struct window {
	string name;
	int posX, posY, width, height;
	int cursorX, cursorY;
};
vector<window> windows;

namespace Consicientia {
	/*=====>>>>>-----FUNCTIONS-----<<<<<=====*/
	/*=====>>>>>-----Initilization-----<<<<<=====*/
	void initilizeConscientia() {

	}
	/*=====>>>>>-----Run Time-----<<<<<=====*/
	/*>>>>>-----WINDOW-----<<<<<*/
	/*>>>>>-----Initilization-----<<<<<*/
	void createWindow(string name, int posX, int posY, int width, int height) {

	}
	/*>>>>>-----Management-----<<<<<*/
	void drawAllBorders() {

	}
	void drawBorder(int pointer) {

	}
	void clearAllWindows() {

	}
	void clearWindow(int pointer) {

	}
	/*>>>>>-----Termination-----<<<<<*/
	void terminateAllWindows() {

	}
	void terminateWindow(int pointer) {

	}
	/*>>>>>-----USER INTERFACE-----<<<<<*/
	/*>>>>>-----Input-----<<<<<*/
	char gchar() {

	}
	void cchar() {

	}
	int gint() {

	}
	int cint() {

	}
	string cstr() {

	}
	/*>>>>>-----Output-----<<<<<*/
	void print(int pointer, string str) {

	}
	void cprint(string str) {

	}
	void mprint(int pointer, int x, int y, string str) {

	}
	void cmprint(int x, int y, string str) {

	}
	void printc(int pointer, string str, int text, int background) {

	}
	void cprintc(string str, int text, int background) {

	}
	void mprintc(int pointer, int x, int y, string str, int text, int background) {

	}
	void cmprintc(int x, int y, string str, int text, int background) {

	}
	/*>>>>>-----SYSTEM-----<<<<<*/
	/*>>>>>-----Update-----<<<<<*/
	void updateAllWindows() {

	}
	void updateWindow(int pointer) {

	}
	void swapBuffers() {

	}
	/*=====>>>>>-----Termination-----<<<<<=====*/
	void terminateConscientia() {

	}
}