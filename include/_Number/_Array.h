#ifndef __ARRAY_H__
#define __ARRAY_H__

#include "_TemplateArray.h"


template<class T=float>
class ndArray: public TemplateArray<T>
{
    typedef TemplateArray<T> super;
    public:
        ndArray(){}
        ndArray(const super &other){ static_cast<super&>(*this) = other; }
        ndArray(range<T> other) { static_cast<super&>(*this) = other; }
};

template<>
class ndArray<bool>: public TemplateArray<bool>
{
    typedef TemplateArray super;
    public:
        ndArray(){}
        ndArray(const super &other){ static_cast<super&>(*this) = other; }
        //ndArray(const range<bool> &other) { super(other); }
};
#endif