#ifndef __DATA_H__
#define __DATA_H__

#include <iostream>
#include <string>
#include "_Number.h"

//Expresiones con numero de aurgumentos infinitos
void print();
template<class T, class ... Types>
void print(const T& first, const Types& ... args){
    std::cout<<first<<" ";
    print(args...);
}

// Entrada de un numero por consola
template<class T>
void input(T &var,std::string msg=""){
    std::cout<<msg;
    std::cin>>var;
    fflush(stdin);
}
#endif
