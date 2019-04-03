//#include <number.h>
#include "_Vector.h"
#include "_Matrix.h"
#include <string>
#include <iostream>

using namespace std;

int main(){
    Matrix a = Matrix(
        Vector(1,2,3),
        Vector(4,5,6),
        Vector(7,8,9)
    );
    print(a);

    Vector b = a[0];
    b[2] = 0;
    print(a);
    print(b);
    a.appendCol(b);
    print(a);
    return 0;
}
