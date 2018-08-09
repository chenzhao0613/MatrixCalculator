//  matrix.cpp
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
    
    // Matrix Addition
    Matrix addMatrix(const Matrix &anotherMatrix)
    {
        Matrix newMatrix(m_rows, m_columns);
        for( int m = 0; m < m_rows; m++)
        {
            for( int n = 0; n < m_columns; ++n)
            {
                newMatrix.m_pArray[m][n] = m_pArray[m][n] + anotherMatrix.m_pArray[m][n];
            }
        }
        return newMatrix;
    }
    
    // Matrix Subtraction
    Matrix substractMatrix(const Matrix &anotherMatrix)
    {
        Matrix newMatrix(m_rows, m_columns);
        for( int m = 0; m < m_rows; m++)
        {
            for( int n = 0; n < m_columns; ++n)
            {
                newMatrix.m_pArray[m][n] = m_pArray[m][n] - anotherMatrix.m_pArray[m][n];
            }
        }
        return newMatrix;
    }
    
    // Matrix multiplication scalar
    Matrix multiply(int scalar)
    {
        Matrix newMatrix(m_rows, m_columns);
        for (int m = 0; m < m_rows; m++)
        {
            for (int n = 0; n < m_columns; ++n)
            {
                newMatrix.m_pArray[m][n] = m_pArray[m][n] * scalar;
            }
        }
        return newMatrix;
    }
    
    // Matrix multiplication
    Matrix multiply(const Matrix &matrix2)
    {
        Matrix newMatrix(m_rows, matrix2.m_columns);
        for (int m = 0; m < newMatrix.m_rows; m++)
        {
            for (int n = 0; n < newMatrix.m_columns; n++)
            {
                int sum = 0;
                for (int i = 0; i < m_columns; i++)
                {
                    sum = sum + m_pArray[m][i] * matrix2.m_pArray[i][n];
                }
                newMatrix.m_pArray[m][n] = sum;
            }
        }
        return newMatrix;
    }
    
    void print()
    {
        for (int m = 0; m < m_rows; m++)
        {
            for (int n = 0; n < m_columns; ++n)
            {
                cout << std::setw(3);
                cout << m_pArray[m][n] << " ";
            }
            cout << endl;
        }
    }
    
    // Additional functions
    int GetNumberOfRows() const
    {
        return m_rows;
    }
    
    int GetNumberOfColumns() const
    {
        return m_columns;
    }
    
    int **m_pArray; // Dynamically allocated 2d array
    
private:
    int m_rows;
    int m_columns;
    
};

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
    
    for (int m = 0; m < rows; ++m)
    {
        for (int n = 0; n < columns; ++n)
        {
            cin >> newMatrix.m_pArray[m][n];
        }
    }
    
    return newMatrix;
}

int main()
{
    Matrix matrix1(CreateMatrixFromInput(1));
    Matrix matrix2(CreateMatrixFromInput(2));
    
    
    cout << "Matrix Addition" << endl;
    cout << "Matrix1 is: " << endl;
    matrix1.print();
    cout << "Matrix2 is: " << endl;
    matrix2.print();
    if (matrix1.GetNumberOfRows() == matrix2.GetNumberOfRows() && matrix1.GetNumberOfColumns() == matrix2.GetNumberOfColumns())
    {
        Matrix addMatrix = matrix1.addMatrix(matrix2);
        cout << "Result is: " << endl;
        addMatrix.print();
    }
    else
    {
        cout << "Skip Addition (Matrix Size Does not Match)" << endl;
    }
    
    
    cout << "Matrix Subtraction" << endl;
    cout << "Matrix1 is: " << endl;
    matrix1.print();
    cout << "Matrix2 is: " << endl;
    matrix2.print();
    if (matrix1.GetNumberOfRows() == matrix2.GetNumberOfRows() && matrix1.GetNumberOfColumns() == matrix2.GetNumberOfColumns())
    {
        Matrix subMatrix = matrix1.substractMatrix(matrix2);
        cout << "Result is: " << endl;
        subMatrix.print();
    }
    else
    {
        cout << "Skip Subtraction (Matrix Size Does not Match)" << endl;
    }
    
    cout << "Matrix Multiplication Scalar" << endl;
    cout << "Matrix1 is: " << endl;
    matrix1.print();
    srand( static_cast<unsigned int>(time(NULL)));  // initialize random
    int iRandomNumber = rand() % 10 + 1;
    cout << "Scalar value is: " << iRandomNumber << endl;
    Matrix mulScalarMatrix = matrix1.multiply(iRandomNumber);
    cout << "Result is: " << endl;
    mulScalarMatrix.print();
    
    
    cout << "Matrix Multiplication" << endl;
    cout << "Matrix1 is: " << endl;
    matrix1.print();
    cout << "Matrix2 is: " << endl;
    matrix2.print();
    if (matrix1.GetNumberOfColumns() == matrix2.GetNumberOfRows())
    {
        Matrix mulMatrix = matrix1.multiply(matrix2);
        cout << "Result is: " << endl;
        mulMatrix.print();
    }
    else
    {
        cout << "Skip Multiplication (Matrix Size Does not Match)" << endl;
    }
    
    return 0;
}
