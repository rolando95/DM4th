#include <iostream>
#include <string>
#include "N.h"
using namespace std;
//Expresiones con numero de aurgumentos infinitos
void print();
template<class T, class ... Types>
void print(const T& first, const Types& ... args){
    cout<<first<<" ";
    print(args...);
}

// Entrada de datos utilizando un input similar al de python
N input(string msg="");