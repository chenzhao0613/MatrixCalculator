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
	friend matrix* operator+ (const matrix &n1, const matrix &n2);
	friend matrix* operator- (const matrix &n1, const matrix &n2);
	friend matrix* operator* (const matrix &n1, const matrix &n2);
	friend matrix* operator* (int scalar, const matrix &n1);
	friend matrix* operator* (const matrix &n1, int scalar);
	friend ostream& operator<< (ostream&, const matrix&);
	friend istream& operator>> (istream&, const matrix&);
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


// define non-default constructor

matrix::~matrix()
{
	for (int i = 0; i < rows; i++) {
		delete data[i];
		data[i] = nullptr;
	}

	delete[] data;
	data = nullptr;
}

matrix* operator+(const matrix &n1, const matrix &n2) {
	matrix* result = new matrix(n1.rows, n1.columns);
	for (int i = 0; i < n1.rows; i++) {
		for (int j = 0; j < n1.columns; j++) {
			result->data[i][j] = n1.data[i][j] + n2.data[i][j];
		}
	}
	return result;
}

matrix* operator - (const matrix &n1, const matrix &n2) {
	matrix* result = new matrix(n1.rows, n1.columns);
	for (int i = 0; i < n1.rows; i++) {
		for (int j = 0; j < n1.columns; j++) {
			result->data[i][j] = n1.data[i][j] - n2.data[i][j];
		}
	}
	return result;
}

matrix* operator * (const matrix &n1, const matrix &n2) {
	matrix* result = new matrix(n1.rows, n2.columns);
	for (int i = 0; i < n1.rows; i++) {
		for (int j = 0; j < n2.columns; j++) {
			result->data[i][j] = 0;
		}
	}
	for (int i = 0; i < n1.rows; i++)
	{
		for (int j = 0; j < n2.columns; j++)
			for (int k = 0; k < n2.columns; k++)
				result->data[i][j] += n1.data[i][k] * n2.data[k][j];
	}
	return result;
}

matrix* operator * (int scalar, const matrix &n1) {
	matrix* result = new matrix(n1.rows, n1.columns);
	for (int i = 0; i < n1.rows; i++) {
		for (int j = 0; j < n1.columns; j++) {
			result->data[i][j] = n1.data[i][j] * scalar;
		}
	}
	return result;
}

matrix* operator * (const matrix &n1, int scalar) {
	matrix* result = new matrix(n1.rows, n1.columns);
	for (int i = 0; i < n1.rows; i++) {
		for (int j = 0; j < n1.columns; j++) {
			result->data[i][j] = n1.data[i][j] * scalar;
		}
	}
	return result;
}

ostream& operator<< (ostream& os, const matrix&n1) {
	for (int i = 0; i < n1.rows; i++) {
		for (int j = 0; j < n1.columns; j++) {
			os << n1.data[i][j];
		}
		os << endl;
	}
	return os;
}

istream& operator>> (istream& is, const matrix&n1) {
	for (int i = 0; i < n1.rows; i++) {
		for (int j = 0; j < n1.columns; j++) {
			is >> n1.data[i][j];
		}
	}
	return is;
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
	cin >> first;
	cout << "Number of Rows in Matrix 2: ";
	cin >> row2;
	cout << "Number of Columns in Matrix 2: ";
	cin >> col2;
	matrix second(row2, col2);
	cout << "Values of Matrix 2 (expecting " << row2 * col2 << "): ";
	cin >> second;

	if (row1 == row2 && col1 == col2)//judge whether the two matrix can be added or substracted
	{
		matrix* sum = first + second;
		matrix* difference = first - second;


		cout << first << " +\n";
		cout << second << " =\n";
		cout << *sum << endl;

		cout << first << " -\n";
		cout << second << " =\n";
		cout << *difference << endl;
		
	}
	else
	{
		cout << "You can't do sum or substraction because the sizes of the two matrixs don't match!\n";
	}

	if (col1 == row2)//judge whether the two matrixs can be multiplied
	{
		matrix* product = first * second;
		cout << first << " *\n";
		cout << second << " =\n";
		cout << *product << endl;
	}
	else
	{
		cout << "you can't do multiplication because the sizes of the two matrixs don't match!\n";
	}

	matrix* scalarProduct1 = first * 4;

	cout << "4\n" << " *\n";
	cout << first << " =\n";
	cout << *scalarProduct1 << endl;
	
	matrix* scalarProduct2 = 4 * first;

	cout << "4\n" << " *\n";
	cout << first << " =\n";
	cout << *scalarProduct2 << endl;
	return 0;
}
// define operator+ for matrix addition

