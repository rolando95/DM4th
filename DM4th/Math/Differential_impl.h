#pragma once

#include "Differential.h"


namespace DM4th
{

inline number exp(number x){
    return pow(e,x);
}

inline number PI(number z, number tolerance){
    return gamma(z+1,tolerance);
}
// From Wikipedia https://es.wikipedia.org/wiki/Aproximaci%C3%B3n_de_Lanczos
inline number gamma(number z, number tolerance){
    number result;
    number x;
    number t;
    NDArray<number> p = items<number>(676.5203681218851,  
        -1259.1392167224028,  
        771.32342877765313,
        -176.61502916214059,     
        12.507343278686905, 
        -0.13857109526572012,
        9.9843695780195716e-6, 
        1.5056327351493116e-7
    );

    if(z<0.5) result = pi/(sin(pi*z)*gamma(1-z));
    else{
        z -= 1;
        x = 0.99999999999980993;
        for(number j=0; j<p.shape(0); ++j){
            x += p(j)/(z+j+1);
        }
        t = z + p.shape(0) - 0.5;
        result = std::sqrt(2*pi) *pow(t,z+0.5) * exp(-t) * x;
    }

    if (std::abs(result.imag() - std::abs(result.imag()))<=tolerance){
        return result.real();
    }
    return result;
}

// Derivative
inline number derivative(Function f, const number x0, const number order, const number h){
    number o(std::abs(std::floor(order.real())));
    if(order<=0){
        return f(x0);
    }else if(order==1){
        return (f(x0+h)-f(x0-h))/(2*h);
    }else if(order==2){
        return (f(x0+h) - 2*f(x0) + f(x0-h))/pow(h,2);
    }else{
        return (derivative(f,x0+h/2,o-1,2*h) - derivative(f,x0-h/2,o-1,2*h) )/h;
    }
}

inline NDArray<number> diff(NDArray<number> v, number iter){
    if(iter<=0) return v;
    else{



        if(v.shape(0) >= 2){
            NDArray<number> diffV;
            diffV.resize(v.shape(0)-1);
            
            DM4thUtils::parallelLoopItems<number>([&](number&item, const int j) {
                item = (v(j+1) - v(j));
            },
            diffV.data(), diffV.data_size()
            );

            return diff(diffV,iter - 1);
        }else{
            return NDArray<number>();
        }
    }
}

// Integral
inline number integral(Function f, const number &a, const number &b, const number subintervals){
    int n = subintervals.real();
    number h = (b-a)/n;
    
    number s=0;
    
    // DM4thLoopItems REDUCTION
    IFDM4thOmp(n>=DM4thConfig::minParallelLoops)
    {

        #pragma omp parallel for DM4thReductionSum(s)
        for(int j=0; j<n; ++j){
            s+=f(a+h*(j+0.5));
        }

    }else{

        for(int j=0; j<n; ++j){
            s+=f(a+h*(j+0.5));
        }

    }

    return s*h;

    /*

    int n = int(round(subintervals).real())/3*3;

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

// Runge-Kutta 4
inline number RK4(std::function<number(number,number)> fd, number t0, number w, number tn, number iter)
{
    number k1, k2, k3, k4;
    number h = (tn - t0) / iter;
    for(number t=0; t<tn; t+=h)
    {
        k1 = h * fd(t    , w);
        k2 = h * fd(t+h/2, w+k1/2);
        k3 = h * fd(t+h/2, w+k2/2);
        k4 = h * fd(t+h  , w+k3);
        w = w + (k1 + 2*k2 + 2*k3 + k4)/6;
    }
    return w;
}
}