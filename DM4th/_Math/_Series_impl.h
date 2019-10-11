#pragma once 

#include "_Series.h"
#include "_Differential.h"

namespace DM4th
{

inline number fibonacci(number n){
    return (pow(phi,n) - cos(n*pi)*pow(phi,-n))/std::sqrt(5);
}

inline number fibonacci2(number iter){
    int n = abs(round(iter)).real();
    int a=0, b=1, c;

    for(int j=0; j<n; ++j)
    {
        c = b + a;
        a = b;
        b = c;
    }
    return number(a,0);
}


inline number factorial(const number n){
    return gamma(n+1);
}

inline number factorial2(const number iter)
{
    int n = abs(round(iter)).real();
    int x = 1;

    #if defined DM4thOmpFor
        #pragma omp parallel for DM4thReductionMult(x)
    #endif
    for(auto i=1; i<=n; ++i){
        x *= i;
    }

    return number(x,0);
}

inline number sumatory(Function f, NDArray<number> v, const number increment){
    number x=0;
    int iter = increment.real();
    DM4thAssert(iter>0);

    #if defined DM4thOmpFor
        #pragma omp parallel for DM4thReductionSum(x)
    #endif
    for(int j=0; j<v.shape(0); j+=iter){
        x += f(v(j));
    }
    return x;
}

inline number sumatory(Function f,  number begin,  number end, const number increment ){
    number x=0;

    #if defined DM4thOmpFor
        #pragma omp parallel  DM4thReductionSum(x)
        {
            number j = begin + increment*omp_get_thread_num();
            number iter = increment*omp_get_num_threads();
            
            while(j<end)
            {
                x += f(j);
                j += iter;
            }
        } 
    #else
        for(number j=begin; j>=begin && j<end; j+=increment ){
            x += f(j);
        }
    #endif
    return x;
}

inline number sumatory(NDArray<number> v, number begin, number end, number increment){
    number x=0;
    if(end==END) end = v.shape(0);

    #if defined DM4thOmpFor
        #pragma omp parallel  DM4thReductionSum(x)
        {
            number j = begin + increment*omp_get_thread_num();
            number iter = increment*omp_get_num_threads();
            
            while(j<end)
            {
                x += v(j);
                j += iter;
            }
        } 
    #else
        for(number j=begin; j>=0 && j<end; j+=increment ){
            x += v(j);
        }
    #endif
    return x;
}

inline number product(Function f, NDArray<number> v, const number increment){
    number x=1;
    int iter = increment.real();
    DM4thAssert(iter>0);

    #if defined DM4thOmpFor
        #pragma omp parallel for DM4thReductionMult(x)
    #endif
    for(int j=0; j<v.shape(0); j+=iter){
        x *= f(v(j));
    }
    return x;
}

inline number product(Function f, number begin, number end, const number increment){
    number x=1;

    #if defined DM4thOmpFor
        #pragma omp parallel  DM4thReductionMult(x)
        {
            number j = begin + increment*omp_get_thread_num();
            number iter = increment*omp_get_num_threads();
            
            while(j<end)
            {
                x *= f(j);
                j += iter;
            }
        } 
    #else
        for(number j=begin; j>=begin && j<end; j+=increment ){
            x *= f(j);
        }
    #endif
    return x;
}

inline number product(NDArray<number> v, number begin, number end, number increment){
    number x=1;
    if(end==END) end = v.shape(0);

    #if defined DM4thOmpFor
        #pragma omp parallel  DM4thReductionMult(x) shared(v)
        {
            number j = begin + increment*omp_get_thread_num();
            number iter = increment*omp_get_num_threads();
            
            while(j<end)
            {
                x *= v(j);
                j += iter;
            }
        } 
    #else
        for(number j=begin; j>=0 && j<end; j+=increment ){
            x *= v(j);
        }
    #endif
    return x;
}

}