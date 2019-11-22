#pragma once

#include "MathUtils.h"

namespace DM4th
{

// Fibonacci number 
inline number fibonacci(number);
// Fibonacci number using iterative methods
inline number fibonacci2(number);
// factorial(value)
inline number factorial(const number);
// factorial(value)
inline number factorial2(const number);
// sumatory(f, V(xn...) , interval)
inline number sumatory(Function f, NDArray<number>, const number increment=1); 
// sumatory(f, begin, end, interval)
inline number sumatory(Function f, number begin, number end, const number increment=1); 
// sumatory(NDArray<number>, begin, end, interval) 
inline number sumatory(NDArray<number>, number begin=0, number end=END, const number increment =1);
// product(f, V(xn...), interval)
inline number product(Function f, NDArray<number>, const number increment=1); 
// product(f, begin, end, interval)
inline number product(Function f, number, number, const number increment=1); 
// product(NDArray<number>, begin, end, interval) 
inline number product(NDArray<number>, number begin=0, number end=END, const number increment=1);

}