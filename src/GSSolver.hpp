//
// Created by mariella on 04.12.17.
//

#ifndef PCSC2017_GROUP12_GSSOLVER_HPP
#define PCSC2017_GROUP12_GSSOLVER_HPP
#include "IterativeSolver.hpp"

class GSSolver :IterativeSolver{
public:
    Vector Solve(const Matrix& A, const Vector& b) override;
};


#endif //PCSC2017_GROUP12_GSSOLVER_HPP
