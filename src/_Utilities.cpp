#include "../include/_Number/_Utilities.h"

//Range class
template class range<int>;
template class range<float>;
template class range<double>;

template<class T> range<T>::range(): _begin(0), _end(0), _step(1) {}

template<class T> range<T>::range(T end){
    _end = end;
    if(end<0){
        _isInverse = true;
        _step = -1;
    }
}

template<class T> range<T>::range(T begin, T end){
    _begin = begin;
    _end = end;
    _step = 1;
    if(begin>end){
        _isInverse = true;
        _step = -1;
    }
}

template<class T> range<T>::range(T begin, T end, T step){
    _begin = begin;
    _end = end;
    _step = step;
    if(begin>end){
        _isInverse = true;
    }
    assert(
        (begin<end && step>0) ||
        (begin>end && step<0)
    );
}

template<class T> range<T>::operator Array<T>(){
    int count=0;
    {
        T j=_begin;
        if(!_isInverse){
            while(j<_end){
                ++count;
                j+=_step;
            }
        }else{
            while(j>_end){
                ++count;
                j+=_step;
            }
        }
    }
    
    Array<T> result;
    result.resize(count);

    {
        int idx=0;
        T j=_begin;
        while(idx<count){
            result.item(idx) = j;
            j+=_step;
            ++idx;
        }
    }
    
    return result;
}

