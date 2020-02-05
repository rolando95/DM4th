#include "NDArrayView.h"

namespace DM4th
{

template<class T, class ... U>
NDArrayView<T, U...>::operator NDArray<T>() const
{
    NDArray<T> result;
    result._resizeEmpty(getDataSize());
    
    iterateOverNDArrayView([&](const int &j, const T& item){
        result.data_item(j) = item;
    });

    if(result.data_size()>1) setShape<0>(result,0);
    return result;
}

template<class T, class ... U>
inline const NDArrayView<T, U ...> &NDArrayView<T, U ...>::operator=(NDArrayView<T, U ...> &other)
{
    NDArray<T> tmp = NDArray<T>(other);

    if(tmp.data_size()>=this->getDataSize())
    {
        iterateOverNDArrayView([&](const int &j, T& item){
            item = tmp.data_item(j);
        });
    }else{
        iterateOverNDArrayView([&](const int &j, T& item){
            item = tmp.data_item(j%tmp.data_size());
        });
    }
    return *this;
}

template<class T, class ... U> template<class ... V>
inline const NDArrayView<T, U ...> &NDArrayView<T, U ...>::operator=(NDArrayView<T, V ...> &other)
{
    NDArray<T> tmp = NDArray<T>(other);

    if(tmp.data_size()>=this->getDataSize())
    {
        iterateOverNDArrayView([&](const int &j, T& item){
            item = tmp.data_item(j);
        });
    }else{
        iterateOverNDArrayView([&](const int &j, T& item){
            item = tmp.data_item(j%tmp.data_size());
        });
    }
    return *this;
}

template<class T, class ... U> template<class V>
inline typename std::enable_if< std::is_convertible<V,T>::value, const NDArrayView<T, U...>>::type 
&NDArrayView<T, U...>::operator=(const V &other)
{
    iterateOverNDArrayView([&](const int &j, T& item){
        item = other;
    });
    return *this;                   
} 

template<class T, class ... U>
inline const NDArrayView<T, U ...> &NDArrayView<T, U ...>::operator=(const NDArray<T> &other)
{
    if(other.data_size()>=this->getDataSize())
    {
        iterateOverNDArrayView([&](const int &j, T& item){
            item = other.data_item(j);
        });
    }else{
        iterateOverNDArrayView([&](const int &j, T& item){
            item = other.data_item(j%other.data_size());
        });
    }
    return *this;                   
} 

template<class T, class ... U>
inline void NDArrayView<T, U ...>::iterateOverNDArrayView(const std::function<void(const int &, T&)> &f)
{
    int idx = 0;
    _iterateOverNDArrayView<0>(idx, 0, f);
}     

template<class T, class ... U>
inline void NDArrayView<T, U ...>::iterateOverNDArrayView(const std::function<void(const int &, const T&)> &f) const
{
    int idx = 0;
    _iterateOverNDArrayView<0>(idx, 0, f);
}   

template<class T, class ... U>
inline int NDArrayView<T, U ...>::getDataSize() const
{
    const int size = getStrideAxis<0>();
    return size*queryAxisSize<0>(std::get<0>(this->_view));
}

// int
template<class T, class ... U> template<int axis>
inline int NDArrayView<T, U...>::queryAxisSize(const int &value) const
{
    if(value==ALL) return this->_ptr.shape(axis);
    return 1;
}

// NDArray<int>
template<class T, class ... U> template<int axis>
inline int NDArrayView<T, U...>::queryAxisSize(const NDArray<int> &value) const
{
    return value.data_size();
}

// NDArray<bool>
template<class T, class ... U> template<int axis>
inline int NDArrayView<T, U...>::queryAxisSize(const NDArray<bool> &value) const
{
    int size = 0;
    for(int j=0; j<value.data_size(); ++j)
    {
        if(value.data_item(j)==true) ++size;
    }
    return size;
}

// range
template<class T, class ... U> template<int axis>
inline int NDArrayView<T, U...>::queryAxisSize(const range<int> &value) const
{
    return value.size();
}

// slice
template<class T, class ... U> template<int axis>
inline int NDArrayView<T, U...>::queryAxisSize(const slice &value) const
{
    const int size =  value.size(this->_ptr, axis);
    return size;
}

}