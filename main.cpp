#include "DM4th/DM4th.h"

int main(){

    NDArray<string> salute = items<string>("Hello", "World"); 
    NDArray<int> myRange = range<int>(0,10);

    print(salute, myRange);

    sleep(5);
}
