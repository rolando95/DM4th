#include <immintrin.h>

namespace DM4th
{
namespace DM4thSIMD
{

// ADD ARRAY
template<class T>
inline void iAddArray(T *arr1, const T *arr2)
{
    arr1[0] += arr2[0];
}

template<>
inline void iAddArray<float>(float *arr1, const float *arr2)
{
    __m128 mArr1 = _mm_loadu_ps(arr1);
    __m128 mArr2 = _mm_loadu_ps(arr2);
    _mm_storeu_ps(arr1, _mm_add_ps(mArr1, mArr2));   
}

template<>
inline void iAddArray<double>(double *arr1, const double *arr2)
{
    __m128d mArr1 = _mm_loadu_pd(arr1);
    __m128d mArr2 = _mm_loadu_pd(arr2);
    _mm_storeu_pd(arr1, _mm_add_pd(mArr1, mArr2)); 
}

// ADD SCALAR
template<class T>
inline void iAddScalar(T *arr, const T &scalar)
{
    arr[0] += scalar;
}

template<>
inline void iAddScalar<double>(double *arr, const double &scalar)
{
    __m128d mArr = _mm_loadu_pd(arr);
    __m128d mNum = _mm_set1_pd(scalar);
    _mm_storeu_pd(arr, _mm_add_pd(mArr, mNum)); 
}

template<>
inline void iAddScalar<float>(float *arr, const float &scalar)
{
    __m128 mArr = _mm_loadu_ps(arr);
    __m128 mNum = _mm_set1_ps(scalar);
    _mm_storeu_ps(arr, _mm_add_ps(mArr, mNum)); 
}

// SUB ARRAY
template<class T>
inline void iSubArray(T *arr1, const T *arr2)
{
    arr1[0] -= arr2[0];
}

template<>
inline void iSubArray<float>(float *arr1, const float *arr2)
{
    __m128 mArr1 = _mm_loadu_ps(arr1);
    __m128 mArr2 = _mm_loadu_ps(arr2);
    _mm_storeu_ps(arr1, _mm_sub_ps(mArr1, mArr2));   
}

template<>
inline void iSubArray<double>(double *arr1, const double *arr2)
{
    __m128d mArr1 = _mm_loadu_pd(arr1);
    __m128d mArr2 = _mm_loadu_pd(arr2);
    _mm_storeu_pd(arr1, _mm_sub_pd(mArr1, mArr2)); 
}

// SUB SCALAR
template<class T>
inline void iSubScalar(T *arr, const T &scalar)
{
    arr[0] -= scalar;
}

template<>
inline void iSubScalar<double>(double *arr, const double &scalar)
{
    __m128d mArr = _mm_loadu_pd(arr);
    __m128d mNum = _mm_set1_pd(scalar);
    _mm_storeu_pd(arr, _mm_sub_pd(mArr, mNum)); 
}

template<>
inline void iSubScalar<float>(float *arr, const float &scalar)
{
    __m128 mArr = _mm_loadu_ps(arr);
    __m128 mNum = _mm_set1_ps(scalar);
    _mm_storeu_ps(arr, _mm_sub_ps(mArr, mNum)); 
}

// MUL SCALAR
template<class T>
inline void iMulScalar(T *arr, const T &scalar)
{
    arr[0] *= scalar;
}

template<>
inline void iMulScalar<double>(double *arr, const double &scalar)
{
    __m128d mArr = _mm_loadu_pd(arr);
    __m128d mNum = _mm_set1_pd(scalar);
    _mm_storeu_pd(arr, _mm_mul_pd(mArr, mNum)); 
}

template<>
inline void iMulScalar<float>(float *arr, const float &scalar)
{
    __m128 mArr = _mm_loadu_ps(arr);
    __m128 mNum = _mm_set1_ps(scalar);
    _mm_storeu_ps(arr, _mm_mul_ps(mArr, mNum)); 
}

// DIV SCALAR
template<class T>
inline void iDivScalar(T *arr, const T &scalar)
{
    arr[0] /= scalar;
}

template<>
inline void iDivScalar<double>(double *arr, const double &scalar)
{
    __m128d mArr = _mm_loadu_pd(arr);
    __m128d mNum = _mm_set1_pd(scalar);
    _mm_storeu_pd(arr, _mm_div_pd(mArr, mNum)); 
}

template<>
inline void iDivScalar<float>(float *arr, const float &scalar)
{
    __m128 mArr = _mm_loadu_ps(arr);
    __m128 mNum = _mm_set1_ps(scalar);
    _mm_storeu_ps(arr, _mm_div_ps(mArr, mNum)); 
}

// SIMD SIZE
template<class T> int simdArrSize        (){ return 1; }
template<>        int simdArrSize<double>(){ return 2; }
template<>        int simdArrSize<float> (){ return 4; }

}

}