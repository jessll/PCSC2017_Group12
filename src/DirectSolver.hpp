//
// Created by 吕文媛 on 05/12/2017.
//

#ifndef PCSC2017_GROUP12_DIRECTSOLVER_H
#define PCSC2017_GROUP12_DIRECTSOLVER_H

#include "Matrix.hpp"
#include "Vector.hpp"
#include <string>
#include "LinSysSolver.hpp"

class DirectSolver:public LinSysSolver {
public:
    DirectSolver();
    // Solver method
    virtual Vector Solve(const Matrix& A, const Vector& b)=0;

};


#endif //PCSC2017_GROUP12_DIRECTSOLVER_H
