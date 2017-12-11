#ifndef PCSC2017_GROUP12_JACSOLVER_HPP
#define PCSC2017_GROUP12_JACSOLVER_HPP

#include "IterativeSolver.hpp"

/**
* The JacSolver class implements the methods for the Jacobi method.
*/
class JacSolver: public IterativeSolver
{
public:
    /// The standard constructor for a JacSolver
    explicit JacSolver(double tol= 1e-05, int max_iter= 10000 );

    /// Implementation of Solve(A,b) with the Jacobi method.
    Vector Solve(const Matrix& A, const Vector& b) override;
};

#endif //PCSC2017_GROUP12_JACSOLVER_HPP