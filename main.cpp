#include <string>
#include <iostream>
#include <number.h>

int main(){
    V a;
    a = array(5,2,3);
    for(auto n=0; n<a.length(); n++){
        print(a.data[n]);
    }
    return 0;
}