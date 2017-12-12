#ifndef PCSC2017_GROUP12_EXCEPTION_H
#define PCSC2017_GROUP12_EXCEPTION_H

#include <string>
/**
* The Exception class implements the exception when there are invalid behaviors.
*/
class Exception {
/// private variables about the problem tag and relative problem
private:
    std :: string mTag, mProblem;
public:
    /// Constructor for Exception
    Exception(std::string tagString, std::string probString );
    /// method for printing error information
    void PrintDebug() const;
};

#endif //PCSC2017_GROUP12_EXCEPTION_H
