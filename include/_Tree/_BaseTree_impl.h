#pragma once

#include "_BaseTree.h"

//////////////////// _TreeData

template<template<class> class Tree, class T>
void _TreeData<Tree,T>::incrRef()
{
    ++_ref;
    //std::cout<<this<<" INCR+ REF: "<<_ref<<std::endl;
}

template<template<class> class Tree, class T>
void _TreeData<Tree,T>::decrRef()
{
    _ref -= 1;
    //std::cout<<this<<" DECR REF: "<<_ref<<std::endl;
    if(this->_ref <= 0 && !array.isFree())
    { 
        array.freeArray(); 
    }
}

template<template<class> class Tree, class T>
int  _TreeData<Tree,T>::refCount() const 
{ 
    return this->_ref;
}


//////////////////// _TreeDataManager

template<template<class> class Tree, class T>
void _TreeDataManager<Tree,T>::incrRef()
{
    if(this->_data == nullptr)
    {
        this->_data = new _TreeData<Tree, T>();
    }
    this->_data->incrRef();
}

template<template<class> class Tree, class T>
void _TreeDataManager<Tree,T>::decrRef()
{
    this->_data->decrRef();
    if(this->_data->refCount() <= 0) 
    {
        delete this->_data;
        this->_data = nullptr;
    }
    
}

template<template<class> class Tree, class T>
_TreeDataManager<Tree,T>::_TreeDataManager(){ 
    this->incrRef(); 
}

template<template<class> class Tree, class T>
_TreeDataManager<Tree,T>::_TreeDataManager(const _TreeDataManager<Tree,T> &other)
{
    _data = other._data;
    this->incrRef();
}
template<template<class> class Tree, class T>
_TreeDataManager<Tree,T>::~_TreeDataManager()
{ 
    this->decrRef(); 
}

template<template<class> class Tree, class T>
_TreeDataManager<Tree,T> const &_TreeDataManager<Tree,T>::operator=(const _TreeDataManager<Tree,T> &other) 
{
    if(this->_data==other._data) return *this;
    this->decrRef();
    this->_data = other._data;
    this->incrRef();
    return *this;
}

template<template<class> class Tree, class T>
int _TreeDataManager<Tree,T>::childrenCount(){
    return this->_data->array.size();
}

// template<template<class> class Tree, class T>
// _TreeData<Tree, T> const *_TreeDataManager<Tree,T>::_treeData() const
// {
//     return _data;
// }