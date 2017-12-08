
#ifndef PCSC2017_GROUP12_CHOLESKY_H
#define PCSC2017_GROUP12_CHOLESKY_H

#include "DirectSolver.hpp"

class CholeskySolver:public DirectSolver{

public:
    CholeskySolver();
    virtual Vector Solve(const Matrix& A, const Vector& b);
};



#endif //PCSC2017_GROUP12_CHOLESKY_H
