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

        A = map<number>([](number x){return x*x;}, range<number>(5)) * 2i;
        A = A / 2i;
        A = A + 3i;
        A = A - 3i;
        A = A + A;
        A = A - A/2;

        EXPECT_TRUE(A.isEqualTo(items<number>(0,1,4,9,16)));

        A = A % 2;

        EXPECT_TRUE(A.isEqualTo(items<number>(0,1,0,1,0)));

    });

    TEST("NDArray Matrix Aritmethic", []{
        NDArray<number> A = items<number>(
            1,2,
            2,3,
            1,5
        ).reshape(3,2);

        NDArray<number> B = items<number>(
            3,2,5,
            4,5,4
        ).reshape(2,3);

        NDArray<number> C = items<number>(
            11,12,13,
            18,19,22,
            23,27,25
        ).reshape(3,3);

        A = A*2 + A;
        A /= 3;

        EXPECT_TRUE((A*B).isEqualTo(C));

        A.resize(2,2);
        B = A.reshape(1,4).getCopy().reshape(4,1);

        NDArray<number> D = items<number>(18);

        EXPECT_TRUE( (A*B).isEqualTo(D) );

        
    });

    return TEST::ERROR_LEVEL();
}