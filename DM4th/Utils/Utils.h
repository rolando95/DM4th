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

#include "DM4thConfig.h"

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



namespace DM4th
{


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

    /*
        Loop in parallel over array elements
    */
    template<class T>
    inline void parallelLoopItems(const std::function<void(T& item, const int &idx)> &f, T* arr, const int size)
    {
        IFDM4thOmp(size>=DM4thConfig::minParallelLoops)
        {
            #pragma omp parallel for
            for(int j=0; j<size; ++j)
            {
                f(arr[j], j);
            }  

        }else{
            for(int j=0; j<size; ++j)
            {
                f(arr[j], j);
            }
        }
    }

    /*
        Loop in parallel over array elements
        break parallel loop when return value is false
    */
    template<class T>
    inline bool parallelLoopItemsCond(const std::function<bool(T& item, const int &idx)> &f, T* arr, const int size)
    {
        bool result = true;

        IFDM4thOmp(size>=DM4thConfig::minParallelLoops)
        {
            #pragma omp parallel shared(result)
            {
                int pStep = omp_get_num_threads();
                int j = omp_get_thread_num();
                while (j < size && result)
                {
                    if(!f(arr[j], j))
                    {
                        #pragma omp critical
                        {
                            
                            result = false;
                        }
                    }
                    j += pStep;
                }
            }

        }else{

            for(int j=0; j<size; ++j)
            {
                if(!f(arr[j], j)) 
                {
                    result = false;
                    break;
                }
            }

        }
        return result;
    }


    enum ReduceOp{
        SUM, SUB, MUL, DIV
    };

    template<class T, ReduceOp op>
    inline void reduceOp(T& op1, T& op2)
    {
        switch (op)
        {
        case SUM:
            op1 += op2;
            break;
        case SUB:
            op1 -= op2;
            break;
        case MUL:
            op1 *= op2;
            break;
        case DIV:
            op1 *= op2;
            break;
        default:
            DM4thAssert(false);
            break;
        }
    }

    /*
        Loop in parallel over array elements.
        The function must be return the reduce operation to calculate a local value for each thread.
        The reduceFunction must be return the reduce operation of local values.
    */
    template<class T, ReduceOp op>
    inline T parallelLoopReduce(const std::function<T(T acum, T item, int idx)> &f, T *arr, const int size, T initValue=0)
    {
        T result = initValue;

        IFDM4thOmp(size>=DM4thConfig::minParallelLoops)
        {

            #pragma omp parallel shared(result)
            {
                int pStep = omp_get_num_threads();
                int j = omp_get_thread_num();

                T lResult = initValue;
                
                // Map
                while (j < size)
                {
                    lResult = f(lResult, arr[j], j);
                    j += pStep;
                }

                // Reduce
                #pragma omp critical
                {
                    reduceOp<T, op>(result, lResult);
                }
            }

        }else{

            for(int j=0; j<size; ++j)
            {
                result = f(result, arr[j], j);
            }

        }
        return result;
    }


    template<class T, ReduceOp op>
    inline T parallelLoopReduceS(const std::function<T(T acum, T item)> &f, const T from, const T to, const T step=1, T initValue=0)
    {
        T result = initValue;

        IFDM4thOmp((to-from)/step>=DM4thConfig::minParallelLoops)
        {
            #pragma omp parallel shared(result)
            {
                T pStep = omp_get_num_threads()*step;
                T j = omp_get_thread_num()+from;
    
                T lResult = initValue;

                while (j < to)
                {
                    lResult = f(lResult, j);
                    j += pStep;
                }

                #pragma omp critical
                {
                    reduceOp<T, op>(result, lResult);
                }
            }

        }else{
            for(T j=from; j<to; j+=step)
            {
                result = f(result, j);
            }

        }
        return result;
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