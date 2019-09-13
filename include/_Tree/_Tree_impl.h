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
inline int TemplateTree<T>::size(){
    return this->_data->array.size();
}


template<class T> 
inline void TemplateTree<T>::resize(int size)
{
    super::_data->array.resize(size);
} 

template<class T> 
inline TemplateTree<T> &TemplateTree<T>::left()
{
    if(this->size()<1) this->resize(1);
    return super::_data->array[0];
}

template<class T> 
inline TemplateTree<T> &TemplateTree<T>::right()
{
    if(this->size()<2) this->resize(2);
    return super::_data->array[1];
}

template<class T>
std::ostream& TemplateTree<T>::ostream(std::ostream& stream, int ident, bool quotes) const
{
    // int c_idx = 0;          
    // this->_ostream(stream, 0, c_idx, ident, quotes);
    // return stream;
}

template<class T>
std::istream& TemplateTree<T>::istream(std::istream& stream)
{
    // int c_size = 0;
    // std::queue<T> values;
    // bool shapeAllocated = false;
    // _handleIstreamSpacesAndNewLines(stream);

    // assert(stream.peek()=='['); stream.get();
    
    // this->_istream(stream, values, 0, c_size, shapeAllocated);
    // _handleIstreamSpacesAndNewLines(stream);

    // assert(stream.peek()==']'); stream.get();

    // super::_data->array.resize(c_size);
    // for(int j=0; j<c_size; ++j)
    // {
    //     assert(!values.empty());
    //     this->c_arr()[j] = values.front(); 
    //     values.pop();
    // }
    return stream;
}