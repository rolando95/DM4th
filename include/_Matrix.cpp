#include "_Matrix.h" 
Matrix::Matrix(){}
Matrix::Matrix(const Matrix &m){
    *this = m;
}

Matrix::Matrix(std::string str){
    std::stringstream ss;
    ss << str;
    ss >> *this;
}

Vector& Matrix::operator[](Number n){
    int pos = n.r;
    //if(pos<0) pos = 0;
    assert(pos<this->rowsLength());
    if(this->data[pos].length() != _cols) this->data[pos].resize(_cols);
    return this->data[pos];
}

void Matrix::resize(const Number &posR,Number posC){
    int r = int(posR.r), c = int(posC.r);
    if (c<0) c = r;
    if(r>=0 && c>=0){
        data.resize(r);
        for(int j=0; j<r; j++){
            data[j].resize(c);
        }
        _rows = r; _cols = c;
    }   
}

Number Matrix::rowsLength()const{
    return this->_rows;
}

Number Matrix::colsLength()const{
    return this->_cols;
}

Matrix Matrix::appendRow(Matrix m, Number position){
    if(m._rows > 0){
        int pos = position.r;
        if(pos<0 || pos>=this->_rows) {data.insert(data.end(), m.data.begin(), m.data.end());}
        else{
            data.insert(data.begin() + pos, m.data.begin(), m.data.end());
        }
        this->_rows += m._rows;
    }
    return m;
}

Vector Matrix::appendRow(const Vector &v, Number position){
    int pos = position.r;

    // Insercion de vector en matriz
    if(pos<0 || pos>= this->_rows) {
        data.push_back(v); 
        pos = _rows;
    }else{
        data.insert(data.begin() + pos, v);
    }

    // Reescala el numero de columnas si anteriormente era igual a 0
    if(_cols==0) _cols = (int)v.length();
    // Verifica que el numero de elementos del vector insertado es igual al numero de columnas de la matriz
    else if(v.length() != _cols) data[pos].resize(_cols);
    _rows++;
    return v;
}

Vector Matrix::appendCol(const Vector &vec, Number position){
    int pos = position.r;
    Vector v = vec;

    // Reescala el numero de filas si anteriormente era igual a 0
    if(_rows==0) _rows = (int)v.length();
    // Verifica que el numero de elementos del vector insertado es igual al numero de filas de la matriz
    else if(v.length() != _rows) v.resize(_rows);
    
    for(int j=0; j<_rows; j++){
        data[j].append(v[j], pos);
    }
    _cols++;
    return vec;
}

Matrix Matrix::appendCol(Matrix mat, Number position){
    int pos = position.r;
    Matrix m = mat;
    if(_rows==0){
        this->resize(m.rowsLength());
    } 
    if(m.rowsLength()!= _rows) m.resize(_rows);

    for(int j=0; j<_rows; j++){
        data[j].append(m[j],pos);
    }
    _cols += (int)mat.colsLength();
    return mat;
}

Vector Matrix::popRow(const Number position){
    Vector value;
    int pos = position.r;
    if(this->_rows > 0){
        if(pos>=this->_rows) {
            value = this->data[_rows-1];
            data.pop_back();
        }else{
            value = this->data[pos];
            data.erase(data.begin()+pos);
        }
        _rows-=1;
    }
    return value;
}  

Vector Matrix::popCol(const Number position){
    Vector value;
    int pos = position.r;
    if(this->_cols>0){
        if(pos<0 || pos>=this->_cols){
            pos = _cols-1;
        }
        value.resize(_rows);
        for(int j=0; j<_rows; j++){
            value[j] = data[j].pop(pos);
        }
        _cols -= 1;
    }
    return value;
}

Matrix Matrix::loadFile(std::string url){
    std::ifstream file;
    file.open(url);
    if(file.fail()) {
        // Validar que no existe fichero
        this->resize(0);
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

Matrix Matrix::operator+=(Matrix m){
    int maxj = (int)this->rowsLength();
    int maxk = (int)this->colsLength();
    for(int j=0; j<maxj; j++){
        for(int k=0; k<maxk; k++){
            this->data[j][k] += m[j][k];
        }
    }
    return *this;
}

Matrix Matrix::operator-=(Matrix m){
    int maxj = (int)this->rowsLength();
    int maxk = (int)this->colsLength();
    for(int j=0; j<maxj; j++){
        for(int k=0; k<maxk; k++){
            this->data[j][k] -= m[j][k];
        }
    }
    return *this;
}

Matrix Matrix::operator*=(Matrix m){
    int maxX = (int)this->rowsLength();
    int maxY = (int)m.colsLength();
    int maxZ = (int)m.rowsLength();
    Matrix result = zeros(maxX,maxY);
    for(int x=0; x<maxX; x++){
        for(int y=0; y<maxY; y++){
            for(int z=0;z<maxZ; z++){
                result[x][y] += this->data[x][z] * m[z][y];
            }
        }
    }
    *this = result;
    return *this;
    
}

Matrix Matrix::operator*=(Number n){
    int maxJ = (int)this->rowsLength();
    int maxK = (int)this->colsLength();
    for(int j=0; j<maxJ; j++){
        for(int k=0; k<maxK; k++){
            this->data[j][k] *= n;
        }
    }
    return *this;
}

Matrix Matrix::operator/=(Number n){
    int maxJ = (int)this->rowsLength();
    int maxK = (int)this->colsLength();
    for(int j=0; j<maxJ; j++){
        for(int k=0; k<maxK; k++){
            this->data[j][k] /= n;
        }
    }
    return *this;
}

Matrix Matrix::operator%=(Number n){
    int maxJ = (int)this->rowsLength();
    int maxK = (int)this->colsLength();
    for(int j=0; j<maxJ; j++){
        for(int k=0; k<maxK; k++){
            this->data[j][k] %= n;
        }
    }
    return *this;
}

std::vector<Vector>::iterator Matrix::begin(){return data.begin();}
std::vector<Vector>::iterator Matrix::end(){ return data.end();}

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
    Matrix result = m1;
    result += m2;
    return result;
}

// Resta de Matrices
Matrix operator-(Matrix m1,Matrix m2){
    Matrix result = m1;
    result -= m2;
    return result;
}

// Multiplicacion de Matrices
Matrix operator*(Matrix m1,Matrix m2){
    Matrix result = m1;
    result *= m2;
    return result;
}

// Producto entre Matriz y escalar
Matrix operator*(Matrix m,const Number &n){
    Matrix result = m;
    result*=n;
    return result;
}

Matrix operator*(const Number &n, Matrix m){
    Matrix result = m;
    result*=n;
    return result;
}

// Producto entre Vector y Matriz
Vector operator*(Vector v, Matrix m){
    Vector result;
    int len = (int)m.colsLength();
    result.resize(len);
    int lenV = (int)v.length();
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
    int len = (int)m.rowsLength();
    result.resize(len);
    for(int j=0; j<len; j++){
        result[j] = m[j]*v;
    }
    return result;
}

Matrix operator/(Matrix m,const Number &n){
    Matrix result = m;
    result/=n;
    return result;
}

Matrix operator%(Matrix m,const Number &n){
    Matrix result = m;
    result%=n;
    return result;
}

Matrix zeros(const Number &r, const Number &c){
    Matrix result;
    for(int j=0; j<r.r;j++){
        result.appendRow(zeros(c));
    }
    return result;
}

Matrix ones(const Number &r, const Number &c){
    Matrix o;
    o.resize(r,c);
    for(int j=0; j<r; j++) 
        for(int k=0; k<c; k++) o[j][k] = 1;
    return o;
}

Matrix identity(Number r, Number c){
    Matrix result;
    result.resize(r,c);
    if(c<0) c = r;
    for(int j=0; j<r.r;j++){
        if(j<c) result[j][j] = 1;
        else break;
    }
    return result;
}

template<class T>
void matrixToArray(Matrix &m, T *array, int N, int M, bool imaginary){
    int lenR = (int)m.rowsLength();
    int lenC = (int)m.colsLength();
    if(!imaginary){
        if(lenR<N) N = lenR;
        if(lenC<M) M = lenC;
        for(int j=0; j<N; j++){
            for(int k=0; k<M; k++){
                array[j*M+k] = (T)m[j][k].r;
            }
        }
    }else
    {
        if(lenR*2<N) N = lenR*2;
        if(lenC<M) M = lenC;
        for(int j=0; j<N/2; j++){
            for(int k=0; k<M; k++){
                array[j*M+k] = (T)m[j][k].r;
                array[(j+N/2)*M+k] = (T)m[j][k].i;
            }
        }
    }
    
}

template void matrixToArray(Matrix&, int*     , int, int, bool);
template void matrixToArray(Matrix&, long int*, int, int, bool);
template void matrixToArray(Matrix&, float*   , int, int, bool);
template void matrixToArray(Matrix&, double*  , int, int, bool);
template void matrixToArray(Matrix&, Number*  , int, int, bool);
template<class T>
void arrayToMatrix(T *array, Matrix &m, int N, int M, bool imaginary){

    if(!imaginary){
        m.resize(N,M);
        for(int j=0; j<N; j++){
            for(int k=0; k<M; k++){
                m[j][k] = array[j*M+k];
            }
        }
    }else{
        m.resize(N/2,M);
        for(int j=0; j<N/2; j++){
            for(int k=0; k<M; k++){
                m[j][k] = array[j*M+k] + array[(j+N/2)*M+k]*i;
            }
        }
    }
}
template void arrayToMatrix(int*,      Matrix&, int, int, bool);
template void arrayToMatrix(long int*, Matrix&, int, int, bool);
template void arrayToMatrix(float*,    Matrix&, int, int, bool);
template void arrayToMatrix(double*,   Matrix&, int, int, bool);
template void arrayToMatrix(Number*,   Matrix&, int, int, bool);
