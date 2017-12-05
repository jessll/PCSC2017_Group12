
#include <iostream>
#include <sstream>
#include "IterativeSolver.hpp"

int IterativeSolver::SetMaxIter(int max_iter) {
    // check that max_iter is larger than 0, else throw exception
    mMaxIter = max_iter;
    return 0;
}

int IterativeSolver::GetMaxIter() {
    return mMaxIter;
}

int IterativeSolver::SetTol(double new_tol) {
    //check that new tol is positive and non-zero, else throw exception
    mTol = new_tol;
    return 0;
}

double IterativeSolver::GetTol() {
    return mTol;
}

IterativeSolver::IterativeSolver(double tol, int max_iter) {
    mTol = tol;
    mMaxIter = max_iter;
}

int IterativeSolver::PrintConvergenceWarning(double res_norm) {
    std::ostringstream warning_msg;
    warning_msg << "Warning: Solver has not reached desired error tolerance of " << mTol <<", "
            "current error of residual is " << res_norm  <<". \n";
    std::cout << warning_msg.str();
}
