#include <string>
#include <iostream>
#include <number.h>

int main(){
    V a,b;
    a = array(10,10,10);
    b = array(6,7,8,9);
    a.push(b);
    for(auto n=0; n<a.length(); n++){
        print(a.data[n], 3+6i);
    }
    return 0;
}