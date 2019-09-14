#pragma once

#include "_MathUtilities.h"

namespace DM4th
{

// e^x
number exp(number x);

// PI Function
number PI(number z, number tolerance=1e-7);
// gamma Function
number gamma(number z, number tolerance=1e-7);

number derivative(Function f, const number&, const number order=1, const number tolerance=1e-2);
/*
 Difference between adjacent elements of vector.
 Returns n-1 values of the vector for each iteration
 diff(vector, iterations)
*/
NDArray<number> diff(NDArray<number>, number=1);
// integral(f, begin, end, subintervals=99)
number integral(Function f, const number&, const number&, const number subintervals=1000);

}