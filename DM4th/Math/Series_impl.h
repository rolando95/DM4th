#pragma once 

#include "Series.h"
#include "Differential.h"

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

    return DM4thUtils::parallelLoopReduce<int, int>(
        DM4thUtils::ReduceOp::MUL, 
        1, n+1, 1, // from, to, step

        [&](const int &acum, const int &j)
        {
            return acum * j;
        }

        , 1 // initialValue
    ); 
}

inline number sumatory(Function f, NDArray<number> v, const number increment){
    int iter = increment.real();
    DM4thAssert(iter>0);

    return DM4thUtils::parallelLoopReduce<number, int>(
        DM4thUtils::ReduceOp::SUM, 
        0, v.data_size(), iter, // from, to, step

        [&](number acum, number j)
        {
            return acum + f(v((int)j));
        }
    );

}

inline number sumatory(Function f,  number begin,  number end, const number increment ){
    
    return DM4thUtils::parallelLoopReduce<number, number>(
        DM4thUtils::ReduceOp::SUM, 
        begin, end, increment, // from, to, step

        [&](const number &acum, const number &j)
        {
            return acum + f(j);
        }
    );
}

inline number sumatory(NDArray<number> v, number begin, number end, number increment){
    if(end==END) end = v.shape(0);

    return DM4thUtils::parallelLoopReduce<number, number>(
        DM4thUtils::ReduceOp::SUM, 
        begin, end, increment, // from, to, step

        [&](number acum, number j)
        {
            return acum + v((int)j);
        }
    );
}

inline number product(Function f, NDArray<number> v, const number increment){
    int iter = increment.real();
    DM4thAssert(iter>0);

    return DM4thUtils::parallelLoopReduce<number, int>(
        DM4thUtils::ReduceOp::MUL,
        0, v.data_size(), iter, // from, to, step

        [&](number acum, const int &j)
        {
            return acum * f(v((int)j));
        }

        , 1 // initialValue
    );
}

inline number product(Function f, number begin, number end, const number increment){
    
    return DM4thUtils::parallelLoopReduce<number, number>(
        DM4thUtils::ReduceOp::MUL, 
        begin, end, increment, // from, to, step

        [&](const number &acum, const number &j)
        {
            return acum * f(j);
        }

        , 1 // intialValue
    );
}

inline number product(NDArray<number> v, number begin, number end, number increment){
    if(end==END) end = v.shape(0);

    return DM4thUtils::parallelLoopReduce<number, number>(
        DM4thUtils::ReduceOp::MUL,
        begin, end, increment, // from, to, step

        [&](const number &acum, number j)
        {
            return acum * v((int)j);
        }

        , 1 // initialValue
    );
}

}