#ifndef __ANALISIS_H__
#define __ANALISIS_H__

#include "N.h"
#include "V.h"
#define max maximum
#define min minimum

typedef N (* function)(N x);

N maximum(const N a);
N maximum(V);
template<class ... T>
// get maximum value of list
N maximum(const N a, const T ... b){
    N value = max(b...);
    return a>value?a:value;
}

N minimum(const N a);
N minimum(V);
template<class ... T>
// get minimum value of list
N minimum(const N a, const T ... b){
    N value = max(b...);
    return a<value?a:value;
}

// 
V zeros(const N&);
//
V ones(const N&);
// range(begin, end, interval)
V range(const N&, const N&, N=1);
// range(vector, pos begin, pos end, interval)
V range(V, const N&, const N&, N=1);
// range(f, x0=begin, xn=end, interval)
V range(function, const N&, const N&, N=1);
// e^x
N exp(N x);
// PI function
N PI(N z, N tolerance=1e-7);
// gamma function
N gamma(N z, N tolerance=1e-7);
// Rieman's zeta function
//N zeta(N z, N tolerance=1e-7);
// factorial(value)
N factorial(const N&);
// sumatory(f, V(xn...) , interval)
N sumatory(function f, V, const N interval=1); 
// sumatory(f, begin, end, interval)
N sumatory(function f, const N&, const N&, const N interval=1); 
// sumatory(V, begin, end, interval) 
N sumatory(V, N begin=0, N end=-1, const N interval=1);
// product(f, V(xn...), interval)
N product(function f, V, const N interval=1); 
// product(f, begin, end, interval)
N product(function f, const N&, const N&, const N interval=1); 
// product(V, begin, end, interval) 
N product(V, N begin=0, N end=-1, const N interval=1);
// derivative(f, x0, order=1, tolerance)
N derivative(function f, const N&, const N order=1, const N tolerance=1e-2);
/*
 Difference between adjacent elements of vector.
 Returns n-1 values of the vector for each iteration
 diff(vector, iterations)
*/
V diff(V, N=1);
// integral(f, begin, end, subintervals=99)
N integral(function f, const N&, const N&, const N subintervals=1000);
// quadratic(a,b,c)
V quadratic(const N&, const N&, const N&);
// newtonRaphson(f, x0=seed, max iterations, tolerance)
N newtonRaphson(function f, N x0=1.01, N maxIter=100, N tolerance=1e-5);
// newtonRaphson(f, f', x0=seed, max iterations, tolerance)
N newtonRaphson(function f, function fd, N x0=1.01, N maxIter=100, N tolerance=1e-5);
// secantMethod(f, x0=seed, x1=seed2, max iterations, tolerance)
N secantMethod(function f, N x0=0.01, N x1=1.01, N maxIter=100, N tolerance=1e-5);
/*
 Returns all roots of a polynomial function
 x^2-1 ==> bairstowMethod( V(1, 0,-1) ); ==> returns (-1, 1)
 bairstowMethod(polynomial coefficients, r=seed, s=seed2, max iterations, tolerance)
*/
V bairstowsMethod(V,N r=0.1,N s=0.1, N maxIter=100, N tolerance=1e-5);

#endif