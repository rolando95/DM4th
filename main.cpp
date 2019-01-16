#include <string>
#include <iostream>
#include <number.h>
using namespace std;

int main()
{
    number::precision = 2;
    number A=-1;
    cout<< A      <<" "<<(std::complex<double>)A<<endl;
    cout<< sin(A) <<" "<<sin((std::complex<double>)A)<<endl;
    cout<< cos(A) <<" "<<cos((std::complex<double>)A)<<endl;
    cout<< tan(A) <<" "<<tan((std::complex<double>)A)<<endl;
    cout<< cot(A) <<" "<<(std::complex<double>)1/tan((std::complex<double>)A)<<endl;
    cout<< sec(A) <<" "<<(std::complex<double>)1/cos((std::complex<double>)A)<<endl;
    cout<< csc(A) <<" "<<(std::complex<double>)1/sin((std::complex<double>)A)<<endl;
    cout<< pow(A,2)<<" "<<pow(A,2)<<" "<<arg(A);
}