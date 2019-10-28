#include "DM4th/DM4th.h"

int main()
{
    NDArray<number> myList = range<number>(10);
    print(myList);

    input();
    return 0;
}