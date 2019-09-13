#pragma once

#include "_BaseTree_impl.h"
#include "../_Array/_Array.h"

//class Tree: public _TreeManager<Tree,Number>{
template<class T>
class TemplateTree: public _TreeDataManager<TemplateTree,T>
{
        typedef _TreeDataManager<TemplateTree,T> super;
    public:
        inline T &node();
        inline T &item();
        template<class ... U> inline T &item(U ... args);

        template<class CHILD, class ... U> TemplateTree<T> &operator()(CHILD idx, U ... args) const;
        // template<class CHILD, class ... U> const inline TemplateTree<T> &operator()(U ... args) const;
        template<class CHILD> inline TemplateTree<T> &operator()(CHILD idx) const;
        // template<class U> inline TemplateTree<T> &operator()(NDArray<U> axisTree, int level=0);

        
        inline void resizeChildren(int size);

};