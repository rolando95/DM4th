#include <string>
#include <iostream>
#include <number.h>
using namespace std;

int main()
{
    number::precision = 2;
    number A=2i, B=2;
    cout<<"A   : "<< A      <<endl;//" "<<(std::complex<double>)A<<endl;
    cout<<"sin : "<< sin(A) <<endl;//" "<<sin((std::complex<double>)A)<<endl;
    cout<<"cos : "<< cos(A) <<endl;//" "<<cos((std::complex<double>)A)<<endl;
    cout<<"tan : "<< tan(A) <<endl;//" "<<tan((std::complex<double>)A)<<endl;
    cout<<"cot : "<< cot(A) <<endl;//" "<<(std::complex<double>)1/tan((std::complex<double>)A)<<endl;
    cout<<"sec : "<< sec(A) <<endl;//" "<<(std::complex<double>)1/cos((std::complex<double>)A)<<endl;
    cout<<"csc : "<< csc(A) <<endl;//" "<<(std::complex<double>)1/sin((std::complex<double>)A)<<endl;
    cout<<"ln  : "<< ln(A)  <<endl;//" "<<log(A.r)<<endl;
    cout<<"logn: "<< logn(A)<<endl;//" "<<log10(A.r)<<endl;
    cout<<"logn: "<< pow(A,B)<<endl;//" "<<pow2(A,B)<<endl;
    cout<<"sqrt: "<< sqrt(A)<<endl;//" "<<sqrt((std::complex<double>)A)<<endl;
}