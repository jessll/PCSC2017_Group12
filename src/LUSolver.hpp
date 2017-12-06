

#ifndef PCSC2017_GROUP12_LUSOLVER_H
#define PCSC2017_GROUP12_LUSOLVER_H

#include "DirectSolver.h"

class LUSolver: public DirectSolver{
    virtual Vector Solve(const Matrix& A, const Vector& b);
};


#endif //PCSC2017_GROUP12_LUSOLVER_H
