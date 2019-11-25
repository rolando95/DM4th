#pragma once

#include <iomanip>   
#include<iostream>
#include <chrono>

class TEST
{
    static int failed;
    static int success;
    public:

    TEST(const char *name, std::function<void(void)> f, int wait=1000)
    {
        #ifdef DM4thParallel
            #pragma omp parallel 
            {
                #pragma omp single
                {
                    std::cout<<"Running test: "<<name<<" (Threads:"<<omp_get_num_threads()<<")"<<std::endl;
                }
            }
        #else
            std::cout<<"Running test: "<<name<<" (Threads:"<<1<<")"<<std::endl;
        #endif
        try{
            auto start = std::chrono::steady_clock::now();

            f();

            auto end = std::chrono::steady_clock::now();

            std::cout<<"  [+] Successful";
            std::cout << std::setprecision(25) <<" (" << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " ms)" << std::endl<<std::endl;
            success += 1;
        }
        catch(...)
        {
            failed += 1;
            std::cout<< "--TEST FAILED--" <<std::endl;
        }
    }

    static int ERROR_LEVEL(){ return (failed)? 1:0; };
};

int TEST::failed = 0;
int TEST::success = 0;

template<class T>
bool setAll(const T& a)
{
    return a;
}

template<class T>
bool setAll(const NDArray<T>& a)
{
    return a.all(true);
}

#define EXPECT_TRUE(a)  if(!(a))             { std::cout<<"  [ ] Expect true failed.  file:"<<__FILE__<<" line:"<<__LINE__<<" EXPECT_TRUE("<<#a<<")"<<std::endl<<std::endl; throw 1; }
#define EXPECT_FALSE(a) if(a)                { std::cout<<"  [ ] Expect false failed. file:"<<__FILE__<<" line:"<<__LINE__<<" EXPECT_FALSE("<<#a<<")"<<std::endl<<std::endl; throw 1; }
#define EXPECT_EQ(a,b) if(!setAll((a)==(b))) { std::cout<<"  [ ] Expect EQ failed.    file:"<<__FILE__<<" line:"<<__LINE__<<" EXPECT_EQ("<<#a<<","<<#b<<")\n"<<(a)<<"\nand\n"<<(b)<<std::endl<<std::endl;throw 1;}
#define EXPECT_NE(a,b) if( setAll((a)==(b))) { std::cout<<"  [ ] Expect NE failed.    file:"<<__FILE__<<" line:"<<__LINE__<<" EXPECT_NE("<<#a<<","<<#b<<")\n"<<(a)<<"\nand\n"<<(b)<<std::endl<<std::endl;throw 1;}
