#include "V.h"

V::V(){
    data.reserve(1);
}

N V::push(const N &n, const N position){
    int pos = position.r;
    if(pos<0) {data.push_back(n);count++;}
    else {
        if(pos<=count){
            vector<N>::iterator ni=data.begin() + pos;
            data.insert(ni,n);
            count++;
        }else{
            data.resize(pos-1);
            data.push_back(n);
            count = pos;
        }
    }
    return n;
}

V V::push(const V& v, const N position){
    int pos = position.r;
    if(pos<0 || pos>=this->count) {data.insert(data.end(), v.data.begin(), v.data.end());}
    else{
        if(pos<=count){
            vector<N>::iterator ni=data.begin() + pos;
            data.insert(ni,v.data.begin(), v.data.end());
        }
    }
    this->count += v.count;
    return v;
}

N V::length(){
    return this->count;
}

void V::resize(const N &pos){
    int c = int(pos.r);
    if(c>=0){
        data.resize(c);
        count = c;
    }
}

V array(){return V();}