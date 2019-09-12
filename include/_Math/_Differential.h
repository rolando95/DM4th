#pragma once

#include "_MathUtilities.h"

// e^x
Number exp(Number x);

// PI Function
Number PI(Number z, Number tolerance=1e-7);
// gamma Function
Number gamma(Number z, Number tolerance=1e-7);

Number derivative(Function f, const Number&, const Number order=1, const Number tolerance=1e-2);
/*
 Difference between adjacent elements of vector.
 Returns n-1 values of the vector for each iteration
 diff(vector, iterations)
*/
NDArray<Number> diff(NDArray<Number>, Number=1);
// integral(f, begin, end, subintervals=99)
Number integral(Function f, const Number&, const Number&, const Number subintervals=1000);