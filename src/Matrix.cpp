#include <cmath>
#include <cassert>
#include "Matrix.hpp"
#include "Exception.hpp"

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
    if (numRows <1  || numCols <1){
        throw Exception("InitError", "The number of rows and columns in a matrix have to be larger than 0.");
    }
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
    try {
        CheckIndexValid(row, col);
    }
    catch (const Exception& error){
        error.PrintDebug();
        Exception("BadInput", "Cannot access matrix at this index.");
    }
    return mData[row*mNumCols+col];
}

// Overloading to allow for direct access of array
double& Matrix::operator()(int index) {
    try {
        CheckIndexValid(index);
    }
    catch (const Exception& error){
        error.PrintDebug();
        Exception("BadInput", "Cannot access matrix at this index.");
    }
    return mData[index];
}

double Matrix::at(int index) const{
    try {
        CheckIndexValid(index);
    }
    catch (const Exception& error){
        error.PrintDebug();
        Exception("BadInput", "Cannot access matrix at this index.");
    }
    return mData[index];
}

// Overloading the assignment operator
Matrix& Matrix::operator=(const Matrix& otherMatrix) {
    try {
        CheckDimensionsEqual(otherMatrix);
    }
    catch (const Exception& error) {
        error.PrintDebug();
        throw(Exception("DimensionMismatch", "Cannot assign matrix of different dimensions to already existing matrix"
                ". Consider the copy constructor instead."));
    }
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
    try {
        CheckDimensionsEqual(m1);
    }
    catch (const Exception& error) {
        error.PrintDebug();
        throw(Exception("DimensionMismatch", "Cannot add matrices of different dimensions."));
    }
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
    try {
        CheckDimensionsEqual(m1);
    }
    catch (const Exception& error) {
        error.PrintDebug();
        throw(Exception("DimensionMismatch", "Cannot substract matrices of different dimensions."));
    }
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
    try {
        ml.CheckDimensionsCompatible(ml.mNumCols, mr.mNumRows);
    }
    catch (const Exception& error) {
        error.PrintDebug();
        throw(Exception("DimensionMismatch", "Cannot multiply matrices when the number of columns of the left matrix "
                "does not equal the number of rows in the right matrix."));
    }
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

double Matrix::at(int row, int col) const {
    try{
        CheckIndexValid(row, col);
    }
    catch (const Exception& error){
        error.PrintDebug();
        throw Exception("BadInput", "Cannot access matrix at this index.");
    }

    return mData[row*mNumCols+col];
}


int Matrix::CheckIndexValid(int row, int col) const{
    if( row <0 || col < 0 || row >=mNumRows || col >=mNumRows) {
        throw Exception("BadIndex", "Index exceeds dimensions.");
    }
    return 0;
}

int Matrix::CheckIndexValid(int index) const{
    if(index <0 || index >=mNumRows*mNumCols){
        throw Exception("BadIndex", "Index exceeds dimensions.");
    }
    return 0;
}

int Matrix::CheckDimensionsCompatible(int leftCols, int rightRows) const {
    if(leftCols != rightRows) {
        throw Exception("DimensionMismatch", "Dimensions of the two inputs are not compatible for this operation.");
    }
    return 0;
}

int Matrix::CheckDimensionsEqual(const Matrix &otherMatrix) const{
    if(mNumRows != otherMatrix.mNumRows || mNumCols != otherMatrix.mNumCols) {
        throw Exception("DimensionMismatch", "Dimensions of the two inputs are not equal.");
    }
    return 0;
}


