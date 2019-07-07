#ifndef __ARRAY_H__
#define __ARRAY_H__

#include "_TemplateArray.h"


template<class T=float>
class Array: public TemplateArray<T>
{
    typedef TemplateArray<T> super;
    public:
        Array(){}
        Array(const super &other){ static_cast<super&>(*this) = other; }
        Array(range<T> other) { static_cast<super&>(*this) = other; }
};

template<>
class Array<bool>: public TemplateArray<bool>
{
    typedef TemplateArray super;
    public:
        Array(){}
        Array(const super &other){ static_cast<super&>(*this) = other; }
        //Array(const range<bool> &other) { super(other); }
};
#endif