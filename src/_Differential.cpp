#include "../include/_Math/_Differential.h"

Number exp(Number x){
    return pow(e,x);
}

Number PI(Number z, Number tolerance){
    return gamma(z+1,tolerance);
}
// From Wikipedia https://es.wikipedia.org/wiki/Aproximaci%C3%B3n_de_Lanczos
Number gamma(Number z, Number tolerance){
    Number result;
    Number x;
    Number t;
    NDArray<Number> p = items<Number>(676.5203681218851,  
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
        for(Number j=0; j<p.shape(0); ++j){
            x += p(j)/(z+j+1);
        }
        t = z + p.shape(0) - 0.5;
        result = sqrt(2*pi) *pow(t,z+0.5) * exp(-t) * x;
    }

    if (abs(result.imag() - abs(result.imag()))<=tolerance){
        return result.real();
    }
    return result;
}

// Derivative
Number derivative(Function f, const Number &x0, const Number order, const Number h){
    Number o(abs(floor(order.real())));
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
NDArray<Number> diff(NDArray<Number> v, Number iter){
    if(iter<=0) return v;
    else{
        NDArray<Number> diffV;
        if(v.shape(0) >= 2){
            for(auto j=0; j<v.shape(0)-1; ++j){
                diffV.push(v(j+1) - v(j));
            }
            return diff(diffV,iter - 1);
        }else{
            return NDArray<Number>(0);
        }
    }
}
// Integral
Number integral(Function f, const Number &a, const Number &b, const Number subintervals){
    Number n = int(round(subintervals).real())/3*3;
    Number h = (b-a)/n;
    
    Number s=0;
    for(Number j=0; j<n; ++j){
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