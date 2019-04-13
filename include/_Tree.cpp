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
            for(int j=*_rows; j<size;j++){
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

void _printStructure(Tree &_tree, int level=0, std::string levelStr="", bool last=false){
    if(level==0){
        std::cout<<_tree.getValue()<<std::endl;
    }else{
        std::cout<<levelStr;

        if(last) std::cout<<(char)192<<(char)196<<(char)196<<" "; //print: "├── "
        else std::cout<<(char)195<<(char)196<<(char)196<<" "; //print: "└── "

        std::cout<<_tree.getValue()<<std::endl;

        if(!last) levelStr += (char)179 + std::string("   "); // append "|   "
        else levelStr += std::string("    "); // append "    "
    }
    for(int j=0; j<_tree.childLength(); ++j){
        _printStructure(_tree[j], level+1, levelStr, j==_tree.childLength()-1 );
    }
    return;
}

void Tree::printStructure(){
    _printStructure(*this);
}


std::ostream& operator<<(std::ostream& stream, const Tree &t){
    int size = t.childLength();
    
    stream<<"{\"value\":"<<t.getValue()<<",\"child\":[";  
    for(int j=0; j<size; j++){
        if(j!=0) stream<<", ";
        stream<<t.getChild(j);

    }
    stream<<"]}";
    
    return stream;
}


