#include <string>
#include <iostream>
#include <number.h>

int main(){
    V a;
    a = array(5,2,3);
    N b = input();
    for(auto n=0; n<a.length(); n++){
        print(a.data[n], 3+6i);
    }
    return 0;
}