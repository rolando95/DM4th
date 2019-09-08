#pragma once
#include "_Array.h"

template<class T>
T mult(TemplateArray<T> arr)
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
T sum(TemplateArray<T> arr)
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
int count(TemplateArray<T> arr){ return arr.c_arr_size(); }

template<class T, class U, class ... V>
void _items(TemplateArray<T> &arr, int axis, U first, V ... args)
{
    arr.c_arr()[axis] = (T)first;
    _items(arr, axis+1, args...);
}

template<class T>
void _items(TemplateArray<T> &arr, int axis){}

template<class T, class ... U>
TemplateArray<T> items(T first, U ... args)
{
    TemplateArray<T> result;
    int size = count(first, args...);
    result.resize(size);
    _items(result, 0, first, args...);
    return result;
}