#ifndef __ARRAY_H__
#define __ARRAY_H__

#include "_TemplateArray_impl.h"


template<class T=float>
class NDArray: public TemplateArray<T>
{
    typedef TemplateArray<T> super;
    public:
        NDArray(){}
        NDArray(const super &other){ static_cast<super&>(*this) = other; }
        NDArray(range<T> other) { static_cast<super&>(*this) = other; }
};

template<>
class NDArray<bool>: public TemplateArray<bool>
{
    typedef TemplateArray super;
    public:
        NDArray(){}
        NDArray(const super &other){ static_cast<super&>(*this) = other; }
        //NDArray(const range<bool> &other) { super(other); }
};


#endif