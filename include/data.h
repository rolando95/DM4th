#ifndef __DATA_H__
#define __DATA_H__

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

// Entrada de un numero por consola
template<class T>
void input(T &var,string msg=""){
    cout<<msg;
    cin>>var;
}

#endif
