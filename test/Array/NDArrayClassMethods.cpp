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

        EXPECT_TRUE(A.rank()<2);
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
        EXPECT_EQ(A.rank(), 2);

        A.resize(6);
        A(0) = 0; A(1) = 1_i; A(2) = 2_i; A(3) = 3_i; A(4) = 4_i; A(5) = 5_i; 

        EXPECT_EQ(A, items<number>(0,1_i,2_i,3_i,4_i,5_i));

        A.reshape(2,3);
        EXPECT_EQ(A.shape(), items<int>(2,3));
        EXPECT_EQ( NDArray<number>(A.subArr(0)), items<number>( 0,1_i,2_i));
        EXPECT_EQ( NDArray<number>(A.subArr(1)), items<number>(3_i,4_i,5_i));

        A.resize(2,1,1);
        A.reshape(2);

        EXPECT_EQ(A, items<number>(0,3_i));
    });

    TEST("NDArray push and pop",[]{
        NDArray<number> A = items<number>(1,2,3,4,5,6,7);
        A.push(8);
        A.push(0,0);
        A.push(2.5,3);

        EXPECT_EQ(A, items<number>(0,1,2,2.5,3,4,5,6,7,8));

        A.pop();
        A.pop(3);
        A.pop(0);

        EXPECT_EQ(A, items<number>(1,2,3,4,5,6,7));

        A.pushArray(items<number>(8,9,10));
        A.pushArray(items<number>(0,0.3,0.6),0);

        EXPECT_EQ(A, items<number>(0,0.3,0.6,1,2,3,4,5,6,7,8,9,10));

        A.pop(0);
        A.reshape(6,2);
        A.popArray(0);
        A.popArray();
        A.reshape(8);
        A.pop();
        
        EXPECT_EQ(A, items<number>(1,2,3,4,5,6,7));
    });

    TEST("NDArray other methods",[]{

        // Sort
        NDArray<number> A = items<number>(5,3,7,6,2,1,4);
        A.sort();
        EXPECT_EQ(A,items<number>(1,2,3,4,5,6,7));
        A.sort(true);
        EXPECT_EQ(A,items<number>(7,6,5,4,3,2,1));

        // Reduce 
        A = items<number>(1,2,3,4,5,6,7,8,9,10);
        number result = A.reduce([](number a, number b){return a+b;});
        EXPECT_EQ(result, 55);

        // I/O file
        A.saveFile("test.txt");
        NDArray<number> B;
        B.loadFile("test.txt");
        EXPECT_EQ(B,items<number>(7,6,5,4,3,2,1));

        // Displacement
        B.pushArray(items<number>(8,9,10,11,12));
        B.reshape(2,2,3);
        EXPECT_EQ(B._getAxisDisplacement(), items<int>(6,3,1));

        // Iterator
        int j = 0;
        for(auto &x: A)
        {
            EXPECT_EQ(x,7-j);
            x *= i;
            ++j;
        }
        EXPECT_EQ(A,items<number>(7_i,6_i,5_i,4_i,3_i,2_i,_i));

        const NDArray<number> C = A.getCopy();

        // Iterator_const
        j = 0;
        for(auto &x: C)
        {
            EXPECT_EQ(x,A(j));
            ++j;
        }
        EXPECT_EQ(j,C.data_size());
    });


    return TEST::ERROR_LEVEL();
}