#include "Number.h"
int main(){
    const NDArray<float> arr = items<float>(10,20,30,40,50,60,70,80,90,100);
    NDArray<float> arr2 = range<float>(10);
    NDArray<float> arr3 = arr+arr2;
    cout<<(arr-arr2);

    NDArray<string> list = items<string>("Hola", "Mundo");
    cout<<list;
    
    
    return 0;
}
