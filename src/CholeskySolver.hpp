
#ifndef PCSC2017_GROUP12_CHOLESKY_H
#define PCSC2017_GROUP12_CHOLESKY_H

#include "DirectSolver.hpp"

/**
 * The CholeskySolver class derived from class DirectSolver, providing the Cholesky decomposition method for linear
 * system.
 */
class CholeskySolver:public DirectSolver{

public:
    /// Constructor;
    CholeskySolver();

    /// Virtual method Solve for implementing Cholesky Decomposition for linear system.
    virtual Vector Solve(const Matrix& A, const Vector& b);
};

#endif //PCSC2017_GROUP12_CHOLESKY_H
