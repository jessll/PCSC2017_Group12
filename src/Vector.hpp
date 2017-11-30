#ifndef VECTORHEADERDEF
#define VECTORHEADERDEF

class Vector
{
private:
   double* mData; // data stored in vector
   int mSize; // size of vector
public:
   Vector(const Vector& otherVector);
   Vector(int size);
   //Vector(std::string directory, std::string file_name);
   ~Vector();
   int GetSize() const;
   double& operator()(int i); // zero-based indexing
   // read-only zero-based indexing 
   double Read(int i) const;
   // assignment
   Vector& operator=(const Vector& otherVector);
   Vector operator+() const; // unary +
   Vector operator-() const; // unary -
   Vector operator+(const Vector& v1) const; // binary +
   Vector operator-(const Vector& v1) const; // binary -
   // scalar multiplication
   Vector operator*(double a) const;
   // inner product with another vector
   double operator*(const Vector& v1) const;
    // p-norm method
   double CalculateNorm(int p=2) const;
   int WriteVecToFile(std::string directory, std::string file_name);

   // declare length function as a friend
   friend int length(const Vector& v);
};

// Prototype signature of length() friend function
int length(const Vector& v);

#endif
//Code from Chapter10.tex line 19 save as Vector.hpp
