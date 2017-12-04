
#include "RichSolver.hpp"
#include <cassert>

RichSolver::RichSolver() : IterativeSolver(){
    mW = 0.5;
}

RichSolver::RichSolver(double w) : IterativeSolver() {
    assert(w>0);
    mW =w;
}

RichSolver::RichSolver(double w, double tol, int max_iter) : IterativeSolver(tol, max_iter) {
    assert(w>0);
    mW =w;
}

Vector RichSolver::Solve(const Matrix &A, const Vector &b) {

    assert(b.Cols() == A.Rows());
    // Generate starting guess to zero, enable starting guess in another function?

    // Initialize data.
    Vector x(b.Size());
    for(int iter= 0; iter< this->getMaxIter(); iter++){
        Vector residual = b-A*x;
        double res_norm = residual.CalculateNorm();
        if(res_norm< this->getTol()){
            break;
        }
       x = x + residual*mW;
    }
    return x;
}
