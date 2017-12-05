#include "JacSolver.hpp"
#include <cassert>


Vector JacSolver::Solve(const Matrix &A, const Vector &b) {
    // rework this
    assert(A.Cols() == A.Rows());
    assert(b.Rows() == A.Cols());
    // Generate starting guess to zero, enable starting guess in another function?

    // Initialize data.
    Vector x(b.Size());
    // Elementwise notation, to save space
    for(int iter= 0; iter< this->GetMaxIter(); iter++){
        // Check for convergence
        double res_norm = (b-A*x).CalculateNorm();
        if(res_norm< this->GetTol()){
            return x;
        }
        // calculate next guess
        Vector x_next(b.Size());
        for (int row = 0; row <A.Rows(); row ++) {
            double sigma = 0;
            for(int col= 0; col <A.Cols(); col++) {
                sigma +=  A.at(row,col) *x(col);
            }
            sigma = sigma - x(row)*A.at(row,row); //This avoids if statement in code above
            x_next(row) = (b.at(row) - sigma) /A.at(row, row);
        }

        // Update guess
        x = x_next;

    }
    this->PrintConvergenceWarning((b-A*x).CalculateNorm());
    return x;
}

JacSolver::JacSolver(double tol, int max_iter) : IterativeSolver(tol, max_iter) {}
