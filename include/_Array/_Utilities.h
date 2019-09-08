#pragma once
#include <cassert>
#include <istream>
template<class T=int>
class range{
    private:
        int _count;
        T _begin;
        T _end;
        T _step;
        bool _isInverse=false;

        void setCount();
    public:
        range();
        range(T end);
        range(T begin, T end);
        range(T begin, T end, T step);

        inline int count() const{
            return this->_count;
        }
        inline T begin() const {
            return this->_begin;
        }
        inline T end() const {
            return this->_end;
        }
        inline T step(){
            return this->_step;
        }
};


template<class T>
T mult(T last){
    return last;
}
template<class T, class ... U>
T mult(T first, U ... args){
    return first*mult(args...);
}


template<class T>
T sum(T last){
    return last;
}
template<class T, class ... U>
T sum(T first, U ... args){
    return first+sum(args...);
}

template<class T>
int count(T last){
    return 1;
}
template<class T, class ... U>
int count(T first, U ... args){
    return 1+count(args...);
}

void _handleIstreamSpacesAndNewLines(std::istream &stream);