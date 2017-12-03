

#include "CGSolver.hpp"
#include <cassert>


Vector CGSolver::Solve(const Matrix &A, const Vector &b) {
    assert(A.Cols() == A.Rows());
    assert(b.Cols() == A.Rows());
    // Generate starting guess to zero, enable starting guess in another function?
    Vector x(b.Size());
    Vector residual = b-A*x;
    Vector p(residual);
    for(int iter=0; iter< this->getMaxIter(); iter++){
        Vector prod = A*p;
        double alpha = residual.CalculateNorm() /dotProduct(p, prod);
        x =x + p*alpha;
        Vector residual_next = residual - prod*alpha;
        double beta = residual_next.CalculateNorm() / residual.CalculateNorm();
        residual = residual_next;
        p =  residual + p*beta;
    }
    return x;
}
