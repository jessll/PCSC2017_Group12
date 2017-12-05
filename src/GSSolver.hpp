//
// Created by mariella on 04.12.17.
//

#ifndef PCSC2017_GROUP12_GSSOLVER_HPP
#define PCSC2017_GROUP12_GSSOLVER_HPP
#include "IterativeSolver.hpp"

class GSSolver : public IterativeSolver{
public:
    explicit GSSolver(double tol= 1e-05, int max_iter= 10000 );
    Vector Solve(const Matrix& A, const Vector& b) override;
};


#endif //PCSC2017_GROUP12_GSSOLVER_HPP
