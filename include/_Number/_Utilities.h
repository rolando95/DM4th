#pragma once

#include <cassert>

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
