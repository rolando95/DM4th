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
    int x = 1;

    x = DM4thUtils::parallelLoopReduceS<int, DM4thUtils::ReduceOp::MUL>(
        [&](int acum, int j)
        {
            return acum * j;
        }
    ,1, n+1, 1, 1);

    return number(x,0);
}

inline number sumatory(Function f, NDArray<number> v, const number increment){
    int iter = increment.real();
    DM4thAssert(iter>0);

    number x = DM4thUtils::parallelLoopReduceS<number, DM4thUtils::ReduceOp::SUM>(
        [&](number acum, number j)
        {
            return acum + f(v((int)j));
        }
    ,0, v.data_size(), iter);

    return x;
}

inline number sumatory(Function f,  number begin,  number end, const number increment ){
    number x= DM4thUtils::parallelLoopReduceS<number, DM4thUtils::ReduceOp::SUM>(
        [&](number acum, number j)
        {
            return acum + f(j);
        }
    ,begin, end, increment);
    return x;
}

inline number sumatory(NDArray<number> v, number begin, number end, number increment){
    if(end==END) end = v.shape(0);

    number x = DM4thUtils::parallelLoopReduceS<number, DM4thUtils::ReduceOp::SUM>(
        [&](number acum, number j)
        {
            return acum + v((int)j);
        }
    ,begin, end, increment);
    return x;
}

inline number product(Function f, NDArray<number> v, const number increment){
    int iter = increment.real();
    DM4thAssert(iter>0);

    number x = DM4thUtils::parallelLoopReduceS<number, DM4thUtils::ReduceOp::MUL>(
        [&](number acum, number j)
        {
            return acum * f(v((int)j));
        }
    ,0, v.data_size(), iter, 1);
    return x;
}

inline number product(Function f, number begin, number end, const number increment){
    number x= DM4thUtils::parallelLoopReduceS<number, DM4thUtils::ReduceOp::MUL>(
        [&](number acum, number j)
        {
            return acum * f(j);
        }
    ,begin, end, increment, 1);

    return x;
}

inline number product(NDArray<number> v, number begin, number end, number increment){
    if(end==END) end = v.shape(0);

    number x = DM4thUtils::parallelLoopReduceS<number, DM4thUtils::ReduceOp::MUL>(
        [&](number acum, number j)
        {
            return acum * v((int)j);
        }
    ,begin, end, increment, 1);
    return x;
}

}