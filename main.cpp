#include "DM4th/DM4th.h"

using namespace std;

int main()
{
    NDArray<number> hello  = items<number>(15,20);
    NDArray<number> myList = range<number>(10);

    myList.subArr() = hello.subArr();

    cout << hello << endl;
    cout << myList << endl;

    cin.get();
    return 0;
}