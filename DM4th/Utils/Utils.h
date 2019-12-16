#pragma once

#include "multithreading.h"
#include "simd.h"
#include "_c_arr_Utils.h"
#include "_Constants.h"
#include "_miscellaneos.h"

#include <cstring>
#include <string>
#include <string.h>
#include <tuple>

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



#if defined(_OPENMP)
    #include <omp.h>
    #define DM4thOmpNumber
#endif

//#include "DM4thConfig.h"

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

//#define DM4thAutoParallel
#ifdef DM4thAutoParallel
    #define DM4thOmp
#endif

//#define DM4thOmp
#ifdef DM4thOmp
    #define IFDM4thOmp(a) if(a)
#else
    #define IFDM4thOmp(a) if(false)
#endif

//Declare number reductions, etc.




namespace DM4th
{



constexpr int BEGIN = 0;
constexpr int END = std::numeric_limits<int>::max();
constexpr int ALL = std::numeric_limits<int>::max() - 1;

// #define _min(a,b) (a<b)? a: b
// #define _max(a,b) (a>b)? a: b

namespace DM4thUtils
{
    namespace DM4thInternal {

        template<class T, class ... U>
        inline void _initArray(T* arr, const int &idx, const T &last)
        {
            arr[idx] = last;
        }

        template<class T, class ... U>
        inline void _initArray(T* arr, const int &idx, const T &first, U ... args)
        {
            arr[idx] = first;
            _initArray(arr, idx+1, args ...);
        }
    }
    
    template<class T>
    inline T min(const T &a,const T &b){ return (a<b)? a: b; }

    template<class T>
    inline T max(const T &a,const T &b){ return (a>b)? a: b; }

    template<class T>
    inline T mul(const T &last){
        return last;
    }
    template<class T, class ... U>
    inline T mul(const T &first, U ... args){
        return first*mul(args...);
    }


    template<class T>
    inline T add(const T &last){
        return last;
    }
    template<class T, class ... U>
    inline T add(const T &first, U ... args){
        return first+add(args...);
    }

    template<class T>
    inline int count(const T &last){
        return 1;
    }
    template<class T, class ... U>
    inline int count(const T &first, U ... args){
        return 1+count(args...);
    }

    template<class T, class ... U>
    inline void initArray(T* arr, const T &last)
    {
        arr[0] = last;
    }

    template<class T, class ... U>
    inline void initArray(T* arr, const T &first, U ... args)
    {
        arr[0] = first;
        DM4thInternal::_initArray(arr, 1, args ...);
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