#include "N.h"

typedef N (* function)(N x);

//
N factorial(const N&);

// sumatory(f, begin, end)
N sumatory(function f, const N&, const N&); 
// sumatory(value, begin, end) 
N sumatory(const N&, const N&, const N&);

// product(f, begin, end)
N product(function f, const N&, const N&); 
// product(value, begin, end) 
N product(const N&, const N&, const N&);

// newtonRaphson(f, f', x0=seed, max iterations, tolerance)
N newtonRaphson(function f, function fd, N x0=1.01, N maxIter=100, N tolerance=0.00001);

// secantMethod(f, x0=seed, x1=seed2, max iterations, tolerance)
N secantMethod(function f, N x0=0.01, N x1=1.01, N maxIter=100, N tolerance=0.0001);