#include "../../DM4th/DM4th.h"
#include "../../DM4th/Test/DM4thTest.h"

using namespace std;
using namespace DM4th;

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

        NDArray<number> _A = {1,2,3};
        EXPECT_EQ(_A(0), 1);
        EXPECT_EQ(_A(1), 2);
        EXPECT_EQ(_A(2), 3);

        _A = {5,6,7};
        EXPECT_EQ(_A(0), 5);
        EXPECT_EQ(_A(1), 6);
        EXPECT_EQ(_A(2), 7);
    });

    DM4thTest::TEST("Subscript", []{
        NDArray<number> A = items<number>(1,3,5,7,9,11);

        EXPECT_EQ(A(0), 1);
        EXPECT_EQ(A(1), 3);
        EXPECT_EQ(A(2), 5);
        EXPECT_EQ(A(3), 7);
        EXPECT_EQ(A(4), 9);
        EXPECT_EQ(A(5), 11);

        A.reshape(3,1,2);

        EXPECT_EQ(A(0,0,0), 1);
        EXPECT_EQ(A(0,0,1), 3);
        EXPECT_EQ(A(1,0,0), 5);
        EXPECT_EQ(A(1,0,1), 7);
        EXPECT_EQ(A(2,0,0), 9);
        EXPECT_EQ(A(2,0,1), 11);
    });

    return DM4thTest::TEST::ERROR_LEVEL();
}