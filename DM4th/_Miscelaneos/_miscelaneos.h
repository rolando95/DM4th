#ifdef _WIN32
    #include <windows.h>

    void sleep(double seconds)
    {
        Sleep(seconds*1000);
    }
#else
    #include <unistd.h>

    void sleep(double seconds)
    {
        usleep(seconds * 1000 * 1000); // takes microseconds
    }
#endif

#include<ios>      
#include<limits>  

namespace DM4th
{

inline void print()
{
    std::cout<<"\n";
}

template<class T, class ... U>
void print(T first, U... args)
{
    std::cout<<first<<"\n";
    print(args ...);
}


inline void input()
{
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n'); 

}

template<class T>
inline void input(T last)
{
    std::cin>>last;
}

template<class T, class ... U>
void input(T first, U... args)
{
    std::cin>>first;
    input(args ...);
}

}