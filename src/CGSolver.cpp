#include "CGSolver.hpp"
#include "Exception.hpp"
#include <cmath>


Vector CGSolver::Solve(const Matrix &A, const Vector &b) {
    // Check Matrix-vector compatibility.
    try {
        this->CheckSolveInput(A, b);
    }
    catch (const Exception& error) {
        error.PrintDebug();
        throw Exception("InvalidInput", "Bad input into 'Solve' function.");
    }

    // Check if A is symmetric and thus suitable for CG.
    try {
        CheckSymmetry(A);
    }
    catch (const Exception &error) {

        error.PrintDebug();
        throw Exception("CGSolver", "Matrix of the linear system has to be symmetric.");
    }

    // Initialize data.
    Vector x(b.Size());
    Vector residual = b-A*x;

    Vector p(residual);

    for(int iter= 0; iter< this->GetMaxIter(); iter++){
        //Check convergence
        double norm_res = residual.CalculateNorm();
        if (norm_res < this->GetTol()) {
            return x;
        }
        // Find next iterative guess and calculate remaining residual.
        Vector prod = A*p;
        double alpha = dotProduct(residual, residual) /dotProduct(p, prod);
        x = x + p*alpha;
        Vector residual_next = residual - prod*alpha;
        // Update residual and search direction.
        double beta = pow(residual_next.CalculateNorm() / norm_res, 2);
        residual = residual_next;
        p =  residual + p*beta;
    }
    this->PrintConvergenceWarning(residual.CalculateNorm());
    return x;
}

Vector CGSolver::Solve(const Matrix &A, const Vector &b, const Matrix &precond) {
    // Check Matrix -Vector compatibility.
    try {
        CheckSolveInput(A, b);
    }
    catch (const Exception& error) {
        error.PrintDebug();
        throw Exception("InvalidInput", "Bad input into 'Solve' function.");
    }
    // Check if A is symmetric and thus suitable for CG.
    try {
        CheckSymmetry(A);
    }
    catch (const Exception &error) {
        error.PrintDebug();
        throw Exception("CGSolver", "Matrix of the linear system has to be symmetric.");
    }
    // Check if precondtioner is symmetric and thus suitable for CG.
    if(precond.Cols() != A.Cols() || precond.Rows() != A.Rows()){
        throw Exception("CGSolver", "Preconditioner does not fit matrix dimensions.");
    }
    try {
        CheckSymmetry(precond);
    }
    catch (const Exception &error) {
        error.PrintDebug();
        throw Exception("CGSolver", "Preconditioner has to be symmetric for the CG method, input did not fulfill "
                "requirements.");
    }

    // Initialize data.
    Vector x(b.Size());
    Vector residual = b-A*x;
    Vector p= precond* residual;

    for(int iter= 0; iter< this->GetMaxIter(); iter++){
        // Check for convergence.
        double norm_res = residual.CalculateNorm();
        if (norm_res < this->GetTol()) {
            return x;
        }
        // Find next iterative guess and calculate remaining residual.
        Vector prod = A*p;
        Vector res_prod = precond* residual;
        double alpha = dotProduct(residual, res_prod)/dotProduct(p, prod);
        x = x + p*alpha;
        Vector residual_next = residual - prod*alpha;
        Vector res_prod_next = precond*residual_next;
        // Update residual and search direction.
        double beta =  dotProduct(residual_next, res_prod_next)/ dotProduct(residual, res_prod);
        residual = residual_next;
        p =  res_prod_next + p*beta;
    }
    this->PrintConvergenceWarning(residual.CalculateNorm());
    return x;
}

CGSolver::CGSolver(double tol, int max_iter) : IterativeSolver(tol, max_iter) {}

Matrix CGSolver::CreateDiagPreconditioner(const Matrix &A) {
    if (A.Rows() != A.Cols()) {
        throw Exception("NonSquare", "Input matrix is not square and one cannot build a diagonal preconditioner from it"
                ".");
    }

    Matrix precond(A.Rows(), A.Cols());
    for (int index = 0; index < A.Cols(); index++) {
        if (std::abs(A.at(index, index)) < 1e-14) {
            throw Exception("ZeroOnDiag", "Input matrix has an entry close to zero on the diagonal and one cannot build"
                    " a diagonal preconditioner from it.");
        }
        precond(index, index) = 1.0 / A.at(index, index);
    }
    return precond;
}
