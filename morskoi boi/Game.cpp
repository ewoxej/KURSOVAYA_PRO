/*Game.cpp �������� ������� ��� �������������� � �������������*/
#include"Game.h"

void drawField(int** arr, string msg, bool visible) {//���������� ������� ����
	system("cls");
	int ship_value = (visible) ? ship_inst : ship_wounded;
	int dot_value = (visible) ? ship_fence : sea_marked;//�����(� ����������� �� ��������� ����)
	std::cout << "\n\n\n" << "    0123456789\n";
	for (int i = 0; i < fieldSize; i++) {
		std::cout << "   " << (char)(65 + i);//����� ���� �� A-J �� ������ ��������
		for (int j = 0; j < fieldSize; j++) {
			if (arr[i][j] == ship_value)std::cout << SHIP; else
			if (arr[i][j] == dot_value)std::cout << DOT; else
			if (arr[i][j] == ship_killed) std::cout << KILLED;
			else std::cout << SEA;	
			}
		std::cout << " "; ConsoleMessage(msg, i);//����� ��������� � ������� �� ������ ��������
		}
	}


void Game(bool save,int** field){//����(��� �������������� ����������?(��/���),������� ����)
	bool stat = false;
	if (!save) //���� ��� �� ����������
	{
	IntegerMatrixZero(field, fieldSize, fieldSize);//��������� ���� ������
	ShipAllocateRandom(field); //���������� �������
	stat = true;//����� ����������
	}
	string name;
	if (stat) {
		drawField(field, "Stat", 0);
		if (_getch() == KEY_ESC) stat = false; //��������� ������� Esc
		ConsoleMessage("EnterName");
		std::cin >> name;
	}
	int killed_ships = 0;//���-�� ���������� ������
	int steps = 0;//���-�� �����
	int x, y;
	clock_t clock1 = clock();//����������� ��������� ������ �������
	while (killed_ships != 20)
	{
		drawField(field, "Game", 0); ReadPosition(x, y, field); 
		if (field[x][y] == sea_clean||field[x][y]==ship_fence) {field[x][y] = sea_marked; steps++;}
		if (field[x][y] == ship_inst) {killOrWound(field,x,y); killed_ships++; steps++;}
	}

	if(stat) StatToFile(name, returnTimeInSec(clock1), steps);//���� ���������� ������� �������� �� � ����
	drawField(field, "Win", 0);
	_getch();
}

void ReadPosition(int& x, int& y, int** arr) {
	char tempsym0, tempsym1;//���������� ��� �������� ��������� ��������
	while (true) {
		ConsoleMessage("EnterPosition");
		tempsym0 = _getche();
		if (tempsym0 == KEY_TAB) {
			SaveToFile(arr); continue;
		}
		if (tempsym0 == KEY_ESC) {
			exit(0);
		}
		tempsym1 = _getche();
		if (isDigit(tempsym0) || isDigit(tempsym1)) {//���� ���� ���� �� ���� �����
			if (isDigit(tempsym0)) y = (tempsym0 - 48);//���� ����� ������
			else y = (tempsym1 - 48);//���� ���,������ ��� ������
		}
		else { drawField(arr, "PosInc", 0); continue; }
		if (isletter(tempsym0) != -1 || isletter(tempsym1) != -1) {//���� ���� ���� �� ���� �����
			if (isletter(tempsym0) != -1) x = isletter(tempsym0);
			else x = isletter(tempsym1);
		}
		else { drawField(arr, "PosInc", 0); continue; }//� ��������� ������ ������ ��������� ��  ������,������ ������
		return;
	}
}