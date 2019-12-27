#include <immintrin.h>
#include "../Number/Number_impl.h"
namespace DM4th
{
namespace SIMD
{

#if defined __AVX2__
    // AVX2 ADD ARRAY
    template<class T>
    inline void addArray(T *r, T *lhs, const T *rhs)
    {
        r[0] = lhs[0] + rhs[0];
    }

    template<>
    inline void addArray<double>(double *r, double *lhs, const double *rhs)
    {
        __m256d mlhs = _mm256_loadu_pd(lhs);
        __m256d mrhs = _mm256_loadu_pd(rhs);
        _mm256_storeu_pd(r, _mm256_add_pd(mlhs, mrhs)); 
    }

    template<>
    inline void addArray<float>(float *r, float *lhs, const float *rhs)
    {
        __m256 mlhs = _mm256_loadu_ps(lhs);
        __m256 mrhs = _mm256_loadu_ps(rhs);
        _mm256_storeu_ps(r, _mm256_add_ps(mlhs, mrhs));   
    }

    // ADD SCALAR
    template<class T>
    inline void addScalar(T *r, T *lhs, const T &rhs)
    {
        r[0] = lhs[0] + rhs;
    }

    template<>
    inline void addScalar<double>(double *r, double *lhs, const double &rhs)
    {
        __m256d mlhs = _mm256_loadu_pd(lhs);
        __m256d mrhs = _mm256_set1_pd(rhs);
        _mm256_storeu_pd(r, _mm256_add_pd(mlhs, mrhs)); 
    }

    template<>
    inline void addScalar<float>(float *r, float *lhs, const float &rhs)
    {
        __m256 mlhs = _mm256_loadu_ps(lhs);
        __m256 mrhs = _mm256_set1_ps(rhs);
        _mm256_storeu_ps(r, _mm256_add_ps(mlhs, mrhs)); 
    }

    // SUB ARRAY
    template<class T>
    inline void subArray(T *r, T *lhs, const T *rhs)
    {
        r[0] = lhs[0] - rhs[0];
    }

    template<>
    inline void subArray<double>(double *r, double *lhs, const double *rhs)
    {
        __m256d mlhs = _mm256_loadu_pd(lhs);
        __m256d mrhs = _mm256_loadu_pd(rhs);
        _mm256_storeu_pd(r, _mm256_sub_pd(mlhs, mrhs)); 
    }

    template<>
    inline void subArray<float>(float *r, float *lhs, const float *rhs)
    {
        __m256 mlhs = _mm256_loadu_ps(lhs);
        __m256 mrhs = _mm256_loadu_ps(rhs);
        _mm256_storeu_ps(r, _mm256_sub_ps(mlhs, mrhs));   
    }

    // SUB SCALAR
    template<class T>
    inline void subScalar(T *r, T *lhs, const T &rhs)
    {
        r[0] = lhs[0] - rhs;
    }

    template<>
    inline void subScalar<double>(double *r, double *lhs, const double &rhs)
    {
        __m256d mlhs = _mm256_loadu_pd(lhs);
        __m256d mrhs = _mm256_set1_pd(rhs);
        _mm256_storeu_pd(r, _mm256_sub_pd(mlhs, mrhs)); 
    }

    template<>
    inline void subScalar<float>(float *r, float *lhs, const float &rhs)
    {
        __m256 mlhs = _mm256_loadu_ps(lhs);
        __m256 mrhs = _mm256_set1_ps(rhs);
        _mm256_storeu_ps(r, _mm256_sub_ps(mlhs, mrhs)); 
    }

    // MUL SCALAR
    template<class T>
    inline void mulScalar(T *r, T *lhs, const T &rhs)
    {
        r[0] = lhs[0] * rhs;
    }

    template<>
    inline void mulScalar<double>(double *r, double *lhs, const double &rhs)
    {
        __m256d mlhs = _mm256_loadu_pd(lhs);
        __m256d mrhs = _mm256_set1_pd(rhs);
        _mm256_storeu_pd(r, _mm256_mul_pd(mlhs, mrhs)); 
    }

    template<>
    inline void mulScalar<float>(float *r, float *lhs, const float &rhs)
    {
        __m256 mlhs = _mm256_loadu_ps(lhs);
        __m256 mrhs = _mm256_set1_ps(rhs);
        _mm256_storeu_ps(r, _mm256_mul_ps(mlhs, mrhs)); 
    }

    // DIV SCALAR
    template<class T>
    inline void divScalar(T *r, T *lhs, const T &rhs)
    {
        r[0] = lhs[0] / rhs;
    }

    template<>
    inline void divScalar<double>(double *r, double *lhs, const double &rhs)
    {
        __m256d mlhs = _mm256_loadu_pd(lhs);
        __m256d mrhs = _mm256_set1_pd(rhs);
        _mm256_storeu_pd(r, _mm256_div_pd(mlhs, mrhs)); 
    }

    template<>
    inline void divScalar<float>(float *r, float *lhs, const float &rhs)
    {
        __m256 mlhs = _mm256_loadu_ps(lhs);
        __m256 mrhs = _mm256_set1_ps(rhs);
        _mm256_storeu_ps(r, _mm256_div_ps(mlhs, mrhs)); 
    }

    // SIMD SIZE
    template<class T> inline int vectorizeSize        (){ return 1; }
    template<>        inline int vectorizeSize<double>(){ return 4; }
    template<>        inline int vectorizeSize<float> (){ return 8; }

#else

    // ADD ARRAY
    template<class T>
    inline void addArray(T *r, T *lhs, const T *rhs)
    {
        r[0] = lhs[0] + rhs[0];
    }

    template<>
    inline void addArray<double>(double *r, double *lhs, const double *rhs)
    {
        __m128d mlhs1 = _mm_loadu_pd(lhs);
        __m128d mlhs2 = _mm_loadu_pd(rhs);
        _mm_storeu_pd(r, _mm_add_pd(mlhs1, mlhs2)); 
    }

    template<>
    inline void addArray<float>(float *r, float *lhs, const float *rhs)
    {
        __m128 mlhs1 = _mm_loadu_ps(lhs);
        __m128 mlhs2 = _mm_loadu_ps(rhs);
        _mm_storeu_ps(r, _mm_add_ps(mlhs1, mlhs2));   
    }

    // ADD SCALAR
    template<class T>
    inline void addScalar(T *r, T *lhs, const T &rhs)
    {
        r[0] = lhs[0] + rhs;
    }

    template<>
    inline void addScalar<double>(double *r, double *lhs, const double &rhs)
    {
        __m128d mlhs = _mm_loadu_pd(lhs);
        __m128d mrhs = _mm_set1_pd(rhs);
        _mm_storeu_pd(r, _mm_add_pd(mlhs, mrhs)); 
    }

    template<>
    inline void addScalar<float>(float *r, float *lhs, const float &rhs)
    {
        __m128 mlhs = _mm_loadu_ps(lhs);
        __m128 mrhs = _mm_set1_ps(rhs);
        _mm_storeu_ps(r, _mm_add_ps(mlhs, mrhs)); 
    }

    // SUB ARRAY
    template<class T>
    inline void subArray(T *r, T *lhs, const T *rhs)
    {
        r[0] = lhs[0] - rhs[0];
    }

    template<>
    inline void subArray<double>(double *r, double *lhs, const double *rhs)
    {
        __m128d mlhs1 = _mm_loadu_pd(lhs);
        __m128d mlhs2 = _mm_loadu_pd(rhs);
        _mm_storeu_pd(r, _mm_sub_pd(mlhs1, mlhs2)); 
    }

    template<>
    inline void subArray<float>(float *r, float *lhs, const float *rhs)
    {
        __m128 mlhs1 = _mm_loadu_ps(lhs);
        __m128 mlhs2 = _mm_loadu_ps(rhs);
        _mm_storeu_ps(r, _mm_sub_ps(mlhs1, mlhs2));   
    }

    // SUB SCALAR
    template<class T>
    inline void subScalar(T *r, T *lhs, const T &rhs)
    {
        r[0] = lhs[0] - rhs;
    }

    template<>
    inline void subScalar<double>(double *r, double *lhs, const double &rhs)
    {
        __m128d mlhs = _mm_loadu_pd(lhs);
        __m128d mrhs = _mm_set1_pd(rhs);
        _mm_storeu_pd(r, _mm_sub_pd(mlhs, mrhs)); 
    }

    template<>
    inline void subScalar<float>(float *r, float *lhs, const float &rhs)
    {
        __m128 mlhs = _mm_loadu_ps(lhs);
        __m128 mrhs = _mm_set1_ps(rhs);
        _mm_storeu_ps(r, _mm_sub_ps(mlhs, mrhs)); 
    }

    // MUL SCALAR
    template<class T>
    inline void mulScalar(T *r, T *lhs, const T &rhs)
    {
        r[0] = lhs[0] * rhs;
    }

    template<>
    inline void mulScalar<double>(double *r, double *lhs, const double &rhs)
    {
        __m128d mlhs = _mm_loadu_pd(lhs);
        __m128d mrhs = _mm_set1_pd(rhs);
        _mm_storeu_pd(r, _mm_mul_pd(mlhs, mrhs)); 
    }

    template<>
    inline void mulScalar<float>(float *r, float *lhs, const float &rhs)
    {
        __m128 mlhs = _mm_loadu_ps(lhs);
        __m128 mrhs = _mm_set1_ps(rhs);
        _mm_storeu_ps(r, _mm_mul_ps(mlhs, mrhs)); 
    }

    // DIV SCALAR
    template<class T>
    inline void divScalar(T *r, T *lhs, const T &rhs)
    {
        r[0] = lhs[0] / rhs;
    }

    template<>
    inline void divScalar<double>(double *r, double *lhs, const double &rhs)
    {
        __m128d mlhs = _mm_loadu_pd(lhs);
        __m128d mrhs = _mm_set1_pd(rhs);
        _mm_storeu_pd(r, _mm_div_pd(mlhs, mrhs)); 
    }

    template<>
    inline void divScalar<float>(float *r, float *lhs, const float &rhs)
    {
        __m128 mlhs = _mm_loadu_ps(lhs);
        __m128 mrhs = _mm_set1_ps(rhs);
        _mm_storeu_ps(r, _mm_div_ps(mlhs, mrhs)); 
    }

    // SIMD SIZE
    template<class T> inline int vectorizeSize         (){ return 1; }
    template<>        inline int vectorizeSize<double> (){ return 2; }
    template<>        inline int vectorizeSize<float>  (){ return 4; }
#endif


}

}