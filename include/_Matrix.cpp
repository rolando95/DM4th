#include "_Matrix.h"

Matrix::Matrix(){}
Matrix::Matrix(const Matrix &m){
    *this = m;
}

Vector& Matrix::operator[](Number n){
    int pos = n.r;
    if(pos<0) pos = 0;
    //if(pos>= this->rows)  /* TODO resize */
    if(this->data[pos].length() != cols) this->data[pos].resize(cols);
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
        rows = r; cols = c;
    }   
}

Number Matrix::rowsLength()const{
    return this->rows;
}

Number Matrix::colsLength()const{
    return this->cols;
}

Vector Matrix::appendRow(const Vector &v, Number position){
    int pos = position.r;

    // Insercion de vector en matriz
    if(pos<0 || pos>= this->rows) {
        data.push_back(v); 
        pos = rows;
    }else{
        data.insert(data.begin() + pos, v);
    }

    // Reescala el numero de columnas si anteriormente era igual a 0
    if(cols==0) cols = (int)v.length();
    // Verifica que el numero de elementos del vector insertado es igual al numero de columnas de la matriz
    else if(v.length() != cols) data[pos].resize(cols);
    rows++;
    return v;
}

Vector Matrix::appendCol(const Vector &vec, Number position){
    int pos = position.r;
    Vector v = vec;

    // Reescala el numero de filas si anteriormente era igual a 0
    if(rows==0) rows = (int)v.length();
    // Verifica que el numero de elementos del vector insertado es igual al numero de filas de la matriz
    else if(v.length() != rows) v.resize(rows);
    
    for(int j=0; j<rows; j++){
        data[j].append(v[j], pos);
    }
    cols++;
    return vec;
}

Vector Matrix::popRow(const Number position){
    Vector value;
    int pos = position.r;
    if(this->rows > 0){
        if(pos>=this->rows) {
            value = this->data[rows-1];
            data.pop_back();
        }else{
            value = this->data[pos];
            data.erase(data.begin()+pos);
        }
        rows-=1;
    }
    return value;
}  

Vector Matrix::popCol(const Number position){
    Vector value;
    int pos = position.r;
    if(this->cols>0){
        if(pos<0 || pos>=this->cols){
            pos = cols-1;
        }
        value.resize(rows);
        for(int j=0; j<rows; j++){
            value[j] = data[j].pop(pos);
        }
        cols -= 1;
    }
    return value;
}

Matrix Matrix::operator+=(Matrix m){
    int maxj = (int)this->rowsLength();
    int maxk = (int)this->colsLength();
    for(int j=0; j<maxj; j++){
        for(int k=0; k<maxj; k++){
            this->data[j][k] += m[j][k];
        }
    }
    return *this;
}

Matrix Matrix::operator-=(Matrix m){
    int maxj = (int)this->rowsLength();
    int maxk = (int)this->colsLength();
    for(int j=0; j<maxj; j++){
        for(int k=0; k<maxj; k++){
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
    stream<<"[";
    for(int n=0; n<m.rowsLength(); n++){
        if(n!=0) stream<<",\n ";
        stream<<m[n];
    }
    stream<<"]";
    return stream;
}

std::istream& operator>>(std::istream& stream, Matrix &m){
    // Pregunta por numero de elementos filas/columnas de la matriz si no fue definido previamente
    if(m.rowsLength()==0 || m.colsLength()==0) {
        int countC, countR;
        std::cout<<"Rows: ";
        std::cin>>countR;
        fflush(stdin);
        std::cout<<"Columns: ";
        std::cin>>countC;
        fflush(stdin);
        m.resize(countR,countC);   
    }

    for(int j=0; j<m.rowsLength(); j++){
        for(int k=0; k<m.colsLength(); k++){
            std::cout<<"["<<j<<"]["<<k<<"]: ";
            stream>>m[j][k];
        }
    }
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
    if(c<0) c = r;
    for(int j=0; j<r.r;j++){
        result.appendRow(zeros(c));
        if(j<c) result[j][j] = 1;
    }
    return result;
}