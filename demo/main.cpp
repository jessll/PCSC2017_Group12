
#include <iostream>
#include <Exception.hpp>
#include "Matrix.hpp"
#include "Vector.hpp"
#include "CGSolver.hpp"
#include "LUSolver.hpp"
#include "Exception.hpp"
#include "CholeskySolver.hpp"

int main(int argc, char* argv[])
{
    // Create two demo variables
    int demo_size = 5;
    Vector demo_vector(demo_size);
    Matrix demo_matrix(demo_size, demo_size);
    // Fill them with values. The matrix will be an identity, the Vector contains values from 0 to demo_size
    for (int index = 0; index< demo_size; index ++ ) {
        demo_vector(index) = index;
        demo_matrix(index, index) = 1.0;
    }

    // Create a solver
    CGSolver solver;

    // Solve the system and print the result.
    Vector demo_result(5);
    try
    {
        demo_result = solver.Solve(demo_matrix, demo_vector);
    }
    catch(const Exception& error)  {
        error.PrintDebug();
        return EXIT_FAILURE;
    }

    std::cout << "Result vector of demo with CG solver:\n";
    for (int index = 0; index< demo_size; index ++ ) {
        std::cout << demo_result.at(index) << "\n";
    }


    // Create another (direct) solver
    LUSolver ssolver;
    // Solve the system and print the result.
    try {
        Vector demo_result_1 = ssolver.Solve(demo_matrix, demo_vector);
        std::cout << "Result vector of lu :\n";
        for (int index = 0; index< demo_size; index ++ ) {
            std::cout << demo_result_1.at(index) << "\n";
        }

    }
    catch (Exception& error)
    {
        error.PrintDebug();
    }

    // Create cholesky slover
    CholeskySolver csolver;
    try {
        Vector demo_result_2 = csolver.Solve(demo_matrix, demo_vector);
        std::cout << "Result vector of cholesky :\n";
        for (int index = 0; index < demo_size; index++) {
            std::cout << demo_result_2.at(index) << "\n";
        }
    }
    catch (Exception& error)
    {
        error.PrintDebug();
    }




    // Write the result to file
    solver.WriteMatrixToFile("../../demo/demo_vec.dat", demo_result);
    return 0;
}
