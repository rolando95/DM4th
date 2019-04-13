#ifndef __DATA_H__
#define __DATA_H__

//#define REFDEBUG

#include <iostream>
#include <string>
#include <cassert>
#include "_Number.h"

#ifdef REFDEBUG
    #include <typeinfo>
    #include <cxxabi.h>
    #include "console.h"
#endif

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
        }else{
            allocArray(size);
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
    #ifdef REFDEBUG
        std::string type = abi::__cxa_demangle(typeid(T).name(),0,0,0);
    #endif
    int *_rows = nullptr;
    int *_cols = nullptr;
    int *_ref = nullptr;
     _Array<T> *_data = new _Array<T>();

    void _alloc(){
        //_data->allocArray(0);
        _ref = new int(1);
        _rows = new int(0);
        _cols = new int(0);

        #ifdef REFDEBUG
            //setTextColor(GREEN);
            std::cout<<"\nNew ";
            //setTextColor(WHITE);
            std::cout<<type<<" Array: "<<this<<"\n";
        #endif
    }

    void _free(){
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
        }

        #ifdef REFDEBUG
            //setTextColor(MAGENTA);
            std::cout<<"\nFree ";
            //setTextColor(WHITE); 
            std::cout<<type<<" Array: "<<this<<"\n";
        #endif  
    }

    void _addRef(){
        if(_ref != nullptr){
            *_ref += 1;

            #ifdef REFDEBUG
                std::cout<<"\n"<<type<<" "<<this;
                //setTextColor(YELLOW);
                std::cout<<" ref: "<<*_ref-1<<" -> "<<*_ref<<"\n";
                //setTextColor(WHITE);
            #endif
        }
    }
    void _subRef(){
        if(_ref != nullptr){
            *_ref -= 1;

            #ifdef REFDEBUG
                std::cout<<"\n"<<type<<" "<<this;
                //setTextColor(YELLOW);
                std::cout<<" ref: "<<*_ref+1<<" -> "<<*_ref<<"\n";
                //setTextColor(WHITE);
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
    void operator=(const _ArrayManager &A) {
        this->_subRef();
        this->_data = A._data;
        this->_rows = A._rows;
        this->_cols = A._cols;
        this->_ref = A._ref;
        this->_addRef();
    }
    ~_ArrayManager(){
         this->_subRef();
    }
};

template<class TreeClass, typename T>
class _TreeManager: protected _ArrayManager<TreeClass>{
protected:
    T* _value = nullptr;
public:
    void funcion(){
        
    }
    _TreeManager(){
        _value = new T();
    }
    void operator=(const _TreeManager &A){
        this->_subRef();
        this->_data = A._data;
        this->_rows = A._rows;
        this->_cols = A._cols;
        this->_ref = A._ref;

        this->_value = A._value;

        this->_addRef();
    }

    ~_TreeManager(){
        if(this->_ref != nullptr){
            if(this->_ref[0]==1 && _value!=nullptr){
                delete _value;
                _value = nullptr;
            }
        }
    }
};

/*
template<class T>
class Property{
    private:
    T (* _get)();
    void (* _set)(T);
    public:
    Property(T(*get)(), void(*set)(T)){
        _get=get;
        _set=set;
    }

    void operator=(T value){
        _set(value);
    }

    
    operator T(){
        return _get();
    }
};
*/
#endif
