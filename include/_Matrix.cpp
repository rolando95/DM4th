#include "_Matrix.h"

void Matrix::_addRef(){
    if(_ref != nullptr){
        *_ref += 1;
        std::cout<<"Matrix ref "<<*_ref-1<<" -> "<<*_ref<<std::endl;
    }
}

void Matrix::_subRef(){
    if(_ref != nullptr){
        *_ref -= 1;
          std::cout<<"Matrix ref "<<*_ref+1<<" -> "<<*_ref<<std::endl;
        if(*_ref<=0){ 
            this->free();
        }
    }
}

void Matrix::alloc(){
    std::cout<<"New Matrix  ---------- N(M)"<<std::endl;
    _ref = new int(1);
    _rows = new int(0);
    _cols = new int(0);
}

void Matrix::free(){
    std::cout<<"Free Matrix ---------- F(M)"<<std::endl;   
    //No resized Matrix (this->_data = nullptr)
    if(_data){
        for(int j=0; j<*_rows; j++){
            _data->array[j]._subRef();
        }
        _data->freeArray();
        delete _data;
        _data = nullptr;
        if(_ref){
            delete _ref;
            _ref = nullptr;
        }

        if(_rows){
            delete _rows;
            _rows = nullptr;
        }

        if(_cols){
            delete _cols;
            _cols = nullptr;
        }
    }else{
        //std::cout<<"!"<<std::endl;
    }
}

void Matrix::operator=(const Matrix &D) {
    this->_subRef();
    this->_data = D._data;
    this->_rows = D._rows;
    this->_cols = D._cols;
    this->_ref = D._ref;
    this->_addRef();
}

Matrix::Matrix(){
    this->alloc();
}

Matrix::Matrix(const Matrix &m){
    *this = m;
}


Matrix::Matrix(std::string str){
    /*
    this->alloc();
    std::stringstream ss;
    ss << str;
    ss >> *this;
    */
}

Matrix::~Matrix(){
    this->_subRef();
}

Matrix Matrix::appendRow(Matrix m, Number position){
    /*
    if(m._rows > 0){
        int pos = position.real();
        if(pos<0 || pos>=this->_rows) {data.insert(data.end(), m.data.begin(), m.data.end());}
        else{
            data.insert(data.begin() + pos, m.data.begin(), m.data.end());
        }
        this->_rows += m._rows;
    }
    */
    return m;
}

Vector Matrix::appendRow(const Vector &v, Number idx){
    int pos = idx.real();
    assert(pos>=-1 && pos<= *_rows);
    this->resize(*_rows+1, *_cols);
    //Append
    if(pos<0 || pos >= *_rows) {
        _data->array[*_rows-1] = v;
    }
    //Insert
    else {
        for(int j=*_rows-1; j > pos; j--){
            _data->array[j] = _data->array[j-1];
        }
        _data->array[pos] = v;
    }
    return v;
}

Vector Matrix::appendCol(const Vector &vec, Number position){
    /*
    int pos = position.real();
    Vector v = vec;

    // Reescala el numero de filas si anteriormente era igual a 0
    if(_rows==0) _rows = (int)v.length();
    // Verifica que el numero de elementos del vector insertado es igual al numero de filas de la matriz
    else if(v.length() != _rows) v.resize(_rows);
    
    for(int j=0; j<_rows; j++){
        data[j].append(v[j], pos);
    }
    _cols++;
    */
    return vec;
}

Matrix Matrix::appendCol(Matrix mat, Number position){
    /*
    int pos = position.real();
    Matrix m = mat;
    if(_rows==0){
        this->resize(m.rowsLength());
    } 
    if(m.rowsLength()!= _rows) m.resize(_rows);

    for(int j=0; j<_rows; j++){
        data[j].append(m[j],pos);
    }
    _cols += (int)mat.colsLength();
    */
    return mat;
}

void Matrix::resize(const Number &posR,Number posC){
    int r = posR.real(), c = posC.real();
    //c = (c==-1)?r:c;
    assert(r>=0 && c>=0);
    if(r != *_rows){
        //Malloc data firt time
        if(!this->_data){
            this->_data = new _Array<Vector>();
            assert(_data);
            //Alloc rows
            this->_data->allocArray(r);
            //Alloc cols
            for(int j=0; j<r; j++){
                this->_data->array[j].resize(c);
            }
        //Realloc
        }else if(r>0){
            if(r<*_rows){
                //Sub ref to out of range vectors
                for(int j=r; j<*_rows; j++){
                    this->_data->array[j]._subRef();
                }
            }
            //Realloc rows
            this->_data->resizeArray(r);
            //Realloc cols
            for(int j=0; j<r; j++){
                this->_data->array[j].resize(c);
            }
        }
        *_rows = r;
        *_cols = c;
    }
}

std::ostream& operator<<(std::ostream& stream, Matrix m){
    //stream<<"\n";
    stream<<"[";
    for(int n=0; n<m.rowsLength(); n++){
        if(n!=0) stream<<",\n ";
        stream<<m[n];
    }
    stream<<"]";
    //stream<<"\n";
    return stream;
}

std::istream& operator>>(std::istream& stream, Matrix &m){
    m.resize(0,0);
    Vector value;
    if(stream.peek()==' ')stream>>std::ws;
    if(stream.peek()=='['){
        stream.get(); // Captura el corchete abierto
        while(stream>>value){
            if(value.length()>0) m.appendRow(value);
            if(stream.peek()==']')break;
            else if(stream.peek()==',')stream.get(); //Captura la comma
        }
        stream.get(); // Captura el corchete cerrado
    }
    if(stream.peek()=='\n')stream.get();
    return stream;
}