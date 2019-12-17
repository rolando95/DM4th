#pragma once

#include "../Array/BaseArray_impl.h"

namespace DM4th
{

namespace Internal
{

template<template<class> class Tree, class T>
class TreeData
{
    private:
        std::atomic<int> _ref{0};
    public:

        BaseArray<Tree<T>> array;
        T                   node;  
        void incrRef();
        void decrRef();
        int refCount() const;
};


template<template<class> class Tree, class T>
class TreeDataManager
{
    protected:
        TreeData<Tree,T> *_data = nullptr;

        void incrRef();
        void decrRef();

    public:
        
        TreeDataManager();
        TreeDataManager(const TreeDataManager<Tree,T> &other);
        ~TreeDataManager();

        TreeDataManager<Tree,T> const &operator=(const TreeDataManager<Tree,T> &other);

        

        //TreeData<Tree,T> const *TreeData() const;

};

}

}