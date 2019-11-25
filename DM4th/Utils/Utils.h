#pragma once

#include "_Constants.h"
#include "../Exceptions/Exceptions.h"

#include <cstring>
#include <string>
#include <string.h>

#include <istream>
#include <iostream>
#include <limits>

#include <queue>

#include <sstream>
#include <fstream>

#include <memory>
#include <atomic>

#include <iterator>
#include<algorithm>

#include <type_traits>

#include <functional>

#include <omp.h>

// Check windows
#if _WIN32 || _WIN64
    #if _WIN64
        #define DM4th64
    #else
        #define DM4th32
    #endif
#elif __GNUC__
    #if __x86_64__ || __ppc64__
        #define DM4th64
    #else
        #define DM4th32
    #endif
#else
    #define DM4th32
#endif

//#define DM4thParallel
#ifdef DM4thParallel
    #define DM4thOmp
#endif

//#define DM4thOmp
#ifdef DM4thOmp
    #define IFDM4thOmp(a) if(a)
#else
    #define IFDM4thOmp(a) if(false)
#endif

//Declare number reductions, etc.
#define DM4thOmpNumber

#ifndef DM4thMinOmpLoops
    #define DM4thMinOmpLoops 100
#endif

namespace DM4th
{

namespace DM4thGlobal
{
    static int minOmpLoops = DM4thMinOmpLoops;
}

constexpr int BEGIN = 0;
constexpr int END = std::numeric_limits<int>::max();
constexpr int ALL = std::numeric_limits<int>::max();

#define _min(a,b) (a<b)? a: b
#define _max(a,b) (a>b)? a: b

namespace DM4thUtils
{

template<class T>
T mult(T last){
    return last;
}
template<class T, class ... U>
T mult(T first, U ... args){
    return first*mult(args...);
}


template<class T>
T sum(T last){
    return last;
}
template<class T, class ... U>
T sum(T first, U ... args){
    return first+sum(args...);
}

template<class T>
int count(T last){
    return 1;
}
template<class T, class ... U>
int count(T first, U ... args){
    return 1+count(args...);
}

}

namespace DM4thInternal 
{

inline void _handleIstreamSpacesAndNewLines(std::istream &stream)
{
    while(stream.peek()==' ' || stream.peek()=='\n')
    {
        if(stream.peek()==' ') stream>>std::ws;
        if(stream.peek()=='\n') stream.get();
        if(stream.peek()==' ') stream>>std::ws;
    }
}

inline void _handleStringInQuotes(std::istream &stream, std::string &value)
{
    char delimeter('"');
    _handleIstreamSpacesAndNewLines(stream);
    if(stream.peek()=='"') stream.get();
    else DM4thAssert(false);
    std::getline(stream, value, delimeter);
    _handleIstreamSpacesAndNewLines(stream);
}

}

}