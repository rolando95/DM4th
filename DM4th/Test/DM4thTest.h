#pragma once

#include <iomanip>   
#include<iostream>
#include <chrono>
#include <omp.h>
#include "../Array.h"

namespace DM4th 
{

namespace DM4thTest
{

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-variable"

    static int failed = 0;
    static int success = 0;

#pragma GCC diagnostic pop

class TEST
{

    public:

    inline TEST(const char *name, const std::function<void(void)> &f, const int &how_many_times=1)
    {
        IFDM4thOmp(true)
        {
            #pragma omp parallel 
            {
                #pragma omp single
                {
                    std::cout<<"Running test: "<<name<<" (Threads:"<<omp_get_num_threads()<<", Times:"<<how_many_times<<")"<<std::endl;
                }
            }
        }else{
            std::cout<<"Running test: "<<name<<" (Threads:"<<1<<", Times:"<<how_many_times<<")"<<std::endl;
        }
        
        try{
            auto start = std::chrono::steady_clock::now();

            for(int j=0; j<how_many_times; ++j)
            {
                f();
            }

            auto end = std::chrono::steady_clock::now();

            std::cout<<"  [+] Successful";
            std::cout << std::setprecision(15) <<" (" << double(std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count())/(1000*1000) << " ms)" << std::endl<<std::endl;
            DM4thTest::success += 1;
        }
        catch(...)
        {
            DM4thTest::failed += 1;
            std::cout<< "--TEST FAILED--" <<std::endl;
        }
    }

    static int ERROR_LEVEL(){ return (failed)? 1:0; };
};

template<class T>
bool setAll(const T& a)
{
    return a;
}

template<class T>
bool setAll(const DM4th::NDArray<T>& a)
{
    return a.all(true);
}

}

#define EXPECT_TRUE(a)  if(!(a))             { std::cout<<"  [ ] Expect true failed.  file:"<<__FILE__<<" line:"<<__LINE__<<" EXPECT_TRUE("<<#a<<")"<<std::endl<<std::endl; throw 1; }
#define EXPECT_FALSE(a) if(a)                { std::cout<<"  [ ] Expect false failed. file:"<<__FILE__<<" line:"<<__LINE__<<" EXPECT_FALSE("<<#a<<")"<<std::endl<<std::endl; throw 1; }
#define EXPECT_EQ(a,b) if(!DM4thTest::setAll((a)==(b))) { std::cout<<"  [ ] Expect EQ failed.    file:"<<__FILE__<<" line:"<<__LINE__<<" EXPECT_EQ("<<#a<<","<<#b<<")\n"<<(a)<<"\nand\n"<<(b)<<std::endl<<std::endl;throw 1;}
#define EXPECT_NE(a,b) if( DM4thTest::setAll((a)==(b))) { std::cout<<"  [ ] Expect NE failed.    file:"<<__FILE__<<" line:"<<__LINE__<<" EXPECT_NE("<<#a<<","<<#b<<")\n"<<(a)<<"\nand\n"<<(b)<<std::endl<<std::endl;throw 1;}

}