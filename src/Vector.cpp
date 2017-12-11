#include <cmath>
#include <cassert>
#include "Vector.hpp"
#include "Exception.hpp"

// Overridden copy constructor
// Allocates memory for new vector, and copies
// entries of other vector into it using the base class
Vector::Vector( const Vector &otherVector) : Matrix(otherVector) {}

// Constructor for vector of a given size
// Allocates memory, and initialises entries
// to zero. We create column vectors by default;
Vector::Vector(int size) : Matrix(size, 1) {}

//Constructor for explicit row vector
Vector::Vector(int size, bool is_column) : Matrix(size, 1) {
    if (!is_column) {
        mNumCols=size;
        mNumRows= 1;
    }
}


// Method to get the size of a vector
int Vector::Size() const {
    return mNumRows*mNumCols; // We exploit the invariant that one of the two dimensions is always zero
}

// Overloading the assignment operator
Vector& Vector::operator=(const Vector& otherVector)
{     try {
        CheckDimensionsEqual(otherVector);
    }
    catch (const Exception& error) {
        error.PrintDebug();
        throw(Exception("DimensionMismatch", "Cannot assign a vector of different dimensions to a vector that has "
                "already been declared. Consider using the copy constructor instead."));
    }
    for (int index=0; index<mNumRows*mNumCols; index++)
    {
        mData[index] = otherVector.mData[index];
    }
    return *this;
}


// Overloading the binary + operator
Vector Vector::operator+(const Vector& otherVector) const {
    try {
        CheckDimensionsEqual(otherVector);
    }
    catch (const Exception& error) {
        error.PrintDebug();
        throw(Exception("DimensionMismatch", "Cannot add two vectors of different dimension. Check for row/column "
                "vector or transpose, if you are sure the vectors have the same size."));
    }
    int new_length= mNumCols*mNumRows;
    Vector v(new_length);
    for (int index=0; index<new_length; index++) {
        v(index) = mData[index] + otherVector.mData[index];
    }
    return v;
}

// Overloading the binary - operator
Vector Vector::operator-(const Vector& otherVector) const {
    try {
        CheckDimensionsEqual(otherVector);
    }
    catch (const Exception& error) {
        error.PrintDebug();
        throw(Exception("DimensionMismatch", "Cannot substract two vectors of different dimension. Check for "
                "row/column vector or transpose, if you are sure the vectors have the same size."));
    }
    int new_length= mNumCols*mNumRows;
    Vector v(new_length);
    for (int index=0; index<new_length; index++) {
        v(index) = mData[index] - otherVector.mData[index];
    }
    return v;
}


// Method to calculate norm (with default value p=2)
// corresponding to the Euclidean norm
double Vector::CalculateNorm(int p) const
{   if (p<=0) {
        throw Exception("BadParameter", "Cannot calculate norm of negative or zero p.");
    }
    double norm_val, sum = 0.0;
    for (int index=0; index<mNumCols*mNumRows; index++)
    {
        sum += pow(fabs(mData[index]), p);
    }
    norm_val = pow(sum, 1.0/((double)(p)));
    return norm_val;
}

// MATLAB style friend to get the size of a vector
int length(const Vector& v)
{
    return v.Size();
}
// Is this more efficient? maybe do a friend function instead?
Vector Vector::vec_transpose() const {
    Vector transp_vec(*this);
    transp_vec.mNumRows = mNumCols;
    transp_vec.mNumCols = mNumRows;
    return transp_vec;
}

Vector operator*(const Vector &vl, const Matrix &mr) {
    try{
        vl.CheckDimensionsCompatible(vl.Cols(), mr.Rows());
    }
    catch( const Exception& error) {
        error.PrintDebug();
        throw Exception("DimensionMismatch", "Cannot multiply vector with matrix, because dimensions don't correspond"
                ". Check if you use a row vector or multiply in correct order.");
    }
    Vector res_v(mr.Cols(), false);
    for (int v_index=0; v_index < mr.Cols(); v_index++) {
        double sum = 0;
        for (int m_index =0; m_index<mr.Rows(); m_index++) {
            int ind= m_index* mr.Cols() +v_index;
            sum += vl.mData[m_index]* mr.at(ind);
        }
        res_v(v_index) = sum;
    }
    return res_v;
}

Vector operator*(const Matrix &ml, const Vector &vr) {
    try{
        ml.CheckDimensionsCompatible(ml.Cols(), vr.Rows());
    }
    catch( const Exception& error) {
        error.PrintDebug();
        throw Exception("DimensionMismatch", "Cannot multiply vector with matrix, because dimensions don't correspond"
                ". Check if you use a column vector or multiply in correct order.");
    }
    Vector res_v(ml.Rows());
    for (int v_index=0; v_index < ml.Rows(); v_index++) {
        double sum = 0;
        for (int m_index =0; m_index<ml.Cols(); m_index++) {
            int ind= v_index* ml.Cols() +m_index;
            sum += ml.at(ind)*vr.mData[m_index];
        }
        res_v(v_index) = sum;
    }
    return res_v;
}

bool Vector::isColumn() const {
    return mNumRows > 1;
}

Vector asVector(const Matrix &matrix){
    int rows = matrix.Rows();
    int cols = matrix.Cols();
    if (rows == 1) {
        Vector as_vec(cols, false);
        for (int index = 0; index< cols; index++) {
            as_vec(index) = matrix.at(index);
        }
        return as_vec;
    }

    if(cols ==1){
        Vector as_vec(rows, true);
        for (int index=0; index<rows; index++) {
            as_vec(index) = matrix.at(index);
        }
        return as_vec;
    }
    // If we reach this part of the function. The matrix cannot be cast into a Vector.
    throw Exception("BadInput", "This matrix does not have the dimensions of a Vector and thus cannot be used as a "
            "Vector.");
}

//dot product implementation that doesn't care about dimensions
// Consider also doing one, that is explicit for dimensions

double dotProduct(const Vector &vl, const Vector &vr) {
    try{
        vl.CheckDimensionsCompatible(vl.Size(), vr.Size());
    }
    catch( const Exception& error) {
        error.PrintDebug();
        throw Exception("DimensionMismatch", "Cannot calculate the dot product of two vectors with different size.");
    }
    assert(vl.Size()== vr.Size());
    double dot_product = 0;
    for ( int index = 0; index <vl.Size(); index++){
        dot_product +=vl.at(index)*vr.at(index);
    }
    return dot_product;
}

Vector Vector::operator*(double factor) const {
    Vector new_vec(this->Size());
    for (int index=0; index < this->Size(); index++) {
        new_vec(index) = mData[index]*factor;
    }
    return new_vec;
}




