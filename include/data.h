#ifndef __DATA_H__
#define __DATA_H__

#include <iostream>
#include <string>
#include <cassert>
#include "_Number.h"

//Expresiones con numero de argumentos infinitos
void print();
template<class T, class ... Types>
void print(const T& first, const Types& ... args){
    std::cout<<first<<" ";
    print(args...);
}

// Entrada de un numero por consola
template<class T>
void input(T& last){
    std::cin>>last;
}
template<class T, class ... Types>
void input(T& first, Types& ... args){
    std::cin>>first;
    input(args...);
}

/*
 Low implementation!
*/
template<typename T>
struct Node
{
    Node(){
        allocArray(1);
    }

    T *array = nullptr;
    inline void allocArray(int size){
        array = new T[size];
        assert(array);
    }
    inline void resizeArray(int size){
        array = (T*) realloc(array, size*sizeof(T));
        assert(array);
    }
    inline void freeArray(){
        delete array;
        array = nullptr;
    }
};
#endif
