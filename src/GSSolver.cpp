//
// Created by mariella on 04.12.17.
//

#include "GSSolver.hpp"
#include <cassert>

Vector GSSolver::Solve(const Matrix &A, const Vector &b) {
    // rework this
    assert(A.Cols() == A.Rows());
    assert(b.Rows() == A.Cols());
    // Generate starting guess to zero, enable starting guess in another function?

    // Initialize data.
    Vector x(b.Size());
    //elementwise notation, to save space

    for(int iter= 0; iter< this->GetMaxIter(); iter++){
        //Check for convergence
        double norm_res = (b-A*x).CalculateNorm();
        if(norm_res < this->GetTol()) {
            return x; }

        for (int row = 0; row <A.Rows(); row ++) {
            double sigma = 0;
            for(int col= 0; col <A.Cols(); col++) {
                sigma +=  A.at(row,col) *x(col);
            }
            sigma = sigma - A.at(row,row)*x(row); //This avoids if statement in code above
            x(row) = (b.at(row) - sigma) /A.at(row, row);
        }
    }

    this->PrintConvergenceWarning((b-A*x).CalculateNorm());
    return x;
}

GSSolver::GSSolver(double tol, int max_iter) : IterativeSolver(tol, max_iter) {}
