
#ifndef PCSC2017_GROUP12_LUSOLVER_H
#define PCSC2017_GROUP12_LUSOLVER_H

#include "DirectSolver.hpp"

/**
 * Thr LUSolver class derived from DirectSolver, providing direct method for the solution of linear system.
 */
class LUSolver: public DirectSolver{
public:
    /// Constructor;
    LUSolver();

    /// Virtual method Solve for implementing LU Decomposition of the linear system
    virtual Vector Solve(const Matrix& A, const Vector& b);
};
#endif //PCSC2017_GROUP12_LUSOLVER_H
