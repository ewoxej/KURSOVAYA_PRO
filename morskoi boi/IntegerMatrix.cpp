void IntegerMatrixCreate(int**& _arr, int _row, int _col) {//создание матрицы
	_arr = new int*[_row];
	for (int i = 0; i<_row; i++) _arr[i] = new int[_col];
}

void IntegerMatrixZero(int** _arr, int _row, int _col) {//заполнить матрицу нулями
	for (int i = 0; i<_row; i++)
	for (int j = 0; j<_col; j++) 
	_arr[i][j] = 0;
}

void IntegerMatrixDelete(int**& _arr, int _row) {//удалить матрицу
	for (int i = 0; i<_row; i++) delete[] _arr[i];
	delete[] _arr;
}

