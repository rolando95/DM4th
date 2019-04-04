//#include <number.h>
#include "number.h"
#include <string>
#include <iostream>

using namespace std;

int main(){
    Matrix a = identity(3);
    Matrix b = identity(3);
    a[0][2] = 10;
    print(a>b);
    return 0;
}
