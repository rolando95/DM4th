#pragma once

#include "MathUtils.h"

namespace DM4th
{

// e^x
inline number exp(number x);

// PI Function
inline number PI(number z, number tolerance=1e-7);
// gamma Function
inline number gamma(number z, number tolerance=1e-7);

inline number derivative(Function f, const number x0, const number order=1, const number tolerance=1e-2);
/*
 Difference between adjacent elements of vector.
 Returns n-1 values of the vector for each iteration
 diff(vector, iterations)
*/
inline NDArray<number> diff(NDArray<number>, number=1);
// integral(f, begin, end, subintervals=99)
inline number integral(Function f, const number&, const number&, const number subintervals=1000);

/* 
 Runge-Kutta method of order 4
*/
inline number RK4(std::function<number(number t,number y)> fd, number t0, number y0, number tn, number iter=100);

}