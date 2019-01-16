#include <string>
#include <iostream>
#include <N.h>

int main()
{
    N::precision = 2;
    N A=5, B=2;
    cout<<"A   : "<< A      <<endl;//" "<<(std::complex<double>)A<<endl;
    cout<<"B   : "<< B      <<endl;
    cout<<"A\%B: "<< A%B    <<endl;
    cout<<"sin : "<< sin(A) <<endl;//" "<<sin((std::complex<double>)A)<<endl;
    cout<<"cos : "<< cos(A) <<endl;//" "<<cos((std::complex<double>)A)<<endl;
    cout<<"tan : "<< tan(A) <<endl;//" "<<tan((std::complex<double>)A)<<endl;
    cout<<"cot : "<< cot(A) <<endl;//" "<<(std::complex<double>)1/tan((std::complex<double>)A)<<endl;
    cout<<"sec : "<< sec(A) <<endl;//" "<<(std::complex<double>)1/cos((std::complex<double>)A)<<endl;
    cout<<"csc : "<< csc(A) <<endl;//" "<<(std::complex<double>)1/sin((std::complex<double>)A)<<endl;
    cout<<"ln  : "<< ln(A)  <<endl;//" "<<log(A.r)<<endl;
    cout<<"logn: "<< logn(A)<<endl;//" "<<log10(A.r)<<endl;
    cout<<"pow : "<< pow(A,B)<<endl;//" "<<pow2(A,B)<<endl;
    cout<<"sqrt: "<< sqrt(A)<<endl;//" "<<sqrt((std::complex<double>)A)<<endl;
}