
#include "LinSysSolver.hpp"
#include <iostream>
#include <fstream>
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
        std::cout << "Could not open or read from file. Check path!";
        throw( Exception("File", "Could not open and read from file!") );
    }
}

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
        std::cout << "Cannot open the file and thus not write to it. \n";
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

