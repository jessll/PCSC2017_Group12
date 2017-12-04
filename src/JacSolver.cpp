#include "JacSolver.hpp"
#include <cassert>


Vector JacSolver::Solve(const Matrix &A, const Vector &b) {
    // rework this
    assert(A.Cols() == A.Rows());
    assert(b.Cols() == A.Rows());
    // Generate starting guess to zero, enable starting guess in another function?

    // Initialize data.
    Vector x(b.Size());
    //elementwise notation, to save space
    for(int iter= 0; iter< this->getMaxIter(); iter++){
        double norm_res = (A*x-b).CalculateNorm();
        if(norm_res < this->getTol()) {
            break;
        }
        Vector x_next(b.Size());
        for (int row = 0; row <A.Rows(); row ++) {
            double sigma = 0;
            for(int col= 0; col <A.Cols(); col++) {
                sigma += sigma + A.at(row,col) *x(col);
            }
            sigma = sigma - x(row)*A.at(row,row); //This avoids if statement in code above
            x_next(row) = (b.at(row) - sigma) * 1.0/A.at(row, row);
        }
        x = x_next;

    }
    return x;
}