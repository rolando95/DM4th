//#include <number.h>
#include "_Vector.h"
#include "_Matrix.h"
#include <string>
#include <iostream>

using namespace std;

int main(){
    Matrix a;
    Vector b;
    a.resize(3,3);
    b = a[0];
    a[2][2] = 10;
    a[0][0] = 1;
    print(a);
    a.resize(5,5);
    print(a);
    a.resize(2,2);
    print(a);
    a.resize(4,4);
    print(a);
    print(b);
    return 0;
}
