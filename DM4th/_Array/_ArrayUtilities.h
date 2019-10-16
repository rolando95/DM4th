#pragma once
#include "_TemplateArray.h"

namespace DM4th
{

template<class T>
T mult(TemplateArray<T> arr)
{
    T result = 1;
    int size = arr.data_size();
    for(int j=0; j<size; ++j){
        result*=arr.data_item(j);
    }
    return result;
}


template<class T>
T sum(TemplateArray<T> arr)
{
    T result = 0;
    int size = arr.data_size();
    for(int j=0; j<size; ++j){
        result+=arr.data_item(j);
    }
    return result;
}

template<class T>
T min(TemplateArray<T> arr)
{
    T result = INF;
    int size = arr.data_size();
    for(int j=0; j<size; ++j){
        if(arr.data_item(j) < result)
        {
            result=arr.data_item(j);
        }
    }
    return result;
}

template<class T>
T max(TemplateArray<T> arr)
{
    T result = INF;
    int size = arr.data_size();
    for(int j=0; j<size; ++j){
        if(arr.data_item(j) > result)
        {
            result=arr.data_item(j);
        }
    }
    return result;
}

template<class T>
int count(TemplateArray<T> arr){ return arr.data_size(); }

template<class T, class U, class ... V>
void _items(TemplateArray<T> &arr, int axis, U first, V ... args)
{
    arr.data_item(axis) = (T)first;
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

template<class T>
TemplateArray<T> range(T begin, T end, T step)
{
    TemplateArray<T> result;
    DM4thAssert( (end>begin && step>0) || (end<begin && step<0));
    int count = 0;
    T j = begin;
    if(step>0)
    {
        while(j<end)
        {
            ++count;
            j += step;
        }
    }else
    {
        while(j>end)
        {
            ++count;
            j += step;
        }
    }

    j = begin;
    result.resize(count);
    int idx=0;
    
    while(idx<count)
    {
        result.item(idx) = j;
        j+=step;
        ++idx;
    }

    return result;
}

template<class T>
inline TemplateArray<T> range(T end)
{
    T begin = 0;
    T step = 1;
    if(end<begin)
    {
        step = -1;
    }
    return range<T>(begin, end, step);
}

template<class T>
inline TemplateArray<T> range(T begin, T end)
{
    T step = 1;
    if(end<begin)
    {
        step = -1;
    }
    return range<T>(begin, end, step);
}

template<class T, class ... U>
TemplateArray<T> repeat(T value, U ... axisSize)
{
    TemplateArray<T> result;
    int size = (int)mult(axisSize ...);
    result.resize(axisSize...);

    for(int j=0; j<size; ++j)
    {
        result.data_item(j) = value;
    }
    
    return result;
}

template<class T, class ...U>
TemplateArray<T> zeros(U ... axisSize)
{
    // TemplateArray<T> result;
    // int size = (int)mult(axisSize ...);
    // result.resize(axisSize...);

    // for(int j=0; j<size; ++j)
    // {
    //     result.data_item(j) = 0;
    // }

    
    // return result;
    return repeat<T>(0, axisSize...);
}

template<class T, class ...U>
TemplateArray<T> ones(U ... axisSize)
{
    // TemplateArray<T> result;
    // int size = (int)mult(axisSize ...);
    // result.resize(axisSize...);

    // for(int j=0; j<size; ++j)
    // {
    //     result.data_item(j) = 1;
    // }

    
    // return result;
    return repeat<T>(1, axisSize...);
}

template<class T, class ...U>
TemplateArray<T> identity(U ... axisSize)
{
    TemplateArray<T> result = zeros<T>(axisSize ...);
    //result.resize(axisSize...);

    TemplateArray<T> axis = items<T>(axisSize ...);
    int size = min<T>(axis);
    int disp = result._getAxisDisplacement(0) + 1;
    for(int j=0, idx=0; j<size; ++j, idx+=disp)
    {
        result.data_item(idx) = 1;
    }

    return result;
}

}