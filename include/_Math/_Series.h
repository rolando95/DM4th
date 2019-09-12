#pragma once

#include "_MathUtilities.h"
// Fibonacci number 
Number fibonacci(Number);
// factorial(value)
Number factorial(const Number&);
// sumatory(f, V(xn...) , interval)
Number sumatory(Function f, NDArray<Number>, const Number interval=1); 
// sumatory(f, begin, end, interval)
Number sumatory(Function f, const Number&, const Number&, const Number interval=1); 
// sumatory(NDArray<Number>, begin, end, interval) 
Number sumatory(NDArray<Number>, Number begin=0, Number end=-1, const Number interval=1);
// product(f, V(xn...), interval)
Number product(Function f, NDArray<Number>, const Number interval=1); 
// product(f, begin, end, interval)
Number product(Function f, const Number&, const Number&, const Number interval=1); 
// product(NDArray<Number>, begin, end, interval) 
Number product(NDArray<Number>, Number begin=0, Number end=-1, const Number interval=1);