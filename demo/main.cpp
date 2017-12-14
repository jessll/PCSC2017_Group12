
#include <iostream>
#include <Exception.hpp>
#include "Matrix.hpp"
#include "Vector.hpp"
#include "CGSolver.hpp"
#include "GSSolver.hpp"
#include "JacSolver.hpp"
#include "RichSolver.hpp"
#include "LUSolver.hpp"
#include "CholeskySolver.hpp"

int main(int argc, char* argv[])
{


    /********* Example use 1 - manual creation for iterative solver******/
    // Create two demo variables
    int demo_size = 5;
    Vector demo_vector(demo_size);
    Matrix demo_matrix(demo_size, demo_size);

    // Fill variables with values. The matrix will be an identity, the vector contains values from 0 to demo_size.
    for (int index = 0; index< demo_size; index ++ ) {
        demo_vector(index) = index;
        demo_matrix(index, index) = 1.0;
    }
    //** Do any further kind of manipulations on matrix and vector if desired.**//

    // Create a iterative solver.
    CGSolver solver;
    //** Other iterative solvers are for example: JacSolver, GSSolver, RichSolver **//
    //JacSolver solver;
    //GSSolver solver;
    //RichSolver solver;

    // Iterative Solve the system and catch debug message if there is an error.
    Vector demo_result(5);
    try {
        demo_result = solver.Solve(demo_matrix, demo_vector);
    }
    catch(const Exception& error)  {
        error.PrintDebug();
        return EXIT_FAILURE;
    }
    // Print results to console
    std::cout.setf(std::ios::scientific);
    std::cout.setf(std::ios::showpos);
    std::cout << "Result vector of demo with iterative solver:\n";
    for (int index = 0; index< demo_size; index ++ ) {
        std::cout << demo_result.at(index) << "\n";
    }
    // Write the result to file (optional)
    solver.WriteMatrixToFile("../../demo/demo_vec.dat", demo_result);






    /********* Example use 2 - manual creation for direct solver******/
    // Create a direct solver.(You could also use CholeskySolver)
    LUSolver solver1;
    //CholeskySolver solver1;

    //Direct solve the system and catch debug message if there is an error.
    Vector demo_result_1(5);
    try {
        demo_result_1 = solver1.Solve(demo_matrix, demo_vector);
    }
    catch(const Exception& error)  {
        error.PrintDebug();
        return EXIT_FAILURE;
    }
    // Print results to console
    std::cout.setf(std::ios::scientific);
    std::cout.setf(std::ios::showpos);
    std::cout << "Result vector of demo with LU solver:\n";
    for (int index = 0; index< demo_size; index ++ ) {
        std::cout << demo_result_1.at(index) << "\n";
    }
    // Write the result to file (optional)
    solver1.WriteMatrixToFile("../../demo/demo_vec_lu.dat", demo_result_1);






    /********* Example use 3 - load values of a bigger system for iterative solver ******/

    // Create a solver first (or use one that you have already created)
    // Create iterative solver
    CGSolver solver2;
    //** Other iterative solvers are for example: JacSolver, GSSolver, RichSolver **//
    //JacSolver solver2;
    //GSSolver solver2;
    //RichSolver solver2;

    // Read matrix and vector from demo file.
    Matrix mat_big = solver2.ReadMatrixFromFile("../../demo/Demo10_mat.dat");
    Vector vector_big = asVector(solver2.ReadMatrixFromFile("../../demo/Demo10_vec.dat"));

    // Create a simple preconditioner (optional)
    Matrix precond = solver2.CreateDiagPreconditioner(mat_big);
    // Set parameters of the solver.
    solver2.SetTol(1e-4);
    solver2.SetMaxIter(100);
    // Solve the system using iterative method (and don't catch any errors, this will give fewer information if something goes wrong!)
    Vector result = solver2.Solve(mat_big, vector_big, precond);
    //Vector result = solver2.Solve(mat_big, vector_big); //For other iterative solvers, we don't need third argument

    // Print the result to the terminal:
    std::cout << "Result vector of a slightly bigger system with Iterative solver :\n";
    for (int index = 0; index < result.Size(); index++) {
        std::cout << result.at(index) << "\n";
    }






    /********* Example use 4 - load values of a bigger system for direct solver ******/
    // Create direct solver (you could also use CholeskySolver)
    LUSolver solver3;
    //CholeskySolver solver3;

    // Read matrix and vector from demo file.
    Matrix mat_big1 = solver3.ReadMatrixFromFile("../../demo/Demo10_mat.dat");
    Vector vector_big1 = asVector(solver3.ReadMatrixFromFile("../../demo/Demo10_vec.dat"));

    //Solve the system using direct method
    Vector result1 = solver3.Solve(mat_big1, vector_big1);
    // Print the result to the terminal:
    std::cout<< "Result vector of a slightly bigger system with LUsolver : \n";
    for (int index = 0; index < result1.Size(); index++){
        std::cout << result1.at(index) << "\n";
    }







    /******** Example use 5 - input matrix A and vector b from keyboard *********/
    // Solve by direct or iterative method
    LUSolver solver4;
    CGSolver solver5;
    // Read matrix and vector from keyboard
    std::cout<< "Input matrix first : \n";
    Matrix mat_input = solver4.ReadMatrixFromKeyboard();
    std::cout<<"Input vector then: \n";
    Vector vec_input = asVector(solver4.ReadMatrixFromKeyboard());


    // Solve the system
    Vector result2 = solver4.Solve(mat_input,vec_input);
    Vector result3 = solver5.Solve(mat_input,vec_input);

    // Print the result to the terminal:
    std::cout<< "Result vector of a slightly bigger system with LUSolver : \n";
    for (int index = 0; index < result2.Size(); index++){
        std::cout << result2.at(index) << "\n";
    }

    // Print the result to the terminal:
    std::cout<< "Result vector of a slightly bigger system with CGSolver : \n";
    for (int index = 0; index < result3.Size(); index++){
        std::cout << result3.at(index) << "\n";
    }

    //** If desired, you can compare the output of this vector with a solution pre-computed with MATLAB: Demo10_sol
    // .dat **/


    return 0;
}
