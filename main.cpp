#include "Number.h"


int main(){
    
    int *ref;

    Array<> arr;
    Array<> arr2;
    arr2.resize(3);
    arr.resize(10);
    arr(0) = 10;
    arr(1) = 20;
    arr(2) = 30;
    arr.resize(5);

    arr.size();

    arr2 = arr;

    ref = arr.c_arr();

    ref[2] = 100;

    for(int j=0; j<arr.size(); j++){
        std::cout<<arr2(j)<<" "<<arr(j)<<std::endl;
    }
    std::cout<<arr.size()<<" "<<std::endl;
}
