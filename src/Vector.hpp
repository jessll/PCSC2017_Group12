#ifndef VECTORHEADERDEF
#define VECTORHEADERDEF

#include<string>
#include "Matrix.hpp"
class Vector: public Matrix
{
public:
    Vector(const Vector &otherVector);
    explicit Vector(int size);
    Vector(int size, bool isColumn);

    // Return size of the vector
    int Size() const;
    // assignment
    Vector& operator=(const Vector& otherVector);
    Vector operator+(const Vector& v1) const; // binary +
    Vector operator-(const Vector& v1) const; // binary -
    Matrix transpose() const override;

    // p-norm method
    double CalculateNorm(int p=2) const;
    bool isColumn() const;
    // Write matrix vector product explicitely to obtain vectors
    friend Vector operator*(const Vector& vl,
                            const Matrix& mr);

    friend Vector operator*(const Matrix& ml,
                            const Vector& vr);
    // declare length function as a friend
    friend int length(const Vector& v);
};

#endif

