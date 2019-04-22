#ifndef __TREE_H__
#define __TREE_H__

#include "_Matrix.h"


class Tree: public _TreeManager<Tree,Number>{
public:
    Tree();
    Tree(Number);

    inline Number getValue() const {return *_value;}

    inline void setValue(Number n){ *_value = n;}

    inline int childLength() const {return *_rows;}

    // Acceso a hijos del nodo
    inline Tree& operator[](Number n){
        int pos = (int)n;
        assert(pos>=0 && pos<*_rows);
        return _data->array[pos];
    } 
     // Acceso a hijos del nodo
    inline Tree& operator()(Number n){
        int pos = (int)n;
        assert(pos>=0 && pos<*_rows);
        return _data->array[pos];
    }    

    inline Tree& getChild(Number n) const { 
        int pos = (int)n;
        assert(pos>=0 && pos<*_rows);
        return _data->array[pos];
    }
    void resize(const Number&);

    void appendChild(Number, Number=-1);

    void appendChild(Tree&, Number=-1);
    void _appendRefChild(Tree&, Number=-1);

    // Carga valor de tipo Tree desde un fichero
    void loadFile(std::string url);
    // Guarda valor de tipo Tree en un fichero
    void saveFile(std::string url);

    Tree getCopy();
    
    void printStructure();
};

// Impresion en pantalla del Tree
std::ostream& operator<<(std::ostream&, const Tree&);

// Lectura en pantalla del Tree
std::istream& operator>>(std::istream&, Tree&);
#endif