#include "analysis.h"

N factorial(const N &n){
    N x = 1;
    for(auto i=1; i<=n; i++){
        x *= i;
    }
    return x;
}

N sumatory(function f, const N &begin, const N &end, const N interval){
    N x=0;
    for(auto i=begin; i<=end; i+=interval){
        x += f(i);
    }
    return x;
}

N sumatory(const N &value, const N &begin, const N &end, const N interval){
    N x=0;
    for(auto i=begin; i<=end; i+= interval){
        x += value;
    }
    return x;
}

N product(function f, const N &begin, const N &end, const N interval){
    N x=1;
    for(auto i=begin; i<=end; i+=interval){
        x *= f(i);
    }
    return x;
}

N product(const N &value, const N &begin, const N &end, const N interval){
    N x=1;
    for(auto i=begin; i<=end; i+=interval){
        x *= value;
    }
    return x;
}
// Derivative
N derivative(function f, const N &x0, const N h){
    return (f(x0+h)-f(x0-h))/(2*h);
}
// Integral
N integral(function f, const N &a, const N &b, const N subintervals){
    N n = int(round(subintervals).r)/3*3;
    N h = (b-a)/n;

    
    N s=0;
    for(N i=0; i<n; i++){
        s+=f(a+h*(i+0.5));
    }
    return s*h;
    
    /*
    N x1 = a+h;
    N x2 = x1+h;
    N x3 = x2+h; 

    N s = f(a);
    for(N i=0; i<n-2; i+=3){
        s += 3*f(x1);
        s += 3*f(x2);
        s += 2*f(x3);

        x1 = x3+h;
        x2 = x1+h;
        x3 = x2+h;
    }
    s+=f(b);
    return 3*h/8*s;
    */
}

// Aproximaciones de raices
N newtonRaphson(function f, function fd, N x1, N maxIter, N tolerance){
    x1 = x1.r;
    N y1 = (x1.i==0)? 1.00i : x1.i;
    
    for(int n=0; n<maxIter.r && abs(f(x1))>tolerance; n++){
        x1 = x1 - f(x1)/fd(x1);
    }
    if(abs(f(x1))>tolerance){
        for(int n=0; n<maxIter.r && abs(f(y1))>tolerance; n++){
            y1 = y1 - f(y1)/fd(y1);
        }
        if(abs(f(y1))>tolerance) x1 = NAN;
        else x1 = y1;
    }
    return x1;
}
N secantMethod(function f, N x0,N x1, N maxIter, N tolerance){
    x0 = x0.r; x1 = x1.r;
    N x2;

    N y0 = x0.i==0? 1.00i : x0.i;
    N y1 = x1.i==0? 1.01i : x1.i;
    N y2;

    for(int n=0; n<maxIter && abs(f(x1))>tolerance; n++){
        x2 = x1 - f(x1) * ((x0-x1)/(f(x0) - f(x1)));
        x0 = x1; x1 = x2;
    }

    if(abs(f(x2))>tolerance){
        for(int n=0; n<maxIter && abs(f(y1))>tolerance; n++){
            y2 = y1 - f(y1) * ((y0-y1)/(f(y0) - f(y1)));
            y0 = y1; y1 = y2;
        }
        if(abs(f(y2))>tolerance) x2 = NAN;
        else x2 = y2;
    }
    return x2;
}