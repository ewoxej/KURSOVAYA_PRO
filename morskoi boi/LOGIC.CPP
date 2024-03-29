/*logic.cpp �������� �������,���������� �� ������ ����*/
#include"Logic.h"

bool isDigit(char& c) {
	return c >= 48 && c <= 57;
}

bool pointIsExist(int x, int y) {//����� ���������� ���� �� ���������� ������ ���� � ������ ������� ����
	return ((x < fieldSize) && (x >= 0) && (y < fieldSize) && (y >= 0));
}

bool isCorrectPosition(int** arr, int x, int y, int size, bool rotate) {//������� ���������?
	if (pointIsExist(x, y) && arr[x][y] == sea_clean)//���� ���������� ����� ������
	{
		if (!rotate) {
			if (pointIsExist(x + size - 1, y) && (arr[x + size - 1][y] == sea_clean)) return true;
		}
		else {
			if ((arr[x][y + size - 1] == sea_clean) && pointIsExist(x, y + size - 1)) return true;
		}
	}//� ����� �����
	return false;
}

int isletter(char& c) {//������ �������� ������ A-J
	if (c >= 97 && c <= 106) { c -= 32; return (c - 65); }//���� ����� ���������,������� �� �������.������� �� ���������� �����
	if (c >= 65 && c <= 74) return (c - 65);//����� �������.������� �� �����
	return -1;//������ �� ����� ������� -1
}

void generateRandomPosition(int& x, int& y) {
	x = rand() % fieldSize;
	y = rand() % fieldSize;
}

void ShipInstall(int** arr, int x, int y, int size, bool rotate) {//��������� �������
	for (int i = 0; i < size; i++) {
		if (rotate) { arr[x][y + i] = 1; pointFence(arr, x, y + i); }
		else { arr[x + i][y] = 1; pointFence(arr, x + i, y); }
	}
}

void pointFence(int** arr, int x, int y) {//������ ����� ������ �������,����� ��� ������ ���� ��������� ������
	int myX[] = { -1,0,1,-1,0,1,-1,0,1 };//������ ��������� �� �,������� ����� ������
	int myY[] = { 1,1,1,0,0,0,-1,-1,-1 };//�� �
	for (int i = 0; i < 9; i++)
		if (pointIsExist(x + myX[i], y + myY[i]) && (arr[x + myX[i]][y + myY[i]] == 0))
			arr[x + myX[i]][y + myY[i]] = ship_fence;//���� ����� ���������� �������� �� 
}

void ShipAllocateRandom(int** arr) {
	srand(time(NULL));
	int x, y;
	bool rotate;//������� �������
	int sizes[5]{ 0,4,3,2,1 };//�����������.����-������ �������-������.��������-���������� ��������
	for (int j = 1; j < 5; j++) {
		for (int i = 0; i < sizes[j]; i++) {
			do
			{
				generateRandomPosition(x, y);
				rotate = rand() % 2;
			} while (!isCorrectPosition(arr, x, y, j, rotate));//������������ ������� ���� ��� �� ������ ����������
			ShipInstall(arr, x, y, j, rotate);
		}
	}
}

void killOrWound(int** field, int x, int y) {//���� ��� �����?
	int myX[]{ 1,-1,0,0 };
	int myY[]{ 0,0,-1,1 };
	for (int i = 0; i < 4; i++)
		if (pointIsExist(x + myX[i], y + myY[i]) && field[x + myX[i]][y + myY[i]] == ship_inst) { field[x][y] = ship_wounded; return; }
	field[x][y] = ship_killed; research(field, x, y);
}

void research(int** field, int x, int y) {//�������� ������� ��� ������
	int myX[]{ 1,-1,0,0 };
	int myY[]{ 0,0,-1,1 };
	//��� ������ ����� ��� ����� ���� �������,����� ��� � �������� ��� ������.
	//��������� ������� ���������� ��� ��������� �����
	for (int i = 0; i < 4; i++)
		if (pointIsExist(x + myX[i], y + myY[i]) && field[x + myX[i]][y + myY[i]] == ship_wounded) { 
		field[x + myX[i]][y + myY[i]] = ship_killed; 
	    research(field, x + myX[i], y + myY[i]); }
}

int returnTimeInSec(clock_t clock1) {
	clock_t clock2 = clock();
	return (clock2 - clock1) / 1000.0;
}

