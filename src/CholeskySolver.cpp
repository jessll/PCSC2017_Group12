#include <cassert>
#include <iostream>
#include <cmath>
#include "CholeskySolver.hpp"
#include "Vector.hpp"
#include "Matrix.hpp"
#include "Exception.hpp"
//Constructor
CholeskySolver::CholeskySolver()
{}

//method for solving linear system
Vector CholeskySolver::Solve(const Matrix &A, const Vector &b) {
    // check the size validation
    try {
        this->CheckSolveInput(A, b);
    }
    catch (const Exception& error) {
        error.PrintDebug();
        throw Exception("InvalidInput", "Bad input into 'Solve' function.");
    }
    // check about the symmetric of input matrix
    try{
        CheckSymmetry(A);
    }
    catch (const Exception& error) {
        error.PrintDebug();
        throw Exception("InvalidInput", "Bad input into 'Solve' function.");
    }

    // linear system size
    int n = b.Size();
    double sum3 = 0.0;
    // initialize of a copy of A
    Matrix AA(A);
    // Initialize of lower triangular matrix
    Matrix L(A.Rows(),A.Cols());
    // Initialize of upper triangular matrix
    Matrix LT(A.Rows(),A.Cols());
    // Create matrix S for checking whether A is SPD
    Matrix S(A.Rows(),A.Cols());
    // initialize of a copy of b
    Vector x(b);


    L(0,0) = sqrt(AA(0,0));

    // calculate first column of L
    for (int i =1; i< n; i++)
        L(i,0) = AA(i,0) / L(0,0);

    // calculate the element of L
    for (int j = 1; j < (n-1); j++) {
        double sum1 = 0;
        for (int k = 0; k < j; k++) {
            sum1 += pow(L(j, k), 2);
        }
        try{
            // when A is not SPD, here may produce negative value, check it and throw exception
            if(AA(j, j) - sum1 < 0){
                throw Exception("Matrix", "Input matrix is not symmetrical positive definition");
            }
        }
        catch (const Exception& error) {
            error.PrintDebug();
            throw Exception("InvalidInput", "Bad input into 'Solve' function.");
        }
        L(j, j) = sqrt(AA(j, j) - sum1);


        for (int i = j+1; i < n; i++){
            double sum2 = 0;
            for (int k = 0; k < j; k++){
                sum2 += L(i,k) * L(j,k);
            }
            L(i, j) = (AA(i, j) - sum2)/L(j,j);
        }

    }

    for (int k = 0; k < (n-1); k++)
        sum3 += pow(L(n-1, k),2);

    L(n-1,n-1) = sqrt(AA(n-1,n-1)-sum3);

    // LT is the transpose of L
    LT = L.transpose();


    // check whether matrix is positive definition: when it is SPD, the multiplication of L and LT will equal to A
    // otherwise throw the exception
    S = L * LT;
    for (int i = 0; i < n*n; i++) {
        try {
            if (std::abs(S(i) - AA(i)) > 1e-06) {
                throw (Exception("Matrix", "Matrix is not positive definite"));
            }
        }
        catch (const Exception& error) {
            error.PrintDebug();
            throw Exception("InvalidInput", "Bad input into 'Solve' function.");
        }
    }


    //solve linear system by forward substitution method

    for(int i = 0; i < n; i++){
        for (int j = 0; j < i; j++) {
            x(i) -= L(i, j) * x(j);
        }
        x(i) = x(i)/L(i, i);
    }

    for(int i = n-1; i>=0; i--){
        for (int k = i+1; k<n; k++){
            x(i) -= LT(i,k) * x(k);
        }
        x(i) /= LT(i,i);
    }
    return x;
}