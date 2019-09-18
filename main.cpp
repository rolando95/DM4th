#include "DM4th/DM4th.h"

int main(){

    NDArray<string> hello  = items<string>("Hello", "World");
    NDArray<number> myList = range<number>(10);

    print(hello, myList);

    Tree<int> a;
    input();
    return 0;
}