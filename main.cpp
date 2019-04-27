#include "number.h"
#include <string>
#include <iostream>
#include <thread>
using namespace std;

Number f(Number x){
    return x*x+2;
}
int main(){
    Number a = 0, b = 9;
    print(a,b, a<b);
    Vector c = Vector(10,1,1,2,33,4,5,6,6,10);
    print(c.sort());
    return 0;
}
