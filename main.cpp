#include "DM4th/DM4th.h"

using namespace std;
using namespace DM4th;

inline void iAddArray1(_number<float> *arr1, const _number<float> *arr2)
{
    SIMD::iAddArray<float>((float *)&arr1[0], (const float *)&arr2[0]);
}

int main()
{
    NDArray<string> hello  = items<string>("Hello", "World");
    NDArray<fnumber> myList = range<fnumber>(10);

    //iAddArray1(myList.data()+1, myList.data()+1);

    myList = myList *2 / 2;
    //hello = hello + hello + "WORLD";

    std::move(myList);

    print(myList);

    cin.get();
    return 0;
}