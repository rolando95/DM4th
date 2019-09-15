#include "DM4th/DM4th.h"

int main()
{
    NDArray<number> values = range<number>(0,10);
    print(values, values*2);

    // 6x^(3)+x^(2)−x-3
    NDArray<number> polynomial = items<number>(6,1,-1,-3);
    print(bairstowsMethod(polynomial));

    input();
    return 0;
}