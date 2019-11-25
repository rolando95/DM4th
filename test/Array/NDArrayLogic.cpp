#include "../../DM4th/DM4th.h"

int main()
{
    DM4thTest::TEST("NDArray Relational operators", []{
        NDArray<number> A = map<number>([](number x){return x%3;}, items<number>(0,1,2,3,4));
        NDArray<number> B = items<number>(0,1,2,0,1);
        
        EXPECT_TRUE( (A==B).all());

        NDArray<number> C = items<number>(1,2,0,1,2);
        EXPECT_FALSE( (A==C).any());
        C(3) = 0;
        EXPECT_TRUE ( (A==C).any());

        C = items<number>(0,2,0,1,1);

        EXPECT_EQ( C> A, items<bool>(false,true,false,true,false));
        EXPECT_EQ( C>=A, items<bool>(true,true,false,true,true));
        EXPECT_EQ( C< A, items<bool>(false,false,true,false,false));
        EXPECT_EQ( C<=A, items<bool>(true,false,true,false,true));
        EXPECT_EQ( C==A, items<bool>(true,false,false,false,true));
        EXPECT_EQ( C!=A, items<bool>(false,true, true, true, false));

        A = range<number>(5);
        EXPECT_EQ( (A> 3), items<bool>(false,false,false,false,true));
        EXPECT_EQ( (A>=4), items<bool>(false,false,false,false,true));
        EXPECT_EQ( (A< 2), items<bool>(true,true,false,false,false));
        EXPECT_EQ( (A<=2), items<bool>(true,true,true,false,false));
        
    });

    DM4thTest::TEST("NDArray Logical operators", []{
        NDArray<bool> A = items<bool>(true,false,true,false);
        NDArray<bool> B = items<bool>(true,true,false,false);

        EXPECT_EQ( !A  , items<bool>(false, true, false, true));
        EXPECT_EQ( A&&B, items<bool>(true, false, false, false));
        EXPECT_EQ( A||B, items<bool>(true, true, true, false));
        
        NDArray<number> C = range<number>(10);
        NDArray<number> D = range<number>(10,0);

        NDArray<bool> result = C > 2 && D >= 4;

        EXPECT_EQ( result, items<bool>(false, false, false, true, true, true, true, false, false, false));

        result = !(C > 2 || D > 2) || D == 8;

        EXPECT_EQ( result, items<bool>(false, false, true, false, false, false, false, false, false, false));
    });

    return DM4thTest::TEST::ERROR_LEVEL();
}