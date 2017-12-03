

#ifndef PCSC2017_GROUP12_LINSYSSOLVER_H
#define PCSC2017_GROUP12_LINSYSSOLVER_H

#include "Matrix.hpp"
#include "Vector.hpp"
#include <string>

class LinSysSolver
{
public:
    // Solver method
    virtual Vector Solve(const Matrix& A, const Vector& b) = 0;
    // Read matrix from file
    Matrix ReadMatrixFromFile(std::string path_to_file);
    // Write matrix to file
    int WriteMatrixToFile(std::string path_to_file,Matrix& mat);
};


#endif //PCSC2017_GROUP12_LINSYSSOLVER_H
