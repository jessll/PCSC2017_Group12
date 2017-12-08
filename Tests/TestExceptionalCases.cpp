
#include <Exception.hpp>
#include "gtest/gtest.h"
#include "Matrix.hpp"
#include "Vector.hpp"


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




