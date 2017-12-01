//
// Example for a googletest
//
#include "gtest/gtest.h"
#include "../src/Matrix.hpp"
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






int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}