#include "number.h"
#include <string>
#include <iostream>

using namespace std;

int main(){
    //Vector a = Vector(1,2,3,4);
    
    Tree a;
    a.setValue(10);
    a.resize(2);
    a[0].setValue(15);
    a[1].setValue(17);
    a[0].appendChild(1);
    a[0].appendChild(2);
    a[0].appendChild(5);
    a[0][1].appendChild(7-5i);
    a[0][1][0].appendChild(-12);
    a.printStructure();
    
    return 0;
}
