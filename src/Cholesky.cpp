#include <cassert>
#include <cmath>
#include "Cholesky.h"

Vector Cholesky::Solve(const Matrix &A, const Vector &b) {
    assert(A.Cols() == A.Rows());
    assert(b.Cols() == A.Rows());
    

    int n = b.Size();
    double sum1 = 0.0;
    double sum2 = 0.0;
    double sum3 = 0.0;

    Matrix AA(A);
    Matrix Zero(A);
    Matrix L(A.Rows(),A.Cols());
    Matrix LT(A.Rows(),A.Cols());
    Matrix S(A.Rows(),A.Cols());
    Vector x(n);
    Vector bb(n);


    L(0,0) = sqrt(AA(0,0));

    for (int i =1; i< n; i++)
        L(i,0) = AA(i,0) / L(0,0);

    for (int j = 1; j < (n-1); j++) {
        for (int k = 0; k < j; k++) {
            sum1 += pow(L(j, k), 2);
        }
        L(j, j) = sqrt(AA(j, j) - sum1);


        for (int i = j+1; i < n; i++){
            for (int k = 0; k < j; k++){
                sum2 += L(i,k) * L(j,k);
            }
            L(i,j) = (AA(i,j) - sum2)/L(j,j);
        }

    }

    for (int k = 0; k < (n-1); k++)
        sum3 += pow(L(n-1, k),2);

    L(n-1,n-1) = sqrt(AA(n-1,n-1)-sum3);

    LT = L.transpose();

    //check whether matrix is positive definition
    S = L * LT;
    for (int i = 0; i < n*n; i++)
        assert (S(i) == AA(i));


    //solve linear system by forward subtitution method
    for(int i = 0; i < n; i++)
        x(i) = bb(i);

    for(int i = 1; i < n; i++){
        for (int j = 0; j < i; j++) {
            x(i) -= L(i, j) * x(j);
        }
        x(i) /= L(i, i);
    }

    for(int i = n-1; i>=0; i--){
        for (int k = i+1; k<n; k++){
            x(i) -= LT(i,k) * x(k);
        }
        x(i) /= LT(i,i);
    }
    return x;
}