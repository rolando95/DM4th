#include "../../DM4th/DM4th.h"
#include "../../DM4th/Test/DM4thTest.h"

using namespace std;
using namespace DM4th;

// Assign value into ref array
NDArray<number> dummyFunction(NDArray<number> array, int idx, number value)
{
    array(idx) = value;
    return array;
}

// Doesn't doing nothing
NDArray<number> dummyFunction2(NDArray<number> array)
{
    array = range<number>(10);
    return array;
}

int main()
{

    DM4thTest::TEST("NDArray References", []{
        NDArray<number> A, B, C;
        A = range<number>(10);

        // Ref assignments
        C = B = dummyFunction(A, 0, -50_i);

        C(5) = 150;
        B(2) = 35_i;

        // In-place operations
        dummyFunction2(A);
        A += B;
        A -= B;
        A += 1;
        A -= 1;
        A *= 2;
        A /= 2;
        A %= 1;
        A.resize(3,5);
        A.reshape(15);
        A *= items<number>(2);

        EXPECT_EQ(A.refCount(), 3);
        EXPECT_TRUE( (A==B).all() );
        EXPECT_TRUE(A.isEqualTo(C));
        EXPECT_TRUE( A.isSameRef(B) );
        EXPECT_FALSE( !B.isSameRef(C) );
        
        // Copy assignments
        B = A.getCopy();
        C = B.getCopy();

        EXPECT_EQ(A, B);
        EXPECT_EQ(A, C);
        EXPECT_EQ(A.refCount(), 1);
        EXPECT_EQ(B.refCount(), 1);
        EXPECT_EQ(C.refCount(), 1);

        C(9) = -1;
        B(8) = -2;
        
        EXPECT_FALSE(A.isEqualTo(C));
        EXPECT_NE(A, C);
        EXPECT_NE(A, B);

    });


    return DM4thTest::TEST::ERROR_LEVEL();
}