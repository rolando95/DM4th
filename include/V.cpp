#include "V.h"
Vector::Vector(){}

Vector::Vector(const Vector &v){
    *this = v;
}

Number& Vector::operator[](Number n){
    int pos = n.r;
    if(pos<0) pos = 0;
    if(pos>=this->count) resize(pos+1);
    return this->data[pos];
}
const Vector Vector::operator[](Vector v)const {
    Vector result;
    for(int j=0; j<v.length(); j++){
        result.append(this->data[(int)v[j]]);
    }
    return result;
}

Number Vector::append(const Number &n, const Number position){
    int pos = position.r;
    if(pos<0 || pos>=this->count) {data.push_back(n);count++;}
    else {
        data.insert(data.begin() + pos,n);
        count++;
    }
    return n;
}

Vector Vector::append(const Vector& v, const Number position){
    if(v.count > 0){
        int pos = position.r;
        if(pos<0 || pos>=this->count) {data.insert(data.end(), v.data.begin(), v.data.end());}
        else{
            data.insert(data.begin() + pos, v.data.begin(), v.data.end());
        }
        this->count += v.count;
    }
    return v;
}

Number Vector::pop(const Number position){
    Number value;
    int pos = position.r;
    if(this->count > 0){
        if(pos>=this->count) {
            value = this->data[count-1];
            data.pop_back();count--;
        }else{
            value = this->data[pos];
            data.erase(data.begin()+pos);
        }
        count-=1;
    }else
        return 0;
    return value;
}

Number Vector::length() const{
    return this->count;
}

Vector Vector::find(const Number &value){
    Vector result;
    for(int j=0; j<count; j++){
        if(value==this->data[j]) result.append(j);
    }
    return result;
}

Vector Vector::find(Vector value){
    Vector result;
    for(int j=0; j<value.count; j++){
        result.append(find(value[j]));
    }
    return result;
}

void Vector::resize(const Number &pos){
    int c = int(pos.r);
    if(c>=0){
        data.resize(c);
        count = c;
    }
}

void Vector::operator+=(Vector v){
    Number max = std::min(this->length(), v.length());
    for(int j=0; j<max; j++){ this->data[j] += v[j];}
}
void Vector::operator-=(Vector v){
    Number max = std::min(this->length(), v.length());
    for(int j=0; j<max; j++){ this->data[j] -= v[j];}
}
void Vector::operator*=(Number n){
    for(int j=0; j<this->length(); j++){ this->data[j] *= n;}
}
void Vector::operator/=(Number n){
    for(int j=0; j<this->length(); j++){ this->data[j] /= n;}
}
void Vector::operator%=(Number n){
    for(int j=0; j<this->length(); j++){ this->data[j] %= n;}
}

std::vector<Number>::iterator Vector::begin(){return data.begin();}
std::vector<Number>::iterator Vector::end(){ return data.end();}

std::ostream& operator<<(std::ostream& stream, Vector v){
    stream<<"[";
    for(int n=0; n<v.length(); n++){
        if(n!=0) stream<<", ";
        stream<<v[n];
    }
    stream<<"]";
    return stream;
}

std::istream& operator>>(std::istream& stream, Vector &v){
    for(int n=0; n<v.length(); n++){
        std::cout<<"["<<n<<"]: ";
        stream>>v[n];
    }
    return stream;
}

// Suma de vectores
Vector operator+(Vector v1,Vector v2){
    Vector result = v1;
    result += v2;
    return result;
}

// Resta de vectores
Vector operator-(Vector v1,Vector v2){
    Vector result = v1;
    result -= v2;
    return result;
}

// Producto escalar
Number operator*(Vector v1,Vector v2){
    Number result = 0;
    Number max = std::min(v1.length(), v2.length());
    for(int j=0; j<max; j++){
        result += v1[j]*v2[j];
    }
    return result;
}

// Producto entre vector y escalar
Vector operator*(Vector v,const Number &n){
    Vector result = v;
    result*=n;
    return result;
}
Vector operator*(const Number &n, Vector v){
    return v*n;
}

// Division entre vector y escalar
Vector operator/(Vector v,const Number &n){
    Vector result = v;
    result/=n;
    return result;
}


template<class T>
void vectorToArray(Vector &v, T *array, int n, bool imaginary){
    int lenV = (int)v.length();
    if(!imaginary){
        if(lenV<n) n = lenV;
        for(int j=0; j<n; j++){
            array[j] = (T)v[j].r;
        }
    }else{
        if(lenV*2<n) n = lenV*2;
        for(int j=0; j<n/2; j++){
            array[j] = (T)v[j].r;
            array[j+n/2] = (T)v[j].i;
        }
    }
}
template void vectorToArray(Vector&, int*     , int, bool);
template void vectorToArray(Vector&, long int*, int, bool);
template void vectorToArray(Vector&, float*   , int, bool);
template void vectorToArray(Vector&, double*  , int, bool);
template void vectorToArray(Vector&, Number*  , int, bool);

template<class T>
void arrayToVector(T* array, Vector &v, int n, bool imaginary){
    v.resize(0);
    if(!imaginary){
        for(int j=0; j<n; j++){
            v.append(array[j]);
        }
    }else{
        for(int j=0; j<n/2; j++){
            v.append(array[j]+array[j+n/2]*i);
        }
    }
}

template void arrayToVector(int*,      Vector&, int, bool);
template void arrayToVector(long int*, Vector&, int, bool);
template void arrayToVector(float*,    Vector&, int, bool);
template void arrayToVector(double*,   Vector&, int, bool);
template void arrayToVector(Number*,   Vector&, int, bool);