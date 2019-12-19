#pragma once

#include <iostream>
#include "../Utils/Utils.h"
//#include "../Math/Math.h"

namespace DM4th
{

template <class T>
class _number
{
    T _data[2];
    
public:

    _number(const T &a = 0, const T &b = 0)
    {
        this->real() = (T)a;
        this->imag() = (T)b;
    }

    // template<class U>
    // _number(U=0, U=0);

    explicit _number(std::string str)
    {
        std::stringstream ss;
        ss << str;
        ss >> *this;
    }

    // get set parte real
    inline const T real() const { return this->_data[0]; }
    inline T &real() { return this->_data[0]; };
    inline T &real(T a)
    {
        this->_data[0] = a;
        return this->_data[0];
    }

    inline T *data() { return this->_data; }

    //inline double &real() { return this->_data[0]; }

    // get set parte imaginaria
    inline const T imag() const { return this->_data[1]; }
    inline T &imag() { return this->_data[1]; };
    inline T &imag(T a)
    {
        this->_data[1] = a;
        return this->_data[1];
    }
    //inline double &imag() { return this->_data[1]; }

    // Asignacion de un valor numerico
    template <class U, typename std::enable_if<std::is_arithmetic<U>::value, U>::type>
    _number operator=(U a)
    {
        this->real() = a;
        this->imag() = 0;
        return *this;
    }

    // Asignacion de un valor numerico
    template <class U>
    inline _number operator=(const _number<U> &a)
    {
        this->real() = a.real();
        this->imag() = a.imag();
        return *this;
    }

    template <class U>
    explicit operator U() { return (U)this->real(); }

    inline explicit operator int() { return (int)std::round(this->real()); }

    explicit operator std::string()
    {
        std::ostringstream ss;
        ss << *this;
        return ss.str();
    };

    void loadFile(std::string url)
    {
        std::ifstream file;
        file.open(url);
        if (file.fail())
        {
            *this = 0;
        }
        else
        {
            file >> *this;
        }
        file.close();
    }

    void saveFile(std::string url)
    {
        std::ofstream file;
        file.open(url);
        file << *this;
        file.close();
    }

    inline _number operator+=(_number n);
    inline _number operator-=(_number n);
    _number operator*=(_number n);
    _number operator/=(_number n);
    _number operator%=(_number n);
};


typedef _number<double> number;
typedef _number<float> fnumber;
#define DM4th_i _number<T>(0,1)

// template<typename T>
// using enable_if_is_number = typename std::enable_if<std::is_arithmetic<T>::value, T>::type;

template <typename T, typename alt_type = number>
using check_if_is_number = typename std::enable_if<std::is_arithmetic<T>::value || std::is_same<_number<T>, alt_type>::value, T>::type;

// template<typename T, typename alt_type = _number<double>>
// using check_if_is_number = typename std::enable_if<std::is_arithmetic<T>::value, T>::type;

#define enable_if_is_number(T, U) typename = check_if_is_number<T, _number<U>>


// Define como constante el valor de i
static const number i(0, 1);
static const number _i(0, 1);
static const number fi(0, 1);
static const number _fi(0, 1);

// Convert string to number
inline number strTonumber(std::string);

// Conversion de expresion literal <double>i a tipo number
inline number operator""_i(long double);

// Conversion de expresion literal <entero>i a tipo number
inline number operator""_i(unsigned long long int);

// Conversion de expresion literal <float>i a tipo number
inline fnumber operator""_fi(long double);

// Conversion de expresion literal <float>i a tipo number
inline fnumber operator""_fi(unsigned long long int);

#ifndef DM4thOnlyStandardLiterals
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wliteral-suffix"

// Conversion de expresion literal <double>i a tipo number
inline number operator""i(long double);

// Conversion de expresion literal <entero>i a tipo numbers
inline number operator""i(unsigned long long int);

// Conversion de expresion literal <float>i a tipo number
inline fnumber operator""fi(long double);

// Conversion de expresion literal <float>i a tipo number
inline fnumber operator""fi(unsigned long long int);

#pragma GCC diagnostic pop
#endif

// Cambio a signo negativo
template <class T>
inline _number<T> operator-(_number<T>);

// Impresion en pantalla de numeros complejos
template <class T>
std::ostream &operator<<(std::ostream &, _number<T>);

// Lectura en pantalla de numeros complejos
template <class T>
std::istream &operator>>(std::istream &, _number<T> &);

// Incremento y decremento
template <class T>
inline _number<T> operator++(_number<T> &n)
{
    ++n.real();
    return n;
}

template <class T>
inline _number<T> operator++(_number<T> &n, int)
{
    _number<T> result = n;
    ++n.real();
    return result;
}

template <class T>
inline _number<T> operator--(_number<T> &n)
{
    --n.real();
    return n;
}

template <class T>
inline _number<T> operator--(_number<T> &n, int)
{
    _number<T> result = n;
    --n.real();
    return result;
}

// Suma de numeros complejos
template <class T>
inline _number<T> operator+(_number<T>, _number<T>);

template <class T, typename U, enable_if_is_number(U, _number<T>)>
inline _number<T> operator+(_number<T>, U);
template <class U, typename T, enable_if_is_number(U, _number<T>)>
inline _number<T> operator+(U, _number<T>);

// Resta de numeros complejos
template <class T>
inline _number<T> operator-(_number<T>, _number<T>);

template <class T, typename U, enable_if_is_number(U, _number<T>)>
inline _number<T> operator-(_number<T>, U);
template <class U, typename T, enable_if_is_number(U, _number<T>)>
inline _number<T> operator-(U, _number<T>);

// Multiplicacion de numeros complejos
template <class T>
_number<T> operator*(_number<T> n1, _number<T> n2);

template <class T, typename U, enable_if_is_number(U, _number<T>)>
inline _number<T> operator*(_number<T>, U);
template <class U, typename T, enable_if_is_number(U, _number<T>)>
inline _number<T> operator*(U, _number<T>);

//Division de numeros complejos
template <class T>
_number<T> operator/(_number<T>, _number<T>);

template <class T, typename U, enable_if_is_number(U, _number<T>)>
inline _number<T> operator/(_number<T>, U);

template <class U, typename T, enable_if_is_number(U, _number<T>)>
inline _number<T> operator/(U, _number<T>);

// Residuo de numeros complejos (Solo trabaja como numeros enteros)
template <class T>
_number<T> operator%(_number<T>, _number<T>);

template <class T, typename U, enable_if_is_number(U, _number<T>)>
inline _number<T> operator%(_number<T>, U);

template <class U, typename T, enable_if_is_number(U, _number<T>)>
inline _number<T> operator%(U, _number<T>);

// Relacional
template <class T>
inline bool operator==(_number<T>, _number<T>);
template <class T, typename U, enable_if_is_number(U, _number<T>)>
inline bool operator==(_number<T>, U);
template <class U, typename T, enable_if_is_number(U, _number<T>)>
inline bool operator==(U, _number<T>);

template <class T>
inline bool operator!=(_number<T>, _number<T>);
template <class T, typename U, enable_if_is_number(U, _number<T>)>
inline bool operator!=(_number<T>, U);
template <class U, typename T, enable_if_is_number(U, _number<T>)>
inline bool operator!=(U, _number<T>);

template <class T>
inline bool operator>=(_number<T>, _number<T>);
template <class T, typename U, enable_if_is_number(U, _number<T>)>
inline bool operator>=(_number<T>, U);
template <class U, typename T, enable_if_is_number(U, _number<T>)>
inline bool operator>=(U, _number<T>);

template <class T>
inline bool operator<=(_number<T>, _number<T>);
template <class T, typename U, enable_if_is_number(U, _number<T>)>
inline bool operator<=(_number<T>, U);
template <class U, typename T, enable_if_is_number(U, _number<T>)>
inline bool operator<=(U, _number<T>);

template <class T>
inline bool operator>(_number<T>, _number<T>);
template <class T, typename U, enable_if_is_number(U, _number<T>)>
inline bool operator>(_number<T>, U);
template <class U, typename T, enable_if_is_number(U, _number<T>)>
inline bool operator>(U, _number<T>);

template <class T>
inline bool operator<(_number<T>, _number<T>);
template <class T, typename U, enable_if_is_number(U, _number<T>)>
inline bool operator<(_number<T>, U);
template <class U, typename T, enable_if_is_number(U, _number<T>)>
inline bool operator<(U, _number<T>);

// Math
template <class T>
inline _number<T> rad(_number<T>);
template <class T>
inline _number<T> deg(_number<T>);

template <class T>
inline _number<T> fmod(_number<T>, _number<T>);

template <class T, typename U, enable_if_is_number(U, _number<T>)>
inline _number<T> fmod(_number<T>, U);
template <class U, typename T, enable_if_is_number(U, _number<T>)>
inline _number<T> fmod(U, _number<T>);

template <class T>
inline _number<T> round(_number<T>, int p = 0);
template <class T>
inline _number<T> ceil(_number<T>, int p = 0);
template <class T>
inline _number<T> floor(_number<T>, int p = 0);
template <class T>
inline _number<T> truncate(_number<T>, int p = 0);
template <class T>
inline _number<T> trunc(const _number<T> &value, int p = 0) { return truncate(value, p); }

template <class T>
inline bool isInf(_number<T>);
template <class T>
inline bool isReal(_number<T>);
template <class T>
inline bool isComplex(_number<T>);
template <class T>
inline bool isImag(_number<T>);

template <class T>
inline _number<T> abs(_number<T>);
template <class T>
inline _number<T> norm(_number<T>);
template <class T>
inline _number<T> arg(_number<T>);
template <class T>
inline _number<T> conjugate(_number<T>);

template <class T>
inline _number<T> pow(_number<T>, _number<T>);

template <class T, typename U, enable_if_is_number(U, _number<T>)>
inline _number<T> pow(_number<T>, U);
template <class U, typename T, enable_if_is_number(U, _number<T>)>
inline _number<T> pow(U, _number<T>);

template <class T>
inline _number<T> sqrt(_number<T>);
template <class T>
inline _number<T> ln(_number<T>);
template <class T>
inline _number<T> log(_number<T>, _number<T> base = e);

template <class T, typename U, enable_if_is_number(U, _number<T>)>
inline _number<T> log(_number<T>, U base = e);
template <class U, typename T, enable_if_is_number(U, _number<T>)>
inline _number<T> log(U, _number<T> base = e);

template <class T>
inline _number<T> sin(_number<T>);
template <class T>
inline _number<T> cos(_number<T>);
template <class T>
inline _number<T> tan(_number<T>);
template <class T>
inline _number<T> cot(_number<T>);
template <class T>
inline _number<T> sec(_number<T>);
template <class T>
inline _number<T> csc(_number<T>);

template <class T>
inline _number<T> asin(_number<T>);
template <class T>
inline _number<T> acos(_number<T>);
template <class T>
inline _number<T> atan(_number<T>);
template <class T>
inline _number<T> acot(_number<T>);
template <class T>
inline _number<T> asec(_number<T>);
template <class T>
inline _number<T> acsc(_number<T>);

template <class T>
inline _number<T> sinh(_number<T>);
template <class T>
inline _number<T> cosh(_number<T>);
template <class T>
inline _number<T> tanh(_number<T>);
template <class T>
inline _number<T> coth(_number<T>);
template <class T>
inline _number<T> sech(_number<T>);
template <class T>
inline _number<T> csch(_number<T>);

template <class T>
inline _number<T> asinh(_number<T>);
template <class T>
inline _number<T> acosh(_number<T>);
template <class T>
inline _number<T> atanh(_number<T>);
template <class T>
inline _number<T> acoth(_number<T>);
template <class T>
inline _number<T> asech(_number<T>);
template <class T>
inline _number<T> acsch(_number<T>);

// #ifdef DM4thSIMDNumber

// template<>
// inline number number::operator+=(number n)
// {
//     this->_ddata = _mm_add_pd(this->_ddata, n._ddata);
//     return *this;
// }

// template<>
// inline number number::operator-=(number n)
// {
//     this->_ddata = _mm_sub_pd(this->_ddata, n._ddata);
//     return *this;
// }

// template<>
// number number::operator*=(number n)
// {
//     if (isReal(*this) && isReal(n))
//     {
//         this->_ddata = _mm_mul_pd(this->_ddata, n._ddata);
//     }
//     else
//     {
//         // __m128d real = _mm_mul_pd(this->_ddata, n._ddata);
//         // __m128d imag = _mm_mul_pd(this->_ddata, _mm_setr_pd(n.imag(), n.real()));

//         // this->_ddata = _mm_add_pd(_mm_setr_pd(real[0], imag[0]), _mm_setr_pd(-real[1], imag[1]));

//         __m128d num1, num2, num3, num4;

//         // Copies a single element into the vector

//         //   num1:  [x.real, x.real]

//         num1 = _mm_load1_pd(&this->real());

//         // Move y elements into a vector

//         //   num2: [y.img, y.real]

//         num2 = _mm_set_pd(n.imag(), n.real());

//         // Multiplies vector elements

//         //   num3: [(x.real*y.img), (x.real*y.real)]

//         num3 = _mm_mul_pd(num2, num1);

//         //   num1: [x.img, x.img]

//         num1 = _mm_load1_pd(&this->imag());

//         // Swaps the vector elements.

//         //   num2: [y.real, y.img]

//         num2 = _mm_shuffle_pd(num2, num2, 1);

//         //   num2: [(x.img*y.real), (x.img*y.img)]

//         num2 = _mm_mul_pd(num2, num1);

//         num4 = _mm_add_pd(num3, num2);

//         num3 = _mm_sub_pd(num3, num2);

//         num4 = _mm_shuffle_pd(num3, num4, 2);

//         // Stores the elements of num4 into z

//         _mm_storeu_pd(reinterpret_cast<double*>(this), num4);

//     }

//     return *this;
// }

// #endif

#if defined DM4thOmpNumber

#pragma omp declare reduction(+        \
                              : number \
                              : omp_out = (omp_out + omp_in))
#pragma omp declare reduction(-        \
                              : number \
                              : omp_out = (omp_out - omp_in))
#pragma omp declare reduction(*        \
                              : number \
                              : omp_out = (omp_out * omp_in)) initializer(omp_priv = 1)
#pragma omp declare reduction(max      \
                              : number \
                              : omp_out = (omp_out > omp_in) ? omp_out : omp_in) initializer(omp_priv = -std::numeric_limits<double>::infinity())
#pragma omp declare reduction(min      \
                              : number \
                              : omp_out = (omp_out < omp_in) ? omp_out : omp_in) initializer(omp_priv = std::numeric_limits<double>::infinity())

#define DM4thReductionadd(...) reduction(+ \
                                         : __VA_ARGS__)
#define DM4thReductionSub(...) reduction(- \
                                         : __VA_ARGS__)
#define DM4thReductionmul(...) reduction(* \
                                          : __VA_ARGS__)
#define DM4thReductionMax(...) reduction(max \
                                         : __VA_ARGS__)
#define DM4thReductionMin(...) reduction(min \
                                         : __VA_ARGS__)
#endif

} // namespace DM4th
