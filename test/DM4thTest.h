#include<functional>
#include <iomanip>   
#include<iostream>
#include <ctime>

#ifdef _WIN32
    #define TO_SECONDS 1000
#else
    #define TO_SECONDS 1000*1000
#endif

class TEST
{
    static int failed;
    static int success;
    public:

    TEST(const char *name, std::function<void(void)> f)
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
            //clock_t begin = clock();
            f();
            //clock_t end = clock();
            //double elapsed_secs = double(end - begin) / TO_SECONDS;
            std::cout<<std::setprecision(15)<<"  [+] Successful";
            std::cout<<std::endl;
            //std::cout<< "("<<elapsed_secs<<"s)"<<std::endl;
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

#define EXPECT_TRUE(a)  if(!(a))             { std::cout<<"  [ ] Expect true failed.  file:"<<__FILE__<<" line:"<<__LINE__<<" EXPECT_TRUE("<<#a<<")"<<std::endl; throw 1; }
#define EXPECT_FALSE(a) if(a)                { std::cout<<"  [ ] Expect false failed. file:"<<__FILE__<<" line:"<<__LINE__<<" EXPECT_FALSE("<<#a<<")"<<std::endl; throw 1; }
#define EXPECT_EQ(a,b) if(!setAll((a)==(b))) { std::cout<<"  [ ] Expect EQ failed.    file:"<<__FILE__<<" line:"<<__LINE__<<" EXPECT_EQ("<<#a<<","<<#b<<")\n"<<(a)<<"\nand\n"<<(b)<<std::endl;throw 1;}
#define EXPECT_NE(a,b) if( setAll((a)==(b))) { std::cout<<"  [ ] Expect NE failed.    file:"<<__FILE__<<" line:"<<__LINE__<<" EXPECT_NE("<<#a<<","<<#b<<")\n"<<(a)<<"\nand\n"<<(b)<<std::endl;throw 1;}
