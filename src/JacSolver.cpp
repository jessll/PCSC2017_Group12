#include "JacSolver.hpp"
#include "Exception.hpp"
#include <cassert>
#include "cmath"


Vector JacSolver::Solve(const Matrix &A, const Vector &b) {

    try {
        this->CheckSolveInput(A, b);
    }
    catch (const Exception& error) {
        error.PrintDebug();
        throw Exception("InvalidInput", "Bad input into 'Solve' function.");
    }

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
            if(std::abs(A.at(row, row)) < 1e-14) {
                throw (Exception("JacSolver","Diagonal element of matrix close to zero. Danger of zero division. Check "
                        "if input matrix is actually diagonally dominant."));
            }
            x_next(row) = (b.at(row) - sigma) /A.at(row, row);
        }

        // Update guess
        x = x_next;

    }
    this->PrintConvergenceWarning((b-A*x).CalculateNorm());
    return x;
}

JacSolver::JacSolver(double tol, int max_iter) : IterativeSolver(tol, max_iter) {}
