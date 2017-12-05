
#include <iostream>
#include "Matrix.hpp"
#include "Vector.hpp"
#include "CGSolver.hpp";

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
    Vector demo_result = solver.Solve(demo_matrix, demo_vector);
    std::cout << "Result vector of demo :\n";
    for (int index = 0; index< demo_size; index ++ ) {
        std::cout << demo_result.at(index) << "\n";
    }

    // Write the result to file
    solver.WriteMatrixToFile("../../demo/demo_vec.dat", demo_result);
    return 0;
}
