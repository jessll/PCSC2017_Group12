#ifndef PCSC2017_GROUP12_CGSOLVER_H
#define PCSC2017_GROUP12_CGSOLVER_H

#include "IterativeSolver.hpp"

/**
* The CGSolver class implements the methods for the conjugate gradient method.
*/
class CGSolver: public IterativeSolver
{

public:
    /// The standard constructor fo a CG solver
    explicit CGSolver(double tol= 1e-05, int max_iter= 1000 );

    /// Implementation of Solve(A,b) with the conjugate gradient method.
    Vector Solve(const Matrix& A, const Vector& b) override;

    /// Implementation of preconditioned CG, uses inv(M) as precond, where M is a good preconditioner for the system
    /// Ax=b.
    Vector Solve(const Matrix& A, const Vector& b, const Matrix& precond);

    /// This function creates a simple diagonal preconditoner for the input matrix A, provided that A has no zero
    /// entries on its diagonal.
    Matrix CreateDiagPreconditioner(const Matrix &A);
};
#endif //PCSC2017_GROUP12_CGSOLVER_H