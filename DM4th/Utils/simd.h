#include <immintrin.h>
#include "../Number/Number_impl.h"
namespace DM4th
{
namespace SIMD
{


template<class T>
class Vec
{
    union {
        T data;
        T arr[1];
    };

    static const int _size = 1;

    public:

    inline Vec() {};
    inline Vec(T o) { this->data = o;};
    inline Vec(const T *other)       { this->data = *other; }
    
    static int size() { return _size; }
    inline void operator=(Vec other)        { data = other.data; }
    inline void operator=(const T *other)       { this->data = *other; }
    inline void set1(const T other)        { this->data = other; }

    inline Vec<T> operator+(Vec<T> other) { return this->data + other.data; } 
    inline Vec<T> operator-(Vec<T> other) { return this->data - other.data; } 
    inline Vec<T> operator*(Vec<T> other) { return this->data * other.data; } 
    inline Vec<T> operator/(Vec<T> other) { return this->data / other.data; } 

    inline void storeu_To(T *other) { *other = data; }
};

template<>
class Vec<float>
{
    union {
        __m128 data;
        float arr[4];
    };

    static const int _size = 4;

    public:

    inline Vec() {};
    inline Vec(__m128 o) { this->data = o;};
    inline Vec(const float *other)       { this->data = _mm_loadu_ps(other); }  

    static int size() { return _size; }

    inline void operator=(Vec other)            { data = other.data; }
    inline void operator=(const float *other)       { this->data = _mm_loadu_ps(other); }   
    inline void set1(const float other)        { this->data = _mm_load1_ps(&other); }

    inline Vec<float> operator+(Vec<float> other) { return _mm_add_ps(this->data ,other.data); }
    inline Vec<float> operator-(Vec<float> other) { return _mm_sub_ps(this->data ,other.data); }
    inline Vec<float> operator*(Vec<float> other) { return _mm_mul_ps(this->data ,other.data); } 
    inline Vec<float> operator/(Vec<float> other) { return _mm_div_ps(this->data ,other.data); } 

    inline void storeu_To(float *other) { _mm_storeu_ps(other, this->data); }
};

template<>
class Vec<double>
{
    union {
        __m128d data;
        double arr[2];
    };

    static const int _size = 2;

    public:

    inline Vec() {};
    inline Vec(__m128d o) { this->data = o;};
    inline Vec(const double *other)       { this->data = _mm_loadu_pd(other); }  

    static int size() { return _size; }
    inline void operator=(Vec other)            { data = other.data; }
    inline void operator=(const double *other)       { this->data = _mm_loadu_pd(other); }   
    inline void set1(const double other)        { this->data = _mm_load1_pd(&other); }

    inline Vec<double> operator+(Vec<double> other) { return _mm_add_pd(this->data ,other.data); }
    inline Vec<double> operator-(Vec<double> other) { return _mm_sub_pd(this->data ,other.data); }
    inline Vec<double> operator*(Vec<double> other) { return _mm_mul_pd(this->data ,other.data); } 
    inline Vec<double> operator/(Vec<double> other) { return _mm_div_pd(this->data ,other.data); } 

    inline void storeu_To(double *other) { _mm_storeu_pd(other, this->data); }
};

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
        Vec<T> mlhs = lhs;
        Vec<T> mrhs = rhs;
        (mlhs+mrhs).storeu_To(r); 
    }

    // ADD SCALAR
    template<class T>
    inline void addScalar(T *r, T *lhs, const T &rhs)
    {
        Vec<T> mlhs = lhs;
        Vec<T> mrhs; mrhs.set1(rhs);
        (mlhs+mrhs).storeu_To(r); 
    }

    // SUB ARRAY
    template<class T>
    inline void subArray(T *r, T *lhs, const T *rhs)
    {
        Vec<T> mlhs = lhs;
        Vec<T> mrhs = rhs;
        (mlhs-mrhs).storeu_To(r); 
    }

    // SUB SCALAR
    template<class T>
    inline void subScalar(T *r, T *lhs, const T &rhs)
    {
        Vec<T> mlhs = lhs;
        Vec<T> mrhs; mrhs.set1(rhs);
        (mlhs-mrhs).storeu_To(r); 
    }

    // MUL SCALAR
    template<class T>
    inline void mulScalar(T *r, T *lhs, const T &rhs)
    {
        Vec<T> mlhs = lhs;
        Vec<T> mrhs; mrhs.set1(rhs);
        (mlhs*mrhs).storeu_To(r); 
    }

    // DIV SCALAR
    template<class T>
    inline void divScalar(T *r, T *lhs, const T &rhs)
    {
        Vec<T> mlhs = lhs;
        Vec<T> mrhs; mrhs.set1(rhs);
        (mlhs/mrhs).storeu_To(r); 
    }

    // SIMD SIZE
    template<class T> inline int vectorizeSize         (){ return Vec<T>::size(); }
#endif


}

}