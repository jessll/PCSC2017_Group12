

#ifndef PCSC2017_GROUP12_DEMO_HPP
#define PCSC2017_GROUP12_DEMO_HPP

/**
 * The Demo class contains a few examples on how to use the LinSys library.
 */
class Demo {
public:
    /// A function to demonstrate how matrices and vectors can be created and filled with values. Also shows the use
    /// of solvers.
    int example1();

    /// A function to demonstrate how data can be read from/written to file. Also shows the use of solvers on a "real"
    /// example.
    int example2();

    /// A function to demonstrate the preconditioned Conjugate Gradient solver.
    int example3();

    /// A function that demonstrates essential linear algebra operations of the matrix and vector class.
    int example4();
};


#endif //PCSC2017_GROUP12_DEMO_HPP
