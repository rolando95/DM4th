#include "_Vector.h"

Vector::Vector(){}

Vector::Vector(const Vector &v){
    *this = v;
}

Number& Vector::operator[](Number n){
    int pos = n.r;
    if(pos<0) pos = 0;
    //if(pos>=this->count) resize(pos+1);
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
    if(pos<0 || pos>=this->count) {data.push_back(n);}
    else {
        data.insert(data.begin() + pos,n);
    }
    count++;
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
        if(pos<0 || pos>=this->count) {
            value = this->data[count-1];
            data.pop_back();
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

Vector Vector::index(const Number &value){
    Vector result;
    for(int j=0; j<count; j++){
        if(value==this->data[j]) result.append(j);
    }
    return result;
}

Vector Vector::index(Vector value){
    Vector result;
    for(int j=0; j<value.count; j++){
        result.append(index(value[j]));
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

void Vector::swap(Number p1, Number p2, Number c){
    int pos1 = (int)p1, pos2 = (int)p2, count = (int)c;
    if(count <= 1){
        Number tmp = this->data[pos1];
        this->data[pos1] = this->data[pos2];
        this->data[pos2] = tmp;
    }else{
        Vector tmp; tmp.resize(count);
        for(int j=0; j<count; j++){
            tmp[j] = this->data[pos1+j];
            this->data[pos1+j] = this->data[pos2+j];
            this->data[pos2+j] = tmp[j];
        }
    }
}


/*Quicksort*/
Number partition(Vector &v, Number &lo, Number &hi){
    Number pivot = v[hi];
    Number i = lo;
    for(Number j=lo; j<=hi-1; j++){
        if(v[j]<pivot){
            v.swap(i,j);
            i+=1;
        }
    }
    v.swap(i,hi);
    return i;
}

Vector Vector::sort(Number lo, Number hi){
    if(hi<=-1)hi = this->length()-1;
    if(lo<hi){ 
        Number p = partition(*this,lo,hi);
        this->sort(lo, p-1);
        this->sort(p+1,hi);
    }
    return *this;
}

Vector sort(Vector v){
    return v.sort();
}

Vector Vector::reverse(){
    for(Number j=0; j<this->length()/2; j++){
        this->swap(j,this->length()-j-1);
    }
    return *this;
}

Vector reverse(Vector v){
    return v.reverse();
}

Vector Vector::operator+=(Vector v){
    Number max = std::min(this->length(), v.length());
    for(int j=0; j<max; j++){ this->data[j] += v[j];}
    return *this;
}

Vector Vector::operator-=(Vector v){
    Number max = std::min(this->length(), v.length());
    for(int j=0; j<max; j++){ this->data[j] -= v[j];}
    return *this;
}

Vector Vector::operator*=(Number n){
    for(int j=0; j<this->length(); j++){ this->data[j] *= n;}
    return *this;
}

Vector Vector::operator/=(Number n){
    for(int j=0; j<this->length(); j++){ this->data[j] /= n;}
    return *this;
}

Vector Vector::operator%=(Number n){
    for(int j=0; j<this->length(); j++){ this->data[j] %= n;}
    return *this;
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

    // Pregunta por numero de elementos del vector si no fue definido previamente
    if(v.length()==0) {
        int count;
        std::cout<<"Vector size: ";
        std::cin>>count;
        fflush(stdin);
        v.resize(count);
    }

    // Lectura de datos
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
// Residuo
Vector operator%(Vector v,const Number &n){
    Vector result = v;
    result%=n;
    return result;
}

Vector zeros(const Number &n){
    Vector z; z.resize(n);
    return z;
}

Vector ones(const Number &n){
    Vector o;
    o.resize(n);
    for(int j=0; j<n; j++) o[j] = 1;
    return o;
}

Vector range(Vector v, const Number &begin, const Number &end, Number value){
    Vector result;
    if(value>0 && end>begin){
        for(Number j=begin; j<=end; j+=value){
            result.append(v[j]);
        }
    }else if(value<0 && begin>end){
        for(Number j=begin; j>=end; j+=value){
            result.append(v[j]);
        }
    }
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