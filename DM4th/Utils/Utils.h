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

#if defined(_OPENMP)
    #include <omp.h>
    #define DM4thOmpNumber
#endif

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

enum EDM4thParallelSettings
{
    DEFAULT = 0,

    // Parallel Type
    ORDERED          = 1 << 0,
    OMP_PARALLEL    = 1 << 1,
    OMP_WORK_SHARED = 1 << 2,
    PARALLEL_TYPE   = 2*OMP_WORK_SHARED - ORDERED,

    // Reduce operation
    ADD             = 1 << 3,
    SUB             = 1 << 4,
    MUL             = 1 << 5,
    DIV             = 1 << 6,
    REDUCE_OP       = 2*DIV - ADD,
};

typedef unsigned int DM4thParallelSettings;

constexpr int BEGIN = 0;
constexpr int END = std::numeric_limits<int>::max();
constexpr int ALL = std::numeric_limits<int>::max();

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


    template<class T>
    inline T reduceOp(const DM4thParallelSettings &settings,const T& op1,const T& op2)
    {   
        T result = 0;
        switch (settings & EDM4thParallelSettings::REDUCE_OP)
        {
        case ADD:
            result = op1 + op2;
            break;
        case SUB:
            result = op1 - op2;
            break;
        case MUL:
            result = op1 * op2;
            break;
        case DIV:
            result = op1 / op2;
            break;
        default:
            DM4thAssert(false);
            break;
        }

        return result;
    }

    /*
        Loop in parallel over range
    */
    template<class T>
    inline void parallelLoopItems(
        const DM4thParallelSettings &settings, 
        const T &from, const T &to, const T &step, 
        const std::function<void(T& item)> &f, 
        const bool &forceParallel=false)
    {
        switch (settings & EDM4thParallelSettings::PARALLEL_TYPE)
        {
        #if defined(_OPENMP)

            case OMP_WORK_SHARED:

                #pragma omp for
                for(T j=from; j<to; j+=step)
                {
                    f(j);
                }
                break;

            case DEFAULT:
            case OMP_PARALLEL:
                #pragma omp parallel for IFDM4thOmp((to-from)/step>=DM4thConfig::minParallelLoops || forceParallel)
                for(T j=from; j<to; j+=step)
                {
                    f(j);
                }
                break;

        #endif
            case ORDERED:
            default:

                for(T j=from; j<to; j+=step)
                {
                    f(j);
                }
                break;

        }

    }

    /*
        Loop in parallel over array elements
        The loop breaks if return value of const std::function<number(number)> &callback is false

        If you're using OMP_WORK_SHARED, the 'out' parameter must be shared to get the same result as the other configurations.
        A private 'out' parameter will only calculate an independ result for each thread.

    */
    template<class T>
    inline void parallelLoopItemsCond(
        const DM4thParallelSettings &settings,  
        const T &from, const T &to, const T &step, 
        const std::function<bool(T& item)> &f, 
        bool &out,
        const bool &forceParallel=false)
    {
        out = true;

        switch (settings & EDM4thParallelSettings::PARALLEL_TYPE)
        {

        #if defined(_OPENMP)

            case OMP_WORK_SHARED:
                {
                    #pragma omp barrier

                    T pStep = omp_get_num_threads()*step;
                    T j = omp_get_thread_num()*step+from;

                    while (j < to && out)
                    {
                        if(!f(j))
                        {
                            #pragma omp critical
                            {
                                out = false;
                            }
                        }
                        j += pStep;
                    }    

                    #pragma omp barrier
                    
                }
                break;

            case OMP_PARALLEL:
                {
                    IFDM4thOmp((to-from)/step>=DM4thConfig::minParallelLoops || forceParallel)
                    {
                        #pragma omp parallel shared(out)
                        {
                            T pStep = omp_get_num_threads()*step;
                            T j = omp_get_thread_num()*step+from;
                            while (j < to && out)
                            {
                                if(!f(j))
                                {
                                    #pragma omp critical
                                    {
                                        
                                        out = false;
                                    }
                                }
                                j += pStep;
                            }
                        }
                    }else{
                        for(T j=from; j<to; j+=step)
                        {
                            if(!f(j)) 
                            {
                                out = false;
                                break;
                            }
                        }
                    }
                }
                break;

        #endif
            case ORDERED:
            default:
                {
                    for(T j=from; j<to; j+=step)
                    {
                        if(!f(j)) 
                        {
                            out = false;
                            break;
                        }
                    }
                }

                break;

            }
    }

    /*
        Loop in parallel over array elements

        If you're using OMP_WORK_SHARED, the 'out' parameter must be shared to get the same result as the other configurations.
        A private 'out' parameter will only calculate an independ result for each thread.
    */
    template<class Type, class Iter>
    inline void parallelLoopReduce(
        const DM4thParallelSettings &settings,  
        const Iter &from, const Iter &to, const Iter &step, 
        const std::function<Type(Type acum, Iter item)> &f, 
        Type &out,
        const Type &initValue=0, 
        const bool &forceParallel=false)
    {
        out = initValue;
        switch (settings & EDM4thParallelSettings::PARALLEL_TYPE)
        {

        #if defined(_OPENMP)

            case OMP_WORK_SHARED:
            {
                #pragma omp barrier
                Iter pStep = omp_get_num_threads()*step;
                Iter j = omp_get_thread_num()*step+from;
    
                Type lResult = initValue;

                while (j < to)
                {
                    lResult = f(lResult, j);
                    j += pStep;
                }

                #pragma omp critical
                {
                    out = reduceOp<Type>(settings, out, lResult);
                }

                #pragma omp barrier

            }
            break;

            case OMP_PARALLEL:
            {
                IFDM4thOmp((to-from)/step>=DM4thConfig::minParallelLoops || forceParallel)
                {
                    #pragma omp parallel shared(out)
                    {
                        Iter pStep = omp_get_num_threads()*step;
                        Iter j = omp_get_thread_num()*step+from;
            
                        Type lResult = initValue;

                        while (j < to)
                        {
                            lResult = f(lResult, j);
                            j += pStep;
                        }

                        #pragma omp critical
                        {
                            out = reduceOp<Type>(settings, out, lResult);
                        }
                    }

                }else{
                    for(Iter j=from; j<to; j+=step)
                    {
                        out = f(out, j);
                    }

                }
            }
            break;

        #endif
            case ORDERED:
            default:
            {
                for(Iter j=from; j<to; j+=step)
                {
                    out = f(out, j);
                }
            }
            break;
        }
    } 

    /*
        Perform a single thread operation similar to #pragma omp single
    */
    inline void singleThreadOperation(
        const DM4thParallelSettings &settings,
        const std::function<void(void)> &f)
    {
        #pragma omp single
        {
            f();
        }
    }

    /*
        Execute an operation in a critical section similar to #pragma omp critical
    */
    inline void criticalSection(
        const DM4thParallelSettings &settings,
        const std::function<void(void)> &f)
    {
        #pragma omp critical
        {
            f();
        }
    }

    /*
        
    */
    inline void parallelSections(
        const DM4thParallelSettings &settings,
        const std::function<void(void)> &f1,
        const std::function<void(void)> &f2)
    {
        switch (settings & EDM4thParallelSettings::PARALLEL_TYPE)
        {
        
        #if defined(_OPENMP)
        #endif
            case OMP_WORK_SHARED:
                {
                    #pragma omp barrier
                    #pragma omp sections
                    {
                        #pragma omp section
                        f1();
                        #pragma omp section
                        f2();
                    }
                    #pragma omp barrier
                }
                break;

            case DEFAULT:
            case OMP_PARALLEL:
                {
                    
                    #pragma omp parallel sections
                    {
                        #pragma omp section
                        {
                            f1();
                        }
                        
                        #pragma omp section
                        {
                            f2();
                        }
                        
                    }               
                }
                break;

            case ORDERED:
            default:
                {
                    f1();
                    f2();
                }
                break;
        }
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