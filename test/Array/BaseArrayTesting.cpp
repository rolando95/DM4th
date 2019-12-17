#include "../../DM4th/DM4th.h"
#include "../../DM4th/Test/DM4thTest.h"

using namespace std;
using namespace DM4th;


int main()
{
    DM4thTest::TEST("BaseArray References", []{

        DM4th::Internal::BaseArray<number> A, B;

        A.resize(5);

        A.moveDataTo(B);

        EXPECT_EQ(A.size(), 0);
        B.resize(15);
        B.resize(5);
        EXPECT_EQ(B.size(), 5);

        B.copyDataTo(A);

        EXPECT_EQ(B.size(), A.size());

        B.clear(); A.clear();
    });

    DM4thTest::TEST("Base Array EQ NEQ", []{
        DM4th::Internal::BaseArray<number> A, B;

        A.resize(10);
        B.resize(10);

        for(int j=0; j<A.size(); ++j)
        {
            A.set(j, j);
            B.set(j, A.get(j));
        }

        EXPECT_EQ(A,B);

        B.set(9, 4);

        EXPECT_NE(A,B);

        A.clear(); B.clear();
    });

    DM4thTest::TEST("BaseArray Arithmetic", []{
        DM4th::Internal::BaseArray<number> A, B;

        A.resize(10);
        for(int j=0; j<A.size(); ++j)
        {
            A.set(j, 1);
        }
        A.copyDataTo(B);
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

        
        DM4th::Internal::BaseArray<number> C;
        C = A;
        C.set(0,-1);
        EXPECT_NE(C,A);
        C.set(0, A.get(0));
        A += B; 
        A -= B;
        EXPECT_EQ(A,C);

        A.clear(); B.clear(); C.clear();
    });

    DM4thTest::TEST("BaseArray Resize", []{
        DM4th::Internal::BaseArray<double> A, B;
        A.resize(5);
        B.resize(5);
        B(0) = 0;
        B(1) = 0;
        B(2) = 0;
        B(3) = 0;
        B(4) = 0;
        EXPECT_EQ(A,B);
        A(2) = -15;
        B(2) = -15;
        A.resize(3);
        A.resize(5);
        EXPECT_EQ(A,B);

        A.resize(10);
        B.resize(10);
        B(5) = 0;
        B(6) = 0;
        B(7) = 0;
        B(8) = 0;
        B(9) = 0;

        EXPECT_EQ(A,B);

        DM4th::Internal::BaseArray<string> C, D;
        D.resize(3);
        D(0) = "Hola";
        D(1) = "Mis";
        D(2) = "Amigos";
        D.copyDataTo(C);
        EXPECT_EQ(C,D);
        
        C.resize(5);
        D.resize(5);
        D(3) = "";
        D(4) = "";
        EXPECT_EQ(C,D);
    });

    return DM4thTest::TEST::ERROR_LEVEL();
}