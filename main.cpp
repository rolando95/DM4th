#include "DM4th/DM4th.h"

int main(){

    NDArray<string> salute  = items<string>("Hello", "World");
    NDArray<float> myList  = items<float>(1,2,3,4,5);

    print(bairstowsMethod(myList));
    print(salute, myList);

    input();
    return 0;
}
