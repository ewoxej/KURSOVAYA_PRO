#include"IntegerMatrix.h"
#include"Game.h"
int main() {
	setlocale(LC_ALL, "Russian");
	system("mode con cols=60 lines=15");
	int** field;
	IntegerMatrixCreate(field, fieldSize, fieldSize);
	char choose;
	while (true) {
		IntegerMatrixZero(field, fieldSize, fieldSize);
		ShipAllocateRandom(field);
		drawField(field, "Hello", 1);
		choose = _getche();
		switch (choose) {
		case '1': {Game(0,field); break; }
		case '2': {
			drawField(field, "Help", 1);
			choose = _getch();
			if (choose == KEY_ESC) exit(0);
			break; }
		case'3': {statPrint();
			ConsoleMessage("PressAnyKey"); ConsoleMessage("PressEsc");
			if (_getch() == KEY_ESC) exit(0);
			break; }
		case '4': {
			drawField(field, "About", 1);
			choose = _getch();
			if (choose == KEY_ESC) exit(0);
			break; }
		case '5': {RestoreFromFile(field); Game(1, field); break; }
		case KEY_ESC: exit(0);
		}
	}
	IntegerMatrixDelete(field, fieldSize);
	system("pause");
}