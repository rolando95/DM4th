#pragma once
#include<iostream>

#include<ios>      
#include<limits>  

namespace DM4th
{

inline void print()
{
    std::cout<<"\n";
}

template<class T, class ... U>
void print(const T &first, U... args)
{
    std::cout<<first<<" ";
    print(args ...);
}
// template<class ... U>
// inline void print( U... args)
// {
//     std::cout<<(args<<...)<<"\n";
// }

inline void input()
{
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n'); 

}

template<class T>
inline void input(T &last)
{
    std::cin>>last;
}

template<class T, class ... U>
void input(T &first, U... args)
{
    std::cin>>first;
    input(args ...);
}

}