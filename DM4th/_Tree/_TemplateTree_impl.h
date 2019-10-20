#pragma once

#include "_TemplateTree.h"

namespace DM4th
{



template<class T>
TemplateTree<T>::TemplateTree() {}

template<class T>
TemplateTree<T>::TemplateTree(const std::string &str) 
{    
    std::stringstream ss;
    ss << str;
    ss >> *this;
}


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
inline TemplateTree<T> &TemplateTree<T>::child(number idx) const
{
    return super::_data->array[(int)idx];
}

template<class T> 
inline TemplateTree<T> &TemplateTree<T>::child(int idx) const
{
    return super::_data->array[(int)idx];
}

template<class T> template<class ... U>
TemplateTree<T> &TemplateTree<T>::child(number idx, U ... args) const
{
    return super::_data->array[(int)idx].child(args ...);
}

template<class T> template<class ... U>
TemplateTree<T> &TemplateTree<T>::child(int idx, U ... args) const
{
    return super::_data->array[(int)idx].child(args ...);
}

template<class T> template<class U>
const TemplateTree<T> &TemplateTree<T>::child(const TemplateArray<U> &axis, int level) const
{
    if(axis.size()==0) return *this;
    DM4thAssert(axis.shapeSize()==1 && axis.size()>0);
    if(level<axis.size()-1)
    {
        return super::_data->array[(int)axis.item(level)].child(axis, level+1);
    }
    return super::_data->array[(int)axis.item(level)];
}

template<class T> template<class U>
TemplateTree<T> &TemplateTree<T>::child(const TemplateArray<U> &axis, int level)
{
    if(axis.size()==0) return *this;
    DM4thAssert(axis.shapeSize()==1 && axis.size()>0);
    if(level<axis.size()-1)
    {
        return super::_data->array[(int)axis.item(level)].child(axis, level+1);
    }
    return super::_data->array[(int)axis.item(level)];
}

template<class T>
TemplateTree<T> TemplateTree<T>::getCopy() const
{
    TemplateTree<T> result;
    result.item() = this->item();
    if(this->size()>0){
        result.resize(this->size());
        for(int j=0; j<this->size(); ++j){
            result.child(j) = this->child(j).getCopy();
        }
    }
    return result;
}

template<class T>
void TemplateTree<T>::_printTreeStructure(int level, std::string tab, bool last) const{
    if(level==0){
        std::cout<<this->item()<<std::endl;
    }else{
        std::cout<<tab;

        if(last) std::cout<<(char)192<<(char)196<<(char)196<<" "; //print: "├── "
        else std::cout<<(char)195<<(char)196<<(char)196<<" "; //print: "└── "

        std::cout<<this->item()<<std::endl;

        if(!last) tab += (char)179 + std::string("   "); // append "|   "
        else tab += std::string("    "); // append "    "
    }
    for(int j=0; j<this->size(); ++j){
        this->child(j)._printTreeStructure(level+1, tab, j==this->size()-1 );
    }
    return;
}


template<class T>
void TemplateTree<T>::printTreeStructure() const
{
    this->_printTreeStructure();
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

template<class T> template<class U>
void TemplateTree<T>::push(const U &value, const int pos)
{
    DM4thAssert( (pos>=0 && pos<= this->size()) || pos==(int)END);
    this->resize(this->size()+1);
    //Append
    if(pos >= this->size() || pos==(int)END) 
    {
        super::_data->array(this->size()-1).item() = value;
    }
    //Insert
    else
    {
        for(int j=this->size()-1; j > pos; --j)
        {
            super::_data->array(j) = super::_data->array(j-1).getCopy();
        }
        super::_data->array(pos).item() = value;
    }
}

template<class T> template<class U>
void TemplateTree<T>::pushTree(const TemplateTree<U> &tree, const int pos)
{
    this->pushTreeRef(tree.getCopy(), pos);
}

template<class T> template<class U>
void TemplateTree<T>::pushTreeRef(const TemplateTree<U> &tree, const int pos)
{
    DM4thAssert( (pos>=0 && pos<= this->size()) || pos==(int)END);
    this->resize(this->size()+1);
    //Append
    if(pos >= this->size() || pos==(int)END) 
    {
        super::_data->array(this->size()-1) = tree;
    }
    //Insert
    else
    {
        for(int j=this->size()-1; j > pos; --j)
        {
            super::_data->array(j) = super::_data->array(j-1);
        }
        super::_data->array(pos) = tree;
    }
}

template<class T>
TemplateTree<T> TemplateTree<T>::pop(const int idx)
{
    TemplateTree<T> result;
    DM4thAssert( (idx>=0 && idx<this->size()) || idx==(int)END ); 

    if(idx==(int)END || idx==this->size()-1)
    {
        result = this->child(this->size()-1);
    }else{
        result = this->child(idx);
        for(int j=0; j<this->size()-idx-1; ++j)
        {
            this->child(j) = this->child(j+1);
        }
    }
    this->resize(this->size()-1);
    return result;
}

// template<class T>
// TemplateTree<T> TemplateTree<T>::pop(TemplateTree<T> &ref)
// {
//     TemplateTree<T> result;
//     bool found = false;
//     for(int j=0; j<this->size(); ++j)
//     {

//     }
// }

template<class T>
TemplateArray<int> TemplateTree<T>::indexOf(const T value)
{
    TemplateArray<int> result;
    if(this->node()!=value)
    {
        bool found = this->_indexOf(value, result);
        if(!found)
        {
            result.push(-1);
        }
    }
    return result;
}

template<class T>
bool TemplateTree<T>::_indexOf(const T value, TemplateArray<int> &result)
{

    bool found = false;
    if(this->node()==value) found = true;
    else{
        for(int j=0; j<this->size(); ++j)
        {
            found = this->child(j)._indexOf(value, result);
            if(found)
            {
                result.push(j,0);
                break;
            }
        }
        
    }
    return found;
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
    DM4thInternal::_handleIstreamSpacesAndNewLines(stream);
    if(stream.peek()!='{') DM4thAssert(false);
    stream.get();

    // Obtiene la clave "value"
    DM4thInternal::_handleStringInQuotes(stream,inStr);
    if(inStr!="value") DM4thAssert(false);

    // Lee los dos puntos
    DM4thInternal::_handleIstreamSpacesAndNewLines(stream);
    if(stream.peek()!=':') DM4thAssert(false);
    stream.get();

    // Lee el valor
    stream>>value;
    t.item() = value;

    // Lee la comma
    DM4thInternal::_handleIstreamSpacesAndNewLines(stream);
    if(stream.peek()!=',') DM4thAssert(false);
    stream.get();

    // Obtiene la clave "child"
    DM4thInternal::_handleStringInQuotes(stream,inStr);
    if(inStr!="child") DM4thAssert(false);

    // Lee los dos puntos
    DM4thInternal::_handleIstreamSpacesAndNewLines(stream);
    if(stream.peek()!=':') DM4thAssert(false);
    stream.get();

    // Lee el corchete abierto
    DM4thInternal::_handleIstreamSpacesAndNewLines(stream);
    if(stream.peek()!='[') DM4thAssert(false);
    stream.get();

    // Lee iterativamente los hijos del nodo
    while(true){
        DM4thInternal::_handleIstreamSpacesAndNewLines(stream);

        // El nodo no tiene hijos
        if(stream.peek()==']'){stream.get();break;}

        // Lee el arbol recursivamente
        TemplateTree<T> lT;
        lT.istream(stream);
        trees.push(lT);

        DM4thInternal::_handleIstreamSpacesAndNewLines(stream);
        // Siguiente dato en la lista de hijos
        if(stream.peek()==']'){stream.get();break;}
        else if(stream.peek()==',') stream.get();
        else DM4thAssert(false);
    }

    // Lee el corchete cerrado
    DM4thInternal::_handleIstreamSpacesAndNewLines(stream);
    if(stream.peek()!='}') DM4thAssert(false);
    stream.get();
    //DM4thInternal::_handleIstreamSpacesAndNewLines(stream);

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

}
