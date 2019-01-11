#include <string>
#include <iostream>
#include <complex.h>
using namespace std;


int main()
{
    complex A, B, C, D; 
    D = (3 + 2.0i) / (1 - 2.0i);
    cout<<D.r<<" "<<D.i;
    return 0;
}