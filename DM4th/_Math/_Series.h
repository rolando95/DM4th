#pragma once

#include "_MathUtilities.h"

namespace DM4th
{

// Fibonacci number 
number fibonacci(number);
// factorial(value)
number factorial(const number&);
// sumatory(f, V(xn...) , interval)
number sumatory(Function f, NDArray<number>, const number interval=1); 
// sumatory(f, begin, end, interval)
number sumatory(Function f, const number&, const number&, const number interval=1); 
// sumatory(NDArray<number>, begin, end, interval) 
number sumatory(NDArray<number>, number begin=0, number end=-1, const number interval=1);
// product(f, V(xn...), interval)
number product(Function f, NDArray<number>, const number interval=1); 
// product(f, begin, end, interval)
number product(Function f, const number&, const number&, const number interval=1); 
// product(NDArray<number>, begin, end, interval) 
number product(NDArray<number>, number begin=0, number end=-1, const number interval=1);

}