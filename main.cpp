#include "number.h"
#include <string>
#include <iostream>
#include <thread>
using namespace std;

int main(){
    Tree a, b;
    b.loadFile("ejemplo.txt");
    b.printStructure();
    a.setValue(2);
    a.appendChild(3);
    a.appendChild(7);
    a[0].appendChild(4);
    a[0][0].appendChild(9);
    a[0].appendChild(5);
    a[0][1].appendChild(6);
    a[0][1].appendChild(8);
    a[1].appendChild(10);
    a[1][0].appendChild(11);
    a[1][0][0].appendChild(12);
    a.printStructure();
    a.saveFile("ejemplo.txt");
    getchar();
    return 0;
}
