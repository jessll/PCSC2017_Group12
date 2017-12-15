//
// Tests for the solver specific methods
//

#include "gtest/gtest.h"
#include "CGSolver.hpp"
#include "RichSolver.hpp"
#include "JacSolver.hpp"
#include "GSSolver.hpp"
#include "LUSolver.hpp"
#include "CholeskySolver.hpp"

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
    EXPECT_DOUBLE_EQ(solver.GetTol(), 1e-05);
    EXPECT_EQ(solver.GetMaxIter(), 1000);

    // Constructor that only specifies w
    RichSolver solver_w(0.3);
    EXPECT_DOUBLE_EQ(solver_w.GetParameterW(), 0.3);
    EXPECT_DOUBLE_EQ(solver_w.GetTol(), 1e-05);
    EXPECT_EQ(solver_w.GetMaxIter(), 1000);
    // Constructor setting all parameters
    RichSolver solver_all(0.3, 1e-03, 20);
    EXPECT_DOUBLE_EQ(solver_all.GetParameterW(), 0.3);
    EXPECT_DOUBLE_EQ(solver_all.GetTol(), 1e-03);
    EXPECT_EQ(solver_all.GetMaxIter(),20);

    // Testing set and get
    solver.SetParameterW(0.1);
    EXPECT_DOUBLE_EQ(0.1, solver.GetParameterW());
}

TEST(LinSysSolverTest, CheckConstructorsAndSetGet) {
    CGSolver solver;
    EXPECT_DOUBLE_EQ(solver.GetTol(), 1e-05);
    EXPECT_EQ(solver.GetMaxIter(),1000);
    CGSolver solver_param(1e-02, 1000);
    EXPECT_DOUBLE_EQ(solver_param.GetTol(), 1e-02);
    EXPECT_EQ(solver_param.GetMaxIter(),1000);
    solver.SetMaxIter(1);
    EXPECT_EQ(1, solver.GetMaxIter());
    solver.SetTol(1e-4);
    EXPECT_DOUBLE_EQ(1e-4, solver.GetTol());
}

TEST(RichSolverTest, SmallExample) {
    // Set up data
    RichSolver solver;
    Matrix mat = solver.ReadMatrixFromFile(path_to_test_files+"small_Ex_mat.dat");
    Vector vec = asVector(solver.ReadMatrixFromFile(path_to_test_files+"small_Ex_vec.dat"));
    Vector ref_sol = asVector(solver.ReadMatrixFromFile(path_to_test_files+"small_Ex_sol.dat"));
    // Standard tolerance
    Vector calc_sol = solver.Solve(mat, vec);
    EXPECT_NEAR(ref_sol(0), calc_sol(0), solver.GetTol());
    EXPECT_NEAR(ref_sol(1), calc_sol(1), solver.GetTol());

    //Low tolerance
    solver.SetTol(1e-14);
    calc_sol = solver.Solve(mat, vec);
    EXPECT_NEAR(ref_sol(0), calc_sol(0), solver.GetTol());
    EXPECT_NEAR(ref_sol(1), calc_sol(1), solver.GetTol());
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
    EXPECT_NEAR(ref_sol(0), calc_sol(0), solver.GetTol());
    EXPECT_NEAR(ref_sol(1), calc_sol(1), solver.GetTol());

    //Low tolerance
    solver.SetTol(1e-14);
    calc_sol = solver.Solve(mat, vec);
    EXPECT_NEAR(ref_sol(0), calc_sol(0), solver.GetTol());
    EXPECT_NEAR(ref_sol(1), calc_sol(1), solver.GetTol());

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
        EXPECT_NEAR(ref_sol(iter), calc_sol(iter), solver.GetTol());
    }
    //Low tolerance
    solver.SetTol(1e-9);
    calc_sol = solver.Solve(mat, vec);
    for (int iter =0; iter < ref_sol.Size(); iter++ ) {
        EXPECT_NEAR(ref_sol(iter), calc_sol(iter), solver.GetTol());
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
        EXPECT_NEAR(ref_sol(iter), calc_sol(iter), solver.GetTol());
    }
    //Low tolerance
    solver.SetTol(1e-9);
    calc_sol = solver.Solve(mat, vec);
    for (int iter =0; iter < ref_sol.Size(); iter++ ) {
        EXPECT_NEAR(ref_sol(iter), calc_sol(iter), solver.GetTol());
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
        EXPECT_NEAR(ref_sol(iter), calc_sol(iter), solver.GetTol());
    }
    //Low tolerance
    solver.SetTol(1e-9);
    calc_sol = solver.Solve(mat, vec);
    for (int iter =0; iter < ref_sol.Size(); iter++ ) {
        EXPECT_NEAR(ref_sol(iter), calc_sol(iter), solver.GetTol());
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
    EXPECT_NEAR(ref_sol(0), calc_sol(0), solver.GetTol());
    EXPECT_NEAR(ref_sol(1), calc_sol(1), solver.GetTol());

    //Low tolerance
    solver.SetTol(1e-14);
    calc_sol = solver.Solve(mat, vec);
    EXPECT_NEAR(ref_sol(0), calc_sol(0), solver.GetTol());
    EXPECT_NEAR(ref_sol(1), calc_sol(1), solver.GetTol());

}

TEST(CGSolverTest, SmallExample) {
    // Set up data
    CGSolver solver;

    Matrix mat = solver.ReadMatrixFromFile(path_to_test_files+"Spd_Ex_size10_mat.dat");
    Vector vec = asVector(solver.ReadMatrixFromFile(path_to_test_files+"Spd_Ex_size10_vec.dat"));
    Vector ref_sol = asVector(solver.ReadMatrixFromFile(path_to_test_files+"Spd_Ex_size10_sol.dat"));

    // Standard tolerance
    Vector calc_sol = solver.Solve(mat, vec);
    for (int iter =0; iter < ref_sol.Size(); iter++ ) {
        EXPECT_NEAR(ref_sol(iter), calc_sol(iter), solver.GetTol());
    }
    //Low tolerance
    solver.SetTol(1e-8);
    calc_sol = solver.Solve(mat, vec);
    for (int iter =0; iter < ref_sol.Size(); iter++ ) {
        EXPECT_NEAR(ref_sol(iter), calc_sol(iter), solver.GetTol());
    }
}

TEST(CGSolverTest, BigExample) {
    // Set up data
    CGSolver solver;

    Matrix mat = solver.ReadMatrixFromFile(path_to_test_files+"Spd_Ex_size100_mat.dat");
    Vector vec = asVector(solver.ReadMatrixFromFile(path_to_test_files+"Spd_Ex_size100_vec.dat"));
    Vector ref_sol = asVector(solver.ReadMatrixFromFile(path_to_test_files+"Spd_Ex_size100_sol.dat"));

    // Standard tolerance
    Vector calc_sol = solver.Solve(mat, vec);
    for (int iter =0; iter < ref_sol.Size(); iter++ ) {
        EXPECT_NEAR(ref_sol(iter), calc_sol(iter), solver.GetTol());
    }
    //Low tolerance
    solver.SetTol(1e-09);
    calc_sol = solver.Solve(mat, vec);
    for (int iter =0; iter < ref_sol.Size(); iter++ ) {
        EXPECT_NEAR(ref_sol(iter), calc_sol(iter), solver.GetTol());
    }
}


TEST(CGSolverTest, BigExamplePrecondIdentity) {
    // Set up data
    CGSolver solver;

    Matrix mat = solver.ReadMatrixFromFile(path_to_test_files + "Spd_Ex_size100_mat.dat");
    Vector vec = asVector(solver.ReadMatrixFromFile(path_to_test_files + "Spd_Ex_size100_vec.dat"));
    Vector ref_sol = asVector(solver.ReadMatrixFromFile(path_to_test_files + "Spd_Ex_size100_sol.dat"));
    Matrix identity(mat.Rows(), mat.Cols());
    for (int index = 0; index < mat.Rows(); index++) {
        identity(index, index) = 1;
    }
    // Standard tolerance
    Vector calc_sol = solver.Solve(mat, vec, identity);
    for (int iter = 0; iter < ref_sol.Size(); iter++) {
        EXPECT_NEAR(ref_sol(iter), calc_sol(iter), solver.GetTol());
    }
    //Low tolerance
    solver.SetTol(1e-09);
    calc_sol = solver.Solve(mat, vec, identity);
    for (int iter = 0; iter < ref_sol.Size(); iter++) {
        EXPECT_NEAR(ref_sol(iter), calc_sol(iter), solver.GetTol());
    }
}


TEST(CGSolverTest, BigExamplePrecondDiag) {
    // Set up data
    CGSolver solver;

    Matrix mat = solver.ReadMatrixFromFile(path_to_test_files + "Spd_Ex_size100_mat.dat");
    Vector vec = asVector(solver.ReadMatrixFromFile(path_to_test_files + "Spd_Ex_size100_vec.dat"));
    Vector ref_sol = asVector(solver.ReadMatrixFromFile(path_to_test_files + "Spd_Ex_size100_sol.dat"));
    Matrix diag(mat.Rows(), mat.Cols());
    for (int index = 0; index < mat.Rows(); index++) {
        diag(index, index) = 1.0 / mat(index, index);
    }
    // Standard tolerance
    Vector calc_sol = solver.Solve(mat, vec, diag);
    for (int iter = 0; iter < ref_sol.Size(); iter++) {
        EXPECT_NEAR(ref_sol(iter), calc_sol(iter), solver.GetTol());
    }
    //Low tolerance
    solver.SetTol(1e-09);
    calc_sol = solver.Solve(mat, vec, diag);
    for (int iter = 0; iter < ref_sol.Size(); iter++) {
        EXPECT_NEAR(ref_sol(iter), calc_sol(iter), solver.GetTol());
    }
}


TEST(CGSolverTest, PrecondCreator) {
    // Set up data
    CGSolver solver;

    Matrix mat = solver.ReadMatrixFromFile(path_to_test_files + "Spd_Ex_size100_mat.dat");
    Vector vec = asVector(solver.ReadMatrixFromFile(path_to_test_files + "Spd_Ex_size100_vec.dat"));
    Vector ref_sol = asVector(solver.ReadMatrixFromFile(path_to_test_files + "Spd_Ex_size100_sol.dat"));

    Matrix precond = solver.CreateDiagPreconditioner(mat);
    // Standard tolerance
    Vector calc_sol = solver.Solve(mat, vec, precond);
    for (int iter = 0; iter < ref_sol.Size(); iter++) {
        EXPECT_NEAR(ref_sol(iter), calc_sol(iter), solver.GetTol());
    }
    //Low tolerance
    solver.SetTol(1e-09);
    calc_sol = solver.Solve(mat, vec, precond);
    for (int iter = 0; iter < ref_sol.Size(); iter++) {
        EXPECT_NEAR(ref_sol(iter), calc_sol(iter), solver.GetTol());
    }
}

TEST(LUSolverTest, SmallExample) {
    // Set up data
    LUSolver solver;
    Matrix mat = solver.ReadMatrixFromFile(path_to_test_files+"small_Ex_mat.dat");
    Vector vec = asVector(solver.ReadMatrixFromFile(path_to_test_files+"small_Ex_vec.dat"));
    Vector ref_sol = asVector(solver.ReadMatrixFromFile(path_to_test_files+"small_Ex_sol.dat"));
    // Check correction
    Vector calc_sol = solver.Solve(mat, vec);
    EXPECT_NEAR(ref_sol(0), calc_sol(0),1e-06);
    EXPECT_NEAR(ref_sol(1), calc_sol(1),1e-06);
}

TEST(LUSolverTest, BigExample) {
    // Set up data
    LUSolver solver;

    Matrix mat = solver.ReadMatrixFromFile(path_to_test_files+"Spd_Ex_size100_mat.dat");
    Vector vec = asVector(solver.ReadMatrixFromFile(path_to_test_files+"Spd_Ex_size100_vec.dat"));
    Vector ref_sol = asVector(solver.ReadMatrixFromFile(path_to_test_files+"Spd_Ex_size100_sol.dat"));

    // Standard tolerance
    Vector calc_sol = solver.Solve(mat, vec);
    for (int iter =0; iter < ref_sol.Size(); iter++ ) {
        EXPECT_NEAR(ref_sol(iter), calc_sol(iter), 1e-06);
    }
}



TEST(CholeskySolverTest, BigExample) {
    // Set up data
    CholeskySolver solver;
    Matrix mat = solver.ReadMatrixFromFile(path_to_test_files+"Spd_Ex_size100_mat.dat");
    Vector vec = asVector(solver.ReadMatrixFromFile(path_to_test_files+"Spd_Ex_size100_vec.dat"));
    Vector ref_sol = asVector(solver.ReadMatrixFromFile(path_to_test_files+"Spd_Ex_size100_sol.dat"));

    // Standard tolerance
    Vector calc_sol = solver.Solve(mat, vec);
    for (int iter =0; iter < ref_sol.Size(); iter++ ) {
        EXPECT_NEAR(ref_sol(iter), calc_sol(iter), 1e-06);
    }
}
