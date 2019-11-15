#include "../../DM4th/DM4th.h"
#include "../DM4thTest.h"

int main()
{

    TEST("NDArray Vector Aritmethic", []{
        NDArray<number> A = range<number>(5), B = items<number>(0);

        A += 1;
        A += items<number>(2);

        EXPECT_TRUE(A.isEqualTo(items<number>(3,4,5,6,7)));

        A -= 1;
        A -= items<number>(3);

        EXPECT_TRUE(A.isEqualTo(items<number>(-1,0,1,2,3)));

        B += items<number>(1,2,3);
        B -= items<number>(1,2,3);

        EXPECT_TRUE(B.isEqualTo(items<number>(0,0,0)));

        A = items<number>(-1i,0,1,2,3);
        B = items<number>( 5i,4,3,2,1);

        A *= B;

        EXPECT_TRUE(A.isEqualTo(items<number>(15)));

        A %= 2;

        EXPECT_TRUE(A.isEqualTo(items<number>(1)));

        A = map<number>([](number x){return x*x;}, items<number>(1,2,3,4,5)) * 2i;
        A = A / 2i;
        A = A + 3i;
        A = A - 3i;
        A = A + A;
        A = A - A/2;
    
        EXPECT_TRUE(A.isEqualTo(items<number>(1,4,9,16,25)));

        A = A % 2;

        EXPECT_TRUE(A.isEqualTo(items<number>(1,0,1,0,1)));

    });
    
    return TEST::ERROR_LEVEL();
}