#include <iostream>
#include "Matrix.h"
using namespace std;

Matrix::Matrix(int rows, int cols){
	this->rows = rows; this->cols = cols;
	a = new int*[rows];
	for(int i=0; i<rows; i++){
		a[i] = new int[cols];
		for(int j=0; j<cols; j++)
			a[i][j] = -1;
	}
}

int Matrix::rowsCnt() { return rows; }
int Matrix::colsCnt() { return cols; }
void Matrix::setValue(int row, int col, int value){
	a[row][col] = value;
}
void Matrix::print(){
	for(int i=0; i<rows; i++){
		for(int j=0; j<cols; j++){
			cout << a[i][j] << "\t";
		}
		cout << endl;
	}
	cout<< endl;
}

Matrix::~Matrix(){
	for(int i=0; i<rows; i++){
		delete a[i];
	}
	delete a;
}

