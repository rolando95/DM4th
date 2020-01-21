#include "DM4th/DM4th.h"
#include <iostream>

using namespace std;
using namespace DM4th;

int main()
{
    NDArray<string> hello  = items<string>("Hello", "World");
    NDArray<number> myList = range<number>(10);

    cout << hello << endl;
    cout << myList << endl;

    cin.get();
    return 0;
}