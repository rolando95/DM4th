#pragma once

#include "../_Array/_Array.h"
#include "../_Number/_Number.h"

// quadratic(a,b,c)
template<class A, class B, class C>
NDArray<Number> quadratic(const A&, const B&, const C&);

template<class T>
NDArray<Number> bairstowsMethod(NDArray<T> polynomial, Number r=0.1, Number s=0.1, Number maxIter=100, Number tolerance=1e-5);