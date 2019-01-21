#ifndef __ANALISIS_H__
#define __ANALISIS_H__

#include "N.h"
#include "V.h"
#define max maximum
#define min minimum

typedef N (* function)(N x);

N maximum(const N a);
N maximum(V);
// get maximum value of list
template<class ... T>
N maximum(const N a, const T ... b){
    N value = max(b...);
    return a>value?a:value;
}

N minimum(const N a);
N minimum(V);
// get minimum value of list
template<class ... T>
N minimum(const N a, const T ... b){
    N value = max(b...);
    return a<value?a:value;
}

// factorial(value)
N factorial(const N&);
// sumatory(f, begin, end, interval)
N sumatory(function f, const N&, const N&, const N interval=1); 
// sumatory(V, begin, end, interval) 
N sumatory(V, N begin=0, N end=-1, const N interval=1);
// product(f, begin, end)
N product(function f, const N&, const N&, const N interval=1); 
// product(V, begin, end, interval) 
N product(V, N begin=0, N end=-1, const N interval=1);
// derivative(f, x0, order=1)
N derivative(function f, const N&, const N order=1, const N h=1e-2);
/*
 Difference between adjacent elements of vector.
 Returns n-1 values of the vector for each iteration
 diff(vector, iterations)
*/
V diff(V, N=1);
// integral(f, begin, end, subintervals=99)
N integral(function f, const N&, const N&, const N subintervals=999);
// quadratic(a,b,c)
V quadratic(const N&, const N&, const N&);
// newtonRaphson(f, x0=seed, max iterations, tolerance)
N newtonRaphson(function f, N x0=1.01, N maxIter=1000, N tolerance=1e-5);
// newtonRaphson(f, f', x0=seed, max iterations, tolerance)
N newtonRaphson(function f, function fd, N x0=1.01, N maxIter=1000, N tolerance=1e-5);
// secantMethod(f, x0=seed, x1=seed2, max iterations, tolerance)
N secantMethod(function f, N x0=0.01, N x1=1.01, N maxIter=1000, N tolerance=1e-5);

#endif