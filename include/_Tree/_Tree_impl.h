#pragma once

#include "_Tree.h"

template<class T>
inline T &TemplateTree<T>::node()
{
    return super::_data->node;
}

template<class T>
inline T &TemplateTree<T>::item()
{
    return super::_data->node;
}

template <class T>  template<class ... U> 
inline T &TemplateTree<T>::item(U ... args)
{
    return this->operator()(args ...).node();
}

template<class T> template<class CHILD, class ... U>
TemplateTree<T> &TemplateTree<T>::operator()(CHILD idx, U ... args) const
{
    int x = (int)idx;
    return super::_data->array[x].operator()(args...);
}

template<class T> template<class CHILD>
inline TemplateTree<T> &TemplateTree<T>::operator()(CHILD idx) const
{
    int x = (int)idx;
    return super::_data->array[x];
}

template<class T> 
inline void TemplateTree<T>::resizeChildren(int size)
{
    super::_data->array.resize(size);
} 