#include <cmath>
#include <iostream>
#include <fstream>
#include <cassert>
#include "Vector.hpp"

// Overridden copy constructor
// Allocates memory for new vector, and copies
// entries of other vector into it using the base class
Vector::Vector( const Vector &otherVector) : Matrix(otherVector) {}

// Constructor for vector of a given size
// Allocates memory, and initialises entries
// to zero. We create column vectors by default;
Vector::Vector(int size) : Matrix(size, 1) {}

//Constructor for explicit row vector
Vector::Vector(int size, bool isColumn) : Matrix(1,size) {
    if(!isColumn){
        mNumCols=1;
        mNumRows= size;
    }
}


// Method to get the size of a vector
int Vector::Size() const {
    return mNumRows*mNumCols; // We exploit the invariant that one of the two dimensions is always zero
}

// Overloading the assignment operator
Vector& Vector::operator=(const Vector& otherVector)
{    assert(mNumRows == otherVector.mNumRows);
    assert(mNumCols == otherVector.mNumCols);
    for (int index=0; index<mNumRows*mNumCols; index++)
    {
        mData[index] = otherVector.mData[index];
    }
    return *this;
}


// Overloading the binary + operator
Vector Vector::operator+(const Vector& otherVector) const {
    assert(mNumRows == otherVector.mNumRows);
    assert(mNumCols == otherVector.mNumCols);
    int new_length= mNumCols*mNumRows;
    Vector v(new_length);
    for (int index=0; index<new_length; index++) {
        v(index) = mData[index] + otherVector.mData[index];
    }
    return v;
}

// Overloading the binary - operator
Vector Vector::operator-(const Vector& otherVector) const {
    assert(mNumRows == otherVector.mNumRows);
    assert(mNumCols == otherVector.mNumCols);
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
{
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
// Is this more efficient? Does it return a vector?
Matrix Vector::transpose() const {
    Vector transp_vec(*this);
    transp_vec.mNumRows = mNumCols;
    transp_vec.mNumCols = mNumRows;
    return transp_vec;
}

Vector operator*(const Vector &vl, const Matrix &mr) {
    assert(vl.Cols() ==mr.Rows());
    Vector res_v(vl.mNumCols, false);
    for (int v_index=0; v_index < vl.mNumCols; v_index++) {
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
    assert(ml.Cols() ==vr.Rows());
    Vector res_v(vr.mNumRows);
    for (int v_index=0; v_index < vr.mNumRows; v_index++) {
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
    return mNumCols <= 1;
}



