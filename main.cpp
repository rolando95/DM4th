#include <number.h>
#include <string>
#include <iostream>

int main(){
    Matrix a;
    a.loadFile("ejemplo.txt");
    print(a);
    a*=2;
    a.saveFile("ejemplo.txt");
    return 0;
}
