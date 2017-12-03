//
// Created by mariella on 03.12.17.
//

#ifndef PCSC2017_GROUP12_CGSOLVER_H
#define PCSC2017_GROUP12_CGSOLVER_H

#include "IterativeSolver.hpp"
class CGSolver: public IterativeSolver
{
public:
    virtual Vector Solve(const Matrix& A, const Vector& b);
};
#endif //PCSC2017_GROUP12_CGSOLVER_H
