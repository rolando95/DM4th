
template<class T>
T mult(T* c_arr, int size){
    T result = 1;
    for(int j=0; j<size; ++j){
        result*=c_arr[j];
    }
    return result;
}

template<class T>
T sum(T* c_arr, int size){
    T result = 0;
    for(int j=0; j<size; ++j){
        result+=c_arr[j];
    }
    return result;
}
