#include "Number.h"

FUNCTION(f)
{
    return x*x+1;
}

int main(){
    NDArray<Number> arr2 = items<Number>(1,2,0,-1);
    cout<<bairstowsMethod(arr2)<<endl;
    cout<<integral(f, 0, 10);
    return 0;
}
