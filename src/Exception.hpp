#ifndef PCSC2017_GROUP12_EXCEPTION_H
#define PCSC2017_GROUP12_EXCEPTION_H

#include <string>

class Exception {
private:
    std :: string mTag, mProblem;
public:
    Exception(std::string tagString, std::string probString );
    void PrintDebug() const;
};

#endif //PCSC2017_GROUP12_EXCEPTION_H
