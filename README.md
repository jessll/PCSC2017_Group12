# PCSC2017_Group12


# Project Title

Linear System

## Getting Started

There are three parts: the actual linear systems library which is located in ”src”, a ”demo” folder which shows samples use of the features and the ”test” suite.

Structure of the linear system is simple and clear. Based on class Matrix and Vector, we build class LinSysSolver and its derived classes DirectSolver and IterativeSolver. The specific methods derived from the two methods. 

Several examples show in "demo" folder, including different solvers of interative and direct methods. Also, the file also shows three methods of input matrix and vector mentioned in report.

Test based on googletest library. There are three parts in test: the base classes test, which about Matrix and Vector class. The slover classes test and exception test.



## Compilation

Compilation is done via cMake files no other adjustements should be needed.


