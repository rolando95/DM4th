#include "../../DM4th/DM4th.h"
#include "../DM4thTest.h"

int main()
{
    TEST("NDArray Relational operators", []{
        NDArray<number> A = map<number>([](number x){return x%3;}, items<number>(0,1,2,3,4));
        NDArray<number> B = items<number>(0,1,2,0,1);

        EXPECT_TRUE( (A==B).all());

        NDArray<number> C = items<number>(1,2,0,1,2);
        EXPECT_FALSE( (A==C).any());
        C(3) = 0;
        EXPECT_TRUE ( (A==C).any());

        C = items<number>(0,2,0,1,1);

        EXPECT_TRUE( (C>A).isEqualTo(items<bool>(false,true,false,true,false)));
        EXPECT_TRUE( (C>=A).isEqualTo(items<bool>(true,true,false,true,true)));
        EXPECT_TRUE( (C<A).isEqualTo(items<bool>(false,false,true,false,false)));
        EXPECT_TRUE( (C<=A).isEqualTo(items<bool>(true,false,true,false,true)));
        EXPECT_TRUE( (C==A).isEqualTo(items<bool>(true,false,false,false,true)));
        EXPECT_TRUE( (C!=A).isEqualTo(items<bool>(false,true, true, true, false)));

        A = range<number>(5);
        EXPECT_TRUE( (A>3).isEqualTo(items<bool>(false,false,false,false,true)));
        EXPECT_TRUE( (A>=4).isEqualTo(items<bool>(false,false,false,false,true)));
        EXPECT_TRUE( (A<2).isEqualTo(items<bool>(true,true,false,false,false)));
        EXPECT_TRUE( (A<=2).isEqualTo(items<bool>(true,true,true,false,false)));
        
    });

    TEST("NDArray Logical operators", []{
        NDArray<bool> A = items<bool>(true,false,true,false);
        NDArray<bool> B = items<bool>(true,true,false,false);

        EXPECT_TRUE( (!A).isEqualTo(items<bool>(false, true, false, true)));
        EXPECT_TRUE( (A&&B).isEqualTo(items<bool>(true, false, false, false)));
        EXPECT_TRUE( (A||B).isEqualTo(items<bool>(true, true, true, false)));
        
        NDArray<number> C = range<number>(10);
        NDArray<number> D = range<number>(10,0);

        NDArray<bool> result = C > 2 && D >= 4;

        EXPECT_TRUE( result.isEqualTo(items<bool>(false, false, false, true, true, true, true, false, false, false)));

        result = !(C > 2 || D > 2) || D == 8;

        EXPECT_TRUE( result.isEqualTo(items<bool>(false, false, true, false, false, false, false, false, false, false)));
    });

    return TEST::ERROR_LEVEL();
}