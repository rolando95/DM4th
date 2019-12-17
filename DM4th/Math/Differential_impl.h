#pragma once

#include "Differential.h"


namespace DM4th
{

// e^x
template<template<class> class NUMBER, class T>
inline NUMBER<T> exp(const NUMBER<T> &x){
    return pow(e,x);
}

inline number exp(const number &x)
{
    return exp<_number,double>(x);
}

inline fnumber exp(const fnumber &x)
{
    return exp<_number,float>(x);
}

////////// GAMMA //////////

// From Wikipedia https://es.wikipedia.org/wiki/Aproximaci%C3%B3n_de_Lanczos
template<template<class> class NUMBER, class T>
NUMBER<T> gamma(NUMBER<T> z, const NUMBER<T> &tolerance=1e-7){
    NUMBER<T> result;
    NUMBER<T> x;
    NUMBER<T> t;
    NDArray<NUMBER<T>> p = items<NUMBER<T>>(676.5203681218851,  
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
        for(NUMBER<T> j=0; j<p.shape(0); ++j){
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

inline number gamma(const number &z, const number &tolerance)
{
    return gamma<_number, double>(z, tolerance);
}

inline fnumber gamma(const fnumber &z, const fnumber &tolerance)
{
    return gamma<_number, float>(z, tolerance);
}

inline number gamma(const double &z, const number &tolerance)
{
    return gamma(number(z), tolerance);
}

////////// PI //////////

template<template<class> class NUMBER, class T>
inline NUMBER<T> PI(const NUMBER<T> &z, const NUMBER<T> &tolerance=1e-7)
{
    return gamma(z+1,tolerance);
}

inline number PI(const number &z, const number &tolerance)
{
    return gamma(z+1, tolerance);
}

inline fnumber PI(const fnumber &z, const fnumber &tolerance)
{
    return gamma(z+1, tolerance);
}

inline number PI(const double &z, const number &tolerance)
{
    return gamma(number(z+1), tolerance);
}
// Derivative
// template<template<class> class NUMBER=_number, class T=double>
// inline NUMBER<T> derivative(
//         const std::function<NUMBER<T>(NUMBER<T>)> &f, 
//         const NUMBER<T> x0, const NUMBER<T> order=1, const NUMBER<T> h=1e-2
//     ){
//     NUMBER<T> o(std::abs(std::floor(order.real())));
//     if(order<=0){
//         return f(x0);
//     }else if(order==1){
//         return (f(x0+h)-f(x0-h))/(2*h);
//     }else if(order==2){
//         return (f(x0+h) - 2*f(x0) + f(x0-h))/pow(h,2);
//     }else{
//         return (derivative<NUMBER,T>(f,x0+h/2,o-1,2*h) - derivative<NUMBER,T>(f,x0-h/2,o-1,2*h) )/h;
//     }
// }

////////// DERIVATIVE //////////

template<class T>
inline T derivative(
        const std::function<T(T)> &f, 
        const T x0, T order=1, T h=1e-2
    ){
    int o = (int)order;
    if(o<=0){
        return f(x0);
    }else if(o==1){
        return (f(x0+h)-f(x0-h))/(2*h);
    }else if(o==2){
        return (f(x0+h) - 2*f(x0) + f(x0-h))/std::pow<double>((double)h,2);
    }else{
        return (derivative<T>(f,x0+h/2,order-1,2*h) - derivative<T>(f,x0-h/2,order-1,2*h) )/h;
    }
}


inline number derivative(const std::function<number(number)> &f, const number x0, number order, number h)
{
    return derivative<number>(f,x0,order,h);
}

inline fnumber derivative(const std::function<fnumber(fnumber)> &f, const fnumber x0, fnumber order, fnumber h)
{
    return derivative<fnumber>(f,x0,order,h);
}

inline double derivative(const std::function<double(double)> &f, const double x0, double order, double h)
{
    return derivative<double>(f,x0,order,h);
}



// inline float derivative(
//         const std::function<float(float)> &f, 
//         const float x0, float order=1, float h=1e-2
//     ){
//     return derivative<float>(f,x0,order,h);
// }

////////// DIFF //////////

template<class T>
inline NDArray<T> diff(NDArray<T> v, T iter=1){
    if(iter<=0) return v;
    else{
        if(v.shape(0) >= 2){
            NDArray<T> diffV;
            diffV.resize(v.shape(0)-1);
            
             DM4th::Parallel::loop<int>(
                EDM4thParallelSettings::DEFAULT,
                0, diffV.data_size(), 1, // from, to, step

                [&](const int &j) 
                {
                    diffV(j) = (v(j+1) - v(j));
                }
                
            );

            return diff(diffV,iter - 1);
        }else{
            return NDArray<T>();
        }
    }
}

inline NDArray<number> diff(NDArray<number> v, number iter)
{
    return diff<number>(v, iter);
}

inline NDArray<fnumber> diff(NDArray<fnumber> v, fnumber iter)
{
    return diff<fnumber>(v, iter);
}

inline NDArray<double> diff(NDArray<double> v, double iter)
{
    return diff<double>(v, iter);
}

// Integral
// template<template<class> class NUMBER=_number, class T=double>
// inline NUMBER<T> integral(const std::function<NUMBER<T>(NUMBER<T>)> &f, const NUMBER<T> &a, const NUMBER<T> &b, const NUMBER<T> subintervals){
//     int n = subintervals.real();
//     NUMBER<T> h = (b-a)/n;
    
//     NUMBER<T> s;
//      DM4th::Parallel::loopReduce<NUMBER<T>, int>(
//         EDM4thParallelSettings::OMP_PARALLEL | EDM4thParallelSettings::ADD, 
//         0, n, 1, // from, to, step
        
//         [&](const NUMBER<T> &acum, const int &j)
//         {
//             return acum + f(a+h*(j+0.5));
//         },
//         s
//     );

//     return s*h;
// }

template<class T=double>
inline T integral(const std::function<T(T)> &f, const T &a, const T &b, T subintervals=1000){
    int n = (int)subintervals;
    T h = (b-a)/n;
    
    T s;
     DM4th::Parallel::loopReduce<T, int>(
        EDM4thParallelSettings::DEFAULT | EDM4thParallelSettings::ADD, 
        0, n, 1, // from, to, step
        
        [&](const T &acum, const int &j)
        {
            return acum + f(a+h*(j+0.5));
        },
        s
    );

    return s*h;
}

inline number integral(const std::function<number(number)> &f, const number& a, const number& b, const number subintervals)
{
    return integral<number>(f, a, b, subintervals);
}

inline fnumber integral(const std::function<fnumber(fnumber)> &f, const fnumber& a, const fnumber& b, const fnumber subintervals)
{
    return integral<fnumber>(f, a, b, subintervals);
}

inline double integral(const std::function<double(double)> &f, const double& a, const double& b, const double subintervals)
{
    return integral<double>(f, a, b, subintervals);
}

// Runge-Kutta 4
template<class T>
inline T RK4(const std::function<T(T,T)> &fd, T t0, T w, T tn, const T &iter=100)
{
    T k1, k2, k3, k4;
    T h = (tn - t0) / iter;
    for(T t=0; t<tn; t+=h)
    {
        k1 = h * fd(t    , w);
        k2 = h * fd(t+h/2, w+k1/2);
        k3 = h * fd(t+h/2, w+k2/2);
        k4 = h * fd(t+h  , w+k3);
        w = w + (k1 + 2*k2 + 2*k3 + k4)/6;
    }
    return w;
}

inline number RK4(const std::function<number(number,number)> &fd, number t0, number w, number tn, const number &iter)
{
    return RK4<number>(fd, t0, w, tn, iter);
}

inline fnumber RK4(const std::function<fnumber(fnumber,fnumber)> &fd, fnumber t0, fnumber w, fnumber tn, const fnumber &iter)
{
    return RK4<fnumber>(fd, t0, w, tn, iter);
}

inline double RK4(const std::function<double(double,double)> &fd, double t0, double w, double tn, const double &iter)
{
    return RK4<double>(fd, t0, w, tn, iter);
}
}