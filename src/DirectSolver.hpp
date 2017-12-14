
#ifndef PCSC2017_GROUP12_DIRECTSOLVER_H
#define PCSC2017_GROUP12_DIRECTSOLVER_H

#include "Matrix.hpp"
#include "Vector.hpp"
#include <string>
#include "LinSysSolver.hpp"

/**
 * The DirectSolver class is a abstract base class for direct solvers
 */
class DirectSolver : public LinSysSolver {

public:
    /// constructor
    DirectSolver();

    /// Solver method is a pure virtual method for implementing direct methods for linear system
    virtual Vector Solve(const Matrix& A, const Vector& b)=0;
};

#endif //PCSC2017_GROUP12_DIRECTSOLVER_H
