#include <cmath>
#include <cassert>
#include "Matrix.hpp"

// Overwritten copy constructor
// Allocate memory for new matrix, and copy
// entries into this matrix
Matrix::Matrix(const Matrix& otherMatrix) {
    mNumRows = otherMatrix.mNumRows;
    mNumCols = otherMatrix.mNumCols;
    mData = new double[mNumRows*mNumCols];
    for (int row = 0; row<mNumRows; row++) {
        for (int col = 0; col<mNumCols; col++) {
            int index = row*mNumCols +col;
            mData[index] = otherMatrix.mData[index];
        }
    }
}

// Constructor for vector of a given length
// Allocates memory, and initialises entries
// to zero
Matrix::Matrix(int numRows, int numCols) {
    assert(numRows > 0);
    assert(numCols > 0);
    mNumRows = numRows;
    mNumCols = numCols;
    int tot_length = mNumRows*mNumCols;
    mData = new double [tot_length];
    for (int index = 0; index<tot_length; index++) {
        mData[index] = 0.0;
    }
}

// Overwritten destructor to correctly free memory
Matrix::~Matrix() {
    delete[] mData;
}

// Method to get number of rows of matrix
int Matrix::Rows() const {
    return mNumRows;
}

// Method to get number of columns of matrix
int Matrix::Cols() const {
    return mNumCols;
}

// Overloading the round brackets
// Note that this uses `zero-based' indexing,
// and a check on the validity of the index
double& Matrix::operator()(int row, int col) {
    assert(row > -1);
    assert(row < mNumRows);
    assert(col > -1);
    assert(col < mNumCols);
    return mData[row*mNumCols+col];
}

// Overloading to allow for direct access of array
double& Matrix::operator()(int index) {
    assert(index> -1);
    assert(index < mNumRows*mNumCols);
    return mData[index];
}

double Matrix::at(int index) const{
    assert(index> -1);
    assert(index < mNumRows*mNumCols);
    return mData[index];
}

// Overloading the assignment operator
Matrix& Matrix::operator=(const Matrix& otherMatrix) {
    assert(mNumRows == otherMatrix.mNumRows);
    assert(mNumCols == otherMatrix.mNumCols);
    int tot_length = mNumCols*mNumRows;
    for (int index = 0; index<tot_length; index++) {
        mData[index] = otherMatrix.mData[index];
    }
    return *this;
}

// Overloading the unary + operator
Matrix Matrix::operator+() const {
    Matrix mat(mNumRows, mNumCols);
    for (int row=0; row<mNumRows; row++) {
        for (int col=0; col<mNumCols; col++) {
            mat(row,col) = mData[row*mNumCols+col];
        }
    }
    return mat;
}

// Overloading the unary - operator
Matrix Matrix::operator-() const {
    Matrix mat(mNumRows, mNumCols);
    for (int row=0; row<mNumRows; row++) {
        for (int col=0; col<mNumCols; col++) {
            mat(row,col) = -mData[row*mNumCols+col];
        }
    }
    return mat;
}

// Overloading the binary + operator
Matrix Matrix::operator+(const Matrix& m1) const {
    assert(mNumRows == m1.mNumRows);
    assert(mNumCols == m1.mNumCols);
    Matrix mat(mNumRows, mNumCols);
    for (int row=0; row<mNumRows; row++) {
        for (int col=0; col<mNumCols; col++) {
            mat(row,col) = mData[row*mNumCols+col] + m1.mData[row*mNumCols+col];
        }
    }
    return mat;
}

// Overloading the binary - operator
Matrix Matrix::operator-(const Matrix& m1) const {
    assert(mNumRows == m1.mNumRows);
    assert(mNumCols == m1.mNumCols);
    Matrix mat(mNumRows, mNumCols);
    for (int row=0; row<mNumRows; row++) {
        for (int col=0; col<mNumCols; col++) {
            mat(row,col) = mData[row*mNumCols+col] - m1.mData[row*mNumCols+col];
        }
    }
    return mat;
}

// Overloading scalar multiplication
Matrix Matrix::operator*(double a) const {
    Matrix mat(mNumRows, mNumCols);
    for (int row=0; row<mNumRows; row++) {
        for (int col=0; col<mNumCols; col++) {
            mat(row,col) = a*mData[row*mNumCols+col];
        }
    }
    return mat;
}

// Overloading matrix multiplied by a matrix
Matrix operator*(const Matrix& ml, const Matrix& mr) {
    assert(ml.mNumCols == mr.mNumRows);
    int new_rows = ml.mNumRows;
    int new_cols = mr.mNumCols;
    Matrix new_matrix(new_rows, new_cols);

    for (int rowl=0; rowl<new_rows; rowl++) {
        for (int colr=0; colr<new_cols; colr++) {
            double sum = 0;
            for (int mid=0; mid< ml.mNumCols; mid++) {
                sum += ml.mData[rowl*ml.mNumCols+mid]*mr.mData[mid*mr.mNumCols+colr];
            }
            new_matrix(rowl,colr) = sum;
        }
    }
    return new_matrix;
}


// Return a transpose of this matrix, creates a new matrix and
// not a transposed view
Matrix Matrix::transpose() const{
    Matrix transp_mat(mNumCols, mNumRows);
    for (int row=0; row<mNumRows; row++) {
        for (int col=0; col<mNumCols; col++) {
            transp_mat(col,row) = mData[row*mNumCols+col];
        }
    }
    return transp_mat;
}


