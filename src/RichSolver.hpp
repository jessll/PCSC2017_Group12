//
// Created by mariella on 04.12.17.
//

#ifndef PCSC2017_GROUP12_RICHSOLVER_HPP
#define PCSC2017_GROUP12_RICHSOLVER_HPP
#include "IterativeSolver.hpp"
class RichSolver: public IterativeSolver
{
private:
    double mW;
public:
    RichSolver();
    explicit RichSolver(double w);
    RichSolver(double w, double tol, int max_iter);
    Vector Solve(const Matrix& A, const Vector& b) override;
    double GetParameterW();
    int SetParameterW( double w);
};

#endif //PCSC2017_GROUP12_RICHSOLVER_HPP
