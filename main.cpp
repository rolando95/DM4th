#include <string>
#include <iostream>
#include <complex.h>
using namespace std;


int main()
{
    complex C, D; 
    int a = 5;
    C = 10.0i + 5 + 5.0i + a;
    D = C + 1 + 0.5i;
    cout<<D.r<<" "<<D.i;
    return 0;
}