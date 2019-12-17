#include "../../DM4th/DM4th.h"
#include "../../DM4th/Test/DM4thTest.h"

using namespace std;
using namespace DM4th;

int main()
{
    DM4thTest::TEST("NDArray Copy and Move Data", []{
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

        A = items<number>(1,3,2,5).reshape(2,2);
        B = A.getCopy();
        EXPECT_EQ(A,B);
        EXPECT_EQ(A.refCount(),1);
        EXPECT_EQ(B.refCount(),1);
        B(0,0) = 2;
        EXPECT_NE(A,B);
    });

    DM4thTest::TEST("NDArray resize, reshape and shape", []{
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
        EXPECT_EQ( NDArray<number>(A.view(0)), items<number>( 0,1_i,2_i));
        EXPECT_EQ( NDArray<number>(A.view(1)), items<number>(3_i,4_i,5_i));

        A.reshape(3,1,2);
        EXPECT_EQ( NDArray<number>(A.view(slice(0,2),0,1)), items<number>(1_i,3_i));   

        A.reshape(2,3);

        A.resize(2,1,1);
        A.reshape(2);

        EXPECT_EQ(A, items<number>(0,3_i));

        A = items<number>(1,2,3,4,5,6).reshape(3,2);
        A.resize(3,1);
        A.resize(3,4);
        A.reshape(12);
        EXPECT_EQ(A, items<number>(1,0,0,0,3,0,0,0,5,0,0,0));
    });

    DM4thTest::TEST("NDArray push and pop",[]{
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

    DM4thTest::TEST("NDArray other methods",[]{
        NDArray<number> A, B;

        // Sort
        A = items<number>(5,3,7,6,2,1,4);
        A.sort();
        EXPECT_EQ(A,items<number>(1,2,3,4,5,6,7));
        A.sort(true);
        EXPECT_EQ(A,items<number>(7,6,5,4,3,2,1));

        // Reduce 
        A = items<number>(1,2,3,4,5,6,7,8,9,10);
        number result = A.reduce([](number a, number b){return a+b;});
        EXPECT_EQ(result, 55);

        // Map
        A = items<number>(1,2,3,4,5,6,7,8,9,10);
        B = A.map([](number a, number b){ return a-b+15; });
        EXPECT_EQ(B, items<number>(16,16,16,16,16,16,16,16,16,16));
        
        // Filter
        A = items<number>(1,2,3,4,5,6,7,8,9,10).reshape(5,2);
        B = A.filter([](number a, number b)->bool { return true; });
        EXPECT_EQ(B, A);
        B = A.filter([](number a, number b)->bool { return a>3 && a<7; });
        EXPECT_EQ(B, items<number>(4,5,6));

        // I/O file
        A = items<number>(7,6,5,4,3,2,1);
        A.saveFile("test.txt");
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


    return DM4thTest::TEST::ERROR_LEVEL();
}