
#include <iostream>
#include <sstream>
#include "IterativeSolver.hpp"
#include "Exception.hpp"

int IterativeSolver::SetMaxIter(int max_iter) {
    if( max_iter <=0){
        throw Exception("BadParameter", "The maximum number of iterations of the solver has to be larger than 0.");
    }
    mMaxIter = max_iter;
    return 0;
}

int IterativeSolver::GetMaxIter() {
    return mMaxIter;
}

int IterativeSolver::SetTol(double new_tol) {
    if( new_tol <=0){
        throw Exception("BadParameter", "Error tolerance of a solver has to be non-zero and positive.");
    }
    mTol = new_tol;
    return 0;
}

double IterativeSolver::GetTol() {
    return mTol;
}

IterativeSolver::IterativeSolver(double tol, int max_iter) {
    try{
        this->SetTol(tol);
        this->SetMaxIter(max_iter);
    }
    catch (const Exception& error) {
        error.PrintDebug();
        throw Exception ("InitError", "Could not initialize solver. Probably due to a bad parameter.");
    }
}

int IterativeSolver::PrintConvergenceWarning(double res_norm) {
    std::ostringstream warning_msg;
    warning_msg << "Warning: Solver has not reached desired error tolerance of " << mTol <<", "
            "current error of residual is " << res_norm  <<". \n";
    std::cout << warning_msg.str();
    return 0;
}
