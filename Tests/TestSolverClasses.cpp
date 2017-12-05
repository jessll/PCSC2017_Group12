//
// Tests for the solver specific methods
//

#include "gtest/gtest.h"
#include "../src/CGSolver.hpp"
#include "../src/RichSolver.hpp"
#include "../src/JacSolver.hpp"
#include "../src/GSSolver.hpp"

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


TEST(RichSolverTest, CheckConstructorsAndSetGet) {
    // Default constructor
    RichSolver solver;
    EXPECT_DOUBLE_EQ(solver.GetParameterW(), 0.5);
    EXPECT_DOUBLE_EQ(solver.getTol(), 1e-05);
    EXPECT_EQ(solver.getMaxIter(),100);

    // Constructor that only specifies w
    RichSolver solver_w(0.3);
    EXPECT_DOUBLE_EQ(solver_w.GetParameterW(), 0.3);
    EXPECT_DOUBLE_EQ(solver_w.getTol(), 1e-05);
    EXPECT_EQ(solver_w.getMaxIter(),100);
    // Constructor setting all parameters
    RichSolver solver_all(0.3, 1e-03, 20);
    EXPECT_DOUBLE_EQ(solver_all.GetParameterW(), 0.3);
    EXPECT_DOUBLE_EQ(solver_all.getTol(), 1e-03);
    EXPECT_EQ(solver_all.getMaxIter(),20);

    // Testing set and get
    solver.SetParameterW(0.1);
    EXPECT_DOUBLE_EQ(0.1, solver.GetParameterW());
}

TEST(LinSysSolverTest, CheckConstructorsAndSetGet) {
    CGSolver solver;
    EXPECT_DOUBLE_EQ(solver.getTol(), 1e-05);
    EXPECT_EQ(solver.getMaxIter(),1000);
    CGSolver solver_param(1e-02, 1000);
    EXPECT_DOUBLE_EQ(solver_param.getTol(), 1e-02);
    EXPECT_EQ(solver_param.getMaxIter(),1000);
    solver.setMaxIter(1);
    EXPECT_EQ(1, solver.getMaxIter());
    solver.setTol(1e-4);
    EXPECT_DOUBLE_EQ(1e-4, solver.getTol());
}

TEST(RichSolverTest, SmallExample) {
    // Set up data
    RichSolver solver;
    Matrix mat = solver.ReadMatrixFromFile(path_to_test_files+"small_Ex_mat.dat");
    Vector vec = asVector(solver.ReadMatrixFromFile(path_to_test_files+"small_Ex_vec.dat"));
    Vector ref_sol = asVector(solver.ReadMatrixFromFile(path_to_test_files+"small_Ex_sol.dat"));
    // Standard tolerance
    Vector calc_sol = solver.Solve(mat, vec);
    EXPECT_NEAR(ref_sol(0), calc_sol(0), solver.getTol());
    EXPECT_NEAR(ref_sol(1), calc_sol(1), solver.getTol());

    //Low tolerance
    solver.setTol(1e-14);
    calc_sol = solver.Solve(mat, vec);
    EXPECT_NEAR(ref_sol(0), calc_sol(0), solver.getTol());
    EXPECT_NEAR(ref_sol(1), calc_sol(1), solver.getTol());
}


TEST(JacSolverTest, SmallExample) {
    // Set up data
    JacSolver solver;
    Matrix mat = solver.ReadMatrixFromFile(path_to_test_files+"small_Ex_mat.dat");
    Vector vec = asVector(solver.ReadMatrixFromFile(path_to_test_files+"small_Ex_vec.dat"));
    Vector ref_sol = asVector(solver.ReadMatrixFromFile(path_to_test_files+"small_Ex_sol.dat"));
    // Standard tolerance
    Vector calc_sol = solver.Solve(mat, vec);
    EXPECT_NEAR(1.0/mat.at(0, 0), 2.0/3, 1e-06);
    EXPECT_NEAR(ref_sol(0), calc_sol(0), solver.getTol());
    EXPECT_NEAR(ref_sol(1), calc_sol(1), solver.getTol());

    //Low tolerance
    solver.setTol(1e-14);
    calc_sol = solver.Solve(mat, vec);
    EXPECT_NEAR(ref_sol(0), calc_sol(0), solver.getTol());
    EXPECT_NEAR(ref_sol(1), calc_sol(1), solver.getTol());

}


TEST(JacSolverTest, BigExample) {
    // Set up data
    JacSolver solver;
    Matrix mat = solver.ReadMatrixFromFile(path_to_test_files+"Spd_Ex_size100_mat.dat");
    Vector vec = asVector(solver.ReadMatrixFromFile(path_to_test_files+"Spd_Ex_size100_vec.dat"));
    Vector ref_sol = asVector(solver.ReadMatrixFromFile(path_to_test_files+"Spd_Ex_size100_sol.dat"));

    // Standard tolerance
    Vector calc_sol = solver.Solve(mat, vec);
    for (int iter =0; iter < ref_sol.Size(); iter++ ) {
        EXPECT_NEAR(ref_sol(iter), calc_sol(iter), solver.getTol());
    }
    //Low tolerance
    solver.setTol(1e-9);
    calc_sol = solver.Solve(mat, vec);
    for (int iter =0; iter < ref_sol.Size(); iter++ ) {
        EXPECT_NEAR(ref_sol(iter), calc_sol(iter), solver.getTol());
    }
}

TEST(GSSolverTest, BigExample) {
    // Set up data
    GSSolver solver;
    Matrix mat = solver.ReadMatrixFromFile(path_to_test_files+"Spd_Ex_size100_mat.dat");
    Vector vec = asVector(solver.ReadMatrixFromFile(path_to_test_files+"Spd_Ex_size100_vec.dat"));
    Vector ref_sol = asVector(solver.ReadMatrixFromFile(path_to_test_files+"Spd_Ex_size100_sol.dat"));

    // Standard tolerance
    Vector calc_sol = solver.Solve(mat, vec);
    for (int iter =0; iter < ref_sol.Size(); iter++ ) {
        EXPECT_NEAR(ref_sol(iter), calc_sol(iter), solver.getTol());
    }
    //Low tolerance
    solver.setTol(1e-9);
    calc_sol = solver.Solve(mat, vec);
    for (int iter =0; iter < ref_sol.Size(); iter++ ) {
        EXPECT_NEAR(ref_sol(iter), calc_sol(iter), solver.getTol());
    }
}

TEST(RichSolverTest, BigExample) {
    // Set up data
    RichSolver solver;
    solver.SetParameterW(0.01); //magical, comes from construction of the tests
    Matrix mat = solver.ReadMatrixFromFile(path_to_test_files+"Spd_Ex_size100_mat.dat");
    Vector vec = asVector(solver.ReadMatrixFromFile(path_to_test_files+"Spd_Ex_size100_vec.dat"));
    Vector ref_sol = asVector(solver.ReadMatrixFromFile(path_to_test_files+"Spd_Ex_size100_sol.dat"));

    // Standard tolerance
    Vector calc_sol = solver.Solve(mat, vec);
    for (int iter =0; iter < ref_sol.Size(); iter++ ) {
        EXPECT_NEAR(ref_sol(iter), calc_sol(iter), solver.getTol());
    }
    //Low tolerance
    solver.setTol(1e-9);
    calc_sol = solver.Solve(mat, vec);
    for (int iter =0; iter < ref_sol.Size(); iter++ ) {
        EXPECT_NEAR(ref_sol(iter), calc_sol(iter), solver.getTol());
    }
}

TEST(GSSolverTest, SmallExample) {
    // Set up data
    GSSolver solver;
    Matrix mat = solver.ReadMatrixFromFile(path_to_test_files+"small_Ex_mat.dat");
    Vector vec = asVector(solver.ReadMatrixFromFile(path_to_test_files+"small_Ex_vec.dat"));
    Vector ref_sol = asVector(solver.ReadMatrixFromFile(path_to_test_files+"small_Ex_sol.dat"));
    // Standard tolerance
    Vector calc_sol = solver.Solve(mat, vec);
    EXPECT_NEAR(ref_sol(0), calc_sol(0), solver.getTol());
    EXPECT_NEAR(ref_sol(1), calc_sol(1), solver.getTol());

    //Low tolerance
    solver.setTol(1e-14);
    calc_sol = solver.Solve(mat, vec);
    EXPECT_NEAR(ref_sol(0), calc_sol(0), solver.getTol());
    EXPECT_NEAR(ref_sol(1), calc_sol(1), solver.getTol());

}

TEST(CGTest, SmallExample) {
    // Set up data
    CGSolver solver;

    Matrix mat = solver.ReadMatrixFromFile(path_to_test_files+"Spd_Ex_size10_mat.dat");
    Vector vec = asVector(solver.ReadMatrixFromFile(path_to_test_files+"Spd_Ex_size10_vec.dat"));
    Vector ref_sol = asVector(solver.ReadMatrixFromFile(path_to_test_files+"Spd_Ex_size10_sol.dat"));

    // Standard tolerance
    Vector calc_sol = solver.Solve(mat, vec);
    for (int iter =0; iter < ref_sol.Size(); iter++ ) {
        EXPECT_NEAR(ref_sol(iter), calc_sol(iter), solver.getTol());
    }
    //Low tolerance
    solver.setTol(1e-8);
    calc_sol = solver.Solve(mat, vec);
    for (int iter =0; iter < ref_sol.Size(); iter++ ) {
        EXPECT_NEAR(ref_sol(iter), calc_sol(iter), solver.getTol());
    }
}

TEST(CGTest, BigExample) {
    // Set up data
    CGSolver solver;

    Matrix mat = solver.ReadMatrixFromFile(path_to_test_files+"Spd_Ex_size100_mat.dat");
    Vector vec = asVector(solver.ReadMatrixFromFile(path_to_test_files+"Spd_Ex_size100_vec.dat"));
    Vector ref_sol = asVector(solver.ReadMatrixFromFile(path_to_test_files+"Spd_Ex_size100_sol.dat"));

    // Standard tolerance
    Vector calc_sol = solver.Solve(mat, vec);
    for (int iter =0; iter < ref_sol.Size(); iter++ ) {
        EXPECT_NEAR(ref_sol(iter), calc_sol(iter), solver.getTol());
    }
    //Low tolerance
    solver.setTol(1e-09);
    calc_sol = solver.Solve(mat, vec);
    for (int iter =0; iter < ref_sol.Size(); iter++ ) {
        EXPECT_NEAR(ref_sol(iter), calc_sol(iter), solver.getTol());
    }
}