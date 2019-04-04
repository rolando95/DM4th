#include "_Matrix.h"
//#define REFDEBUG

Matrix::Matrix(){
    
}

Matrix::Matrix(const Matrix &m){
    *this = m;
}


Matrix::Matrix(std::string str){
    this->_alloc();
    std::stringstream ss;
    ss << str;
    ss >> *this;
}

Matrix::~Matrix(){
    
}

Matrix Matrix::appendRow(Matrix m, Number idx){
    int pos = idx.real();
    assert(pos>=-1 && pos<=*_rows);
    if(*_rows==0) *_cols = m.colsLength();
    int begin = *_rows;
    this->resize(*_rows+m.rowsLength(), *_cols);
    //Append
    if(pos<0 || pos >= *_rows) {
        for(int j=0; j<m.rowsLength(); j++){
            _data->array[begin+j] = m[j];
        }
    }
    //Insert
    else {
        for(int j=*_rows-1; j >= pos+m.rowsLength(); j--){
            _data->array[j] = _data->array[j-m.rowsLength()];
        }
        for(int j=0; j<m.rowsLength(); j++){
            _data->array[pos+j] = m[j];
        }
    }
    return m;
}

Vector Matrix::appendRow(const Vector &v, Number idx){
    int pos = idx.real();
    assert(pos>=-1 && pos<= *_rows);
    if(*_rows==0) *_cols = v.length();
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

Vector Matrix::appendCol(Vector &vec, Number idx){
    int pos = idx.real();
    Vector v = vec.getCopy();
    // Reescala el numero de filas si anteriormente era igual a 0
    if(*_rows==0) *_rows = v.length();
    // Verifica que el numero de elementos del vector insertado es igual al numero de filas de la matriz
    else assert(v.length() == *_rows);
    for(int j=0; j<*_rows; j++){
        _data->array[j].append(v[j], pos);
    }
    *_cols+=1;
    return vec;
}

Matrix Matrix::appendCol(Matrix mat, Number idx){
    int pos = idx.real();
    Matrix m = mat.getCopy();
    if(*_rows==0){
        this->resize(m.rowsLength(), *_cols);
    } else{
        this->resize(*_rows, *_cols);
    }
    assert(m.rowsLength()==*_rows);
    for(int j=0; j<*_rows; j++){
        _data->array[j].append(m[j],pos);
    }
    *_cols += m.colsLength();
    return m;
}

Vector Matrix::popRow(const Number idx){
    Vector value;
    int pos = idx.real();
    assert(*_rows>0);
    if(pos<0 || pos>=*_rows) {
        value = _data->array[*_rows-1];
    }else{
        value = _data->array[pos];
        for(int j=pos; j<*_rows-1;j++){
            _data->array[j] = _data->array[j+1];
        }
    }
    this->resize(*_rows-1,*_cols);
    return value;
}  

Vector Matrix::popCol(const Number idx){
    Vector value;
    int pos = idx.real();
    assert(*_cols>0);
    value.resize(*_rows);
    if(pos<0 || pos>=*_cols){
        pos = *_cols-1;
    }
    for(int j=0; j<*_rows; j++){
        value[j] = _data->array[j].pop(pos);
    }
    *_cols -= 1;
    return value;
}

Matrix Matrix::loadFile(std::string url){
    std::ifstream file;
    file.open(url);
    if(file.fail()) {
        // Validar que no existe fichero
        this->resize(0,0);
    }else{
        file>>*this;
    }
    file.close();
    return *this;
}
Matrix Matrix::saveFile(std::string url){
    // Crear ruta si no existe  
    std::ofstream file;
    file.open(url);
    file<<*this;
    file.close();
    return *this;
}

void Matrix::resize(const Number &posR,Number posC){
    int r = posR.real(), c = posC.real();
    //c = (c==-1)?r:c;
    assert(r>=0 && c>=0);
    if(r != *_rows){
        //M_alloc data firt time
        if(!this->_data){
            this->_data = new _Array<Vector>();
            assert(_data);
            //_alloc rows
            this->_data->allocArray(r);
            //_alloc cols
            for(int j=0; j<r; j++){
                this->_data->array[j].resize(c);
            }
        //Re_alloc
        }else if(r>0){
            //Re_alloc rows
            this->_data->resizeArray(r);
            //Re_alloc cols
            for(int j=0; j<r; j++){
                this->_data->array[j].resize(c);
            }
        }
        *_rows = r;
        *_cols = c;
    }
}

Matrix Matrix::getCopy(){
    Matrix result;
    result.resize(*_rows,*_cols);
    for(int j=0; j<result.rowsLength(); j++){
        for(int k=0; k<result.colsLength(); k++){
            result[j][k] = _data->array[j][k];
        }
    }
    return result;
}

void Matrix::operator+=(Matrix m){
    assert(this->rowsLength()==m.rowsLength() && 
           this->colsLength()==m.colsLength());
    for(int j=0; j<*_rows; j++){
        for(int k=0; k<*_cols; k++){
            _data->array[j][k] += m[j][k];
        }
    }
}

void Matrix::operator-=(Matrix m){
    assert(this->rowsLength()==m.rowsLength() && 
           this->colsLength()==m.colsLength());
    for(int j=0; j<*_rows; j++){
        for(int k=0; k<*_cols; k++){
            _data->array[j][k] -= m[j][k];
        }
    }
}

void Matrix::operator*=(Matrix m){
    assert(this->colsLength() == m.rowsLength());
    int maxX = this->rowsLength();
    int maxY = m.colsLength();
    int maxZ = m.rowsLength();
    Matrix result;
    result.resize(maxX,maxY);
    for(int x=0; x<maxX; x++){
        for(int y=0; y<maxY; y++){
            for(int z=0;z<maxZ; z++){
                result[x][y] += _data->array[x][z] * m[z][y];
            }
        }
    }
    *this = result; 
}

void Matrix::operator*=(Number n){
    for(int j=0; j<*_rows; j++){
        for(int k=0; k<*_cols; k++){
            _data->array[j][k] *= n;
        }
    }
}

void Matrix::operator/=(Number n){
    for(int j=0; j<*_rows; j++){
        for(int k=0; k<*_cols; k++){
            _data->array[j][k] /= n;
        }
    }
}

void Matrix::operator%=(Number n){
    for(int j=0; j<*_rows; j++){
        for(int k=0; k<*_cols; k++){
            _data->array[j][k] %= n;
        }
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

// Suma de Matrices
Matrix operator+(Matrix m1,Matrix m2){
    Matrix result = m1.getCopy();
    result += m2;
    return result;
}

// Resta de Matrices
Matrix operator-(Matrix m1,Matrix m2){
    Matrix result = m1.getCopy();
    result -= m2;
    return result;
}

// Multiplicacion de Matrices
Matrix operator*(Matrix m1,Matrix m2){
    Matrix result = m1.getCopy();
    result *= m2;
    return result;
}

// Producto entre Matriz y escalar
Matrix operator*(Matrix m,const Number &n){
    Matrix result = m.getCopy();
    result*=n;
    return result;
}

Matrix operator*(const Number &n, Matrix m){
    Matrix result = m.getCopy();
    result*=n;
    return result;
}

// Producto entre Vector y Matriz
Vector operator*(Vector v, Matrix m){
    assert(v.length() == m.rowsLength());
    Vector result;
    int len = m.colsLength();
    result.resize(len);
    int lenV = v.length();
    for(int k=0; k<len; k++){
        result[k] = 0;
        for(int j=0; j<lenV; j++){
            result[k] += v[j]*m[j][k];
        }
    }
    return result;
}
// Producto entre Matriz y Vector
Vector operator*(Matrix m, Vector v){
    Vector result;
    int len = m.rowsLength();
    result.resize(len);
    for(int j=0; j<len; j++){
        result[j] = m[j]*v;
    }
    return result;
}

Matrix operator/(Matrix m,const Number &n){
    Matrix result = m.getCopy();
    result/=n;
    return result;
}

Matrix operator%(Matrix m,const Number &n){
    Matrix result = m.getCopy();
    result%=n;
    return result;
}

bool operator==(Matrix &m1, Matrix &m2){
    bool result = true;
    if(m1.length()!=m2.length() || m1.colsLength()!=m2.colsLength()){
        result = false;
    }else{
        for(int j=0; j<m1.length(); j++){
            if(m1[j]!=m2[j]) {
                result = false;
                break;
            }
            
        }
    }
    return result;
}

bool operator!=(Matrix &m1, Matrix &m2){
    return !(m1==m2);
}

bool operator>(Matrix &m1, Matrix &m2){
    bool result=false;
    int min = m1.length()<m2.length()? m1.length() : m2.length();
    for(int j=0; j<min; j++){
        if(m1[j]!=m2[j]){
            result = m1[j]>m2[j];
            break;
        }
        result = m1.length()>m2.length();
    }
    return result;
}

bool operator<(Matrix &m1, Matrix &m2){
    return !(m1>=m2);
}

bool operator>=(Matrix &m1, Matrix &m2){
    return m1>m2||m1==m2;
}

bool operator<=(Matrix &m1, Matrix &m2){
    return !(m1>m2);
}

Matrix zeros(const Number &r, const Number &c){
    Matrix result;
    for(int j=0; j<r.real();j++){
        result.appendRow(zeros(c));
    }
    return result;
}

Matrix ones(const Number &r, const Number &c){
    Matrix o;
    o.resize(r,c);
    for(int j=0; j<r; j++) {
        for(int k=0; k<c; k++){ 
            o[j][k] = 1;
        }
    }
    return o;
}

Matrix identity(Number r, Number c){
    Matrix result;
    if(c<0) c = r;
    result.resize(r,c);
    for(int j=0; j<result.rowsLength();j++){
        if(j<result.colsLength()) result[j][j] = 1;
        else break;
    }
    return result;
}