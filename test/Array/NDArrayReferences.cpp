#include "../../DM4th/DM4th.h"
#include "../DM4thTest.h"

NDArray<number> dumpFunction(NDArray<number> array, int idx, number value)
{
    array(idx) = value;
    return array;
}

int main()
{

    TEST("NDArray Assignments", []{
        NDArray<number> A, B, C;
        A = range<number>(10);

        C = B = dumpFunction(A, 0, -50i);

        C(5) = 150;
        B(2) = 35i;

        EXPECT_EQ(A.refCount(), 3);
        EXPECT_TRUE( (A==B).all() );
        EXPECT_TRUE(A.isEqualTo(C));
        
        B = A.getCopy();
        C = B.getCopy();

        EXPECT_TRUE(A.isEqualTo(B));
        EXPECT_TRUE(A.isEqualTo(C));
        EXPECT_EQ(A.refCount(), 1);
        EXPECT_EQ(B.refCount(), 1);
        EXPECT_EQ(C.refCount(), 1);

        C(9) = -1;
        B(8) = -2;

        EXPECT_FALSE(A.isEqualTo(C));
        EXPECT_FALSE(A.isEqualTo(B));
    });


    return TEST::ERROR_LEVEL();
}