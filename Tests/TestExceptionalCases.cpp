
#include <Exception.hpp>
#include <RichSolver.hpp>
#include <CGSolver.hpp>
#include <JacSolver.hpp>
#include <GSSolver.hpp>
#include "LUSolver.hpp"
#include "CholeskySolver.hpp"
#include "gtest/gtest.h"


TEST(MatrixTest, checkIllegalDimensions) {
    // Test various ways of creating matrices in a bad way
    EXPECT_THROW(Matrix(-5,3), Exception);
    EXPECT_THROW(Matrix(-5,-3), Exception);
    EXPECT_THROW(Matrix(0,3), Exception);
    EXPECT_THROW(Matrix(3,0), Exception);
}

TEST(MatrixTest, IndexOutOfBounds) {
    // Test various ways of accessing indices in a bad way.
    Matrix test_mat(2,3);
    EXPECT_THROW(test_mat(-1), Exception);
    EXPECT_THROW(test_mat(6), Exception);
    // Check all variants in which index can be out of bounds.
    EXPECT_THROW(test_mat(-1,2), Exception);
    EXPECT_THROW(test_mat(0,3), Exception);
    EXPECT_THROW(test_mat(0,-1), Exception);
    EXPECT_THROW(test_mat(2,0), Exception);

    EXPECT_THROW(test_mat.at(-1), Exception);
    EXPECT_THROW(test_mat.at(6), Exception);
    // Check all variants in which index can be out of bounds.
    EXPECT_THROW(test_mat.at(-1,2), Exception);
    EXPECT_THROW(test_mat.at(0,3), Exception);
    EXPECT_THROW(test_mat.at(0,-1), Exception);
    EXPECT_THROW(test_mat.at(2,0), Exception);
}


TEST(MatrixTest, IncompatibleDimensions) {
    // Test various ways of performing illegal operations
    Matrix test_mat(2,3);
    Matrix other_mat(1,2);
    EXPECT_THROW(test_mat+other_mat, Exception);
    EXPECT_THROW(test_mat-other_mat, Exception);
    EXPECT_THROW(test_mat =other_mat,  Exception);
    EXPECT_THROW(test_mat*other_mat,  Exception);
}


TEST(VectorTest, IncompatibleDimensions) {
    // Test various ways of performing illegal operations
    Vector test_vec(2);
    Vector other_vec(3);
    Matrix test_mat(2,3);
    EXPECT_THROW(test_vec+other_vec, Exception);
    EXPECT_THROW(test_vec-other_vec,  Exception);
    EXPECT_THROW(test_vec =other_vec,  Exception);
    EXPECT_THROW(test_mat*test_vec,  Exception);
    EXPECT_THROW(other_vec.transpose()*test_mat, Exception);
    //Dot product
    EXPECT_THROW(dotProduct(test_vec, other_vec), Exception);
    //Conversion
    EXPECT_THROW(asVector(test_mat), Exception);
}

TEST(VectorTest, InvalidNorm){
    Vector test_vec(2);
    EXPECT_THROW(test_vec.CalculateNorm(0), Exception);
    EXPECT_THROW(test_vec.CalculateNorm(-2), Exception);
}


TEST(LinSysSolverTest, InvalidPaths) {
    std::string wrong_path = "nonsense/nonsense";
    Matrix test_mat(2, 3);
    RichSolver solver;
    EXPECT_THROW(solver.WriteMatrixToFile(wrong_path, test_mat), Exception);
    EXPECT_THROW(solver.ReadMatrixFromFile(wrong_path), Exception);
}


TEST(IterativeSolverTest, BadParameters) {
    double bad_tol = 0;
    double even_worse_tol = -3;
    int bad_iter = -3;
    RichSolver solver;
    EXPECT_THROW(solver.SetMaxIter(bad_iter), Exception);
    EXPECT_THROW(solver.SetTol(bad_tol), Exception);
    EXPECT_THROW(solver.SetTol(even_worse_tol), Exception);
}

TEST(RichSolverTest, BadParameters) {
    double w = -3;
    RichSolver solver;
    EXPECT_THROW(solver.SetParameterW(w), Exception);
    EXPECT_THROW(RichSolver(0), Exception);
    EXPECT_THROW(RichSolver(-2), Exception);
}

TEST(RichSolverTest, BadLinSys) {
    RichSolver solver;
    Vector test_vec(2);
    Matrix test_mat(3, 3);
    for (int index = 0; index < 3; index++) {
        test_mat(index, index) = 1;
    }
    Matrix test_mat_2(2, 3);
    // Non-matching dimensions
    EXPECT_THROW(solver.Solve(test_mat, test_vec), Exception);
    // Nonsquare matrix
    EXPECT_THROW(solver.Solve(test_mat_2, test_vec), Exception);
}

TEST(CGSolverTest, BadLinSys) {
    CGSolver solver;
    Vector test_vec(2);
    Matrix test_mat(3, 3);
    for (int index = 0; index < 3; index++) {
        test_mat(index, index) = 1;
    }
    Matrix test_mat_2(2, 3);
    // Non-matching dimensions
    EXPECT_THROW(solver.Solve(test_mat, test_vec), Exception);
    // Nonsquare matrix
    EXPECT_THROW(solver.Solve(test_mat_2, test_vec), Exception);
}

TEST(JacSolverTest, BadLinSys) {
    JacSolver solver;
    Vector test_vec(2);
    Matrix test_mat(3, 3);
    for (int index = 0; index < 3; index++) {
        test_mat(index, index) = 1;
    }
    Matrix test_mat_2(2, 3);
    // Non-matching dimensions
    EXPECT_THROW(solver.Solve(test_mat, test_vec), Exception);
    // Nonsquare matrix
    EXPECT_THROW(solver.Solve(test_mat_2, test_vec), Exception);
}

TEST(GSSolverTest, BadLinSys) {
    GSSolver solver;
    Vector test_vec(2);
    Matrix test_mat(3, 3);
    for (int index = 0; index < 3; index++) {
        test_mat(index, index) = 1;
    }
    Matrix test_mat_2(2, 3);
    // Non-matching dimensions
    EXPECT_THROW(solver.Solve(test_mat, test_vec), Exception);
    // Nonsquare matrix
    EXPECT_THROW(solver.Solve(test_mat_2, test_vec), Exception);
}


TEST(GSSolverTest, ZeroOnDiag) {
    GSSolver solver;
    Vector test_vec(3);
    test_vec(0) = 2;
    Matrix test_mat(3, 3);
    for (int index = 0; index < 3; index++) {
        test_mat(index, index) = 1;
    }
    // Valid diagonal
    EXPECT_NO_THROW(solver.Solve(test_mat, test_vec));
    // Invalid diagonal
    test_mat(0, 0) = 0;
    EXPECT_THROW(solver.Solve(test_mat, test_vec), Exception);
}


TEST(JacSolverTest, ZeroOnDiag) {
    JacSolver solver;
    Vector test_vec(3);
    test_vec(0) = 2;
    Matrix test_mat(3, 3);
    for (int index = 0; index < 3; index++) {
        test_mat(index, index) = 1;
    }
    // Valid diagonal
    EXPECT_NO_THROW(solver.Solve(test_mat, test_vec));
    // Invalid diagonal
    test_mat(0, 0) = 0;
    EXPECT_THROW(solver.Solve(test_mat, test_vec), Exception);
}

TEST(CGSolverTest, NonSymmetricInput) {
    CGSolver solver;
    Vector test_vec(3);
    Matrix test_mat(3, 3);
    for (int index = 0; index < 3; index++) {
        test_mat(index, index) = 1;
    }
    EXPECT_NO_THROW(solver.Solve(test_mat, test_vec));
    test_mat(0, 1) = 1;
    EXPECT_THROW(solver.Solve(test_mat, test_vec), Exception);
}

TEST(CGSolverTest, InvalidPrecond) {
    CGSolver solver;
    Vector test_vec(3);
    Matrix test_mat(3, 3);
    for (int index = 0; index < 3; index++) {
        test_mat(index, index) = 1;
    }
    Matrix precond(test_mat);
    EXPECT_NO_THROW(solver.Solve(test_mat, test_vec, precond));
    // Non-symmetric preconditioner
    precond(0, 1) = 1;
    EXPECT_THROW(solver.Solve(test_mat, test_vec, precond), Exception);
    // Preconditioner of wrong dimension
    Matrix precond_dim(4, 4);
    EXPECT_THROW(solver.Solve(test_mat, test_vec, precond_dim), Exception);
    // Try to create preconditioner from non-square matrix
    Matrix mat_bad_dim(3, 4);
    for (int index = 0; index < 3; index++) {
        test_mat(index, index) = 1;
    }
    EXPECT_THROW(solver.CreateDiagPreconditioner(mat_bad_dim), Exception);
    // try to create preconditioner from matrix with zeros on diagonal
    Matrix mat_bad_vals(3, 3);
    EXPECT_THROW(solver.CreateDiagPreconditioner(mat_bad_vals), Exception);
}

TEST(LUSolverTest, BadLinSys) {
    LUSolver solver;
    Vector test_vec(2);
    Matrix test_mat(3, 3);
    for (int index = 0; index < 3; index++) {
        test_mat(index, index) = 1;
    }
    Matrix test_mat_2(2, 3);
    // Non-matching dimensions
    EXPECT_THROW(solver.Solve(test_mat, test_vec), Exception);
    // Nonsquare matrix
    EXPECT_THROW(solver.Solve(test_mat_2, test_vec), Exception);
}

TEST(LUSolverTest, sigularcheck) {
    LUSolver solver;
    Vector test_vec(3);
    test_vec(0) = 3;
    Matrix test_mat(3, 3);
    for (int index = 0; index < 3; index++) {
        test_mat(index, index) = 1;
    }
    // Valid
    EXPECT_NO_THROW(solver.Solve(test_mat, test_vec));
    // Invalid
    test_mat(0, 0) = 0;
    EXPECT_THROW(solver.Solve(test_mat, test_vec), Exception);
}


TEST(CholeskySolverTest, BadLinSys) {
    CholeskySolver solver;
    Vector test_vec(2);
    Matrix test_mat(3, 3);
    for (int index = 0; index < 3; index++) {
        test_mat(index, index) = 1;
    }
    Matrix test_mat_2(2, 3);
    // Non-matching dimensions
    EXPECT_THROW(solver.Solve(test_mat, test_vec), Exception);
    // Nonsquare matrix
    EXPECT_THROW(solver.Solve(test_mat_2, test_vec), Exception);
}


TEST(CholeskySolverTest, SPDcheck) {
    CholeskySolver solver;
    Vector test_vec(3);
    test_vec(0) = 3;
    Matrix test_mat(3, 3);
    for (int index = 0; index < 3; index++) {
        test_mat(index, index) = 1;
    }
    // Valid SPD
    EXPECT_NO_THROW(solver.Solve(test_mat, test_vec));
    // Invalid SPD
    test_mat(0, 0) = 0;
    test_mat(0, 2) = 4;
    EXPECT_THROW(solver.Solve(test_mat, test_vec), Exception);
}




