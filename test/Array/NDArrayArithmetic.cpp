#include "../../DM4th/DM4th.h"
#include "../../DM4th/Test/DM4thTest.h"

using namespace std;
using namespace DM4th;

int main()
{

    DM4thTest::TEST("NDArray Vector Aritmethic", []{
        NDArray<number> A = range<number>(5), B = items<number>(0);

        A += 1;
        A += items<number>(2);

        EXPECT_EQ(A,items<number>(3,4,5,6,7));

        A -= 1;
        A -= items<number>(3);

        EXPECT_EQ(A,items<number>(-1,0,1,2,3));

        B = B + items<number>(1,2,3) - items<number>(1,2,3);

        EXPECT_EQ(B,items<number>(0,0,0));

        NDArray<number> C = items<number>(10);
        C -= items<number>(1,2,3);
        EXPECT_EQ(C,items<number>(9,8,7));
        
        A = items<number>(-1_i,0,1,2,3);
        B = items<number>( 5_i,4,3,2,1);

        A *= B;

        EXPECT_EQ(A,items<number>(15));

        A %= 2;

        EXPECT_EQ(A,items<number>(1));

        A = map<number>([](number x){return x*x;}, range<number>(5)) * 2_i;
        A = A / 2_i;
        A = A + 3_i;
        A = A - 3_i;
        A = A + A;
        A = A - A/2;

        EXPECT_EQ(A,items<number>(0,1,4,9,16));

        A = A % 2;

        EXPECT_EQ(A,items<number>(0,1,0,1,0));

    });

    DM4thTest::TEST("NDArray Vector FLOAT Aritmethic", []{
        NDArray<float> A = range<float>(5), B = items<float>(0);

        A += 1;
        A += items<float>(2);

        EXPECT_EQ(A,items<float>(3,4,5,6,7));

        A -= 1;
        A -= items<float>(3);

        EXPECT_EQ(A,items<float>(-1,0,1,2,3));

        B += items<float>(1,2,3);
        B -= items<float>(1,2,3);

        EXPECT_EQ(B,items<float>(0,0,0));

        NDArray<float> C = items<float>(10);
        C -= items<float>(1,2,3);
        EXPECT_EQ(C,items<float>(9,8,7));
        
        A = items<float>( 1,0,1,2,3);
        B = items<float>( 5,4,3,2,1);

        A *= B;

        EXPECT_EQ(A,items<float>(15));

        A %= 2;

        EXPECT_EQ(A,items<float>(1));

        A = map<float>([](float x){return x*x;}, range<float>(5)) * 2;
        A = A / 2;
        A = A + 3;
        A = A - 3;
        A = A + A;
        A = A - A/2;

        EXPECT_EQ(A,items<float>(0,1,4,9,16));

        A = A % 2;

        EXPECT_EQ(A,items<float>(0,1,0,1,0));

    });

    DM4thTest::TEST("NDArray Vector DOUBLE Aritmethic", []{
        NDArray<double> A = range<double>(5), B = items<double>(0);

        A += 1;
        A += items<double>(2);

        EXPECT_EQ(A,items<double>(3,4,5,6,7));

        A -= 1;
        A -= items<double>(3);

        EXPECT_EQ(A,items<double>(-1,0,1,2,3));

        B += items<double>(1,2,3);
        B -= items<double>(1,2,3);

        EXPECT_EQ(B,items<double>(0,0,0));

        NDArray<double> C = items<double>(10);
        C -= items<double>(1,2,3);
        EXPECT_EQ(C,items<double>(9,8,7));
        
        A = items<double>( 1,0,1,2,3);
        B = items<double>( 5,4,3,2,1);

        A *= B;

        EXPECT_EQ(A,items<double>(15));

        A %= 2;

        EXPECT_EQ(A,items<double>(1));

        A = map<double>([](double x){return x*x;}, range<double>(5)) * 2;
        A = A / 2;
        A = A + 3;
        A = A - 3;
        A = A + A;
        A = A - A/2;

        EXPECT_EQ(A,items<double>(0,1,4,9,16));

        A = A % 2;

        EXPECT_EQ(A,items<double>(0,1,0,1,0));

    });

    DM4thTest::TEST("NDArray Matrix Aritmethic", []{
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

        EXPECT_EQ(A*B,C);

        A.resize(2,2);
        B = A.reshape(1,4).getCopy().reshape(4,1);

        NDArray<number> D = items<number>(18);

        EXPECT_EQ(A*B,D);

        
    });

    DM4thTest::TEST("rvalue", [&](){
        NDArray<number> A = items<number>(1,3,5,7,9);
        NDArray<number> B = A*2/2 + 1 - 2 + A;

        EXPECT_EQ(A, items<number>(1,3,5,7,9));
        EXPECT_EQ(B, items<number>(1,5,9,13,17));

    });
    return DM4thTest::TEST::ERROR_LEVEL();
}