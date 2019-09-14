#include "Number.h"

FUNCTION(f)
{
    return x*x+1;
}

int main(){

    NDArray<int> array = range<int>(25);
    array.reshape(5,5);
    array.saveFile("intNDArray.txt");
    TemplateTree<int> example;
    example.loadFile("intTree.txt");

    cout<<example;
    return 0;
}
