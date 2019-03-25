#include <number.h>
#include <string>
#include <iostream>

Number f(Number x, Number y){
    return (5*x*x - y)/pow(e,x+y);
}

int main(){
    print(rungeKutta(f,0,1,1));
    return 0;
}
