#include "number.h"
#include <string>
#include <iostream>
#include <thread>
using namespace std;

int main(){
    Tree a,c;
    c.value = 17;
    a.value = 10;
    c.value = a.value;
    Number b = 5;
    a.value = b;
    b = a.value;
    b = 50 - a.value*a.value;
    print(b);
    print(b>=a.value);
    getchar();
    return 0;
}
