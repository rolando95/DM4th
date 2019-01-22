#include "V.h"
V::V(){}

V::V(const V &v){
    *this = v;
}

N& V::operator[](N n){
    int pos = n.r;
    if(pos<0) pos = 0;
    if(pos>=this->count) resize(pos+1);
    return this->data[pos];
}

N V::append(const N &n, const N position){
    int pos = position.r;
    if(pos<0 || pos>=this->count) {data.push_back(n);count++;}
    else {
        data.insert(data.begin() + pos,n);
        count++;
    }
    return n;
}

V V::append(const V& v, const N position){
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

N V::pop(const N position){
    N value;
    int pos = position.r;
    if(this->count > 0){
        if(pos>=this->count) {
            value = this->data[count-1];
            data.pop_back();count--;
        }else{
            value = this->data[pos];
            data.erase(data.begin()+pos);
        }
    }else
        return 0;
    return value;
}

N V::length() const{
    return this->count;
}

V V::find(const N &value){
    V result;
    for(int j=0; j<count; j++){
        if(value==this->data[j]) result.append(j);
    }
    return result;
}

V V::find(V value){
    V result;
    for(int j=0; j<value.count; j++){
        result.append(find(value[j]));
    }
    return result;
}

void V::resize(const N &pos){
    int c = int(pos.r);
    if(c>=0){
        data.resize(c);
        count = c;
    }
}

V::operator+=(V v){
    N max = min(this->length(), v.length());
    for(int j=0; j<max; j++){ this->data[j] += v[j];}
}
V::operator-=(V v){
    N max = min(this->length(), v.length());
    for(int j=0; j<max; j++){ this->data[j] -= v[j];}
}
V::operator*=(N n){
    for(int j=0; j<this->length(); j++){ this->data[j] *= n;}
}
V::operator/=(N n){
    for(int j=0; j<this->length(); j++){ this->data[j] /= n;}
}
V::operator%=(N n){
    for(int j=0; j<this->length(); j++){ this->data[j] %= n;}
}

ostream& operator<<(ostream& stream, V v){
    stream<<"(";
    for(int n=0; n<v.length(); n++){
        if(n!=0) stream<<", ";
        stream<<v.data[n];
    }
    stream<<")";
    return stream;
}

istream& operator>>(istream& stream, V &v){
    for(int n=0; n<v.length(); n++){
        cout<<"["<<n<<"]: ";
        stream>>v[n];
    }
    return stream;
}

// Suma de vectores
V operator+(V v1,V v2){
    V result = v1;
    result += v2;
    return result;
}

// Resta de vectores
V operator-(V v1,V v2){
    V result = v1;
    result -= v2;
    return result;
}

// Producto escalar
N operator*(V v1,V v2){
    N result = 0;
    N max = min(v1.length(), v2.length());
    for(int j=0; j<max; j++){
        result += v1[j]*v2[j];
    }
    return result;
}

// Producto entre vector y escalar
V operator*(V v,const N &n){
    V result = v;
    result*=n;
    return result;
}
V operator*(const N &n, V v){
    return v*n;
}

// Division entre vector y escalar
V operator/(V v,const N &n){
    V result = v;
    result/=n;
    return result;
}

V range(const N &begin, const N &end, N value){
    V v;
    if(value>0 && end>begin){
        for(N j=begin; j<=end; j+=value){
            v.append(j);
        }
    }else if(value<0 && begin>end){
        for(N j=begin; j>=end; j+=value){
            v.append(j);
        }
    }else{
        return v;
    }
}

template<class T>
void vToArray(V &v, T *array, int n, bool imaginary){
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
template void vToArray(V&, int*     , int, bool);
template void vToArray(V&, long int*, int, bool);
template void vToArray(V&, float*   , int, bool);
template void vToArray(V&, double*  , int, bool);
template void vToArray(V&, N*       , int, bool);

template<class T>
void arrayToV(T* array, V &v, int n, bool imaginary){
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

template void arrayToV(int*,      V&, int, bool);
template void arrayToV(long int*, V&, int, bool);
template void arrayToV(float*,    V&, int, bool);
template void arrayToV(double*,   V&, int, bool);
template void arrayToV(N*,        V&, int, bool);