#include "number.h"
#include <string>
#include <iostream>
#include <thread>
#include <windows.h>
using namespace std;

Number f(Number x){
    return x*x+2;
}
int main(){
    Vector a = range(10,0,-2);
    print(a);
    return 0;
}
