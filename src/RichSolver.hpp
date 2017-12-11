#ifndef PCSC2017_GROUP12_RICHSOLVER_HPP
#define PCSC2017_GROUP12_RICHSOLVER_HPP

#include "IterativeSolver.hpp"

/**
* The RichSolver class implements the methods for the Richardson iteration.
*/

class RichSolver: public IterativeSolver
{
private:
    /// Relaxation parameter w
    double mW;
public:
    /// Standard constructor
    RichSolver();

    /// Constructor, where the parameter w is set at creation time.
    explicit RichSolver(double w);

    /// Constructor where all parameters are set at creation time.
    RichSolver(double w, double tol, int max_iter);

    /// Implementation of Solve(A,b) with the Richardson iteration. Convergence depends very much on w.
    Vector Solve(const Matrix& A, const Vector& b) override;

    /// Returns the method parameter w of the Richardson iteration.
    double GetParameterW();

    /// Sets a new method parameter w of the Richardson iteration. W needs to be larger than 0 and is ideally smaller
    /// than 2/lambda_max, where lambda_max is the maximum eigenvalue of the matrix A.
    int SetParameterW(double w);
};

#endif //PCSC2017_GROUP12_RICHSOLVER_HPP