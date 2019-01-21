#include "V.h"

V::V(){}

V::V(const V &v){
    *this = v;
}

N& V::operator[](N n){
    int pos = n.r;
    if(pos<0) pos = 0;
    if(pos>=this->count) resize(pos+1);
    return data[pos];
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

N V::length(){
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

V list(){return V();}

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