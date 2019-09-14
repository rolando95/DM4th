#pragma once

#include "_TemplateArray_impl.h"

namespace DM4th
{

template<class T=float>
class NDArray: public TemplateArray<T>
{
    typedef TemplateArray<T> super;
    public:
        NDArray(){}
        NDArray(const super &other){ static_cast<super&>(*this) = other; }
        //NDArray(range<T> other) { static_cast<super&>(*this) = other; }
        NDArray(const std::string &other){ static_cast<super&>(*this) = other; };
        NDArray(const char *other){ static_cast<super&>(*this) = std::string(other); };
};

template<>
class NDArray<bool>: public TemplateArray<bool>
{
    typedef TemplateArray super;
    public:
        NDArray(){}
        NDArray(const super &other){ static_cast<super&>(*this) = other; }
        NDArray(const std::string &other){ static_cast<super&>(*this) = other; };
        NDArray(const char *other){ static_cast<super&>(*this) = std::string(other); };
        
        NDArray<bool> operator!() 
        {
            NDArray<bool> result;
            result.resize(super::shape());
            for(int j=0; j<super::c_arr_size(); ++j)
            {
                result.c_arr_item(j) = !super::c_arr_item(j); 
            }
            return result;
        }
};


// Specialization methods
inline std::ostream& operator<<(std::ostream& stream, const NDArray<std::string> &arr){ return arr.ostream(stream,4,true); }

}