

#ifndef PCSC2017_GROUP12_LUSOLVER_H
#define PCSC2017_GROUP12_LUSOLVER_H

#include "DirectSolver.hpp"

class LUSolver: public DirectSolver{
public:
    LUSolver();
    virtual Vector Solve(const Matrix& A, const Vector& b);
};
#endif //PCSC2017_GROUP12_LUSOLVER_H
