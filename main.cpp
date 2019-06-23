#include "Number.h"


int main(){
    
    Array arr;
    Array arr2;
    arr2.resizeArray(3);
    arr.resizeArray(10);
    arr(0) = 10;
    arr(1) = 20;
    arr(2) = 30;
    arr.resizeArray(5);

    arr.size();

    arr2 = arr;

    for(int j=0; j<arr.size(); j++){
        std::cout<<arr2(j)<<" "<<arr(j)<<std::endl;
    }
    std::cout<<arr.size()<<" "<<std::endl;
}
