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

Number Matrix::lengthRows()const{
    return this->rows;
}

Number Matrix::lengthCols()const{
    return this->cols;
}


std::ostream& operator<<(std::ostream& stream, Matrix m){
    stream<<"[";
    for(int n=0; n<m.lengthRows(); n++){
        if(n!=0) stream<<",\n ";
        stream<<m[n];
    }
    stream<<"]";
    return stream;
}

std::istream& operator>>(std::istream& stream, Matrix &m){
    for(int j=0; j<m.lengthRows(); j++){
        for(int k=0; k<m.lengthCols(); k++){
            std::cout<<"["<<j<<"]["<<k<<"]: ";
            stream>>m[j][k];
        }
    }
    return stream;
}