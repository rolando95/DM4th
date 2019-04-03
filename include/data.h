#ifndef __DATA_H__
#define __DATA_H__

#include <iostream>
#include <string>
#include <cassert>
#include "_Number.h"
//#define REFDEBUG
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

template<typename T>
class _ArrayManager{
protected:
    int *_rows = nullptr;
    int *_cols = nullptr;
    int *_ref = nullptr;
     _Array<T> *_data = nullptr;
    void _alloc(){
        #ifdef REFDEBUG
        std::cout<<"New Array  ---------- N"<<std::endl;
        #endif
        _ref = new int(1);
        _rows = new int(0);
        _cols = new int(0);
    }
    void _free(){
        #ifdef REFDEBUG
        std::cout<<"Free Array ---------- F"<<std::endl; 
        #endif  
        //No resized Matrix (this->_data = nullptr)
        if(_data){
            _data->freeArray();
            delete _data;
            _data = nullptr;
            if(_ref){
                delete _ref;
                _ref = nullptr;
            }

            if(_rows){
                delete _rows;
                _rows = nullptr;
            }

            if(_cols){
                delete _cols;
                _cols = nullptr;
            }
        }else{
            //std::cout<<"!"<<std::endl;
        }
    }
    void _addRef(){
        if(_ref != nullptr){
            *_ref += 1;
            #ifdef REFDEBUG
            std::cout<<"Array ref "<<*_ref-1<<" -> "<<*_ref<<std::endl;
            #endif
        }
    }
    void _subRef(){
        if(_ref != nullptr){
            *_ref -= 1;
            #ifdef REFDEBUG
            std::cout<<"Array ref "<<*_ref+1<<" -> "<<*_ref<<std::endl;
            #endif
            if(*_ref<=0){ 
                this->_free();
            }
        }
    }
public:
    _ArrayManager(){
        this->_alloc();
    }
    virtual void operator=(const _ArrayManager &D) {
        this->_subRef();
        this->_data = D._data;
        this->_rows = D._rows;
        this->_ref = D._ref;
        this->_addRef();
    }
    ~_ArrayManager(){
         this->_subRef();
    }
};
#endif
