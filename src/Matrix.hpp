#ifndef MATRIXHEADERDEF
#define MATRIXHEADERDEF

/**
* The matrix class provides a data structure for real matrices in row major format.
*/

class Matrix {
protected:
    /// Entries of matrix
    double *mData;
    /// Dimensions of matrix: Number of rows
    int mNumRows;
    /// Dimensions of matrix: Number of columns
    int mNumCols;

    /// This is an utility function to check whether access indices row, col are valid for this matrix.
    int CheckIndexValid(int row, int col) const;

    /// This is an utility function to check whether access index are valid for this matrix.
    int CheckIndexValid(int index) const;

    /// This is an utility function to check whether the dimensions of this matrix are equal to another matrix and
    /// it is thus possible to e.g.  add/substract these two matrices from another.
    int CheckDimensionsEqual(const Matrix &otherMatrix) const;

public:
    /** \brief This is a a copy constructor.
    * This constructor creates a new object of matrix and copies the shape and values of  the  otherMatrix.
    */
    Matrix(const Matrix &otherMatrix);

    /** \brief This is the standard constructor for creating a matrix.
     *  This constructor creates a new object of matrix with the specified number of rows and columns.
    */
    Matrix(int numRows, int numCols);

    /** \brief This is the standard destructor for a matrix.
    *  This destructor frees memory that has been assigned previously.
    */
    ~Matrix();

    /// This function returns the number of rows of the matrix
    int Rows() const;

    /// This function returns the number of columns of the matrix
    int Cols() const;

    /// This function provides write access at indices i and j with 0-based indexing.
    double &operator()(int i, int j);

    /// This function provides write access at index in row major format with 0-based indexing.
    double &operator()(int index);

    /// This function provides read-only access at index in row major format with 0-based indexing.
    double at(int index) const;

    /// This function provides read-only access at indices i and j with 0-based indexing.
    double at(int row, int col) const;

    /// This function overwrites the assignment operator and assigns the values of otherMatrix to this matrix.
    Matrix &operator=(const Matrix &otherMatrix);

    /// This function overwrites the unary + operator and returns the matrix.
    Matrix operator+() const;

    /// This function overwrites the unary - operator and returns the  negative matrix.
    Matrix operator-() const;

    /// This function overwrites the binary + operator and allows for addition of two matrices.
    Matrix operator+(const Matrix &m1) const;

    /// This function overwrites the binary - operator and allows for substraction of two matrices.
    Matrix operator-(const Matrix &m1) const;

    /// This function overwrites the binary * operator and allows for multiplication of each entry with a scalar.
    Matrix operator*(double a) const;

    /// This function returns the transpose of the matrix object it is applied to.
    virtual Matrix transpose() const;

    /// This is a friend function for  for matrix-matrix multiplication
    friend Matrix operator*(const Matrix &ml,
                            const Matrix &mr);

    /// This is a utility function that is used to  check if the dimensions of two matrices are compatible for
    /// multiplication.
    int CheckDimensionsCompatible(int leftCols, int rightRows) const;
};

#endif
