# PCSC2017_Group12


# The Project 

**Linear Systems**

There are three parts to this project: the actual _Linear Systems_ library which is located in ”src”, a ”demo” folder
which shows example use of the features and the ”test” suite.

The structure of the _Linear Systems_ library is simple and clear. Based on the classes Matrix and Vector, we build 
the  class 
LinSysSolver
and its derived classes DirectSolver and IterativeSolver. The specific numerical solvers are derived from these two
abstract classes.

## Getting Started

To get started, clone this repository and run "doxygen config_file" from your terminal to create a helpful 
documentation.

In order to see how this library works, check out the "demo folder", where we provide examples of how to use the code.
There is a "Demo" class that shows 4 worked examples, so have a look at "Demo.cpp" and run "./demo" from the folder 
to see the results. We provided comments
 in 
the 
source code to document the program flow, but you can always check out the Doxygen for further into. You can either 
build on 
these examples
 or have a look at the demo cMake 
file to see how this library could be included in other projects.


**Demo**
- Example 1 focuses on creating a matrix and vector manually and then solving the linear system with direct and 
iterative solvers.
- Example 2 focuses on reading a linear system from file.
- Example 3 demonstrates performance on a big 1000x1000 system and shows how to use a preconditioner.
- Example 4 shows a few tools for linear algebra computations. 

In order to learn more about which solvers are appropriate and the whole list of features, check out our "official" 
project report located in this repository.

**Tests*

If you want to convince yourself, that our code is doing what it should, simply run the tests we included by running 
"./BasicTests" from the "Test" folder in the build and see them pass.

We base our test suite on the  googletest library. There are three parts: 
- The "Base classes" test, where we check that all functionality of vectors and matrices work as expected.
- The "Solver classes" test , where we check the creation and use of solvers, as well as reading and writing to 
file.
- The "Exceptional cases", where we make sure that our library does check its inputs (e.g. the maximum number of 
iterations is positive, the number of rows is larger than 0, the matrix is symmetric if required by the solver) 
and throws Exceptions for 
invalid access, dimension mismatch in linear system etc.

## Compiling

Compiling is done via cMake files no other adjustments should be needed. (Only tested on Linux and Mac OS X, no 
guarantees for Windows.)


