#ifndef PCSC2017_GROUP12_ITERATIVESOLVER_H
#define PCSC2017_GROUP12_ITERATIVESOLVER_H

#include "Matrix.hpp"
#include "Vector.hpp"
#include <string>
#include "LinSysSolver.hpp"

/**
* The IterativeSolver provides a base class for iterative solvers with the typical parameters.
*/

class IterativeSolver: public LinSysSolver
{
private:
    /// Error tolerance which determines how accurate the returned solution vector x is
    double mTol;
    /// Maximum number of iterations after which the solver stops even if convergence is not reached.
    int mMaxIter;
protected:
    /// This function prints a short message when the iterative solver does not converge to tol within the maximum
    /// number of steps.
    int PrintConvergenceWarning(double res_norm);
public:
    /// This is the standard constructor for an iterative solver that fixes some reasonable values for the tolerance
    /// and maximum number of iterations.
    explicit IterativeSolver(double tol = 1e-05, int max_iter = 1000);

    /// This function sets the maximum number of iterations.
    int SetMaxIter(int max_iter);

    /// This function returns the maximum number of iterations this solver performs in a Solve(A,b) call.
    int GetMaxIter();

    /// This function sets the tolerance for the error in the residual.
    int SetTol(double new_tol);

    /// This function returns the tolerance of the solver.
    double GetTol();
};

#endif //PCSC2017_GROUP12_ITERATIVESOLVER_H