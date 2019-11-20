#pragma once
#include "NDArray.h"

namespace DM4th
{

namespace DM4thNDArrayUtils
{

    template<class T>
    T mult(NDArray<T> arr)
    {
        T result = 1;
        int size = arr.data_size();
        for(int j=0; j<size; ++j){
            result*=arr.data_item(j);
        }
        return result;
    }


    template<class T>
    T sum(NDArray<T> arr)
    {
        T result = 0;
        int size = arr.data_size();
        for(int j=0; j<size; ++j){
            result+=arr.data_item(j);
        }
        return result;
    }

    template<class T>
    T min(NDArray<T> arr)
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
    T max(NDArray<T> arr)
    {
        T result = -INF;
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
    int count(NDArray<T> arr){ return arr.data_size(); }

}

template<class T, class U, class ... V>
void _items(NDArray<T> &arr, int axis, U first, V ... args)
{
    arr.data_item(axis) = (T)first;
    _items(arr, axis+1, args...);
}

template<class T>
void _items(NDArray<T> &arr, int axis){}

template<class T, class ... U>
NDArray<T> items(T first, U ... args)
{
    NDArray<T> result;
    int size = DM4thUtils::count(first, args...);
    result.resize(size);
    _items(result, 0, first, args...);
    return result;
}

template<class T, class ... U>
NDArray<T> repeat(T value, U ... axisSize)
{
    NDArray<T> result;
    unsigned int size = (unsigned int)DM4thUtils::mult(axisSize ...);
    result.resize(axisSize...);

    for(unsigned int j=0; j<size; ++j)
    {
        result.data_item(j) = value;
    }
    
    return result;
}



template<class T, class ...U>
NDArray<T> zeros(U ... axisSize)
{
    return repeat<T>(0, axisSize...);
}

template<class T, class ...U>
NDArray<T> ones(U ... axisSize)
{
    return repeat<T>(1, axisSize...);
}

template<class T, class ...U>
NDArray<T> identity(int axis0, U ... axisSize)
{
    NDArray<T> result;
    if(DM4thUtils::count(axis0, axisSize...)>1)
    {
        result = zeros<T>(axis0, axisSize ...);
        //result.resize(axisSize...);

        NDArray<T> axis = items<T>(axis0, axisSize ...);
        int size = DM4thNDArrayUtils::min<T>(axis);
        int disp = result._getAxisDisplacement(0) + 1;
        for(int j=0, idx=0; j<size; ++j, idx+=disp)
        {
            result.data_item(idx) = 1;
        }
    }else{
        result = zeros<T>(axis0, axis0);
        for(int j=0; j<axis0; ++j)
        {
            result(j,j) = 1;
        }
    }

    return result;
}

template<class T>
NDArray<T> sort(NDArray<T> arr, bool reverse=false)
{
    NDArray<T> result = arr.getCopy();
    result.sort(reverse);
    return result;
}

template<class T=number>
class range 
{
    T _begin;
    T _end;
    T _step;
    int _size;
public:

    friend class iterator;

    range(T end) : _begin(0), _end(end), _step(1) 
    {
        if(this->_begin>this->_end)
        {
            this->_step = -1;
        }
        this->_size = this->_setSize();
    };

    range(T begin, T end) : _begin(begin), _end(end), _step(1) 
    {
        if(this->_begin>this->_end)
        {
            this->_step = -1;
        }
        this->_size = this->_setSize();
    };
    
    range(T begin, T end, T step) : _begin(begin), _end(end), _step(step)  
    {
        DM4thAssert( (end>=begin && step>0) || (end<=begin && step<0));
        this->_size = this->_setSize();
    };

    int size() { return this->_size; }

    operator NDArray<T>()
    {
        int size = this->_size;
        NDArray<T> result;
        T j = this->_begin;
        result.resize(size);
        int idx=0;
        
        while(idx<size)
        {
            result.item(idx) = j;
            j+=this->_step;
            ++idx;
        }

        return result;
    }

    class iterator
    {
        private:
            range<T> _data;
            T _ptr;
        public:
            iterator(range<T> &data, T ptr=0) : _data(data), _ptr(ptr) {};
            bool operator==(iterator other){ return (this->_ptr == other._ptr); }
            bool operator!=(iterator other){ return !(*this==other); }
            iterator &operator++(){ this->_ptr+=_data._step; return *this; }
            iterator operator++(int){ iterator result(this->_data, this->_ptr); this->_ptr+=_data._step; return result; }
            const T &operator*(){ return this->_ptr; }
    };

    iterator begin(){ return iterator(*this, this->_begin); }
    iterator end(){ return iterator(*this, this->_end); }


private:
    int _setSize() 
    { 
        int size = 0;
        T j = this->_begin; 
        if(this->_step>0)
        {
            while(j<this->_end)
            {
                ++size;
                j += this->_step;
            }
        }else
        {
            while(j>this->_end)
            {
                ++size;
                j += this->_step;
            }
        }

        this->_end = j;
        return size; 
    }
};

typedef range<int> slice;

template<class T, class U, class ... V>
void _map(std::function<T(T)> f, NDArray<T> &arr, int axis, U first, V ... args)
{
    arr.data_item(axis) = (T)f(first);
    _map(f, arr, axis+1, args...);
}

template<class T>
void _map(std::function<T(T)> f, NDArray<T> &arr, int axis){}

template<class T, class ... U>
NDArray<T> map(std::function<T(T)> f, T first, U ... args)
{
    NDArray<T> result;
    int size = DM4thUtils::count(first, args ...);
    result.resize(size);
    _map(f, result, 0, first, args...);
    return result;
}

template<class T>
NDArray<T> map(std::function<T(T)> f, NDArray<T> args)
{
    NDArray<T> result;
    result.resize(args.data_size());
    for(int j=0; j<args.data_size(); ++j)
    {
        result(j) = f(args(j));
    }
    return result;
}

template<class T, class U>
NDArray<U> map(std::function<U(T)> f, NDArray<T> args)
{
    NDArray<U> result;
    result.resize(args.data_size());
    for(int j=0; j<args.data_size(); ++j)
    {
        result(j) = f(args(j));
    }
    return result;
}

}