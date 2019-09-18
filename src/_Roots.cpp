#include "../DM4th/Math.h"

namespace DM4th
{

// Aproximaciones de raices
number newtonRaphson(Function f, number x1, number maxIter, number tolerance){
    x1 = x1.real();
    number y1 = (x1.imag()==0)? 1.00i : x1.imag();
    
    for(int n=0; n<maxIter.real() && abs(f(x1))>tolerance; ++n){
        x1 = x1 - f(x1)/derivative(f,x1);
    }
    if(abs(f(x1))>tolerance){
        for(int n=0; n<maxIter.real() && abs(f(y1))>tolerance; ++n){
            y1 = y1 - f(y1)/derivative(f,y1);
        }
        if(abs(f(y1))>tolerance) x1 = NAN;
        else x1 = y1;
    }
    return x1;
}
number newtonRaphson(Function f, Function fd, number x1, number maxIter, number tolerance){
    x1 = x1.real();
    number y1 = (x1.imag()==0)? 1.00i : x1.imag();
    
    for(int n=0; n<maxIter.real() && abs(f(x1))>tolerance; ++n){
        x1 = x1 - f(x1)/fd(x1);
    }
    if(abs(f(x1))>tolerance){
        for(int n=0; n<maxIter.real() && abs(f(y1))>tolerance; ++n){
            y1 = y1 - f(y1)/fd(y1);
        }
        if(abs(f(y1))>tolerance) x1 = NAN;
        else x1 = y1;
    }
    return x1;
}
number secantMethod(Function f, number x0, number x1, number maxIter, number tolerance){
    x0 = x0.real(); x1 = x1.real();
    number x2;

    number y0 = x0.imag()==0? 1.00i : x0.imag();
    number y1 = x1.imag()==0? 1.01i : x1.imag();
    number y2;

    for(int n=0; n<maxIter && abs(f(x1))>tolerance; ++n){
        x2 = x1 - f(x1) * ((x0-x1)/(f(x0) - f(x1)));
        x0 = x1; x1 = x2;
    }

    if(abs(f(x2))>tolerance){
        for(int n=0; n<maxIter && abs(f(y1))>tolerance; ++n){
            y2 = y1 - f(y1) * ((y0-y1)/(f(y0) - f(y1)));
            y0 = y1; y1 = y2;
        }
        if(abs(f(y2))>tolerance) x2 = NAN;
        else x2 = y2;
    }
    return x2;
}

}