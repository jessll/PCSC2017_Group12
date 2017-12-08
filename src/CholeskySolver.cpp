#include <cassert>
#include <iostream>
#include <cmath>
#include "CholeskySolver.hpp"
#include "Vector.hpp"
#include "Matrix.hpp"
#include "Exception.hpp"

CholeskySolver::CholeskySolver()
{}

Vector CholeskySolver::Solve(const Matrix &A, const Vector &b) {
    if (A.Cols() != A.Rows() || b.Rows() != A.Cols()){
        throw (Exception("Size","Matrix or Vector size error"));
    };


    int n = b.Size();
    double sum3 = 0.0;

    Matrix AA(A);
    Matrix L(A.Rows(),A.Cols());
    Matrix LT(A.Rows(),A.Cols());
    Matrix S(A.Rows(),A.Cols());
    Vector x(b);


    L(0,0) = sqrt(AA(0,0));

    for (int i =1; i< n; i++)
        L(i,0) = AA(i,0) / L(0,0);

    for (int j = 1; j < (n-1); j++) {
        double sum1 = 0;
        for (int k = 0; k < j; k++) {
            sum1 += pow(L(j, k), 2);
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


    LT = L.transpose();


    //check whether matrix is positive definition
    S = L * LT;
    for (int i = 0; i < n*n; i++) {
        if (S(i) - AA(i) > 1e-03) {
            throw (Exception("Matrix", "Matrix is not positive definite"));
        }
    }
    for (int i = 0; i < n*n; i++){
        if (S(i) - AA(i) > 1e-03){
            throw (Exception("Matrix","Matrix is not positive definition"));}}

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