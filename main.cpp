#include "DM4th/DM4th.h"

int main(){
    NDArray<string> hello  = items<string>("Hello", "World");
    NDArray<number> myList = range<number>(10);
    myList.resize(5,2);
    myList.reshape(2,5);
    myList.item(2) = 10;
    myList.pushArray(items<int>(1,3,2,5,4));
    print(hello, myList);

    
    input();
    return 0;
}