#include "Number.h"
int main(){
    NDArray<float> arr = items<float>(10,20,30,40,50,60,70,80,90);

    arr.push(100,5);
    float result = arr.pop(0);
    cout<<result<<" "<<arr<<endl;
    arr.push(result);
    cout<<arr<<endl;

    arr.resize(10);
    NDArray<int> arr2 = range<int>(10);
    NDArray<float> arr3 = arr+arr2;
    cout<<(arr-arr2)<<endl;

    NDArray<float> arr4 = arr.getCopy();
    arr4.pushArray(arr2,0);
    cout<<arr4<<endl;

    NDArray<string> list = items<string>("Hola", "Mundo");
    cout<<list<<endl;
    
    NDArray<bool> listB = items<bool>(false, true, false, false);
    cout<<listB<<" "<<!listB<<endl;

    NDArray<float> matriz = items<float>(0,1,2,3,4,5,6,7,8,9);
    matriz.reshape(2,5);
    NDArray<float> rango = range<float>(5);
    matriz.pushArray(rango,1);

    cout<<matriz<<endl;
    NDArray<float> result2 = matriz.popArray(1);
    cout<<result2<<" "<<matriz<<endl;
    return 0;
}
