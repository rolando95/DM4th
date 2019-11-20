#pragma once

#include "MathUtilities.h"

namespace DM4th
{
    inline NDArray<number> LU(const NDArray<number> &matrix, const NDArray<number> &rightPart)
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


    inline NDArray<number> dijkstra(const NDArray<number> &matrix)
    {
        DM4thAssert(matrix.shapeSize()==2 && matrix.shape(0)==matrix.shape(1));

        NDArray<number> before; 
        NDArray<number> result = matrix.getCopy();

        for(int k=0; k<matrix.size(); ++k)
        {
            before = result.getCopy();

            #if defined DM4thOmpFor
                #pragma omp parallel for shared(matrix)
            #endif

            for(int i=0; i<matrix.size(); ++i)
            {
                for(int j=0; j<matrix.size(); ++j)
                {
                    result(i,j) = _min(before(i,j),before(i,k) + before(k,j));
                }
            }
        }
        return result;
    }

    inline NDArray<number> warshall(const NDArray<number> &matrix)
    {
        DM4thAssert(matrix.shapeSize()==2 && matrix.shape(0)==matrix.shape(1));

        NDArray<number> before; 
        NDArray<number> result = matrix.getCopy();

        for(int k=0; k<matrix.size(); ++k)
        {
            before = result.getCopy();

            #if defined DM4thOmpFor
                #pragma omp parallel for shared(matrix)
            #endif 

            for(int i=0; i<matrix.size(); ++i)
            {
                for(int j=0; j<matrix.size(); ++j)
                {
                    result(i,j) = (before(i,j) || (before(i,k) && before(k,j)))? 1:0;
                }
            }
        }
        return result;
    }
}