#ifndef __ANALISIS_H__
#define __ANALISIS_H__

#include "N.h"
#include "V.h"
#define max maximum
#define min minimum

typedef Number (* function)(Number x);

Number maximum(const Number a);
Number maximum(V);
template<class ... T>
// get maximum value of list
Number maximum(const Number a, const T ... b){
    Number value = max(b...);
    return a>value?a:value;
}

Number minimum(const Number a);
Number minimum(V);
template<class ... T>
// get minimum value of list
Number minimum(const Number a, const T ... b){
    Number value = max(b...);
    return a<value?a:value;
}

// 
V zeros(const Number&);
//
V ones(const Number&);
// range(begin, end, interval)
V range(const Number&, const Number&, Number=1);
// range(vector, pos begin, pos end, interval)
V range(V, const Number&, const Number&, Number=1);
// range(f, x0=begin, xn=end, interval)
V range(function, const Number&, const Number&, Number=1);
// e^x
Number exp(Number x);
// PI function
Number PI(Number z, Number tolerance=1e-7);
// gamma function
Number gamma(Number z, Number tolerance=1e-7);
// Rieman's zeta function
//Number zeta(Number z, Number tolerance=1e-7);
// factorial(value)
Number factorial(const Number&);
// sumatory(f, V(xn...) , interval)
Number sumatory(function f, V, const Number interval=1); 
// sumatory(f, begin, end, interval)
Number sumatory(function f, const Number&, const Number&, const Number interval=1); 
// sumatory(V, begin, end, interval) 
Number sumatory(V, Number begin=0, Number end=-1, const Number interval=1);
// product(f, V(xn...), interval)
Number product(function f, V, const Number interval=1); 
// product(f, begin, end, interval)
Number product(function f, const Number&, const Number&, const Number interval=1); 
// product(V, begin, end, interval) 
Number product(V, Number begin=0, Number end=-1, const Number interval=1);
// derivative(f, x0, order=1, tolerance)
Number derivative(function f, const Number&, const Number order=1, const Number tolerance=1e-2);
/*
 Difference between adjacent elements of vector.
 Returns n-1 values of the vector for each iteration
 diff(vector, iterations)
*/
V diff(V, Number=1);
// integral(f, begin, end, subintervals=99)
Number integral(function f, const Number&, const Number&, const Number subintervals=1000);
// quadratic(a,b,c)
V quadratic(const Number&, const Number&, const Number&);
// newtonRaphson(f, x0=seed, max iterations, tolerance)
Number newtonRaphson(function f, Number x0=1.01, Number maxIter=100, Number tolerance=1e-5);
// newtonRaphson(f, f', x0=seed, max iterations, tolerance)
Number newtonRaphson(function f, function fd, Number x0=1.01, Number maxIter=100, Number tolerance=1e-5);
// secantMethod(f, x0=seed, x1=seed2, max iterations, tolerance)
Number secantMethod(function f, Number x0=0.01, Number x1=1.01, Number maxIter=100, Number tolerance=1e-5);
/*
 Returns all roots of a polynomial function
 x^2-1 ==> bairstowMethod( V(1, 0,-1) ); ==> returns (-1, 1)
 bairstowMethod(polynomial coefficients, r=seed, s=seed2, max iterations, tolerance)
*/
V bairstowsMethod(V, Number r=0.1, Number s=0.1, Number maxIter=100, Number tolerance=1e-5);

#endif