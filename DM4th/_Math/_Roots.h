#pragma once

#include "_MathUtilities.h"

namespace DM4th
{

// quadratic(a,b,c)
template<class A, class B, class C>
NDArray<Number> quadratic(const A&, const B&, const C&);

// newtonRaphson(f, x0=seed, max iterations, tolerance)
Number newtonRaphson(Function f, Number x0=1.01, Number maxIter=100, Number tolerance=1e-5);

// newtonRaphson(f, f', x0=seed, max iterations, tolerance)
Number newtonRaphson(Function f, Function fd, Number x0=1.01, Number maxIter=100, Number tolerance=1e-5);
// secantMethod(f, x0=seed, x1=seed2, max iterations, tolerance)
Number secantMethod(Function f, Number x0=0.01, Number x1=1.01, Number maxIter=100, Number tolerance=1e-5);

template<class T>
NDArray<Number> bairstowsMethod(NDArray<T> polynomial, Number r=0.1, Number s=0.1, Number maxIter=100, Number tolerance=1e-5);

}