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

    int result;
    DM4thUtils::parallelLoopReduce<int, int>(
        DM4thUtils::EParallelType::OMP_PARALLEL | DM4thUtils::EParallelType::MUL, 
        1, n+1, 1, // from, to, step

        [&](const int &acum, const int &j)
        {
            return acum * j;
        },
        result

        , 1 // initialValue
    ); 
    return result;
}

inline number sumatory(Function f, NDArray<number> v, const number increment){
    int iter = increment.real();
    DM4thAssert(iter>0);

    number result;
    
    DM4thUtils::parallelLoopReduce<number, int>(
        DM4thUtils::EParallelType::OMP_PARALLEL | DM4thUtils::EParallelType::ADD, 
        0, v.data_size(), iter, // from, to, step

        [&](number acum, number j)
        {
            return acum + f(v((int)j));
        },
        result
    );

    return result;
}

inline number sumatory(Function f,  number begin,  number end, const number increment ){
    
    number result;
    
    DM4thUtils::parallelLoopReduce<number, number>(
        DM4thUtils::EParallelType::OMP_PARALLEL | DM4thUtils::EParallelType::ADD, 
        begin, end, increment, // from, to, step

        [&](const number &acum, const number &j)
        {
            return acum + f(j);
        },
        result
    );

    return result;
}

inline number sumatory(NDArray<number> v, number begin, number end, number increment){
    if(end==END) end = v.shape(0);

    number result;
    
    DM4thUtils::parallelLoopReduce<number, number>(
        DM4thUtils::EParallelType::OMP_PARALLEL | DM4thUtils::EParallelType::ADD, 
        begin, end, increment, // from, to, step

        [&](number acum, number j)
        {
            return acum + v((int)j);
        },
        result
    );

    return result;
}

inline number product(Function f, NDArray<number> v, const number increment){
    int iter = increment.real();
    DM4thAssert(iter>0);

    number result;

    DM4thUtils::parallelLoopReduce<number, int>(
        DM4thUtils::EParallelType::OMP_PARALLEL | DM4thUtils::EParallelType::MUL,
        0, v.data_size(), iter, // from, to, step

        [&](number acum, const int &j)
        {
            return acum * f(v((int)j));
        },
        result

        , 1 // initialValue
    );

    return result;
}

inline number product(Function f, number begin, number end, const number increment){
    
    number result;
    
    DM4thUtils::parallelLoopReduce<number, number>(
        DM4thUtils::EParallelType::OMP_PARALLEL | DM4thUtils::EParallelType::MUL, 
        begin, end, increment, // from, to, step

        [&](const number &acum, const number &j)
        {
            return acum * f(j);
        },
        result

        , 1 // intialValue
    );

    return result;
}

inline number product(NDArray<number> v, number begin, number end, number increment){
    if(end==END) end = v.shape(0);

    number result;
    DM4thUtils::parallelLoopReduce<number, number>(
        DM4thUtils::EParallelType::OMP_PARALLEL | DM4thUtils::EParallelType::MUL,
        begin, end, increment, // from, to, step

        [&](const number &acum, number j)
        {
            return acum * v((int)j);
        },
        result 

        , 1 // initialValue
    );

    return result;
}

}