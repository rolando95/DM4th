#include "DM4th/DM4th.h"

int main(){
    NDArray<number> myList = range<number>(12);
    myList.reshape(3,2,2);

    myList += 1;
    print(myList);
    NDArray<number>::SubArray query = myList.subArr(
        range<int>(0,2), 
        items<int>(0), 
        items<int>(0,1)
    );

    NDArray<number>::SubArray query2 = myList.subArr(
        range<int>(0,2), 
        items<int>(0), 
        items<int>(0,1)
    );

    query = query2;

    print(NDArray<number>(query));

    input();
    return 0;
}