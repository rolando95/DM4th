#if defined(_OPENMP)
    #include <omp.h>
    #define DM4thOmpNumber
#endif

#include "DM4thConfig.h"

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

#include <functional>
#include "../Exceptions/Exceptions.h"

#include "simd.h"

namespace DM4th
{

enum EDM4thParallelSettings
{
    DEFAULT = 0,

    // Parallel Type
    ORDERED         = 1 << 0,
    OMP_PARALLEL    = 1 << 1,
    OMP_WORK_SHARED = 1 << 2,
    PARALLEL_TYPE   = 2*OMP_WORK_SHARED - ORDERED,

    // Reduce operation
    ADD             = 1 << 3,
    SUB             = 1 << 4,
    MUL             = 1 << 5,
    DIV             = 1 << 6,
    MAX             = 1 << 7,
    MIN             = 1 << 8,
    REDUCE_OP       = 2*MIN - ADD,
};

typedef unsigned int DM4thParallelSettings;

namespace Parallel
{
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
        case MAX:
            result = op1 > op2? op1 : op2;
            break;
        case MIN:
            result = op1 < op2? op1 : op2;
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
    inline void loop(
        const DM4thParallelSettings &settings, 
        const T &from, const T &to, const T &step, 
        const std::function<void(T& item)> &f, 
        const bool &forceParallel=false)
    {
        switch (settings & EDM4thParallelSettings::PARALLEL_TYPE)
        {
        #if defined(_OPENMP)

            case OMP_WORK_SHARED:
                {
                    #pragma omp for
                    for(T j=from; j<to; j+=step)
                    {
                        f(j);
                    }
                }
                break;

            case DEFAULT:
            case OMP_PARALLEL:
                {
                    #pragma omp parallel for IFDM4thOmp((to-from)/step>=DM4thConfig::minParallelLoops || forceParallel)
                    for(T j=from; j<to; j+=step)
                    {
                        f(j);
                    }
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
        Loop in parallel over range
    */
    template<class T>
    inline void loop(
        const DM4thParallelSettings &settings, 
        const T &from, const T &to, const T &step, 
        const std::function<void(T& item, T &thread_id)> &f, 
        const bool &forceParallel=false)
    {
        switch (settings & EDM4thParallelSettings::PARALLEL_TYPE)
        {
        #if defined(_OPENMP)

            case OMP_WORK_SHARED:
                {
                    #pragma omp for
                    for(T j=from; j<to; j+=step)
                    {
                        f(j, omp_get_thread_num());
                    }
                }
                break;

            case DEFAULT:
            case OMP_PARALLEL:
                {
                    #pragma omp parallel for IFDM4thOmp((to-from)/step>=DM4thConfig::minParallelLoops || forceParallel)
                    for(T j=from; j<to; j+=step)
                    {
                        f(j, omp_get_thread_num());
                    }
                }
                break;

        #endif
            case ORDERED:
            default:
                for(T j=from; j<to; j+=step)
                {
                    f(j, 0);
                }
                break;

        }

    }

    /*
        Loop in parallel over array elements
        The loop breaks if return value of const std::function<bool(T)> &callback is false

        If you're using OMP_WORK_SHARED, the 'out' parameter must be shared to get the same result as the other configurations.
        A private 'out' parameter will only calculate an independ result for each thread.

    */
    template<class T>
    inline void loopCond(
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
    inline void loopReduce(
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
        #if defined(_OPENMP)
            #pragma omp single
            {
                f();
            }
        #else
            f();
        #endif
    }

    /*
        Perform a single thread operation only if DM4thParallelSettings is OMP_WORK_SHARED 

    */
    inline void singleThreadOperationIfWorkShared(
        const DM4thParallelSettings &settings,
        const std::function<void(void)> &f)
    {
        #if defined(_OPENMP)

        if( (settings & EDM4thParallelSettings::PARALLEL_TYPE) == OMP_WORK_SHARED)
        {
            #pragma omp single
            {
                f();
            }
        }else
        {
            f();
        }

        #else
            f();
        #endif
    }

    /*
        Execute an operation in a critical section similar to #pragma omp critical
    */
    inline void criticalSection(
        const DM4thParallelSettings &settings,
        const std::function<void(void)> &f)
    {
        #if defined(_OPENMP)

        #pragma omp critical
        {
            f();
        }

        #else
            f();
        #endif
    }

    /*
        
    */
    inline void sections(
        const DM4thParallelSettings &settings,
        const std::function<void(void)> &f1,
        const std::function<void(void)> &f2)
    {
        switch (settings & EDM4thParallelSettings::PARALLEL_TYPE)
        {
        
        #if defined(_OPENMP)
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
        #endif
            case ORDERED:
            default:
                {
                    f1();
                    f2();
                }
                break;
        }
    }

    /*
        Performs a Parallel non-square matrix dot operation
        Each matrix must be allocated in memory

        c = dot(a,b)
    */
    template<class T>
    inline void non_square_matrix_dot_operation(
        const DM4thParallelSettings &settings,
        const T *a, const int aRows, const int aCols, 
        const T *b, const int bRows, const int bCols, 
              T *c, const int cRows, const int cCols
    )
    {
        int maxI = aRows;
        int maxJ = bCols;
        int maxK = bRows;

        if( (settings & EDM4thParallelSettings::PARALLEL_TYPE) == ORDERED)
        {
            // Ordered version
            for(int i=0; i<maxI; ++i)
            {
                for(int j=0; j<maxJ; ++j)
                {
                    c[i*cCols+j] = 0;
                    for(int k=0; k<maxK; ++k)
                    {
                        c[i*cCols+j] += a[i*aCols+k] * b[k*bCols+j];
                    }
                }
            }


        }else if (SIMD::Vec<T>::size() > 1){

            // Parallel version
            int maxV = maxJ - maxJ%SIMD::Vec<T>::size();

            DM4th::Parallel::loop<int>(
                settings,
                0,maxI,1, // from, to, step
                
                [&](int i)
                {
                    // vectorizable loop
                    for (int j = 0; j < maxV; j += SIMD::Vec<T>::size()) {    
                        SIMD::Vec<T> m0; m0.set1(0);
                        for (int k = 0; k < maxK; k++) {
                            SIMD::Vec<T> m1; m1.set1(a[i*aCols+k]);
                            SIMD::Vec<T> m2 = b+k*bCols+j;
                            SIMD::Vec<T> m3 = m1*m2;
                            m0 = m0 + m3;
                        }
                        m0.storeu_To(c+i*cCols+j);
                    }

                    // non-vectorizable loop
                    for(int j = maxV; j<maxJ; ++j)
                    {
                        c[i*cCols+j] = 0;
                        for (int k = 0; k < maxK; k++) {
                            c[i*cCols+j] += a[i*aCols+k] * b[k*bCols+j];
                        }
                    }
                }
            );
        }else{

            DM4th::Parallel::loop<int>(
                settings,
                0,maxI,1, // from, to, step
                
                [&](int i)
                {
                    // non-vectorizable loop
                    for(int j = 0; j<maxJ; ++j)
                    {
                        c[i*cCols+j] = 0;
                        for (int k = 0; k < maxK; k++) {
                            c[i*cCols+j] += a[i*aCols+k] * b[k*bCols+j];
                        }
                    }
                }
            ); 
        }
    }
}
}