#include "DM4th/DM4th.h"

int main(){
    NDArray<number> hello  = items<number>(1,2,3);
    NDArray<number> myList = range<number>(10);
    print(hello==myList);

    input();
    return 0;
}