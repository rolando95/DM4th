#include "Number.h"

FUNCTION(f)
{
    return x*x+1;
}

int main(){

    TemplateTree<int> example;

    example.node() = 10;
    example.resizeChildren(5);
    example(3).resizeChildren(10);
    example.item(3,5) = -150;
    cout<<example(3,5).node()<<" "<<example.childrenCount()<<endl;
    NDArray<Number> arr2 = items<Number>(1,2,0,-1);
    cout<<bairstowsMethod(arr2)<<endl;
    cout<<integral(f, 0, 10);
    return 0;
}
