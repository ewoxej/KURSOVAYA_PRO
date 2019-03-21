#ifndef GAMEH
#define GAMEH
#include"IntegerMatrix.h"
#include"Work_with_files.h"
#include"Logic.h"
#include<iostream>
#include<string>
#include<conio.h>
/*константы-коды клавиш*/
int const KEY_ESC = 27;
int const KEY_ENTER = 13;
int const KEY_TAB = 9;
/*константы-символы*/
char const DOT = 183;
char const KILLED = 'O';
char const SHIP = 'X';
char const SEA = ' ';
using std::string;
void drawField(int** arr, string msg, bool visible);
void Game(bool save,int**);
void getStatName(bool& stat, bool& demo,string& name);
void ReadPosition(int& x, int& y,int**);
#endif