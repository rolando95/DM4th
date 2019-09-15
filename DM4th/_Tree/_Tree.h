#pragma once

#include "_BaseTree_impl.h"
#include "../_Array/_Array.h"
#include "../_Number/_Number.h"
//class Tree: public _TreeManager<Tree,number>{

namespace DM4th
{

template<class T>
class TemplateTree: public _TreeDataManager<TemplateTree,T>
{
        typedef _TreeDataManager<TemplateTree,T> super;
    public:
        inline T &node() const;
        inline T &item() const;

        inline TemplateTree<T> &child(number idx) const;
        inline TemplateTree<T> &child(int idx) const;
        template<class ... U> TemplateTree<T> &child(number idx, U ... args) const;
        template<class ... U> TemplateTree<T> &child(int idx, U ... args) const;
        template<class U> TemplateTree<T> &child(const TemplateArray<U> &axis, int level=0) const;
        template<class U> TemplateTree<T> &child(const NDArray<U> &axis, int level=0) const;

        TemplateTree<T> getCopy() const;
        void printTreeStructure() const;

        template<class U>
        inline TemplateTree<T> &operator()(U axis);
        template<class ... U>
        inline TemplateTree<T> &operator()(U ... args);

        inline int size() const;
        inline void resize(int size);

        template<class U>
        void push(U value, const int idx=END);

        /*
        The tree will be copy before insert!!!
        To insert by ref, use pushTreeRef
        */
        template<class U>
        inline void pushTree(const TemplateTree<U> &value, const int idx=END);

        template<class U>
        void pushTreeRef(const TemplateTree<U> &value, const int idx=END);

        TemplateTree<T> pop(const int idx=END);

        inline TemplateTree<T> &left();
        inline TemplateTree<T> &right();

        std::ostream& ostream(std::ostream& stream, int level=0, int ident=2, bool quotes=false) const;
        std::istream& istream(std::istream& stream);

        void loadFile(std::string path);
        void saveFile(std::string path);
    private:
        void _printTreeStructure(int level=0, std::string tab="", bool last=false) const;
};

template<class T>
std::ostream& operator<<(std::ostream&, const TemplateTree<T>&);
template<class T>
std::istream& operator>>(std::istream&, TemplateTree<T>&);

}