#pragma once

#include "_MathUtilities.h"

namespace DM4th
{
    NDArray<number> LU(NDArray<number> matrix, NDArray<number> rightPart)
    {
        DM4thAssert(matrix.shapeSize()==2 && matrix.data_size()==(rightPart.size()*rightPart.size()));

        int n = rightPart.size();

        NDArray<number> lu = zeros<number>(n,n);
        number sum = 0;
        for (int i = 0; i < n; i++)
        {
            for (int j = i; j < n; j++)
            {
                sum = 0;
                for (int k = 0; k < i; k++)
                {
                    sum += lu(i, k) * lu(k, j);
                }           
                lu(i, j) = matrix(i, j) - sum;
            }
            for (int j = i + 1; j < n; j++)
            {
                sum = 0;
                for (int k = 0; k < i; k++)
                    sum += lu(j, k) * lu(k, i);
                lu(j, i) = (1 / lu(i, i)) * (matrix(j, i) - sum);
            }
        }   
    
        // lu = L+U-I

        // find solution of Ly = b
        NDArray<number> y = zeros<number>(n);

        for (int i = 0; i < n; i++)
        {
            sum = 0;
            for (int k = 0; k < i; k++)
            {
                sum += lu(i, k) * y(k);
            }
            y(i) = rightPart(i) - sum;
        }

        // find solution of Ux = y
        NDArray<number> x = zeros<number>(n);

        for (int i = n - 1; i >= 0; i--)
        {
            sum = 0;
            for (int k = i + 1; k < n; k++)
                sum += lu(i, k) * x(k);
            x(i) = (1 / lu(i, i)) * (y(i) - sum);
        }
        return x;
    }

    // NDArray<number> Inv(NDArray<number> A, NDArray<number> P)
    // {
        
    //     DM4thAssert(A.shapeSize()==2, A.shape(0)==A.shape(1));
    //     NDArray<number> IA = zeros<number>(A.shape(0), A.shape(1));
    //     int n = A.size();
    //     for (int j = 0; j < n; j++) {
    //         for (int i = 0; i < n; i++) {
    //             if (P(i) == j) 
    //                 IA(i,j) = 1.0;
    //             else
    //                 IA(i,j) = 0.0;

    //             for (int k = 0; k < i; k++)
    //                 IA(i,j) -= A(i,k) * IA(k,j);
    //         }

    //         for (int i = n - 1; i >= 0; i--) {
    //             for (int k = i + 1; k < n; k++)
    //                 IA(i,j) -= A(i,k) * IA(k,j);

    //             IA(i,j) = IA(i,j) / A(i,i);
    //         }
    //     }
    //     return IA;
    // }
}