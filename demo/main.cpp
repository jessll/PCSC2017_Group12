
#include "Demo.hpp"


int main(int argc, char* argv[])
{
    Demo demo;
    // This example manually creates a matrix and a vector and solves the system with an iterative solver and direct
    // solver.
    demo.example1();

    // This examples loads a "real" linear system from file and solves it.
    demo.example2();

    // This example solves a large 1000 by 1000 system and looks at the speed of the computation and preconditioning.
    demo.example3();

    // This example shows some useful linear algebra operations.
    demo.example4();


    return 0;
}
