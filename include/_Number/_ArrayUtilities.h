#pragma once
#include "_Array.h"

template<class T>
T mult(Array<T> arr)
{
    T result = 1;
    T* c_arr = arr.c_arr();
    int size = arr.c_arr_size();
    for(int j=0; j<size; ++j){
        result*=c_arr[j];
    }
    return result;
}


template<class T>
T sum(Array<T> arr)
{
    T result = 0;
    T* c_arr = arr.c_arr();
    int size = arr.c_arr_size();
    for(int j=0; j<size; ++j){
        result+=c_arr[j];
    }
    return result;
}

template<class T>
int count(Array<T> arr){ return arr.c_arr_size(); }
