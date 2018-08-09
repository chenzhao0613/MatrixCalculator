//---------------------------------------------------------------------
// Name: Taihao Liu
// Email: tzl5365@psu.edu
// Class: CMPSC 122, Section 
// Program 1.1
// Due Date: February 11, 2018, 11:59 PM
//
// Description: This program collects information from the user
// to create two matrices using a Matrix class definition, and
// performs several calculations using those matrices.
// The results of each calculation are retrieved and displayed
// to the user in a readable format.
//---------------------------------------------------------------------
#include<iostream>

using namespace std;

class matrix
{
private:
	int rows;
	int columns;// declare member fields for row, columns
public:
	int ** data;// declare member field for matrix data (int **)
	matrix(int row, int column);// declare non-default constructor, two parameters for row and 
	matrix* add(const matrix& num);
	matrix *subtract(const matrix& num);
	matrix *multiply(const matrix& num);
	matrix *scalarMuliply(int scalar);// declare functions to perform calculations and display output
	void print();
	~matrix();// declare destructor
};

matrix::matrix(int row, int column)
{
	rows = row;
	columns = column;
	data = new int*[rows];
	for (int i = 0; i < rows; i++)
	{
		data[i] = new int[columns];
	}
}

matrix::~matrix()
{
	for (int i = 0; i < rows; i++) {
		delete data[i];
		data[i] = nullptr;
	}

	delete[] data;
	data = nullptr;
}

matrix* matrix::add(const matrix& num) {
	matrix* result = new matrix(rows, columns);
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			result->data[i][j] = data[i][j] + num.data[i][j];
		}
	}
	return result;
}

matrix* matrix::subtract(const matrix& num) {
	matrix* result = new matrix(rows, columns);
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			result->data[i][j] = data[i][j] - num.data[i][j];
		}
	}
	return result;
}

matrix* matrix::multiply(const matrix& num) {
	matrix* result = new matrix(rows, num.columns);
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < num.columns; j++) {
			result->data[i][j] = 0;
		}
	}
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < num.columns; j++)
			for (int k = 0; k < columns; k++)
				result->data[i][j] += data[i][k] * num.data[k][j];
	}
	return result;
}

matrix* matrix::scalarMuliply(int scalar) {
	matrix* result = new matrix(rows, columns);
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			result->data[i][j] = data[i][j] * scalar;
		}
	}
	return result;
}

void matrix::print()
{
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			cout << data[i][j] << " ";
		}
		cout << endl;
	}
}



int main()
{
	int row1, row2, col1, col2;//declare variables
	cout << "Number of Rows in Matrix 1: ";
	cin >> row1;
	cout << "Number of Columns in Matrix 1: ";
	cin >> col1;
	matrix first(row1, col1);
	cout << "Values of Matrix 1 (expecting " << row1 * col1 << "): ";
	for (int i = 0; i < row1; ++i)
		for (int j = 0; j < col1; j++)
		{
			cin >> first.data[i][j];
		}//fill in the matrix
	cout << "Number of Rows in Matrix 2: ";
	cin >> row2;
	cout << "Number of Columns in Matrix 2: ";
	cin >> col2;
	matrix second(row2, col2);
	cout << "Values of Matrix 2 (expecting " << row2 * col2 << "): ";
	for (int i = 0; i < row2; ++i)
		for (int j = 0; j < col2; j++)
		{
			cin >> second.data[i][j];
		}

	if (row1 == row2 && col1 == col2)//judge whether the two matrix can be added or substracted
	{
		matrix* add = first.add(second);
		matrix* substract = first.subtract(second);

		first.print();
		cout << " +\n";
		second.print();
		cout << " =\n";
		add->print();
		cout << endl;

		first.print();
		cout << " -\n";
		second.print();
		cout << " =\n";
		substract->print();
		cout << endl;
	}
	else
	{
		cout << "You can't do sum or substraction because the sizes of the two matrixs don't match!\n";
	}

	if (col1 == row2)//judge whether the two matrixs can be multiplied
	{
		matrix* product = first.multiply(second);
		first.print();
		cout << " *\n";
		second.print();
		cout << " =\n";
		product->print();
		cout << endl;
	}
	else
	{
		cout << "you can't do multiplication because the sizes of the two matrixs don't match!\n";
	}


	matrix* scalarProduct = first.scalarMuliply(4);

	cout << "4\n" << " *\n";
	first.print();
	cout << " =\n";
	scalarProduct->print();
	cout << endl;

	return 0;
}