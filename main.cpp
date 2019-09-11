#include "Number.h"
int main(){
    NDArray<Number> arr2 = items<Number>(1,2,0,-1);
    cout<<bairstowsMethod(arr2)<<endl;

    return 0;
}
