/*Game.cpp содержит функции для взаимодействия с пользователем*/
#include"Game.h"

void drawField(int** arr, string msg, bool visible) {//нарисовать игровое поле
	system("cls");
	int ship_value = (visible) ? ship_inst : ship_wounded;
	int dot_value = (visible) ? ship_fence : sea_marked;//точка(в зависимости от видимости поля)
	std::cout << "\n\n\n" << "    0123456789\n";
	for (int i = 0; i < fieldSize; i++) {
		std::cout << "   " << (char)(65 + i);//вывод букв от A-J на каждой итерации
		for (int j = 0; j < fieldSize; j++) {
			if (arr[i][j] == ship_value)std::cout << SHIP; else
			if (arr[i][j] == dot_value)std::cout << DOT; else
			if (arr[i][j] == ship_killed) std::cout << KILLED;
			else std::cout << SEA;	
			}
		std::cout << " "; ConsoleMessage(msg, i);//вывод сообщения в консоль на каждой итерации
		}
	}


void Game(bool save,int** field){//игра(это востановленное сохранение?(да/нет),игровое поле)
	bool stat = false;
	if (!save) //если это не сохранение
	{
	IntegerMatrixZero(field, fieldSize, fieldSize);//заполнить поле нулями
	ShipAllocateRandom(field); //расставить корабли
	stat = true;//вести статистику
	}
	string name;
	if (stat) {
		drawField(field, "Stat", 0);
		if (_getch() == KEY_ESC) stat = false; //обработка нажатия Esc
		ConsoleMessage("EnterName");
		std::cin >> name;
	}
	int killed_ships = 0;//кол-во пораженных клеток
	int steps = 0;//кол-во ходов
	int x, y;
	clock_t clock1 = clock();//фиксировать начальный момент времени
	while (killed_ships != 20)
	{
		drawField(field, "Game", 0); ReadPosition(x, y, field); 
		if (field[x][y] == sea_clean||field[x][y]==ship_fence) {field[x][y] = sea_marked; steps++;}
		if (field[x][y] == ship_inst) {killOrWound(field,x,y); killed_ships++; steps++;}
	}

	if(stat) StatToFile(name, returnTimeInSec(clock1), steps);//если статистика ведется записать ее в файл
	drawField(field, "Win", 0);
	_getch();
}

void ReadPosition(int& x, int& y, int** arr) {
	char tempsym0, tempsym1;//переменные для хранения введенных символов
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
		if (isDigit(tempsym0) || isDigit(tempsym1)) {//если есть хотя бы одна цифра
			if (isDigit(tempsym0)) y = (tempsym0 - 48);//если цифра первая
			else y = (tempsym1 - 48);//если нет,значит она вторая
		}
		else { drawField(arr, "PosInc", 0); continue; }
		if (isletter(tempsym0) != -1 || isletter(tempsym1) != -1) {//если есть хотя бы одна буква
			if (isletter(tempsym0) != -1) x = isletter(tempsym0);
			else x = isletter(tempsym1);
		}
		else { drawField(arr, "PosInc", 0); continue; }//в противном случае выдать сообщение об  ошибке,начать заново
		return;
	}
}