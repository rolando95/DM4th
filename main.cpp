#include "Number.h"
int main(){ 
    // Array<int> arr;
    // arr.resize(3,4,5);
    // arr.item(1,3,2) = 50;
    // for (int x=0; x<3; x++){
    //     for(int y=0; y<4; ++y){
    //         for(int z=0; z<5; ++z){
    //             std::cout<<arr(x,y,z)<<" ";
    //         }
    //         std::cout<<std::endl;
    //     }
    //     std::cout<<std::endl;
    // }

    // TemplateArray<int> size = arr.shape();

    // for(int x=0; x<size.shape(0); ++x){
    //     std::cout<<size.item(x)<<" ";
    // }
    // std::cout<<std::endl;

    range<int> a;
    float *ref = nullptr;
    Array<> arr;
    Array<> arr2;
    arr2.resize(3);
    arr.resize(10);
    arr.item(0) = 10;
    arr.item(1) = 20;
    arr.item(2) = 30;
    arr.resize(5);

    arr.shape();

    arr2 = arr;

    ref = arr.c_arr();

    ref[2] = 100;


    for(int j=0; j<arr.shape(0); j++){
        std::cout<<arr2.item(j)<<" "<<arr.item(j)<<std::endl;
    }

    range<float> x(0,10,2);

    arr2 =  range<float>(10,0,-2);
    std::cout<<"HOLA "<<arr2.shape(0)<<std::endl;
    for(int j=0; j<arr2.shape(0); j++){
        std::cout<<arr2.item(j)<<std::endl;
    }
    std::cout<<arr.shape(0)<<" "<<std::endl;
}
