
#include "IterativeSolver.hpp"

int IterativeSolver::setMaxIter(int max_iter) {
    // check that max_iter is larger than 0, else throw exception
    mMaxIter = max_iter;
    return 0;
}

int IterativeSolver::getMaxIter() {
    return mMaxIter;
}

int IterativeSolver::setTol(double new_tol) {
    //check that new tol is positive and non-zero, else throw exception
    mTol = new_tol;
    return 0;
}

double IterativeSolver::getTol() {
    return mTol;
}

IterativeSolver::IterativeSolver(double tol, int max_iter) {
    mTol = tol;
    mMaxIter = max_iter;
}
