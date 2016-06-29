#ifndef MATRIX_H
#define MATRIX_H

class Matrix{
public:
	Matrix(int rows, int cols);
	~Matrix();
	int rowsCnt();
	int colsCnt();
	void print();
	void setValue(int row, int col, int value);
private:
	int rows, cols;
	int** a;
};

#endif // MATRIX_H

