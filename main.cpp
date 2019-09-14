#include "DM4th/DM4th.h"

int main(){

    NDArray<string> salute  = items<string>("Hello", "World");
    NDArray<Number> myList  = range<Number>(0,10);

    print(salute, myList);

    input();
    return 0;
}
