#include "analysis.h"

N factorial(const N &n){
    N x = 1;
    for(auto i=1; i<=n; i++){
        x *= i;
    }
    return x;
}

N sumatory(function f, const N &begin, const N &end){
    N x=0;
    for(auto i=begin; i<=end; i++){
        x += f(i);
    }
    return x;
}

N sumatory(const N &value, const N &begin, const N &end){
    N x=0;
    for(auto i=begin; i<=end; i++){
        x += value;
    }
    return x;
}

N product(function f, const N &begin, const N &end){
    N x=1;
    for(auto i=begin; i<=end; i++){
        x *= f(i);
    }
    return x;
}

N product(const N &value, const N &begin, const N &end){
    N x=1;
    for(auto i=begin; i<=end; i++){
        x *= value;
    }
    return x;
}

// Aproximaciones de raices
N newtonRaphson(function f, function fd, N x1, N maxIter, N tolerance){
    x1 = x1.r;
    N y1 = (x1.i==0)?i:x1.i;

    for(int n=0; n<maxIter.r && abs(f(x1))>tolerance && abs(f(y1))>tolerance ; n++){
        x1 = x1 - f(x1)/fd(x1);
        y1 = y1 - f(y1)/fd(y1);
    }
    if( abs(f(x1)) > abs(f(y1))) x1 = y1;
    return x1;
}


N secantMethod(function f, N x0,N x1, N maxIter, N tolerance){
    x0 = x0.r; x1 = x1.r;
    N x2;

    N y0 = x0.i==0?i:x0.i;
    N y1 = x1.i==0?2i:x1.i;
    N y2;

    for(int n=0; n<maxIter && abs(f(x1))>tolerance && abs(f(y1))>tolerance; n++){
        x2 = x1 - f(x1) * ((x0-x1)/(f(x0) - f(x1)));
        x0 = x1; x1 = x2;

        y2 = y1 - f(y1) * ((y0-y1)/(f(y0) - f(y1)));
        y0 = y1; y1 = y2;
    }
    if( abs(f(x2)) > abs(f(y2))) x2 = y2;
    return x2;
}