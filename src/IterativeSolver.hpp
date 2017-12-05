

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
    explicit IterativeSolver(double tol= 1e-05, int max_iter= 100 );
    // Iterative solver specific methods
    int SetMaxIter(int max_iter);
    int GetMaxIter();
    int SetTol(double new_tol);
    double GetTol();
    int PrintConvergenceWarning(double res_norm);
};



#endif //PCSC2017_GROUP12_ITERATIVESOLVER_H
