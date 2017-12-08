
#include "RichSolver.hpp"
#include "Exception.hpp"
#include <cassert>
#include <iostream>

RichSolver::RichSolver() : IterativeSolver(){
    mW = 0.5;
}

RichSolver::RichSolver(double w) : IterativeSolver() {
    try {
        this->SetParameterW(w);
    }
    catch (const Exception& error) {
        error.PrintDebug();
        throw Exception ("InitError", "Could not initialize solver. Probably due to a bad parameter.");
    }

}

RichSolver::RichSolver(double w, double tol, int max_iter) : IterativeSolver(tol, max_iter) {
    try {
        this->SetParameterW(w);
    }
    catch (const Exception& error) {
        error.PrintDebug();
        throw Exception ("InitError", "Could not initialize solver. Probably due to a bad parameter.");
    }
}

Vector RichSolver::Solve(const Matrix &A, const Vector &b) {

    try {
        this->CheckSolveInput(A, b);
    }
    catch (const Exception& error) {
        error.PrintDebug();
        throw Exception("InvalidInput", "Bad input into 'Solve' function.");
    }

    // Initialize data.
    Vector x(b.Size());
    for(int iter= 0; iter< this->GetMaxIter(); iter++){
        Vector residual = b-A*x;
        double res_norm = residual.CalculateNorm();
        if(res_norm< this->GetTol()){
            return x;
        }
       x = x + residual*mW;
    }
    this->PrintConvergenceWarning((b-A*x).CalculateNorm());
    std::cout << "Check your parameter w, it might not be in a good range.\n";
    return x;
}

double RichSolver::GetParameterW() {
    return mW;
}

int RichSolver::SetParameterW(double w) {
    if(w <= 0){
        throw Exception("BadParameter", "W has to be larger than 0");
    }
    mW =w;
    return 0;
}

