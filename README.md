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


## Compiling
(Only tested on Linux and Mac OS X, no 
guarantees for Windows.)  
Note:  
 You will need an internet connection for building, since googletest is included automatically at compile time.  
Compiling is done via CMake files. Everything was set up with CLion, so when using this IDE, no other adjustments 
should be needed.  

**Compilation in terminal**
- Go to the repository folder "PCSC2017_Group12" 
- Execute the following commands in the terminal:   
```
$ mkdir build  
$ cd build  
$ cmake ..  
$ make
```
- In the new "build" folder, you should now see two folders "demo" and "Test", which contain the executables. You can
 run them like this:  
 ``` 
 $ cd demo  
 $ ./demo  
 ```
 **or**  
 ```
 $ cd Tests  
 $ ./BasicTests
 ```
  
  Note:  
  In principle, you can compile the _Linear Systems_ library wherever you want, but the demo and the tests use some 
  files located in this project. So if you do not compile and run in the way described above, you will probably get
   an  Exception, because the executables cannot find the files.
  If you want to write your own executables ( or change the paths in the Test suite), feel free to compile the library 
  wherever you want.

## Getting Started

To get started, clone this repository from github. Then, go to the folder "Documentation" and run the command:
```  
$ doxygen config_file  
```
This will create a helpful documentation of the project.

In order to see how this library works, check out the "demo folder", where we provide examples of how to use the code.
There is a "Demo" class that shows 4 worked examples, so have a look at "Demo.cpp" and run "./demo" from the folder 
to see the results (see above for how to compile). We provided comments
 in 
the 
source code to document the program flow, but you can always check out the Doxygen for further info. You can either 
build on 
these examples
 or have a look at the demo CMake 
file to see how this library could be included in other projects.


**Demo**
- Example 1 focuses on creating a matrix and vector manually and then solving the linear system with direct and 
iterative solvers.
- Example 2 focuses on reading a linear system from file.
- Example 3 demonstrates performance on a big 1000x1000 system and shows how to use a preconditioner.
- Example 4 shows a few tools for linear algebra computations. 

In order to learn more about which solvers are appropriate and the whole list of features, check out our "official" 
project report located in this repository.

**Tests**

If you want to convince yourself, that our code is doing what it should, simply run the tests we included by running 
`./BasicTests` from the "Test" folder in the build and see them pass.

We base our test suite on the  googletest library. There are three parts: 
- The "Base classes" test: `TestBaseClasses.cpp`, where we check that all functionality of vectors and matrices work as expected.
- The "Solver classes" test: `TestSolverClasses.cpp`, where we check the creation and use of solvers, as well as reading and writing to 
file.
- The "Exceptional cases" test: `TestExceptionalCases.cpp`, where we make sure that our library does check its inputs (e.g. the maximum number of iterations is positive, the number of rows is larger than 0, the matrix is symmetric if required by the solver) 
and throws Exceptions for invalid access, dimension mismatch in linear system etc.

Note:  
The output may report a "segmentation fault", when running the tests. This has to do with testing the exceptional
cases and does NOT mean the tests have failed. As long as you can see the line  
[  PASSED  ] XX tests  
all tests have passed as expected.

## List of Features
The main library files are in folder "src". The main contents  are as follows:
* Datatype

	* The datatypes are defined as classes: `Matrix.hpp`, `Vector.hpp`

* Solve Methods

	* Base class `LinSysSolver.hpp` defines:
		* Solve method
		* Read/Write method: read from file/keyboard, write to file
		* Validation check of input

	* Derived classes `IterativeSolver.hpp`, `DirectSolver.hpp`
		* Iterative methods including Conjugate Gradient(`CGSolver.hpp`),  Gauss-Seidel method (`GSSolver.hpp`), 
		Jacobi method (`JacSolver.hpp`), Richardson iteration (`RichSolver
		.hpp`) derived from `IterativeSolver.hpp`.
		* Preconditioned Conjugate Gradient method is implemented in `CGSolver.hpp` by overload of solve method
		 with additional parameter of a preconditioner Matrix.
		* Direct methods including LU factorization (`LUSolver.hpp`) and Cholesky factorization (`CholeskySolver.hpp`).





