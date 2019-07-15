#include "Number.h"
int main(){
    Array<int> arr = items<int>(10,20,30,40,50,60,70,80,90,100);

    arr.resize(3,4,5);
    arr.item(1,3,2) = 50;
    cout<<arr<<endl;

    Array<int> size = arr.shape();
    cout<<size<<endl;

    arr = range<int>(0,10);

    Array<float> arr2 = range<float>(11);
    std::cout<<(arr<arr2)<<" "<<(arr!=arr2)<<std::endl;
}
