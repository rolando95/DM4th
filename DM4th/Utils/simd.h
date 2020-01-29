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



#if defined __AVX2__

    template<>
    class Vec<float>
    {
        static const int _size = 8;

        union {
            __m256 data;
            float arr[_size];
        };

        public:

        inline Vec() {};
        inline Vec(__m256 o) { this->data = o;};
        inline Vec(const float *other)       { this->data = _mm256_loadu_ps(other); }  

        static int size() { return _size; }

        inline void operator=(Vec other)            { data = other.data; }
        inline void operator=(const float *other)       { this->data = _mm256_loadu_ps(other); }   
        inline void set1(const float other)        { this->data = _mm256_broadcast_ss(&other); }

        inline Vec<float> operator+(Vec<float> other) { return _mm256_add_ps(this->data ,other.data); }
        inline Vec<float> operator-(Vec<float> other) { return _mm256_sub_ps(this->data ,other.data); }
        inline Vec<float> operator*(Vec<float> other) { return _mm256_mul_ps(this->data ,other.data); } 
        inline Vec<float> operator/(Vec<float> other) { return _mm256_div_ps(this->data ,other.data); } 

        inline void storeu_To(float *other) { _mm256_storeu_ps(other, this->data); }
    };

    template<>
    class Vec<double>
    {
        static const int _size = 4;

        union {
            __m256d data;
            double arr[_size];
        };

        public:

        inline Vec() {};
        inline Vec(__m256d o) { this->data = o;};
        inline Vec(const double *other)       { this->data = _mm256_loadu_pd(other); }  

        static int size() { return _size; }
        inline void operator=(Vec other)            { data = other.data; }
        inline void operator=(const double *other)       { this->data = _mm256_loadu_pd(other); }   
        inline void set1(const double other)        { this->data = _mm256_broadcast_sd(&other); }

        inline Vec<double> operator+(Vec<double> other) { return _mm256_add_pd(this->data ,other.data); }
        inline Vec<double> operator-(Vec<double> other) { return _mm256_sub_pd(this->data ,other.data); }
        inline Vec<double> operator*(Vec<double> other) { return _mm256_mul_pd(this->data ,other.data); } 
        inline Vec<double> operator/(Vec<double> other) { return _mm256_div_pd(this->data ,other.data); } 

        inline void storeu_To(double *other) { _mm256_storeu_pd(other, this->data); }
    };

#else

    template<>
    class Vec<float>
    {
        static const int _size = 4;

        union {
            __m128 data;
            float arr[_size];
        };

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
        static const int _size = 2;

        union {
            __m128d data;
            double arr[_size];
        };

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

#endif
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
}

}