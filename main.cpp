#include "Number.h"
int main(){
    NDArray<int> arr = items<int>(1,2,3);
    arr.reshape(3,1);
    NDArray<int> arr2 = items<int>(1,2,3);
    arr2.reshape(1,3);

    cout<<arr<<endl;
    arr = arr%2;
    cout<<arr<<endl;
    
    arr*= arr2;
    cout<<(arr);
    return 0;
}
