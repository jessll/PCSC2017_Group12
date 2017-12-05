

#include "CGSolver.hpp"
#include <cassert>
#include <iostream>
#include <cmath>


Vector CGSolver::Solve(const Matrix &A, const Vector &b) {
    assert(A.Cols() == A.Rows());
    assert(b.Rows() == A.Cols());
    // Generate starting guess to zero, enable starting guess in another function?

    // Initialize data.
    Vector x(b.Size());
    Vector residual = b-A*x;
    Vector p(residual);
    for(int iter= 0; iter< this->getMaxIter(); iter++){

        // Find next iteration and calculate remaining residual.
        Vector prod = A*p;
        double alpha = dotProduct(residual, residual) /dotProduct(p, prod);
        x = x + p*alpha;
        Vector residual_next = residual - prod*alpha;


        // Decide if we have converged
        double norm_res = residual_next.CalculateNorm();
        if(norm_res < this->getTol()) {
            return x;
        }
        // Update residual ans search direction.
        double beta =  pow(norm_res/ residual.CalculateNorm(), 2);
        residual = residual_next;
        p =  residual + p*beta;
    }

    std::cout<< "Warning solver has not converged.\n";
    return x;
}

Vector CGSolver::Solve(const Matrix &A, const Vector &b, const Matrix &precond) {
    assert(A.Cols() == A.Rows());
    assert(b.Rows() == A.Cols());
    // Generate starting guess to zero, enable starting guess in another function?

    // Initialize data.
    Vector x(b.Size());
    Vector residual = b-A*x;
    Vector p= precond* residual;
    for(int iter= 0; iter< this->getMaxIter(); iter++){

        // Find next iteration and calculate remaining residual.
        Vector prod = A*p;
        Vector res_prod = precond* residual;
        double alpha = dotProduct(residual, res_prod)/dotProduct(p, prod);
        x = x + p*alpha;
        Vector residual_next = residual - prod*alpha;
        Vector res_prod_next = precond*residual_next;

        // Decide if we have converged
        double norm_res = residual_next.CalculateNorm();
        if(norm_res < this->getTol()) {
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
