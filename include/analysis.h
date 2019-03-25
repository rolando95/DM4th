#ifndef __ANALISIS_H__
#define __ANALISIS_H__

#include "_Number.h"
#include "_Vector.h"
#include "_Matrix.h"

//#define max maximum
//#define min minimum

typedef Number (* Function)(Number x);
typedef Number (* Function2)(Number x, Number y);

Number maximum(const Number a);
Number maximum(Vector);
template<class ... T>
// get maximum value of list
Number maximum(const Number a, const T ... b){
    Number value = maximum(b...);
    return a>value?a:value;
}

Number minimum(const Number a);
Number minimum(Vector);
template<class ... T>
// get minimum value of list
Number minimum(const Number a, const T ... b){
    Number value = minimum(b...);
    return a<value?a:value;
}
// Fibonacci number 
Number fibonacci(Number);
// Fibonaci number (golden ratio)
Vector range(const Number&, const Number&, Number=1);

// range(f, x0=begin, xn=end, interval)
Vector range(Function, const Number&, const Number&, Number=1);
// e^x
Number exp(Number x);
// Convert Complex number to polar expresion
Vector polar(Number n);
// PI Function
Number PI(Number z, Number tolerance=1e-7);
// gamma Function
Number gamma(Number z, Number tolerance=1e-7);
// Rieman's zeta Function
//Number zeta(Number z, Number tolerance=1e-7);
// factorial(value)
Number factorial(const Number&);
// sumatory(f, V(xn...) , interval)
Number sumatory(Function f, Vector, const Number interval=1); 
// sumatory(f, begin, end, interval)
Number sumatory(Function f, const Number&, const Number&, const Number interval=1); 
// sumatory(Vector, begin, end, interval) 
Number sumatory(Vector, Number begin=0, Number end=-1, const Number interval=1);
// product(f, V(xn...), interval)
Number product(Function f, Vector, const Number interval=1); 
// product(f, begin, end, interval)
Number product(Function f, const Number&, const Number&, const Number interval=1); 
// product(Vector, begin, end, interval) 
Number product(Vector, Number begin=0, Number end=-1, const Number interval=1);
// derivative(f, x0, order=1, tolerance)
Number derivative(Function f, const Number&, const Number order=1, const Number tolerance=1e-2);
/*
 Difference between adjacent elements of vector.
 Returns n-1 values of the vector for each iteration
 diff(vector, iterations)
*/
Vector diff(Vector, Number=1);
// integral(f, begin, end, subintervals=1000)
Number integral(Function f, const Number&, const Number&, const Number subintervals=1000);
/* Ordinary differential equations
 
 f(x,y) = y'
 Number f(Number x, Number y){
     ...
     return yf;
 }
 rungeKutta(f, x0, y0, xf, subintervals=1000)
*/
Number rungeKutta(Function2 f, Number x0, Number y0, Number xf, Number subintervals=1000);
// quadratic(a,b,c)
Vector quadratic(const Number&, const Number&, const Number&);
// newtonRaphson(f, x0=seed, max iterations, tolerance)
Number newtonRaphson(Function f, Number x0=1.01, Number maxIter=100, Number tolerance=1e-5);
// newtonRaphson(f, f', x0=seed, max iterations, tolerance)
Number newtonRaphson(Function f, Function fd, Number x0=1.01, Number maxIter=100, Number tolerance=1e-5);
// secantMethod(f, x0=seed, x1=seed2, max iterations, tolerance)
Number secantMethod(Function f, Number x0=0.01, Number x1=1.01, Number maxIter=100, Number tolerance=1e-5);
/*
 Returns all roots of a polynomial Function
 x^2-1 ==> bairstowMethod( V(1, 0,-1) ); ==> returns (-1, 1)
 bairstowMethod(polynomial coefficients, r=seed, s=seed2, max iterations, tolerance)
*/
Vector bairstowsMethod(Vector, Number r=0.1, Number s=0.1, Number maxIter=100, Number tolerance=1e-5);

#endif