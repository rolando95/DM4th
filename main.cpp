#include <string>
#include <iostream>
#include <number.h>

N f(N x){
    return x*x+i;
}

N fd(N x){
    return 2*x;
}

int main(){
    cout<<integral(f,5,15)<<" "<<secantMethod(f)<<" "<<newtonRaphson(f,fd)<<endl;
    return 0;
}