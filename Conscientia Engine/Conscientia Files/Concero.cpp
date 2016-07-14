#include <iostream>
#include <string>
#include <sstream>
#include <Windows.h>
#include <vector>
#include <fstream>
#include <ctime>
#include <conio.h>
#include "Conscientia Headers.h"

int level = 0;
unsigned int index = 1;
vector<JSONFile> loadedJSONFiles;
void CONCERO::RunScript(vector<string> scriptData)
{
	if (scriptData[0] == "") {
		scriptData[0] = "GetPage";
	}
	string transferLocation = scriptData[0] + ".tran";
	ofstream transferData(transferLocation.c_str());
	if (transferData.is_open()) {
		for (unsigned a = 1; a < scriptData.size(); a++) {
			if (a != scriptData.size() - 1) {
				transferData << scriptData[a] << endl;
			}
			else {
				transferData << scriptData[a];
			}
		}
		transferData.close();
	}
	else {
		LOGGING::LogError("Unable to genorate transfer data file for script: " + scriptData[0], "Conscientia.cpp/CONCERO/RunScript");
	}
}
void CONCERO::InterpretJSON(string file)
{
	index = 1;
	level = 0;
	string raw = "";
	ifstream load(file.c_str());
	if (load.is_open()) {
		string line;
		while (getline(load, line)) {
			for (unsigned a = 0; a < line.size(); a++) {
				if (line[a] == '[') {
					line[a] = NULL;
				}
				if (line[a] == ']') {
					line[a] = NULL;
				}
			}
			raw = raw + line;
		}
		load.close();
	}
	else {
		cout << ">>>Unable to open: " + file << endl;
	}
	string current;
	JSONFile fileJSON;
	fileJSON.variables.push_back(ReadVar(file, raw));
	loadedJSONFiles.push_back(fileJSON);
}
subVar CONCERO::ReadVar(string name, string raw)
{
	subVar newLevel;
	newLevel.name = name;
	string strLineA, strLineB;
	bool loadName = false, loadVal = false, stringVal = false, action = false, nameStored = false;
	newLevel.name = name;
	for (index; index < raw.size() - 1; index++) {
		//cout << index << ",";
		if (raw[index] == '{') {
			index++;
			string print = "";
			for (int b = 0; b < level; b++) {
				print = print + ">";
			}
			//cout << print << '"' << strLineA << "\":\n";
			level++;
			subVar level = ReadVar(strLineA, raw);
			newLevel.vars.push_back(level);
			index = index + 1;
			strLineA = "";
			strLineB = "";
			loadName = false;
			loadVal = false;
			stringVal = false;
			action = false;
			nameStored = false;
		}
		if (raw[index] == '"' && loadName == false && action == false && nameStored == false) {
			loadName = true;
			action = true;
		}
		else if (raw[index] == '"' && loadName == true && action == false) {
			loadName = false;
			nameStored = true;
		}
		if (raw[index] == ':' && raw[index + 1] != '{' && action == false) {
			loadVal = true;
			action = true;
		}
		if (raw[index] == '\"' && loadVal == true && action == false) {
			stringVal = true;
			action = true;
		}
		if (raw[index] == ',' && loadVal == true || raw[index] == '}' && loadVal == true) {
			subVar newVariable;
			newVariable.name = strLineA;
			newVariable.strVar = strLineB;
			loadVal == false;
			if (stringVal == false) {
				bool doubleCheck = false;
				for (unsigned b = 0; b < strLineB.size(); b++) {
					if (strLineB[b] == '.') {
						doubleCheck = true;
					}
				}
				if (doubleCheck == false) {
					string::size_type returnSize;
					newVariable.intVar = stoi(strLineB, &returnSize);
				}
				else if (doubleCheck == true) {
					string::size_type returnSize;
					newVariable.doubleVar = stod(strLineB, &returnSize);
				}
			}
			else if (stringVal == true) {
				stringVal = false;
			}
			string print = "";
			for (int b = 0; b < level; b++) {
				print = print + ">";
			}
			//cout << print << newVariable.name << ":" << newVariable.strVar << endl;
			newLevel.vars.push_back(newVariable);
			strLineA = "";
			strLineB = "";
			loadName = false;
			loadVal = false;
			stringVal = false;
			action = false;
			nameStored = false;
		}
		if (loadName == true && action == false) {
			strLineA = strLineA + raw[index];
		}
		if (loadVal == true && action == false) {
			strLineB = strLineB + raw[index];
		}
		if (raw[index] == '}' && action == false) {
			level--;
			return(newLevel);
		}
		action = false;
	}
	return (newLevel);
}
JSONFile CONCERO::GetJSONFile(string name)
{
	for (unsigned a = 0; a < loadedJSONFiles.size(); a++) {
		if (loadedJSONFiles[a].variables[0].name == name) {
			return(loadedJSONFiles[a]);
		}
	}
}