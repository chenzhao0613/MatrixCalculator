//  matrix_ops.cpp
//  Homework 1
//
//  zjc5164@psu.edu
//
//  Created by Zhao  Chen on 2/6/18.
//  Copyright © 2018 Zhao  Chen. All rights reserved.
//

#include <iostream>
#include <iomanip>  // for std::setw
#include <stdlib.h> // for rand() function
#include <time.h>   // time for srand
using namespace std;

class Matrix
{
public:
    // non-default constructor
    Matrix(int rows, int columns) : m_rows(rows), m_columns(columns)
    {
        m_pArray = new int*[m_rows];
        for(int m = 0; m < m_rows; ++m)
        {
            m_pArray[m] = new int[m_columns];
        }
    }
    
    // copy-constructor (allow returning Matrix from functions)
    Matrix(const Matrix& matrix)
    {
        m_rows = matrix.m_rows;
        m_columns = matrix.m_columns;
        m_pArray = new int*[m_rows];
        for(int m = 0; m < m_rows; ++m)
        {
            m_pArray[m] = new int[m_columns];
        }
        
        for (int m = 0; m < m_rows; m++)
        {
            for (int n = 0; n < m_columns; ++n)
            {
                m_pArray[m][n] = matrix.m_pArray[m][n];
            }
        }
    }
    
    // destructors
    ~Matrix()
    {
        for (int m = 0; m < m_rows; ++m)
        {
            delete[] m_pArray[m];
            m_pArray[m] = NULL;
        }
        delete[] m_pArray;
        m_pArray = NULL;
    }
    
    // Friend function
    friend Matrix operator+(const Matrix &m1, const Matrix &m2);
    friend Matrix operator-(const Matrix &m1, const Matrix &m2);
    friend Matrix operator*(const Matrix &m1, int scalar);
    friend Matrix operator*(int scalar, const Matrix &m1);
    friend Matrix operator*(const Matrix &m1, const Matrix &m2);
    friend ostream& operator<<(ostream& out, const Matrix &m);
    friend istream& operator>>(istream& input, Matrix &m);
    
    // additional functions
    int GetNumberOfRows() const
    {
        return m_rows;
    }
    
    int GetNumberOfColumns() const
    {
        return m_columns;
    }
    
    int **m_pArray;  // dynamically allocated 2d array
    
private:
    int m_rows;
    int m_columns;
    
};

// Addition overloaded operator
Matrix operator+(const Matrix &m1, const Matrix &m2)
{
    Matrix newMatrix(m1.m_rows, m1.m_columns);
    for (int m = 0; m < newMatrix.m_rows; m++)
    {
        for (int n = 0; n < newMatrix.m_columns; ++n)
        {
            newMatrix.m_pArray[m][n] = m1.m_pArray[m][n] + m2.m_pArray[m][n];
        }
    }
    return newMatrix;
}

// Multiplication scalar overloaded operator
Matrix operator*(const Matrix &m1, int scalar)
{
    Matrix newMatrix(m1.m_rows, m1.m_columns);
    for (int m = 0; m < m1.m_rows; m++)
    {
        for (int n = 0; n < m1.m_columns; ++n)
        {
            newMatrix.m_pArray[m][n] = m1.m_pArray[m][n] * scalar;
        }
    }
    return newMatrix;
}

// Subtraction overloaded operator
Matrix operator-(const Matrix &m1, const Matrix &m2)
{
    Matrix newMatrix(m1.m_rows, m1.m_columns);
    for( int m = 0; m < newMatrix.m_rows; m++)
    {
        for( int n = 0; n < newMatrix.m_columns; ++n)
        {
            newMatrix.m_pArray[m][n] = m1.m_pArray[m][n] - m2.m_pArray[m][n];
        }
    }
    return newMatrix;
}

// Multiplication scalar overloaded operator
Matrix operator*(int scalar, const Matrix &m1)
{
    Matrix newMatrix(m1.m_rows, m1.m_columns);
    for (int m = 0; m < m1.m_rows; m++)
    {
        for (int n = 0; n < m1.m_columns; ++n)
        {
            newMatrix.m_pArray[m][n] = m1.m_pArray[m][n] * scalar;
        }
    }
    return newMatrix;
}

// Multiplication overloaded opertor
Matrix operator*(const Matrix &m1, const Matrix &m2)
{
    Matrix newMatrix(m1.m_rows, m2.m_columns);
    for (int m = 0; m < newMatrix.m_rows; m++)
    {
        for (int n = 0; n < newMatrix.m_columns; n++)
        {
            int sum = 0;
            for (int i = 0; i < m1.m_columns; i++)
            {
                sum = sum + m1.m_pArray[m][i] * m2.m_pArray[i][n];
            }
            newMatrix.m_pArray[m][n] = sum;
        }
    }
    return newMatrix;
}

ostream& operator<<(ostream& out, const Matrix &matrix)
{
    for (int m = 0; m < matrix.m_rows; m++)
    {
        for (int n = 0; n < matrix.m_columns; ++n)
        {
            out << std::setw(3);
            out << matrix.m_pArray[m][n] << " ";
        }
        out << endl;
    }
    return out;
}

istream& operator>>(istream& input, Matrix &matrix)
{
    for (int m = 0; m < matrix.m_rows; ++m)
    {
        for (int n = 0; n < matrix.m_columns; ++n)
        {
            input >> matrix.m_pArray[m][n];
        }
    }
    
    return input;
}

// Assume input is correct
Matrix CreateMatrixFromInput(int matrixNumber)
{
    cout << "Number of Rows in Matrix " << matrixNumber << ": ";
    int rows, columns;
    cin >> rows;
    cout << "Number of Columns in Matrix " << matrixNumber << ": ";
    cin >> columns;
    cout << "Values of Matrix " << matrixNumber << " (expecting " << rows * columns << "): ";
    
    Matrix newMatrix(rows, columns);
    std::cin >> newMatrix;
    
    return newMatrix;
}

int main()
{
    Matrix matrix1(CreateMatrixFromInput(1));
    Matrix matrix2(CreateMatrixFromInput(2));
    
    
    cout << "Matrix Addition" << endl;
    cout << "Matrix1 is: " << endl << matrix1;
    cout << "Matrix2 is: " << endl << matrix2;
    if (matrix1.GetNumberOfRows() == matrix2.GetNumberOfRows() && matrix1.GetNumberOfColumns() == matrix2.GetNumberOfColumns())
    {
        Matrix addMatrix = matrix1 + matrix2;
        cout << "Result is: " << endl << addMatrix;
    }
    else
    {
        cout << "Skip Addition (Matrix Size Does not Match)" << endl;
    }
    
    
    cout << "Matrix Subtraction" << endl;
    cout << "Matrix1 is: " << endl << matrix1;
    cout << "Matrix2 is: " << endl << matrix2;
    if (matrix1.GetNumberOfRows() == matrix2.GetNumberOfRows() && matrix1.GetNumberOfColumns() == matrix2.GetNumberOfColumns())
    {
        Matrix subMatrix = matrix1 - matrix2;
        cout << "Result is: " << endl << subMatrix;
    }
    else
    {
        cout << "Skip Subtraction (Matrix Size Does not Match)" << endl;
    }
    
    cout << "Matrix Multiplication Scalar" << endl;
    cout << "Matrix1 is: " << endl << matrix1;
    srand(static_cast<unsigned int>(time(NULL)));  // initialize random
    int iRandomNumber = rand() % 10 + 1;
    cout << "Scalar value is: " << iRandomNumber << endl;
    Matrix mulScalarMatrix1 = matrix1 * iRandomNumber;
    cout << "Result is: " << endl << mulScalarMatrix1;
    
    
    cout << "Matrix Multiplication Scalar" << endl;
    cout << "Matrix1 is: " << endl << matrix1;
    cout << "Scalar value is: " << iRandomNumber << endl;
    Matrix mulScalarMatrix2 = iRandomNumber * matrix1;
    cout << "Result is: " << endl << mulScalarMatrix2;
    
    
    cout << "Matrix Multiplication" << endl;
    cout << "Matrix1 is: " << endl << matrix1;
    cout << "Matrix2 is: " << endl << matrix2;
    if (matrix1.GetNumberOfColumns() == matrix2.GetNumberOfRows())
    {
        Matrix mulMatrix = matrix1 * matrix2;
        cout << "Result is: " << endl << mulMatrix;
    }
    else
    {
        cout << "Skip Multiplication (Matrix Size Does not Match)" << endl;
    }
    
    return 0;
}
