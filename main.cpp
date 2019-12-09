//#include "DM4th/DM4th.h"
#include "DM4th/Utils/Utils.h"
#include <iomanip>   
#include<iostream>
#include <chrono>

using namespace DM4th;
using namespace std;

enum C
{
    A = 1 << 0,
    B = 1 << 1,
    C = 1 << 2,
    D = 1 << 3
};

int main()
{
    const int size = 1000000;
    //NDArray<number> a;
    //a.resize(size);

    // unsync the I/O of C and C++.
    ios_base::sync_with_stdio(false);

    auto start = std::chrono::steady_clock::now();

    
    bool cond;
    int result;

    #pragma omp parallel
    {    
        DM4thUtils::parallelLoopReduce<int,int>(
            DM4thUtils::OMP_WORK_SHARED | DM4thUtils::ADD,
            1,101,1,
            [](int reduce, int item){return reduce+item;},
            result
        );

        #pragma omp critical
        {
            cout<<"THREAD: "<<omp_get_thread_num()<<" result:"<<result<<endl;
        }

        // bool cond = DM4thUtils::parallelLoopItemsCond2<int>(
        //     DM4thUtils::ParallelSettings::OMP_WORK_SHARED,
        //     DM4thUtils::ReduceOp::ADD,1,101,1,
        //     [](const int &item)->bool{return (item>100)?true:false;}
        // );
        DM4thUtils::parallelLoopItemsCond<int>(
            DM4thUtils::ParallelType::OMP_WORK_SHARED
            ,
            1,101,1,
            [](int x){return (x<101)?true:false;},
            cond
        );

        #pragma omp critical
        {
            cout<<"THREAD: "<<omp_get_thread_num()<<" result:"<<cond<<endl;
        }

        
    }


    auto end = std::chrono::steady_clock::now();

    std::cout<<"  [+] Successful";
    std::cout << std::setprecision(15) <<" (" << double(std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count())/(1000*1000) << " ms)" << std::endl<<std::endl;

    cin.get();
}