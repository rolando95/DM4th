#include "Number.h"

FUNCTION(f)
{
    return x*x+1;
}

int main(){

    TemplateTree<int> example;
    example.resize(5);
    example.child(3).resize(2);
    example.child(items<int>(3,1)).item() = 19;
    cout<<example(3,1).item()<<endl;
    return 0;
}
