//
// Tests for the solver specific methods
//

#include "gtest/gtest.h"
#include "../src/CGSolver.hpp"

std::string path_to_test_files = "../../Tests/FilesForTests/";
TEST(LinSysSolverTest, ReadAndWriteMatrix) {
    double test_number = 3.1415;
    CGSolver solver;
    Matrix mat(5,4);
    mat(1,2) = test_number;
    solver.WriteMatrixToFile(path_to_test_files+"test_mat.dat", mat);
    Matrix read_mat = solver.ReadMatrixFromFile(path_to_test_files +"test_mat.dat");
    EXPECT_EQ(read_mat.Rows(), 5);
    EXPECT_EQ(read_mat.Cols(), 4);
    EXPECT_DOUBLE_EQ(read_mat(1,2),test_number);
}


TEST(LinSysSolverTest, ReadAndWriteVector) {
    double test_number = 3.1415;
    CGSolver solver;
    Vector vec(3);
    vec(2) = test_number;
    solver.WriteMatrixToFile(path_to_test_files+"test_vec.dat", vec);
    Matrix read_mat = solver.ReadMatrixFromFile(path_to_test_files +"test_vec.dat");
    EXPECT_EQ(read_mat.Rows(), 3);
    EXPECT_EQ(read_mat.Cols(), 1);
    Vector read_vec = asVector(read_mat);
    EXPECT_EQ(read_vec.Size(), 3);
    EXPECT_DOUBLE_EQ(read_vec(2),test_number);
}


