
#include "LinSysSolver.hpp"
#include <iostream>
#include <fstream>
#include <cmath>
#include "Exception.hpp"

Matrix LinSysSolver::ReadMatrixFromFile(std::string full_file_name){
    std::ifstream file(full_file_name);
    int rows;
    int cols;
    if( file.is_open()) {
        file >> rows;
        file >> cols;
        Matrix new_mat(rows,cols);
        for (int row = 0; row <rows; row++){
            for (int col = 0; col < cols; col++) {
                double val;
                file >> val;
                new_mat(row,col) = val;
            }
        }
        return new_mat;
    }
    else {
        std::cerr << "Could not open or read from file. Check path!";
        throw( Exception("File", "Could not open and read from file!") );
    }
}

Matrix LinSysSolver::ReadMatrixFromKeyboard(){
    int rows;
    int cols;
    std::cout << "Please enter the row size:\n";
    std::cin >> rows;
    std::cout << "Please enter the column size:\n";
    std::cin >> cols;
    Matrix new_mat(rows,cols);
    std::cout << "Please enter the element by column:\n";
    for (int row = 0; row < rows; row++){
        for (int col =0; col <cols; col++){
            double val;
            std::cin >> val;
            new_mat(row,col) = val;
        }
    }
    return new_mat;
};



int LinSysSolver::WriteMatrixToFile(std::string full_file_name, Matrix& mat){
    std::ofstream file(full_file_name);
    int num_rows = mat.Rows();
    int numCols = mat.Cols();

    if (file.is_open()) {
        file << num_rows << " " << numCols << "\n";
        file.setf(std::ios::scientific);
        file.setf(std::ios::showpos);
        file.precision(13);
        for( int row = 0; row < num_rows; row++){
            for( int col = 0; col <numCols; col++){
                file << mat(row,col) << " ";
            }
            file << "\n";

        }
        file.close();
        return 0;
    }
    else {
        std::cerr << "Cannot open the file and thus not write to it. \n";
        throw( Exception("File", "Could not open and write to file!") );
    }

}

int LinSysSolver::CheckSolveInput(const Matrix &A, const Vector &b) {
    if( A.Cols() != A.Rows()) {
        throw Exception("LinSysSolver", "Input matrix must be square!");
    }
    if(b.Rows() != A.Cols()) {
        throw Exception("LinSysSolver", "Dimension mismatch for linear system Ax=b.");
    }
    return 0;
}

int LinSysSolver::CheckSymmetry(const Matrix &A) {
    if (A.Rows() != A.Cols()) {
        throw Exception("NonSquare", "Input matrix is not square and thus not symmetric.");
    }
    // In this part of the code, A is clearly square.
    int size = A.Cols();
    for (int row = 0; row < size; row++) {
        for (int col = 0; col < row; col++) {
            if (std::abs(A.at(row, col) - A.at(col, row)) > 1e-14) {
                throw Exception("NonSymmetric", "Input matrix is not symmetric, which is a necessary requirement.");
            }
        }
    }
    return 0;
}

