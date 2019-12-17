#include "../../DM4th/DM4th.h"
#include "../../DM4th/Test/DM4thTest.h"

using namespace std;
using namespace DM4th;

int main()
{
    DM4thTest::TEST("DM4th Differential", []{

        // diff
        NDArray<number> A = items<number>(1,3,4,6,7,9,10);
        A = diff(A);
        EXPECT_EQ(A, items<number>(2,1,2,1,2,1));

        EXPECT_EQ( 
            round(
                integral(
                    [](number x){ 
                        return x*x*x - 6*x*x + 11*x - 6; 
                    }, 
                    1.3, 1.8, 6
                )
            *100)/100, 
            0.17
        );
    });

    return DM4thTest::TEST::ERROR_LEVEL();
}