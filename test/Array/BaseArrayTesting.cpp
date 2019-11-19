#include "../../DM4th/DM4th.h"
#include "../DM4thTest.h"

int main()
{
    TEST("BaseArray References", []{

        DM4thInternal::BaseArray<number> A, B;

        A.resize(5);

        A.moveReferenceTo(B);

        EXPECT_EQ(A.size(), 0);
        EXPECT_EQ(B.size(), 5);

        B.copyReferenceTo(A);

        EXPECT_EQ(B.size(), A.size());

        B.clear(); A.clear();
    });

    TEST("Base Array EQ NEQ", []{
        DM4thInternal::BaseArray<number> A, B;

        A.resize(10);
        B.resize(10);

        for(int j=0; j<A.size(); ++j)
        {
            A.set(j, j);
            B.set(j, A.get(j));
        }

        EXPECT_EQ(A,B);

        number value = B.get(9);
        B.set(9, 4);

        EXPECT_NE(A,B);

        A.clear(); B.clear();
    });

    TEST("BaseArray Arithmetic", []{
        DM4thInternal::BaseArray<number> A, B;

        A.resize(10);
        for(int j=0; j<A.size(); ++j)
        {
            A.set(j, 1);
        }
        A.copyReferenceTo(B);
        A += 4;
        B *= 20;
        B /= 2;
        B -= 5;
        EXPECT_EQ(A,B);

        B %= 2;
        for(int j=0; j<B.size(); j++)
        {
            int k = (int)A.get(j).real();
            if(k%2==0) {EXPECT_EQ(B.get(j), 0);}
            else{EXPECT_NE(B.get(j), 0);}
        }

        
        DM4thInternal::BaseArray<number> C;
        C = A;
        C.set(0,-1);
        EXPECT_NE(C,A);
        C.set(0, A.get(0));
        A += B; 
        A -= B;
        EXPECT_EQ(A,C)

        A.clear(); B.clear(); C.clear();
    });

    return TEST::ERROR_LEVEL();
}