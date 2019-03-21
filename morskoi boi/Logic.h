#ifndef LOGIC
#define LOGIC
#include<ctime>
#include<cstdlib>
int const fieldSize = 10;
enum { sea_clean, ship_inst, ship_wounded, ship_fence, ship_killed, sea_marked };
int isletter(char& c);
bool pointIsExist(int x, int y);
bool isCorrectPosition(int** arr, int x, int y, int size, bool rotate);
void pointFence(int**arr, int x, int y);
void generateRandomPosition(int& x, int& y);
void ShipInstall(int** arr, int x, int y, int size, bool rotate);
void ShipAllocateRandom(int** arr);
void killOrWound(int** field, int x, int y);
void research(int** field, int x, int y);
int returnTimeInSec(clock_t clock1);
bool isDigit(char& c);
#endif