#pragma once

#include "MathUtils.h"

namespace DM4th
{

// quadratic(a,b,c)
template<class A, class B, class C>
NDArray<number> quadratic(const A&, const B&, const C&);

// newtonRaphson(f, x0=seed, max iterations, tolerance)
inline number newtonRaphson(const std::function<number(number)> &f, number x0=1.01, number maxIter=100, number tolerance=1e-5);

// newtonRaphson(f, f', x0=seed, max iterations, tolerance)
inline number newtonRaphson(const std::function<number(number)> &f, const std::function<number(number)> &fd, number x0=1.01, number maxIter=100, number tolerance=1e-5);
// secantMethod(f, x0=seed, x1=seed2, max iterations, tolerance)
inline number secantMethod(const std::function<number(number)> &f, number x0=0.01, number x1=1.01, number maxIter=100, number tolerance=1e-5);

template<class T>
NDArray<number> bairstowsMethod(NDArray<T> polynomial, number r=0.1, number s=0.1, number maxIter=100, number tolerance=1e-5);

}