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
    if(pos<0 || pos>= this->rows) {
        data.push_back(v); 
        pos = rows;
    }else{
        data.insert(data.begin() + pos, v);
    }
    if(v.length()!=cols && cols>0) data[pos].resize(cols);
    if(cols==0) cols = (int)v.length();
    rows++;
    return v;
}

Vector Matrix::appendCol(const Vector &vec, Number position){
    int pos = position.r;
    Vector v = vec;
    if(v.length() != cols && rows>0) v.resize(cols);
    if(rows==0) rows = (int)v.length();
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
    for(int j=0; j<m.rowsLength(); j++){
        for(int k=0; k<m.colsLength(); k++){
            std::cout<<"["<<j<<"]["<<k<<"]: ";
            stream>>m[j][k];
        }
    }
    return stream;
}