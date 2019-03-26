#include <number.h>
#include <string>
#include <iostream>

Number main(){
    Matrix m[3][3]={{1,-4,8},{2,5,6},{3,0,7}};
    print(determinante(m,3));
    return 0;
}
