#include <cmath>
#include <cassert>
#include <iostream>

#include "LUSolver.hpp"
#include "Matrix.hpp"
#include "Vector.hpp"
#include "Exception.hpp"

LUSolver::LUSolver()
{}

Vector LUSolver::Solve(const Matrix &A, const Vector &b) {
    if (A.Cols() != A.Rows() || b.Rows() != A.Cols()){
        throw (Exception("Size","Matrix or Vector size error"));
    };


    // Initialize data.
    int n = b.Size();
    Vector x(n);
    Vector t(n);
    Vector bb(b);
    Matrix LU(A);
    Vector P(n);

    for (int i = 0; i < n; i++)
        P(i) = i;

    // loop over diagonal pivots
    for (int i = 0; i < n - 1; i++) {

        // find the largest pivot
        int Pivot = i;
        for (int k = i + 1; k < n; k++)
            if (fabs(LU(k,i)) > fabs(LU(i,i)))
                Pivot = k;

        // check for singularity
        if (0 == LU(Pivot,i)) {
            throw (Exception("Matrix","Matrix is singular"));
        }

        // swap rows
        if (Pivot != i) {
            int temp = P(Pivot);
            P(Pivot) = P(i);
            P(i) = temp;

            for (int k = i; k < n; k++){
                double tem = LU(i,k);
                LU(i,k) = LU(Pivot,k);
                LU(Pivot,k) = tem;
            }
        }

        // Gaussian elimination
        for (int k = i + 1; k < n; k++) {
            // lower triangle factor is L
            LU(k,i) /= LU(i,i);
            for (int j = i + 1; j < n; j++)
                LU(k,j) = LU(k,j) - LU(i,j) * LU(k,i);
        }
    }

    //solve linear system by forward substitution method

    for(int i = 0; i < n; i++)
        x(i) = bb(P(i));

    for(int i = 1; i < n; i++){
        for (int j = 0; j < i; j++) {
            x(i) -= LU(i, j) * x(j);
        }
    }

    for(int i = n-1; i>=0; i--){
        for (int k = i+1; k<n; k++){
            x(i) -= LU(i,k) * x(k);
        }
        x(i) /= LU(i,i);
    }

    //permute x to get result
    for(int i = 0; i < n; i++){
        int index = P(i);
        t(index) = x(i);
    }

    return t;

}





