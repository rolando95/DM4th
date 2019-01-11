#include <string>
#include <iostream>
#include <complex.h>

using namespace std;


int main()
{
    complex A, B, C, D;
    A = 3;
    B = 4-5.0i;
    cout<<"Ingresa un numero: ";
    cin>>C;
    D = A + B + C;
    cout<<A+B<<" "<<C<<" -- "<<D;
    getchar();
    return 0;
}