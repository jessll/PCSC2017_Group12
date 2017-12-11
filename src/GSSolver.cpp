//
// Created by mariella on 04.12.17.
//

#include "GSSolver.hpp"
#include "Exception.hpp"
#include "cmath"

Vector GSSolver::Solve(const Matrix &A, const Vector &b) {
    try {
        this->CheckSolveInput(A, b);
    }
    catch (const Exception& error) {
        error.PrintDebug();
        throw Exception("InvalidInput", "Bad input into 'Solve' function.");
    }

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

            if(std::abs(A.at(row, row)) < 1e-14) {
                throw (Exception("GSSolver","Diagonal element of matrix close to zero. Danger of zero division. Check "
                        "if input matrix is actually diagonally dominant or spd."));
            }
            x(row) = (b.at(row) - sigma) /A.at(row, row);
        }
    }

    this->PrintConvergenceWarning((b-A*x).CalculateNorm());
    return x;
}

GSSolver::GSSolver(double tol, int max_iter) : IterativeSolver(tol, max_iter) {}
