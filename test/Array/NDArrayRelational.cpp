#include "../../DM4th/DM4th.h"
#include "../DM4thTest.h"

int main()
{
    TEST("NDArray Relational", []{
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
        
    });

    return TEST::ERROR_LEVEL();
}