#pragma once

#include "BaseTree_impl.h"
#include "../Array/NDArray.h"
//class Tree: public TreeManager<Tree,number>{

namespace DM4th
{

template<class T>
class DTree: public DM4th::Internal::TreeDataManager<DTree,T>
{
    public:
        DTree();  
        DTree(const std::string &other);

        inline T &node() const;
        inline T &item() const;

        inline DTree<T> &child(number idx) const;
        inline DTree<T> &child(int idx) const;
        template<class ... U> DTree<T> &child(number idx, U ... args) const;
        template<class ... U> DTree<T> &child(int idx, U ... args) const;
        template<class U> const DTree<T> &child(const NDArray<U> &axis, int level=0) const;
        template<class U> DTree<T> &child(const NDArray<U> &axis, int level=0);
        
        DTree<T> getCopy() const;
        void printTreeStructure() const;

        inline explicit operator T() { return (T)this->node(); }

        template<class U>
        inline DTree<T> &operator()(U axis);
        template<class ... U>
        inline DTree<T> &operator()(U ... args);

        inline int size() const;
        inline void resize(int size);

        template<class U>
        void push(const U &value, const int idx=END);

        /*
        A copy of the tree is going to be inserted
        To insert by reference use pushTreeRef
        */
        template<class U>
        inline void pushTree(const DTree<U> &value, const int idx=END);

        template<class U>
        void pushTreeRef(const DTree<U> &value, const int idx=END);

        DTree<T> pop(const int idx=END);
        //DTree<T> pop(DTree<T> &ref);

        NDArray<int> indexOf(const T value);

        inline DTree<T> &left();
        inline DTree<T> &right();

        std::ostream& ostream(std::ostream& stream, int level=0, int ident=2, bool quotes=false) const;
        std::istream& istream(std::istream& stream);

        void loadFile(std::string path);
        void saveFile(std::string path);
    private:
        void _printTreeStructure(int level=0, std::string tab="", bool last=false) const;
        bool _indexOf(const T value, NDArray<int> &result);
};

template<class T>
std::ostream& operator<<(std::ostream&, const DTree<T>&);
template<class T>
std::istream& operator>>(std::istream&, DTree<T>&);

}