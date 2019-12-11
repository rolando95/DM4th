#include "../../DM4th/DM4th.h"
#include "../../DM4th/Test/DM4thTest.h"

int main()
{
    DM4thTest::TEST("Items & range", []{
        NDArray<number> A = items<number>(1,3,5,7,9);
        number *data = A.data();

        EXPECT_EQ(data[0], 1);
        EXPECT_EQ(data[1], 3);
        EXPECT_EQ(data[2], 5);
        EXPECT_EQ(data[3], 7);
        EXPECT_EQ(data[4], 9);

        A = range<number>(0,-10,-2);
        data = A.data();

        EXPECT_EQ(data[0], 0);
        EXPECT_EQ(data[1], -2);
        EXPECT_EQ(data[2], -4);
        EXPECT_EQ(data[3], -6);
        EXPECT_EQ(data[4], -8);

        A = range<number>(0,2.5,0.5);
        data = A.data();

        EXPECT_EQ(data[0], 0);
        EXPECT_EQ(data[1], 0.5);
        EXPECT_EQ(data[2], 1);
        EXPECT_EQ(data[3], 1.5);
        EXPECT_EQ(data[4], 2);

        A = range<number>(3);
        data = A.data();
        
        EXPECT_EQ(data[0], 0);
        EXPECT_EQ(data[1], 1);
        EXPECT_EQ(data[2], 2);
    });

    return DM4thTest::TEST::ERROR_LEVEL();
}