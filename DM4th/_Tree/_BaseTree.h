#pragma once

#include "../_Array/_BaseArray_impl.h"

namespace DM4th
{

namespace DM4thInternal
{

template<template<class> class Tree, class T>
class _TreeData
{
    private:
        std::atomic<int> _ref{0};
    public:

        _BaseArray<Tree<T>> array;
        T                   node;  
        void incrRef();
        void decrRef();
        int refCount() const;
};


template<template<class> class Tree, class T>
class _TreeDataManager
{
    protected:
        _TreeData<Tree,T> *_data = nullptr;

        void incrRef();
        void decrRef();

    public:
        
        _TreeDataManager();
        _TreeDataManager(const _TreeDataManager<Tree,T> &other);
        ~_TreeDataManager();

        _TreeDataManager<Tree,T> const &operator=(const _TreeDataManager<Tree,T> &other);

        

        //_TreeData<Tree,T> const *_TreeData() const;

};

}

}