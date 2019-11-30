#include "../../DM4th/DM4th.h"
#include "../../DM4th/Test/DM4thTest.h"

int main()
{
    DM4thTest::TEST("DM4th Linear Algebra", []{
        NDArray<number> A;

        // Dijkstra
        A = items<number>(
            INF, 100, INF, 300, 1000,
            INF, INF, 500, INF, INF,
            INF, INF, INF, INF, 100,
            INF, INF, 200, INF, 600,
            INF, INF, INF, INF, INF
        ).reshape(5,5);

        EXPECT_EQ(dijkstra(A), items<number>(
            INF, 100, 500, 300, 600,
            INF, INF, 500, INF, 600,
            INF, INF, INF, INF, 100,
            INF, INF, 200, INF, 300,
            INF, INF, INF, INF, INF
        ).reshape(5,5));

        // Warshall
        A = items<number>(
            000, 100, 000, 300, 1000,
            000, 000, 500, 000, 000,
            000, 000, 000, 000, 100,
            000, 000, 200, 000, 600,
            000, 000, 000, 000, 000
        ).reshape(5,5);

        EXPECT_EQ(warshall(A), items<number>(
            0, 1, 1, 1, 1,
            0, 0, 1, 0, 1,
            0, 0, 0, 0, 1,
            0, 0, 1, 0, 1,
            0, 0, 0, 0, 0
        ).reshape(5,5));
    });

    return DM4thTest::TEST::ERROR_LEVEL();
}