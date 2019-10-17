#include "DM4th/DM4th.h"

int main(){

    NDArray<number> matrix = items<number>(
        1,1,1,
        0,2,5,
        2,5,-1
    ).reshape(3,3);
    //NDArray<number> matrix = items<number>(3,7,8,5,2,1,9,5,4);

    number pos = 2;
    matrix.swap(1,pos);
    
    //print(matrix);
    NDArray<number> result = sort(matrix,true);
    print(result,matrix);

    input();
    return 0;
}