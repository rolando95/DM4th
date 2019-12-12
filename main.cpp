#include "DM4th/DM4th.h"

using namespace std;

int main()
{
    NDArray<string> hello  = items<string>("Hello", "World");
    NDArray<number> myList = range<number>(5*5*5);

    cout << hello << endl;
    cout << myList << endl;

    myList.reshape(3,2,5,3);

    print(myList);

    auto r = myList.query(items<bool>(true,false,true),1,0,items<int>(1,2));
    auto rw = myList.subArr(items<int>(0,2)           ,1,0,items<int>(1,2));

    
    print("R");
    print(NDArray<number>(r));
    print("RW");
    print(NDArray<number>(rw));
    cin.get();
    return 0;
}