
// Simply include necessary headers of the library as you need them.

#include <Vector.hpp>
#include <CGSolver.hpp>
#include <LUSolver.hpp>
#include <Exception.hpp>
#include <iostream>
#include <JacSolver.hpp>
#include <CholeskySolver.hpp>
#include "Demo.hpp"
#include <chrono>

typedef std::chrono::high_resolution_clock::time_point time_point;
typedef std::chrono::high_resolution_clock time_clock;

int Demo::example1() {

    /********* Example use 1 - manual creation of data for solvers******/

    std::cout << "Demo: Example 1, manually building a linear system: \n";
    // Create two demo variables
    int demo_size = 5;
    Vector demo_vector(demo_size);
    Matrix demo_matrix(demo_size, demo_size);

    // Fill variables with values. The matrix will be an identity, the vector contains values from 0 to demo_size.
    for (int index = 0; index < demo_size; index++) {
        demo_vector(index) = index;
        demo_matrix(index, index) = 1.0;
    }

    //** Do any further kind of manipulations on matrix and vector if desired.**//
    demo_vector = demo_vector * 2;

    // Create an iterative solver.
    CGSolver it_solver;
    //** Other iterative solvers are for example: JacSolver, GSSolver, RichSolver **//

    //** Optional: Change tolerance and number of maximum iteration from their default values.**//
    it_solver.SetTol(1e-06);
    it_solver.SetMaxIter(100);

    // Alternative: Create a direct solver.
    LUSolver dir_solver;

    // Solve the system and catch debug message if there is an error.
    Vector demo_result_it(5);
    Vector demo_result_dir(5);
    try {
        demo_result_it = it_solver.Solve(demo_matrix, demo_vector);
        demo_result_dir = dir_solver.Solve(demo_matrix, demo_vector);

    }
    catch (const Exception &error) {
        error.PrintDebug();
        return EXIT_FAILURE;
    }
    // Print results to console to see if the result is as expected.
    std::cout.setf(std::ios::scientific);
    std::cout.setf(std::ios::showpos);
    std::cout << "Result vector of demo 1 with iterative solver:\n";
    for (int index = 0; index < demo_size; index++) {
        std::cout << demo_result_it.at(index) << "\n";
    }

    std::cout << "Result vector of demo 1 with direct solver:\n";
    for (int index = 0; index < demo_size; index++) {
        std::cout << demo_result_dir.at(index) << "\n";
    }

    //** Optional: Write the result to file. (Will throw an error if path is invalid)
    it_solver.WriteMatrixToFile("../../demo/demo_vec.dat", demo_result_it);
    std::cout << "\n \n \n";
    return 0;
}


int Demo::example2() {
    /********* Example use 2 - Load values of a bigger system for both types of solver ******/

    std::cout << "Demo: Example 2, loading a linear system from file: \n";
    // Create a solver first (or use one that you have already created), since we use solvers to read from file.
    // Create iterative solver ( any of the other solvers  would also be fine.)
    JacSolver it_solver;

    // Read matrix and vector from demo file.
    Matrix mat_big = it_solver.ReadMatrixFromFile("../../demo/Demo10_mat.dat");
    // Note: For the vector we use the "cast"-function asVector(..) so that we automatically turn the 1D matrix into a
    // vector.
    Vector vector_big = asVector(it_solver.ReadMatrixFromFile("../../demo/Demo10_vec.dat"));


    // Solve the system using iterative method (and don't catch any errors, this will give fewer information if something goes wrong!)
    // We don't need to preallocate space, but can directly use the result of the Solve(..).
    Vector result_it = it_solver.Solve(mat_big, vector_big);

    // Solve system again with a direct solver:
    CholeskySolver dir_solver;
    Vector result_dir = dir_solver.Solve(mat_big, vector_big);


    // Print both result to the terminal:
    std::cout << "Result vector of a slightly bigger system with an iterative solver :\n";
    for (int index = 0; index < result_it.Size(); index++) {
        std::cout << result_it.at(index) << "\n";
    }

    std::cout << "Result vector of a slightly bigger system with  a direct solver :\n";
    for (int index = 0; index < result_it.Size(); index++) {
        std::cout << result_it.at(index) << "\n";
    }

    //** We can compare the output of out solver with a solution pre-computed with MATLAB: Demo10_sol
    // .dat **/

    Vector result_matlab = asVector(it_solver.ReadMatrixFromFile("../../demo/Demo10_sol.dat"));
    std::cout << "Result vector of a slightly bigger system solved with MATLAB :\n";
    for (int index = 0; index < result_matlab.Size(); index++) {
        std::cout << result_matlab.at(index) << "\n";
    }
    std::cout << "\n \n \n";
    return 0;
}

int Demo::example3() {
    /********* Example use 3 - Demonstrates  CG and preconditioned CG in comparison do direct solvers******/

    std::cout << "Demo: Example 3, solving a 1000x1000 linear system: \n";

    // Generate an it_solver with reasonably high accuracy
    CGSolver it_solver;
    it_solver.SetMaxIter(100);
    it_solver.SetTol(1e-09);

    // Read matrix and vector from demo file.
    Matrix mat = it_solver.ReadMatrixFromFile("../../demo/Demo1000_mat.dat");
    // Note: For the vector we use the "cast"-function asVector(..) so that we automatically turn the 1D matrix into a
    // vector.
    Vector vec = asVector(it_solver.ReadMatrixFromFile("../../demo/Demo1000_vec.dat"));

    // Also load the solution calculated by MATLAB:
    Vector solution = asVector(it_solver.ReadMatrixFromFile("../../demo/Demo1000_sol.dat"));

    // Solve the system using an iterative method (and don't catch any errors, this will give fewer information if
    // something goes wrong!)
    // We don't need to preallocate space, but can directly use the result of the Solve(..).

    std::cout << "Solving with a direct solver: \n";
    // Measure time needed for solve.
    time_point t1 = time_clock::now();
    Vector result_it = it_solver.Solve(mat, vec);
    time_point t2 = time_clock::now();

    // Calculate the error.
    auto error = (result_it - solution).CalculateNorm();

    // Print info about this solve:
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();
    std::cout << "Computation time: " << duration << " ms \n";
    std::cout << "Error: " << error << " \n";


    std::cout << "Solving with preconditioned CG Solver: \n";


    // Create the preconditioner.
    Matrix precond = it_solver.CreateDiagPreconditioner(mat);
    // Solve with preconditioner.
    t1 = time_clock::now();
    Vector result_precond = it_solver.Solve(mat, vec, precond);
    t2 = time_clock::now();

    // Calculate the error.
    error = (result_precond - solution).CalculateNorm();

    // Print info about this solve:
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();
    std::cout << "Computation time: " << duration << " ms \n";
    std::cout << "Error: " << error << " \n";


    // Solve system again with a direct solver:
    std::cout << "Solving with Cholesky factorization: \n";
    CholeskySolver dir_solver;
    t1 = time_clock::now();
    Vector result_dir = dir_solver.Solve(mat, vec);
    t2 = time_clock::now();

    // Calculate the error.
    error = (result_dir - solution).CalculateNorm();

    // Print info about this solve.
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();
    std::cout << "Computation time: " << duration << " ms \n";
    std::cout << "Error: " << error << " \n";
    std::cout << "\n \n \n";
    return 0;
}

int Demo::example4() {
    std::cout << "Demo: Example 4, a few matrix operations. \n";
    // Create a solver to load data.
    LUSolver solver;
    // Load the data.
    Vector vector = asVector(solver.ReadMatrixFromFile("../../demo/Demo10_vec.dat"));
    Vector vector_double = vector * 2;
    Vector vector_triple = vector_double + vector;
    // Transpose a vector
    auto transpose = vector.transpose();

    // Calculate the inner product
    double inner_product = dotProduct(vector, asVector(transpose));
    std::cout << "Inner product with dotProduct(..) is " << inner_product << ".\n";
    // Multiply a transposed vector with another vector.
    auto multiplication = transpose * vector;
    std::cout << "Inner product with matrix product is " << multiplication(0) << ".\n";

    std::cout << "Entering matrices and vectors from the keyboard.\n";  // Not recommended use of this library.
    // Read matrix and vector from keyboard
    std::cout << "Input matrix first : \n";
    Matrix mat_input = solver.ReadMatrixFromKeyboard();
    std::cout << "Input vector then: \n";
    Vector vec_input = asVector(solver.ReadMatrixFromKeyboard());


    return 0;
}
