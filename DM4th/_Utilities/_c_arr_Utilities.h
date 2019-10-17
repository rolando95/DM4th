#pragma once

namespace DM4th
{

template<class T>
T mult(const T* data, int size){
    T result = 1;
    for(int j=0; j<size; ++j){
        result=result*data[j];
    }
    return result;
}

template<class T>
T sum(T* data, int size){
    T result = 0;
    for(int j=0; j<size; ++j){
        result+=data[j];
    }
    return result;
}

}
