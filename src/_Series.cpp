#include "../include/_Math/_Series.h"
#include "../include/_Math/_Differential.h"

Number fibonacci(Number n){
    return (pow(phi,n) - cos(n*pi)*pow(phi,-n))/sqrt(5);
}

Number factorial(const Number &n){
    Number x = 1;
    if(floor(n.real())==n && n>=0){ // Es numero entero positivo 
        for(auto i=1; i<=n; ++i){
            x *= i;
        }
    }else{
        x = gamma(n+1);
    }
    return x;
}

Number sumatory(Function f, NDArray<Number> v, const Number interval){
    Number x=0;
    for(Number j=0; j>=0 && j<v.shape(0); j+=interval){
        x += f(v(j));
    }
    return x;
}
Number sumatory(Function f, const Number &begin, const Number &end, const Number interval){
    Number x=0;
    for(Number j=begin; j>=begin && j<=end; j+=interval){
        x += f(j);
    }
    return x;
}
Number sumatory(NDArray<Number> v, Number begin, Number end, Number interval){
    Number x=0;
    if(v.shape(0)>0){
        if(begin<0) begin = 0;
        if(end<0 || end>v.shape(0)) end = v.shape(0);
        for(Number j=begin; j>=begin && j<end; j+= interval){
            x += v(j);
        }
    }
    return x;
}
Number product(Function f, NDArray<Number> v, const Number interval){
    Number x=1;
    for(Number j=0; j>=0 && j<v.shape(0); j+=interval){
        x *= f(v(j));
    }
    return x;
}
Number product(Function f, const Number &begin, const Number &end, const Number interval){
    Number x=1;
    for(Number j=begin; j>=begin && j<=end; j+=interval){
        x *= f(j);
    }
    return x;
}