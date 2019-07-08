#include "Number.h"
int main(){ 
    Array<int> arr;
    arr.resize(10);
    int* c_arr = arr.c_arr();
    for(int j=0; j<10; ++j){
        c_arr[j] = j+1;
    }
    arr.resize(3,4,5);
    arr.item(1,3,2) = 50;
    for (int x=0; x<3; x++){
        for(int y=0; y<4; ++y){
            for(int z=0; z<5; ++z){
                std::cout<<arr(x,y,z)<<" ";
            }
            std::cout<<std::endl;
        }
        std::cout<<std::endl;
    }

    Array<int> size = arr.shape();

    for(int x=0; x<size.shape(0); ++x){
        std::cout<<size.item(x)<<" ";
    }
    std::cout<<std::endl;
}
