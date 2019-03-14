#include <number.h>
#include <string>
#include <iostream>

Number funcionEjemplo(Number x){
    return x*x+1;
}

int main(){
    print("NewtonRaphson result:",newtonRaphson(funcionEjemplo));

    Vector a = range(0,10);
    print(a);

    Matrix b = identity(5);
    print(b);

    Vector c("[1,2,3,4,5]");
    print(c);
    
    Matrix d = Matrix("[[1,2],[3,4]]");
    print(d);

    return 0;
}
