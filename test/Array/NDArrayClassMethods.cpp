#include "../../DM4th/DM4th.h"
#include "../DM4thTest.h"

int main()
{
    TEST("NDArray Copy and Move Data", []{
        NDArray<number> A = linespace<number>(0,10,10,false);
        NDArray<number> B;

        // Move
        A.moveDataTo(B);

        EXPECT_EQ(A.data_size(),0);

        EXPECT_TRUE(A.shapeSize()<2);
        EXPECT_EQ(A.shape(0),0);

        EXPECT_EQ(B.data_size(),10);
        EXPECT_EQ(B.shape(0), 10);

        // Copy
        B.copyDataTo(A);

        EXPECT_EQ(A,B);
        B(0) =  -1;
        EXPECT_NE(A,B);

        EXPECT_EQ(B.data_size(), 10);
        EXPECT_EQ(B.shape(0), 10);
    });

    TEST("NDArray resize, reshape and shape", []{
        NDArray<number> A;
        EXPECT_EQ(A.shape(), 0);

        A.resize(10,3);
        EXPECT_EQ(A.shape(), items<int>(10,3));

        A.reshape(3,10);
        EXPECT_EQ(A.shape(), items<int>(3,10));
        EXPECT_EQ(A.shapeSize(), 2);

        A.resize(6);
        A(0) = 0; A(1) = 1i; A(2) = 2i; A(3) = 3i; A(4) = 4i; A(5) = 5i; 

        EXPECT_EQ(A, items<number>(0,1i,2i,3i,4i,5i));

        A.reshape(2,3);
        EXPECT_EQ(A.shape(), items<int>(2,3));
        EXPECT_EQ( NDArray<number>(A.subArr(0)), items<number>( 0,1i,2i));
        EXPECT_EQ( NDArray<number>(A.subArr(1)), items<number>(3i,4i,5i));

        A.resize(2,1,1);
        A.reshape(2);

        EXPECT_EQ(A, items<number>(0,3i));
    });

    TEST("NDArray other methods",[]{
        NDArray<number> A = items<number>(5,3,7,6,2,1,4);
        A.sort();
        EXPECT_EQ(A,items<number>(1,2,3,4,5,6,7));
        A.sort(true);
        EXPECT_EQ(A,items<number>(7,6,5,4,3,2,1));

        

    });
    return TEST::ERROR_LEVEL();
}