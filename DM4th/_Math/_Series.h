#pragma once

#include "_MathUtilities.h"

namespace DM4th
{

// Fibonacci number 
inline number fibonacci(number);
// factorial(value)
inline number factorial(const number&);
// sumatory(f, V(xn...) , interval)
inline number sumatory(Function f, NDArray<number>, const number interval=1); 
// sumatory(f, begin, end, interval)
inline number sumatory(Function f, const number&, const number&, const number interval=1); 
// sumatory(NDArray<number>, begin, end, interval) 
inline number sumatory(NDArray<number>, number begin=0, number end=-1, const number interval=1);
// product(f, V(xn...), interval)
inline number product(Function f, NDArray<number>, const number interval=1); 
// product(f, begin, end, interval)
inline number product(Function f, const number&, const number&, const number interval=1); 
// product(NDArray<number>, begin, end, interval) 
inline number product(NDArray<number>, number begin=0, number end=-1, const number interval=1);

}