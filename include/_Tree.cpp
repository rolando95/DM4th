#include "_Tree.h"

Tree::Tree(){
    
}

Tree::Tree(Number n){
    *_value = n;
}

void Tree::resize(const Number &pos){
    int size = (int)pos.real();
    assert(size>=0);
    if(size != *_rows){
        //Realloc items
        this->_data->resizeArray(size);
        //Initialize values
        if(size>*_rows){
            for(int j=*_rows; j<size;++j){
                _data->array[j].setValue(0);
            }
        }
        *_rows = size;
    }
}

Number Tree::appendChild(Number n, Number idx){
    int pos = idx.real();
    assert(pos>=-1 && pos<= *_rows);
    this->resize(*_rows+1);
    //Append
    if(pos<0||pos>=*_rows){
        _data->array[*_rows-1].setValue(n);
    }
    //Insert
    else{
        for(int j=*_rows-1; j>pos; j--){
            _data->array[j].setValue(
                _data->array[j-1].getValue()
            );
        }
        _data->array[pos].setValue(n);
    }
    return n;
}

void _printStructure(Tree &_tree, int level=0, std::string tab="", bool last=false){
    if(level==0){
        std::cout<<_tree.getValue()<<std::endl;
    }else{
        std::cout<<tab;

        if(last) std::cout<<(char)192<<(char)196<<(char)196<<" "; //print: "├── "
        else std::cout<<(char)195<<(char)196<<(char)196<<" "; //print: "└── "

        std::cout<<_tree.getValue()<<std::endl;

        if(!last) tab += (char)179 + std::string("   "); // append "|   "
        else tab += std::string("    "); // append "    "
    }
    for(int j=0; j<_tree.childLength(); ++j){
        _printStructure(_tree[j], level+1, tab, j==_tree.childLength()-1 );
    }
    return;
}

void Tree::printStructure(){
    _printStructure(*this);
}
/*
std::ostream& operator<<(std::ostream& stream, const Tree &t){
    int size = t.childLength();
    
    stream<<"{\"value\":"<<t.getValue()<<",\"child\":[";  
    for(int j=0; j<size; ++j){
        if(j!=0) stream<<", ";
        stream<<t.getChild(j);

    }
    stream<<"]}";
    
    return stream;
}
*/

void outTree(std::ostream& stream, const Tree &t, std::string tab=""){
    std::string value = "value";
    std::string child = "child";
    int size = t.childLength();
    std::string lTab = tab+"  ";

    stream<<tab<<"{\n";
    stream<<lTab<<"\""<<value<<"\" : "<<t.getValue()<<",\n";
    if(size>0){
        stream<<lTab<<"\""<<child<<"\" : [\n";
        for(int j=0; j<size; ++j){
            if(j!=0) stream<<",\n";
            outTree(stream,t.getChild(j), lTab+std::string("  "));
        }
        stream<<"\n"<<lTab<<"]\n";
    }else{
        stream<<lTab<<"\""<<child<<"\" : []\n";
    }
    
    stream<<tab<<"}";
}

std::ostream& operator<<(std::ostream& stream, const Tree &t){
   outTree(stream,t,"");
   return stream;
}
