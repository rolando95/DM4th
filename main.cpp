#include <string>
#include <iostream>
#include <number.h>

N f(N x){
    return pow(x,3) - 2*pow(x,2) + 3;
}

N fd(N x){
    return 3*pow(x,2) - 4*x;
}

N f2(N x){return x*x+1;}
N f2d(N x){return x;}

int main()
{
    N::precision = 5;
    N A=2+10i, B=2, C=5, D;
    cout<<"A   : "<<A<<endl;//" "<<(std::complex<double>)A<<endl;
    cout<<"B   : "<< B      <<endl;
    cout<<"asinh: "<<asinh(A)<<endl;
    cout<<"acosh: "<<acosh(A)<<endl;
    cout<<"atanh: "<<atanh(A)<<endl;
    cout<<"acoth: "<<acoth(A)<<endl;
    cout<<"asech: "<<asech(A)<<endl;
    cout<<"acsch: "<<acsch(A)<<endl;
    cout<< 1/2<<endl;
    cout<<newtonRaphson(f2,f2d)<<endl;
    cout<<secantMethod(f2)<<endl;
}