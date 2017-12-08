

#include "CGSolver.hpp"
#include "Exception.hpp"
#include <cassert>
#include <cmath>


Vector CGSolver::Solve(const Matrix &A, const Vector &b) {
    try {
        this->CheckSolveInput(A, b);
    }
    catch (const Exception& error) {
        error.PrintDebug();
        throw Exception("InvalidInput", "Bad input into 'Solve' function.");
    }

    // Initialize data.
    Vector x(b.Size());
    Vector residual = b-A*x;
    Vector p(residual);

    for(int iter= 0; iter< this->GetMaxIter(); iter++){

        // Find next iteration and calculate remaining residual.
        Vector prod = A*p;
        double alpha = dotProduct(residual, residual) /dotProduct(p, prod);
        x = x + p*alpha;
        Vector residual_next = residual - prod*alpha;


        // Decide if we have converged
        double norm_res = residual_next.CalculateNorm();
        if(norm_res < this->GetTol()) {
            return x;
        }
        // Update residual ans search direction.
        double beta =  pow(norm_res/ residual.CalculateNorm(), 2);
        residual = residual_next;
        p =  residual + p*beta;
    }

    this->PrintConvergenceWarning(residual.CalculateNorm());
    return x;
}

Vector CGSolver::Solve(const Matrix &A, const Vector &b, const Matrix &precond) {
    try {
        this->CheckSolveInput(A, b);
    }
    catch (const Exception& error) {
        error.PrintDebug();
        throw(error);
    }

    if(precond.Cols() != A.Cols() || precond.Rows() != A.Rows()){
        throw Exception("CGSolver", "Preconditioner does not fit matrix dimensions.");
    }

    // Initialize data.
    Vector x(b.Size());
    Vector residual = b-A*x;
    Vector p= precond* residual;
    for(int iter= 0; iter< this->GetMaxIter(); iter++){

        // Find next iteration and calculate remaining residual.
        Vector prod = A*p;
        Vector res_prod = precond* residual;
        double alpha = dotProduct(residual, res_prod)/dotProduct(p, prod);
        x = x + p*alpha;
        Vector residual_next = residual - prod*alpha;
        Vector res_prod_next = precond*residual_next;

        // Decide if we have converged
        double norm_res = residual_next.CalculateNorm();
        if(norm_res < this->GetTol()) {
            break;
        }
        // Update residual ans search direction.
        double beta =  dotProduct(residual_next, res_prod_next)/ dotProduct(residual, res_prod);
        residual = residual_next;
        p =  res_prod_next + p*beta;
    }

    return x;
}

CGSolver::CGSolver(double tol, int max_iter) : IterativeSolver(tol, max_iter) {}
