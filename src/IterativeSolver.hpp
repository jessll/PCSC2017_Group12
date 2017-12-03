

#ifndef PCSC2017_GROUP12_ITERATIVESOLVER_H
#define PCSC2017_GROUP12_ITERATIVESOLVER_H

#include "Matrix.hpp"
#include "Vector.hpp"
#include <string>
#include "LinSysSolver.hpp"

class IterativeSolver: public LinSysSolver
{
private:
    double mTol;
    int mMaxIter;
public:
    // Solver method
    virtual Vector Solve(const Matrix& A, const Vector& b)=0;
    IterativeSolver(double tol= 1e-05, int max_iter= 100 );
    // Iterative solver specific methods
    int setMaxIter(int max_iter);
    int getMaxIter();
    int setTol(double new_tol);
    double getTol();
};



#endif //PCSC2017_GROUP12_ITERATIVESOLVER_H
