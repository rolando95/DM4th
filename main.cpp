#include "Number.h"
int main(){
    Array<int> arr = items<int>(10,20,30,40,50,60,70,80,90,100);

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

    arr = range<int>(0,10);

    Array<float> arr2 = range<float>(11);
    std::cout<<(arr<arr2)<<" "<<(arr!=arr2)<<std::endl;
}
