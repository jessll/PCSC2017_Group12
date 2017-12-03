//
// Example for a googletest
//
#include "gtest/gtest.h"
#include "../src/Matrix.hpp"
#include "../src/Vector.hpp"
int num_rows = 3;
int num_cols = 4;
double number_1 = 3.0;
double number_2 = 1.5;
double number_3= 4.3;
TEST(MatrixTest, CreatesMatrixValid) {
    Matrix test_mat(num_rows, num_cols);
    EXPECT_EQ(test_mat.Cols(), num_cols);
    EXPECT_EQ(test_mat.Rows(), num_rows);
    EXPECT_DOUBLE_EQ(test_mat(0,0),0.0);
}

TEST(MatrixTest, CanAssignReadValues) {
    Matrix test_mat(num_rows, num_cols);
    test_mat(0,2)= number_1;
    EXPECT_DOUBLE_EQ(test_mat(0,2),number_1);
    EXPECT_DOUBLE_EQ(test_mat(2), number_1);
    EXPECT_DOUBLE_EQ(test_mat.at(2), number_1);
}

TEST(MatrixTest, CopyConstructorWorks){
    Matrix test_mat(num_rows, num_cols);
    test_mat(0,2)= number_1;
    Matrix new_mat(test_mat);
    EXPECT_DOUBLE_EQ(new_mat(0,2),number_1);
}

TEST(MatrixTest, BasicOperatorsOverload){
    Matrix test_mat(num_rows, num_cols);
    test_mat(0,2)= number_1;
    Matrix other_mat(num_rows, num_cols);
    //Assignment operator
    other_mat = test_mat;
    EXPECT_DOUBLE_EQ(other_mat(0,2),number_1);

    // unary - operator
    other_mat = -test_mat;
    EXPECT_DOUBLE_EQ(other_mat(0,2),-number_1);

    // unary + operator
    other_mat = +test_mat;
    EXPECT_DOUBLE_EQ(other_mat(0,2),number_1);

    // binary + - operators
    Matrix third_mat(num_rows, num_cols);
    third_mat(0,2)= number_2;
    third_mat(0,0)= -number_2;
    other_mat = test_mat+third_mat;
    EXPECT_DOUBLE_EQ(other_mat(0,2),number_1+number_2);
    EXPECT_DOUBLE_EQ(other_mat(0,0),-number_2);
    EXPECT_DOUBLE_EQ(other_mat(0,1), 0.0);

    other_mat = test_mat-third_mat;
    EXPECT_DOUBLE_EQ(other_mat(0,2),number_1-number_2);
    EXPECT_DOUBLE_EQ(other_mat(0,0),number_2);
    EXPECT_DOUBLE_EQ(other_mat(0,1), 0.0);

    // unary * operator
    other_mat = test_mat-third_mat*3.0;
    EXPECT_DOUBLE_EQ(other_mat(0,2),number_1-3*number_2);

}

TEST(MatrixTest, CheckMatMult){
    // Create two matrices
    Matrix test_mat(num_rows, num_cols);
    test_mat(0,0) =  number_3;
    test_mat(0,2) = number_1;
    test_mat(1,2) = number_2;


    Matrix other_mat(num_cols, num_rows);
    other_mat(0,2)= 1.0;
    other_mat(2,0)= number_1;
    other_mat(2,2) =  number_3;

    // Do multiplication and check for current dimension and values
    Matrix res_mat= test_mat*other_mat;
    EXPECT_EQ(res_mat.Rows(), num_rows);
    EXPECT_EQ(res_mat.Cols(), num_rows);
    EXPECT_DOUBLE_EQ(res_mat(0,0),number_1*number_1);
    EXPECT_DOUBLE_EQ(res_mat(0,2),number_3+number_3*number_1);
    EXPECT_DOUBLE_EQ(res_mat(1,0), number_1*number_2);
    EXPECT_DOUBLE_EQ(res_mat(2,2), 0.0);
}


TEST(MatrixTest, CheckTranspose){
    // Create two matrices
    Matrix test_mat(num_rows, num_cols);
    test_mat(0,0) =  number_3;
    test_mat(0,2) = number_1;
    test_mat(1,2) = number_2;

    //Assign to matrix of correct dimension
    Matrix other_mat(num_cols, num_rows);
    other_mat = test_mat.transpose();
    EXPECT_DOUBLE_EQ(other_mat(0,0), number_3);
    EXPECT_DOUBLE_EQ(other_mat(2,0), number_1);
    EXPECT_DOUBLE_EQ(other_mat(2,1), number_2);

    //Assign to new matrix
    Matrix direct_mat= test_mat.transpose();
    EXPECT_EQ(direct_mat.Rows(), num_cols);
    EXPECT_EQ(direct_mat.Cols(), num_rows);
    EXPECT_DOUBLE_EQ(direct_mat(2,1), number_2);
}

TEST(VectorTest, CheckConstructors){
    Vector test_vec(num_cols);
    EXPECT_EQ(test_vec.Cols(), 1);
    EXPECT_EQ(test_vec.Rows(), num_cols);
    EXPECT_EQ(test_vec.Size(), num_cols);
    EXPECT_EQ(length(test_vec), num_cols);

    Vector test_vec_col(num_cols, true);
    EXPECT_EQ(test_vec.Cols(), 1);
    EXPECT_EQ(test_vec.Rows(), num_cols);
    EXPECT_EQ(test_vec.Size(), num_cols);

    Vector test_vec_row(num_cols, false);
    EXPECT_EQ(test_vec_row.Cols(), num_cols);
    EXPECT_EQ(test_vec_row.Rows(), 1);
    EXPECT_EQ(test_vec_row.Size(), num_cols);

    Vector test_copy(test_vec_row);
    EXPECT_EQ(test_vec_row.Cols(), num_cols);
    EXPECT_EQ(test_vec_row.Rows(), 1);
    EXPECT_EQ(test_vec_row.Size(), num_cols);
}

TEST(VectorTest, CheckTranspose){
    Vector test_vec(num_cols);
    test_vec(2)= 3.0;
    // transpose as matrix
    Matrix transp_as_mat = test_vec.transpose();
    EXPECT_DOUBLE_EQ(transp_as_mat(2), test_vec(2));
    EXPECT_FALSE((asVector(transp_as_mat)).isColumn());
    // transpose as vector
    Vector transp_as_vec = test_vec.vec_transpose();
    EXPECT_DOUBLE_EQ(transp_as_vec(2), test_vec(2));

    //check for dimensions
    EXPECT_FALSE(transp_as_vec.isColumn());
    EXPECT_TRUE(test_vec.isColumn());
}

TEST(VectorTest, Checkp_norm) {
    Vector test_vec(num_cols);
    test_vec(0)= number_1;
    test_vec(1) = number_2;
    test_vec(2) = number_3;
    double expected_result_1 =number_1+number_2+number_3;
    double expected_result_2 = sqrt(number_1*number_1+number_2*number_2+number_3*number_3);
    double norm_2 = test_vec.CalculateNorm();
    EXPECT_DOUBLE_EQ(norm_2, expected_result_2);
    norm_2 = test_vec.CalculateNorm(2);
    double norm_1 = test_vec.CalculateNorm(1);
    EXPECT_DOUBLE_EQ(norm_2, expected_result_2);
    EXPECT_DOUBLE_EQ(norm_1, expected_result_1);
}




int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}