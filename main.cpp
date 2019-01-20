#include <string>
#include <iostream>
#include <number.h>

int main(){
    V a,b;
    a = list(10,10,10);
    b = range(10,-1,-1.5);
    a.push(b);
    V d(a);
    for(auto n=0; n<a.length(); n++){
        print(a.data[n]);
    }
    return 0;
}