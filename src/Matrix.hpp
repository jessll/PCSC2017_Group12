#ifndef MATRIXHEADERDEF
#define MATRIXHEADERDEF

class Matrix
{
protected:
    double* mData; // entries of matrix
    int mNumRows, mNumCols; // dimensions

    int CheckIndexValid(int row, int col) const;
    int CheckIndexValid(int index) const;
    int CheckDimensionsEqual(const Matrix &otherMatrix) const;

public:
    Matrix(const Matrix& otherMatrix);
    Matrix(int numRows, int numCols);
    ~Matrix();
    int Rows() const;
    int Cols() const;
    double& operator()(int i, int j); //0-based indexing
    double& operator()(int index); // 0-based indexing in row-major format
    double at(int index) const; // read only access
    double at(int row, int col) const; // read only access
    Matrix& operator=(const Matrix& otherMatrix);
    Matrix operator+() const; // unary +
    Matrix operator-() const; // unary -
    Matrix operator+(const Matrix& m1) const; // binary +
    Matrix operator-(const Matrix& m1) const; // binary -
    // scalar multiplication
    Matrix operator*(double a) const;
    virtual Matrix  transpose() const;
    // Friend for matrix matrix multiplication;
    friend Matrix operator*(const Matrix& ml,
                            const Matrix& mr);


    int CheckDimensionsCompatible(int leftCols, int rightRows)const;
};

#endif
