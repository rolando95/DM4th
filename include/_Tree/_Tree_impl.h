#pragma once

#include "_Tree.h"

template<class T>
inline T &TemplateTree<T>::node() const
{
    return super::_data->node;
}

template<class T>
inline T &TemplateTree<T>::item() const
{
    return super::_data->node;
}

template<class T> 
inline TemplateTree<T> &TemplateTree<T>::child(Number idx) const
{
    return super::_data->array[(int)idx];
}

template<class T> 
inline TemplateTree<T> &TemplateTree<T>::child(int idx) const
{
    return super::_data->array[(int)idx];
}

template<class T> template<class ... U>
TemplateTree<T> &TemplateTree<T>::child(Number idx, U ... args) const
{
    return super::_data->array[(int)idx].child(args ...);
}

template<class T> template<class ... U>
TemplateTree<T> &TemplateTree<T>::child(int idx, U ... args) const
{
    return super::_data->array[(int)idx].child(args ...);
}

template<class T> template<class U>
TemplateTree<T> &TemplateTree<T>::child(const TemplateArray<U> &axis, int level) const
{
    return this->child((NDArray<U>)axis, level);
}

template<class T> template<class U>
TemplateTree<T> &TemplateTree<T>::child(const NDArray<U> &axis, int level) const
{
    assert(axis.shapeSize()==1 && axis.size()>0);
    if(level<axis.size()-1)
    {
        return super::_data->array[(int)axis.item(level)].child(axis, level+1);
    }
    return super::_data->array[(int)axis.item(level)];
}

template<class T> template<class U>
inline TemplateTree<T> &TemplateTree<T>::operator()(U axis)
{
    return this->child(axis);
}


template<class T> template<class ... U>
inline TemplateTree<T> &TemplateTree<T>::operator()(U ... args)
{
    return this->child(args ...);
}
template<class T>
inline int TemplateTree<T>::size() const {
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
std::ostream& TemplateTree<T>::ostream(std::ostream& stream, int level, int ident, bool quotes) const
{
    std::string valueStr = "value";
    std::string childStr = "child";
    std::string tab = "";
    for(int j=0; j<ident*level;++j)
    {
        tab = tab + " ";
    }

    std::string lTab = tab;
    for(int j=0 ; j<ident; ++j)
    {
        lTab = lTab +" ";
    }

    stream<<tab<<"{\n";
    stream<<lTab<<"\""<<valueStr<<"\" : "<<this->item()<<",\n";
    if(this->size()>0){
        stream<<lTab<<"\""<<childStr<<"\" : [\n";
        for(int j=0; j<this->size(); ++j){
            if(j!=0) stream<<",\n";
            //outTree(stream, this->child(j), lTab+std::string("  "));
            this->child(j).ostream(stream, level+2, ident, quotes);
        }
        stream<<"\n"<<lTab<<"]\n";
    }else{
        stream<<lTab<<"\""<<childStr<<"\" : []\n";
    }
    
    stream<<tab<<"}";
    return stream;
}

template<class T>
std::istream& TemplateTree<T>::istream(std::istream& stream)
{
    std::queue<TemplateTree<T>> trees;
    TemplateTree<T> &t = *this;
    std::string inStr = "XXXXX";
    T value;

    // Lee corchete abierto
    _handleIstreamSpacesAndNewLines(stream);
    if(stream.peek()!='{') assert(false);
    stream.get();

    // Obtiene la clave "value"
    _handleStringInQuotes(stream,inStr);
    if(inStr!="value") assert(false);

    // Lee los dos puntos
    _handleIstreamSpacesAndNewLines(stream);
    if(stream.peek()!=':') assert(false);
    stream.get();

    // Lee el valor
    stream>>value;
    t.item() = value;

    // Lee la comma
    _handleIstreamSpacesAndNewLines(stream);
    if(stream.peek()!=',') assert(false);
    stream.get();

    // Obtiene la clave "child"
    _handleStringInQuotes(stream,inStr);
    if(inStr!="child") assert(false);

    // Lee los dos puntos
    _handleIstreamSpacesAndNewLines(stream);
    if(stream.peek()!=':') assert(false);
    stream.get();

    // Lee el corchete abierto
    _handleIstreamSpacesAndNewLines(stream);
    if(stream.peek()!='[') assert(false);
    stream.get();

    // Lee iterativamente los hijos del nodo
    while(true){
        _handleIstreamSpacesAndNewLines(stream);

        // El nodo no tiene hijos
        if(stream.peek()==']'){stream.get();break;}

        // Lee el arbol recursivamente
        TemplateTree<T> lT;
        lT.istream(stream);
        trees.push(lT);

        _handleIstreamSpacesAndNewLines(stream);
        // Siguiente dato en la lista de hijos
        if(stream.peek()==']'){stream.get();break;}
        else if(stream.peek()==',') stream.get();
        else assert(false);
    }

    // Lee el corchete cerrado
    _handleIstreamSpacesAndNewLines(stream);
    if(stream.peek()!='}') assert(false);
    stream.get();
    //_handleIstreamSpacesAndNewLines(stream);

    t.resize(trees.size());
    for(int j=0; j<t.size(); ++j)
    {
        t.child(j) = trees.front(); 
        trees.pop();
    }
    return stream;
}

template<class T>
void TemplateTree<T>::loadFile(std::string path){
    std::ifstream file;
    file.open(path);
    if(file.fail()) {
        // Validar que no existe fichero
        this->resize(0);
    }else{
        file>>*this;
    }
    file.close();
}

template<class T>
void TemplateTree<T>::saveFile(std::string path){
    // Crear ruta si no existe  
    std::ofstream file;
    file.open(path);
    file<<*this;
    file.close();
}

template<class T>
inline std::ostream& operator<<(std::ostream& stream, const TemplateTree<T> &tree)
{
    return tree.ostream(stream);
}

template<class T>
inline std::istream& operator>>(std::istream& stream, TemplateTree<T> &tree)
{
    return tree.istream(stream);
}