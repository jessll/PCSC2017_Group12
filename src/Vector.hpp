#ifndef VECTORHEADERDEF
#define VECTORHEADERDEF


#include "Matrix.hpp"
class Vector: public Matrix
{
public:
    /** \brief This is a a copy constructor.
    * This constructor creates a new vector and copies the shape and values of  the  other vector.
    */
    Vector(const Vector &otherVector);

    /** \brief This is the standard constructor to create a vector.
    * This constructor creates a a column vector of specified size, i.e. the number of columns will be 1.
    */
    explicit Vector(int size);

    /** \brief This is an alternative  constructor to create a vector.
    * This constructor allows you to choose if  a column or row vector is created. If isColumn evaluates to true, the
     * constructor will create a column vector, if it evaluates to false it will create a row vector.
    */
    Vector(int size, bool is_column);

    /// This function returns the  size of the vector.
    int Size() const;

    /// This function overwrites the assignment operator and assigns the values of the other vector to this one.
    Vector& operator=(const Vector& otherVector);

    /// This function overwrites the * operator for a scalar. We overwrite it, so that a vector is returned in this
    /// case.
    Vector operator*(double factor) const;

    /// This function overwrites the binary + operator and performs addition of two vectors.
    Vector operator+(const Vector &v1) const;

    /// This function overwrites the binary + operator and performs addition of two vectors.
    Vector operator-(const Vector &v1) const;

    /// This function transforms a column vector in a row vector and vice versa.
    Vector  vec_transpose() const;

    /// This function calculates the p-norm of the vector.
    double CalculateNorm(int p=2) const;

    /// This function returns true if the vextor is a column vector and false if it is a row vector, i.e. it checks
    /// orientation.
    bool isColumn() const;

    /// This is a friend function that performs the matrix vector product explicitly to obtain vectors.
    /// Multiplication of a vector from the left.
    friend Vector operator*(const Vector& vl,
                            const Matrix& mr);

    /// This is a friend function that performs the matrix vector product explicitly to obtain vectors. Multiplication
    /// of a vector from the right.
    friend Vector operator*(const Matrix& ml,
                            const Vector& vr);

    /// This friend function calculates the inner product aka dot product of two vectors. It is not orientation
    /// sensitive, i.e. it doesn't matter if an input is a row or column vector.
    friend double dotProduct(const Vector& vl, const Vector& vr);

    ///This friend returns the length of a vector.
    friend int length(const Vector& v);

    /// This convenient function allows for "casting" of a 1D matrix into vector form, so that we can exploit
    /// functions such as the dot and vector product.
    friend Vector asVector(const Matrix& matrix);
};

Vector asVector(const Matrix& matrix);
#endif

