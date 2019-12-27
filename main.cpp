#include "DM4th/DM4th.h"
#include <omp.h>
using namespace std;
using namespace DM4th;

void func(bool value)
{
    #pragma omp single
    {
        std::cout<<omp_get_num_threads()<<std::endl;
    }
}
int main()
{
    #pragma omp parallel
    {
        #pragma omp critical
        {
            func(false);
        }
    }

    cin.get();
    return 0;
}