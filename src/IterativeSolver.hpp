

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
protected:
    int PrintConvergenceWarning(double res_norm);
public:
    explicit IterativeSolver(double tol= 1e-05, int max_iter= 100 );
    // Iterative solver specific methods
    int SetMaxIter(int max_iter);
    int GetMaxIter();
    int SetTol(double new_tol);
    double GetTol();
};



#endif //PCSC2017_GROUP12_ITERATIVESOLVER_H
