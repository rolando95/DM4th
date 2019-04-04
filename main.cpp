//#include <number.h>
#include "_Vector.h"
#include "_Matrix.h"
#include <string>
#include <iostream>

using namespace std;

int main(){
    
    Vector a(1,2,3);
    Matrix b;
    b.resize(3,3);
    b[0] = a;
    print(a,"\n",b,"\n",b.getCol(2));
    b.setCol(2,Vector(7,8,9));
    print(b);
    return 0;
}
