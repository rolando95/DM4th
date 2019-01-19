#include "N.h"
#include "V.h"

typedef N (* function)(N x);

//
N factorial(const N&);
// sumatory(f, begin, end, interval)
N sumatory(function f, const N&, const N&, const N interval=1); 
// sumatory(value, begin, end) 
N sumatory(const N&, const N&, const N&, const N interval=1);
// product(f, begin, end)
N product(function f, const N&, const N&, const N interval=1); 
// product(value, begin, end) 
N product(const N&, const N&, const N&, const N interval=1);
// derivative(f, x0, order=1)
N derivative(function f, const N&, const N order=1, const N h=1e-2);
// integral(f, begin, end, subintervals=99)
N integral(function f, const N&, const N&, const N subintervals=999);
// newtonRaphson(f, f', x0=seed, max iterations, tolerance)
N newtonRaphson(function f, N x0=1.01, N maxIter=1000, N tolerance=1e-5);
// newtonRaphson(f, f', x0=seed, max iterations, tolerance)
N newtonRaphson2(function f, function fd, N x0=1.01, N maxIter=1000, N tolerance=1e-5);
// secantMethod(f, x0=seed, x1=seed2, max iterations, tolerance)
N secantMethod(function f, N x0=0.01, N x1=1.01, N maxIter=1000, N tolerance=1e-5);