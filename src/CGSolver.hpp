//
// Created by mariella on 03.12.17.
//

#ifndef PCSC2017_GROUP12_CGSOLVER_H
#define PCSC2017_GROUP12_CGSOLVER_H

#include "IterativeSolver.hpp"
class CGSolver: public IterativeSolver
{
private:
    int CheckSymmetry(const Matrix &A);
public:
    explicit CGSolver(double tol= 1e-05, int max_iter= 1000 );
    Vector Solve(const Matrix& A, const Vector& b) override;
    // Preconditioned CG, uses inv(M) as precond, where M is a good preconditioner for the system Ax=b.
    Vector Solve(const Matrix& A, const Vector& b, const Matrix& precond);

    Matrix CreateDiagPreconditioner(const Matrix &A);
};
#endif //PCSC2017_GROUP12_CGSOLVER_H
