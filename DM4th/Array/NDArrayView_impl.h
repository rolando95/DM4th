#include "NDArrayView.h"

namespace DM4th
{

template<class T, class ... U>
NDArrayView<T, U...>::operator NDArray<T>()
{
    NDArray<T> result;
    result.resize(getDataSize());
    
    iterateOverNDArrayView([&](const int &j, T& item){
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

template<class T, class ... U>
inline const NDArrayView<T, U...> &NDArrayView<T, U...>::operator=(const T &other)
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
inline int NDArrayView<T, U ...>::getDataSize()
{
    const int size = getStrideAxis<0>();
    return size*queryAxisSize<0>(std::get<0>(this->_query));
}

template<class T, class ... U> template<int axis>
inline int NDArrayView<T, U...>::queryAxisSize(const int &value) const
{
    return 1;
}

template<class T, class ... U> template<int axis>
inline int NDArrayView<T, U...>::queryAxisSize(const NDArray<int> &value) const
{
    return value.data_size();
}

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

template<class T, class ... U> template<int axis>
inline int NDArrayView<T, U...>::queryAxisSize(const range<int> &value) const
{
    return value.size();
}
}