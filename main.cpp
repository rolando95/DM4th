#include <string>
#include <iostream>
#include <N.h>

N f(N x){
    return pow(x,3) - 2*pow(x,2) + 3;
}

N fd(N x){
    return 3*pow(x,2) - 4*x;
}

int main()
{
    N::precision = 5;
    N A=10, B=2, C, D;
    
    cout<<"A   : "<<A<<endl;//" "<<(std::complex<double>)A<<endl;
    cout<<"B   : "<< B      <<endl;
    cout<<"asinh: "<<asinh(A)<<endl;
    cout<<"acosh: "<<acosh(A)<<endl;
    cout<<"atanh: "<<atanh(A)<<endl;
    cout<<"acoth: "<<acoth(A)<<endl;
    cout<<"asech: "<<asech(A)<<endl;
    cout<<"acsch: "<<acsch(A)<<endl;
}