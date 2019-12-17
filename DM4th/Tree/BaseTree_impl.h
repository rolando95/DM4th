#pragma once

#include "BaseTree.h"

namespace DM4th
{

namespace Internal
{
//////////////////// TreeData

template<template<class> class Tree, class T>
void TreeData<Tree,T>::incrRef()
{
    ++_ref;
    //std::cout<<this<<" INCR+ REF: "<<_ref<<std::endl;
}

template<template<class> class Tree, class T>
void TreeData<Tree,T>::decrRef()
{
    _ref -= 1;
    //std::cout<<this<<" DECR REF: "<<_ref<<std::endl;
    if(this->_ref <= 0)
    { 
        array.clear(); 
    }
}

template<template<class> class Tree, class T>
int  TreeData<Tree,T>::refCount() const 
{ 
    return this->_ref;
}


//////////////////// TreeDataManager

template<template<class> class Tree, class T>
void TreeDataManager<Tree,T>::incrRef()
{
    if(this->_data == nullptr)
    {
        this->_data = new TreeData<Tree, T>();
    }
    this->_data->incrRef();
}

template<template<class> class Tree, class T>
void TreeDataManager<Tree,T>::decrRef()
{
    this->_data->decrRef();
    if(this->_data->refCount() <= 0) 
    {
        delete this->_data;
        this->_data = nullptr;
    }
    
}

template<template<class> class Tree, class T>
TreeDataManager<Tree,T>::TreeDataManager(){ 
    this->incrRef(); 
}

template<template<class> class Tree, class T>
TreeDataManager<Tree,T>::TreeDataManager(const TreeDataManager<Tree,T> &other)
{
    _data = other._data;
    this->incrRef();
}
template<template<class> class Tree, class T>
TreeDataManager<Tree,T>::~TreeDataManager()
{ 
    this->decrRef(); 
}

template<template<class> class Tree, class T>
TreeDataManager<Tree,T> const &TreeDataManager<Tree,T>::operator=(const TreeDataManager<Tree,T> &other) 
{
    if(this->_data==other._data) return *this;
    this->decrRef();
    this->_data = other._data;
    this->incrRef();
    return *this;
}


// template<template<class> class Tree, class T>
// TreeData<Tree, T> const *TreeDataManager<Tree,T>::TreeData() const
// {
//     return _data;
// }

}

}