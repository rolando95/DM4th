#include "../include/_Utilities/_Utilities.h"
#include "../include/_Number/_Number.h"
//Range class
template class range<int>;
template class range<float>;
template class range<double>;
template class range<Number>;

template<class T> range<T>::range(): _begin(0), _end(0), _step(1) {
    this->setCount();
}

template<class T> range<T>::range(T end){
    _begin = 0;
    _end = end;
    _step = 1;
    if(end<0){
        _isInverse = true;
        _step = -1;
    }
    this->setCount();
}

template<class T> range<T>::range(T begin, T end){
    _begin = begin;
    _end = end;
    _step = 1;
    if(begin>end){
        _isInverse = true;
        _step = -1;
    }
    this->setCount();
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
    this->setCount();
}

template<class T>  void range<T>::setCount(){
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
    this->_count = count;
}

void _handleIstreamSpacesAndNewLines(std::istream &stream)
{
    while(stream.peek()==' ' || stream.peek()=='\n')
    {
        if(stream.peek()==' ') stream>>std::ws;
        if(stream.peek()=='\n') stream.get();
        if(stream.peek()==' ') stream>>std::ws;
    }
}

