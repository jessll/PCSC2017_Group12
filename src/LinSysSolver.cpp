
#include "LinSysSolver.hpp"
#include <iostream>
#include <fstream>

Matrix LinSysSolver::ReadMatrixFromFile(std::string path_to_file){

    ;
}

int LinSysSolver::WriteMatrixToFile(std::string path_to_file, Matrix& mat){
    auto full_file_name = path_to_file+ ".mat";
    std::ofstream file(full_file_name);
    int numRows = mat.Rows();
    int numCols = mat.Cols();

    if (file.is_open()) {
        file << numRows << " " << numCols << "\n";
        for( int row = 0; row< numRows; row++){
            for( int col = 0; col <numCols; col++){
                file << mat(row,col) << " ";
            }
            file << "\n";

        }
        file.close();
        return 0;
    }
    else {
        std::cout << "Cannot open the file and thus not write to it. This should be an exception \n";
        return 1;
    }

}

