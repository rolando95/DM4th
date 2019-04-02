//#include <number.h>
#include "_Vector.h"
#include "_Matrix.h"
#include <string>
#include <iostream>

using namespace std;

int main(){
    Matrix a = Matrix("[[1,2,3],\
                        [4,5,6],\
                        [7,8,9]]");
    Matrix b = Matrix(
        Vector(10,11,12),
        Vector(13,14,15),
        Vector(16,17,18)
    );
    Vector c(19,20,21);
    Matrix d = a.getCopy();
    a.appendCol(c,2);
    print(a);
    d.appendCol(a,1);
    print(d.popCol());
    print(d.popRow(0));
    print(d);
    return 0;
}
