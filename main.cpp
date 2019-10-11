#include "DM4th/DM4th.h"

int main(){
    NDArray<string> hello  = items<string>("Hello","World");
    NDArray<number> myList = range<number>(10);
    print(hello,myList);

    input();
    return 0;
}