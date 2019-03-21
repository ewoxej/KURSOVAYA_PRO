#ifndef WORK_WITH_FILES
#define WORK_WITH_FILES
#define _CRT_SECURE_NO_WARNINGS
#include"Logic.h"
#include<iostream>
#include<fstream>
#include<iomanip>
#include<string>
using std::string;
void StatHeader(char* filename);
void StatToFile(string gamer_name, double seconds, int steps);
void statPrint();
void SaveToFile(int**);
void RestoreFromFile(int**);
void ConsoleMessage(string key, int index = -1);
#endif