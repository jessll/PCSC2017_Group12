#ifndef PCSC2017_GROUP12_GSSOLVER_HPP
#define PCSC2017_GROUP12_GSSOLVER_HPP
#include "IterativeSolver.hpp"

/**
* The GSSolver class implements the methods for the Gauss-Seidel method.
*/
class GSSolver : public IterativeSolver{
public:
    /// The standard constructor for the GSSolver
    explicit GSSolver(double tol= 1e-05, int max_iter= 10000 );

    /// Implementation of Solve(A,b) with the Gauss-Seidel method.
    Vector Solve(const Matrix& A, const Vector& b) override;
};

#endif //PCSC2017_GROUP12_GSSOLVER_HPP