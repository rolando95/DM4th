#include "../DM4th/Math.h"


namespace DM4th
{

number exp(number x){
    return pow(e,x);
}

number PI(number z, number tolerance){
    return gamma(z+1,tolerance);
}
// From Wikipedia https://es.wikipedia.org/wiki/Aproximaci%C3%B3n_de_Lanczos
number gamma(number z, number tolerance){
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
number derivative(Function f, const number &x0, const number order, const number h){
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
NDArray<number> diff(NDArray<number> v, number iter){
    if(iter<=0) return v;
    else{
        NDArray<number> diffV;
        if(v.shape(0) >= 2){
            for(auto j=0; j<v.shape(0)-1; ++j){
                diffV.push(v(j+1) - v(j));
            }
            return diff(diffV,iter - 1);
        }else{
            return NDArray<number>(0);
        }
    }
}
// Integral
number integral(Function f, const number &a, const number &b, const number subintervals){
    number n = int(round(subintervals).real())/3*3;
    number h = (b-a)/n;
    
    number s=0;
    for(number j=0; j<n; ++j){
        s+=f(a+h*(j+0.5));
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

}