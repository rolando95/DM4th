#ifndef __TREE_H__
#define __TREE_H__

#include "_Matrix.h"

class Tree: protected _TreeManager<Tree,Number>{
public:
    Tree();
    Tree(Number);

    inline Number getValue() {return *_value;}
    inline void setValue(Number n){ *_value = n;}
    inline int childLength(){return *_rows;}
    // Acceso a hijos del nodo
    inline Tree& operator[](Number n){
        int pos = (int)n;
        assert(pos>=0 && pos<*_rows);
        return _data->array[pos];
    }    
    void resize(const Number&);
    Number appendChild(Number, Number=-1);

    void printStructure();
};

#endif