#ifndef PCSC2017_GROUP12_LINSYSSOLVER_H
#define PCSC2017_GROUP12_LINSYSSOLVER_H

#include "Matrix.hpp"
#include "Vector.hpp"

#include <cmath>
#include <string>

/*! An abstract  class to define the interface for the linear system solver. */
class LinSysSolver
{
protected:
    /// Internal utility function to check if input is a valid linear system Ax=b.
    int CheckSolveInput(const Matrix& A, const Vector& b);

    /// Internal utility function to check if input matrix A is symmetric.
    int CheckSymmetry(const Matrix &A);
public:
    /// Solver method for linear system Ax=b. Will return solution vector x.
    virtual Vector Solve(const Matrix& A, const Vector& b) = 0;

    /// Utility function to read matrix data from a txt style file, specified in path.
    Matrix ReadMatrixFromFile(std::string path_to_file);

    /// Utility function to write matrix data to a txt style file, specified in path.
    int WriteMatrixToFile(std::string full_file_name,Matrix& mat);

    /// Utility function to read matrix from keyboard
    Matrix ReadMatrixFromKeyboard();
   
};

#endif //PCSC2017_GROUP12_LINSYSSOLVER_H
