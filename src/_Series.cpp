#include "../DM4th/_Math/_Series.h"
#include "../DM4th/_Math/_Differential.h"

namespace DM4th
{

number fibonacci(number n){
    return (pow(phi,n) - cos(n*pi)*pow(phi,-n))/sqrt(5);
}

number factorial(const number &n){
    number x = 1;
    if(floor(n.real())==n && n>=0){ // Es numero entero positivo 
        for(auto i=1; i<=n; ++i){
            x *= i;
        }
    }else{
        x = gamma(n+1);
    }
    return x;
}

number sumatory(Function f, NDArray<number> v, const number interval){
    number x=0;
    for(number j=0; j>=0 && j<v.shape(0); j+=interval){
        x += f(v(j));
    }
    return x;
}
number sumatory(Function f, const number &begin, const number &end, const number interval){
    number x=0;
    for(number j=begin; j>=begin && j<=end; j+=interval){
        x += f(j);
    }
    return x;
}
number sumatory(NDArray<number> v, number begin, number end, number interval){
    number x=0;
    if(v.shape(0)>0){
        if(begin<0) begin = 0;
        if(end<0 || end>v.shape(0)) end = v.shape(0);
        for(number j=begin; j>=begin && j<end; j+= interval){
            x += v(j);
        }
    }
    return x;
}
number product(Function f, NDArray<number> v, const number interval){
    number x=1;
    for(number j=0; j>=0 && j<v.shape(0); j+=interval){
        x *= f(v(j));
    }
    return x;
}
number product(Function f, const number &begin, const number &end, const number interval){
    number x=1;
    for(number j=begin; j>=begin && j<=end; j+=interval){
        x *= f(j);
    }
    return x;
}

}