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
struct _Array
{
    Node(){
        allocArray(1);
    }
    T *array = nullptr;
    int *_rows = nullptr;
    inline void allocArray(int size){
        array = new T[size];
        assert(array);
        _rows = new int(size);
    }
    inline void resizeArray(int size){
        if(array) {
            T *tmp = (T*) realloc(array, size*sizeof(T));
            if(!tmp) {
                tmp = new T[size];
                int max = (*_rows>size)?size:*_rows;
                for(int j=0; j<max; j++){
                    tmp[j] = array[j];
                }
                delete[] array;
                array = tmp;
                tmp = nullptr;
            }else{
                array = tmp;
                tmp = nullptr;
            }
        }
        assert(array);
        *_rows = size;
    }
    inline void freeArray(){
        delete[] array;
        array = nullptr;
        delete _rows;
        _rows = nullptr;
    }
};
#endif
