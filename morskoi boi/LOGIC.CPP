/*logic.cpp содержит функции,отвечающие за логику игры*/
#include"Logic.h"

bool isDigit(char& c) {
	return c >= 48 && c <= 57;
}

bool pointIsExist(int x, int y) {//точка существует если ее координаты больше нуля и меньше размера поля
	return ((x < fieldSize) && (x >= 0) && (y < fieldSize) && (y >= 0));
}

bool isCorrectPosition(int** arr, int x, int y, int size, bool rotate) {//позиция корректна?
	if (pointIsExist(x, y) && arr[x][y] == sea_clean)//если существует точка начала
	{
		if (!rotate) {
			if (pointIsExist(x + size - 1, y) && (arr[x + size - 1][y] == sea_clean)) return true;
		}
		else {
			if ((arr[x][y + size - 1] == sea_clean) && pointIsExist(x, y + size - 1)) return true;
		}
	}//и точка конца
	return false;
}

int isletter(char& c) {//символ является буквой A-J
	if (c >= 97 && c <= 106) { c -= 32; return (c - 65); }//если буква маленькая,сделать ее большой.Вернуть ее порядковый номер
	if (c >= 65 && c <= 74) return (c - 65);//буква большая.вернуть ее номер
	return -1;//символ не буква вернуть -1
}

void generateRandomPosition(int& x, int& y) {
	x = rand() % fieldSize;
	y = rand() % fieldSize;
}

void ShipInstall(int** arr, int x, int y, int size, bool rotate) {//установка корабля
	for (int i = 0; i < size; i++) {
		if (rotate) { arr[x][y + i] = 1; pointFence(arr, x, y + i); }
		else { arr[x + i][y] = 1; pointFence(arr, x + i, y); }
	}
}

void pointFence(int** arr, int x, int y) {//строит точки вокруг корабля,чтобы там нельзя было поставить другие
	int myX[] = { -1,0,1,-1,0,1,-1,0,1 };//массив координат по х,которые нужно пройти
	int myY[] = { 1,1,1,0,0,0,-1,-1,-1 };//по у
	for (int i = 0; i < 9; i++)
		if (pointIsExist(x + myX[i], y + myY[i]) && (arr[x + myX[i]][y + myY[i]] == 0))
			arr[x + myX[i]][y + myY[i]] = ship_fence;//если точка существует пометить ее 
}

void ShipAllocateRandom(int** arr) {
	srand(time(NULL));
	int x, y;
	bool rotate;//поворот корабля
	int sizes[5]{ 0,4,3,2,1 };//отображения.ключ-индекс массива-размер.значение-количество кораблей
	for (int j = 1; j < 5; j++) {
		for (int i = 0; i < sizes[j]; i++) {
			do
			{
				generateRandomPosition(x, y);
				rotate = rand() % 2;
			} while (!isCorrectPosition(arr, x, y, j, rotate));//генерировать позицию пока она не станет корректной
			ShipInstall(arr, x, y, j, rotate);
		}
	}
}

void killOrWound(int** field, int x, int y) {//убит или ранен?
	int myX[]{ 1,-1,0,0 };
	int myY[]{ 0,0,-1,1 };
	for (int i = 0; i < 4; i++)
		if (pointIsExist(x + myX[i], y + myY[i]) && field[x + myX[i]][y + myY[i]] == ship_inst) { field[x][y] = ship_wounded; return; }
	field[x][y] = ship_killed; research(field, x, y);
}

void research(int** field, int x, int y) {//отмечать корабль как убитый
	int myX[]{ 1,-1,0,0 };
	int myY[]{ 0,0,-1,1 };
	//для каждой точки где может быть корабль,найти его и отметить как убитый.
	//Запустить функцию рекурсивно для найденной точки
	for (int i = 0; i < 4; i++)
		if (pointIsExist(x + myX[i], y + myY[i]) && field[x + myX[i]][y + myY[i]] == ship_wounded) { 
		field[x + myX[i]][y + myY[i]] = ship_killed; 
	    research(field, x + myX[i], y + myY[i]); }
}

int returnTimeInSec(clock_t clock1) {
	clock_t clock2 = clock();
	return (clock2 - clock1) / 1000.0;
}

