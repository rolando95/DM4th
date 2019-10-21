#pragma once

#include "_TemplateArray_impl.h"

namespace DM4th
{

template<class T=number>
class NDArray: public TemplateArray<T>
{
    typedef TemplateArray<T> super;
    public:
        NDArray(){}
        template<class ...U> NDArray(T *data, U ... axis) { static_cast<super&>(*this) = TemplateArray<T>(data, axis ...); }
        NDArray(T *data, const TemplateArray<int> &axisArray) { static_cast<super&>(*this) = TemplateArray<T>(data, axisArray); };
        NDArray(const super &other){ static_cast<super&>(*this) = other; }
        NDArray(const typename super::SubArray &other){ static_cast<super&>(*this) = other; }
        explicit NDArray(const std::string &other){ static_cast<super&>(*this) = other; };
        explicit NDArray(const char *other){ static_cast<super&>(*this) = std::string(other); };
        template<class U> explicit operator NDArray<U>() { return static_cast<TemplateArray<U>>(*this); }
};

template<>
class NDArray<bool>: public TemplateArray<bool>
{
    typedef TemplateArray super;
    public:
        NDArray(){}
        template<class ...U> NDArray(bool *data, U ... axis) { static_cast<super&>(*this) = TemplateArray<bool>(data, axis ...); }
        NDArray(bool *data, const TemplateArray<int> &axisArray) { static_cast<super&>(*this) = TemplateArray<bool>(data, axisArray); };
        NDArray(const super &other){ static_cast<super&>(*this) = other; }
        NDArray(const typename super::SubArray &other){ static_cast<super&>(*this) = other; }
        explicit NDArray(const std::string &other){ static_cast<super&>(*this) = other; };
        explicit NDArray(const char *other){ static_cast<super&>(*this) = std::string(other); };
        
        NDArray<bool> operator!() 
        {
            NDArray<bool> result;
            result.resize(super::shape());
            for(int j=0; j<super::data_size(); ++j)
            {
                result.data_item(j) = !super::data_item(j); 
            }
            return result;
        }
};


// Specialization methods
inline std::ostream& operator<<(std::ostream& stream, const NDArray<std::string> &arr){ return arr.ostream(stream,4,true); }

}