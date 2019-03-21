#include"Work_with_files.h"

void StatToFile(string gamer_name, double seconds, int steps) {
	char* filename = "seawars.txt";
	StatHeader(filename);
	std::ofstream ofile(filename, std::ios::app);
	ofile << std::setw(15) << gamer_name << std::setw(15) << seconds << std::setw(fieldSize) << steps << "\n";
}

void StatHeader(char* filename) {
	std::ifstream ifile(filename);
	if (ifile.peek() == EOF) {
		ifile.close();
		std::ofstream ofile(filename, std::ios::app);
		ofile << std::setw(15) << "Имя" << std::setw(15) << "Время(с)" << std::setw(fieldSize) << "Ходов" << "\n";
		ofile.close();
		return;
	}
}

void SaveToFile(int** arr) {
	string filename;
	std::cout << "Введите имя файла:";
	std::cin >> filename;
	std::ofstream file(filename);
	for (int i = 0; i < fieldSize; i++) 
	for (int j = 0; j < fieldSize; j++) file << arr[i][j] << " ";
}

void RestoreFromFile(int** arr) {
	system("cls");
	string filename;
	std::cout << "Введите имя файла:";
	std::cin >> filename;
	std::ifstream file(filename);
	if (!file) { std::cout << "\nНе удалось открыть файл!\n"; system("pause"); return; }
	for (int i = 0; i < fieldSize; i++)
	for (int j = 0; j < fieldSize; j++) file >> arr[i][j];
	}

void statPrint() {
	char* filename = "seawars.txt";
	system("cls");
	std::ifstream ifile(filename);
	string gamer_name, seconds, steps;
	while (ifile) {
		ifile >> gamer_name >> seconds >> steps;
		std::cout << std::setw(10) << gamer_name << std::setw(10) << seconds << std::setw(7) << steps << "\n";
		gamer_name = ' '; seconds = ' '; steps = ' ';
	}
}

void ConsoleMessage(string key, int index) {
	char indexstr[2];
	if (index != -1) { _itoa(index, indexstr, 10); key += indexstr; }
	std::ifstream ifile("strings.txt");
	string buff;
	int position = -1;
	while (ifile)
	{
		getline(ifile, buff, '=');
		if (key == buff) { getline(ifile, buff, '\n'); std::cout << buff << "\n"; return; }
		else getline(ifile, buff, '\n');
	}
	std::cout << "\n";
}