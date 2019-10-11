#pragma once

#include <iostream>
#include "../_Utilities/_Utilities.h"
//#include "../_Math/_Math.h"
#pragma GCC diagnostic ignored "-Wliteral-suffix"



namespace DM4th
{

template<class T>
class _number{
   T r=0, i=0;
public:
    _number(T=0, T=0);

    // template<class U>
    // _number(U=0, U=0);

    _number(std::string);

    // get set parte real
    inline const double real() const {return this->r;}
    inline double real(double a) {this->r = a; return this->r;}
    //inline double &real() { return this->r; }

    // get set parte imaginaria
    inline const double imag() const  {return this->i;}
    inline double imag(double a) {this->i = a; return this->i;}
    //inline double &imag() { return this->i; }
    
    // Asignacion de un valor numerico
    template<class U, typename std::enable_if<std::is_arithmetic<U>::value, U>::type>
    _number<T> operator=(U);

    // Asignacion de un valor numerico
    template<class U>
    _number<T> operator=(const _number<U>);

    template<class U>
    explicit operator U(){return (U)this->r;}
    inline explicit operator int () { return (int)round(this->r); }
    explicit operator char *();
    explicit operator std::string();

    void loadFile(std::string url);
    void saveFile(std::string url);

    // Incremento prefijo
    _number<T> operator ++();
    // Incremento postfijo
    _number<T> operator ++(int);
    // Decremento prefijo
    _number<T> operator --();
    // Decremento postfijo
    _number<T> operator --(int);
    // Asignacion aditiva
    _number<T> operator +=(_number<T>);
    // Asignacion sustractiva
    _number<T> operator -=(_number<T>);
    // Asignacion multiplicativa
    _number<T> operator *=(_number<T>);
    // Asignacion divisiva
    _number<T> operator /=(_number<T>);
    // Residuo
    _number<T> operator %=(_number<T>);
};
#include <type_traits>
typedef _number<double> number;

// template<typename T>
// using enable_if_is_number = typename std::enable_if<std::is_arithmetic<T>::value, T>::type;

template<typename T, typename alt_type = number>
using check_if_is_number = typename std::enable_if<std::is_arithmetic<T>::value || std::is_same<_number<T>, alt_type>::value, T>::type;

// template<typename T, typename alt_type = _number<double>>
// using check_if_is_number = typename std::enable_if<std::is_arithmetic<T>::value, T>::type;

#define enable_if_is_number(T,U) typename = check_if_is_number<T, _number<U>>

// Define como constante el valor de i
static const number i(0,1);
static const number _i(0,1);

// Convert string to number
inline number strTonumber(std::string);

// Conversion de expresion literal <double>i a tipo numero
inline number operator""_i(long double);

// Conversion de expresion literal <entero>i a tipo numero
inline number operator""_i(unsigned long long int);

// Conversion de expresion literal <double>i a tipo numero
inline number operator""i(long double);

// Conversion de expresion literal <entero>i a tipo numero
inline number operator""i(unsigned long long int);

// Cambio a signo negativo
template<class T>
inline _number<T> operator-(_number<T>);

// Impresion en pantalla de numeros complejos
template<class T>
std::ostream& operator<<(std::ostream&, _number<T>);

// Lectura en pantalla de numeros complejos
template<class T>
std::istream& operator>>(std::istream&, _number<T>&);

// Suma de numeros complejos
template<class T>
inline _number<T> operator+(_number<T>,_number<T>);

template<class  T, typename U, enable_if_is_number(U, _number<T>)> 
inline _number<T> operator+(_number<T>, U);
template<class  U, typename T, enable_if_is_number(U, _number<T>)> 
inline _number<T> operator+(U,_number<T>);

// Resta de numeros complejos
template<class T>
inline _number<T> operator-(_number<T>,_number<T>);

template<class  T, typename U, enable_if_is_number(U, _number<T>)> 
inline _number<T> operator-(_number<T>, U);
template<class  U, typename T, enable_if_is_number(U, _number<T>)> 
inline _number<T> operator-(U , _number<T> );

// Multiplicacion de numeros complejos
template<class T>
_number<T> operator*(_number<T> n1, _number<T> n2);

template<class  T, typename U, enable_if_is_number(U, _number<T>)> 
inline _number<T> operator*(_number<T>, U);
template<class  U, typename T, enable_if_is_number(U, _number<T>)> 
inline _number<T> operator*(U , _number<T>);

//Division de numeros complejos
template<class T>
_number<T> operator/(_number<T>, _number<T>);

template<class  T, typename U, enable_if_is_number(U, _number<T>)> 
inline _number<T> operator/(_number<T>, U);

template<class  U, typename T, enable_if_is_number(U, _number<T>)> 
inline _number<T> operator/(U , _number<T> );

// Residuo de numeros complejos (Solo trabaja como numeros enteros)
template<class T>
_number<T> operator%(_number<T>,_number<T>);

template<class  T, typename U, enable_if_is_number(U, _number<T>)> 
inline _number<T> operator%(_number<T>, U);

template<class  U, typename T, enable_if_is_number(U, _number<T>)> 
inline _number<T> operator%(U , _number<T>);

// Relacional
template<class T> inline bool operator==(_number<T>, _number<T>);
template<class  T, typename U, enable_if_is_number(U, _number<T>)> 
inline _number<T> operator==(_number<T>, U);
template<class  U, typename T, enable_if_is_number(U, _number<T>)> 
inline _number<T> operator==(U ,_number<T>);

template<class T> inline bool operator!=(_number<T>, _number<T>);
template<class  T, typename U, enable_if_is_number(U, _number<T>)> 
inline _number<T> operator!=(_number<T>, U);
template<class  U, typename T, enable_if_is_number(U, _number<T>)> 
inline _number<T> operator!=(U , _number<T> );

template<class T> inline bool operator>=(_number<T>, _number<T>);
template<class  T, typename U, enable_if_is_number(U, _number<T>)> 
inline _number<T> operator>=(_number<T>, U);
template<class  U, typename T, enable_if_is_number(U, _number<T>)> 
inline _number<T> operator>=(U , _number<T> );

template<class T> inline bool operator<=(_number<T>, _number<T>);
template<class  T, typename U, enable_if_is_number(U, _number<T>)> 
inline _number<T> operator<=(_number<T>, U);
template<class  U, typename T, enable_if_is_number(U, _number<T>)> 
inline _number<T> operator<=(U , _number<T> );

template<class T> inline bool operator>(_number<T>, _number<T>);
template<class  T, typename U, enable_if_is_number(U, _number<T>)> 
inline _number<T> operator>(_number<T>, U);
template<class  U, typename T, enable_if_is_number(U, _number<T>)> 
inline _number<T> operator>(U , _number<T> );

template<class T> inline bool operator<(_number<T>, _number<T>);
template<class  T, typename U, enable_if_is_number(U, _number<T>)> 
inline _number<T> operator<(_number<T>, U);
template<class  U, typename T, enable_if_is_number(U, _number<T>)> 
inline _number<T> operator<(U , _number<T>);

// Math
template<class T> inline _number<T> rad(_number<T>);
template<class T> inline _number<T> deg(_number<T>);

template<class T> inline _number<T> fmod(_number<T>, _number<T>);

template<class  T, typename U, enable_if_is_number(U, _number<T>)> 
inline _number<T> fmod(_number<T>, U );
template<class  U, typename T, enable_if_is_number(U, _number<T>)> 
inline _number<T> fmod(U , _number<T> );

template<class T> inline _number<T> round(_number<T>, int p=0);
template<class T> inline _number<T> ceil(_number<T>, int p=0);
template<class T> inline _number<T> floor(_number<T>, int p=0);
template<class T> inline _number<T> truncate(_number<T>, int p=0);
template<class T> inline _number<T> trunc(const _number<T> &value, int p=0) { return truncate(value,p); }

template<class T> inline bool isInf(_number<T>);
template<class T> inline bool isReal(_number<T>);
template<class T> inline bool isComplex(_number<T>);
template<class T> inline bool isImag(_number<T>);

template<class T> inline _number<T> abs(_number<T>);
template<class T> inline _number<T> norm(_number<T>);
template<class T> inline _number<T> arg(_number<T>);
template<class T> inline _number<T> conjugate(_number<T>);

template<class T> inline _number<T> pow(_number<T>,_number<T>);

template<class  T, typename U, enable_if_is_number(U, _number<T>)> 
inline _number<T> pow(_number<T>, U );
template<class  U, typename T, enable_if_is_number(U, _number<T>)> 
inline _number<T> pow(U , _number<T> );

template<class T> inline _number<T> sqrt(_number<T>);
template<class T> inline _number<T> ln(_number<T>);
template<class T> inline _number<T> log(_number<T>, _number<T> base=e);

template<class  T, typename U, enable_if_is_number(U, _number<T>)> 
inline _number<T> log(_number<T>, U base=e);
template<class  U, typename T, enable_if_is_number(U, _number<T>)> 
inline _number<T> log(U, _number<T> base=e);

template<class T> inline _number<T> sin(_number<T>);
template<class T> inline _number<T> cos(_number<T>);
template<class T> inline _number<T> tan(_number<T>);
template<class T> inline _number<T> cot(_number<T>);
template<class T> inline _number<T> sec(_number<T>);
template<class T> inline _number<T> csc(_number<T>);

template<class T> inline _number<T> asin(_number<T>);
template<class T> inline _number<T> acos(_number<T>);
template<class T> inline _number<T> atan(_number<T>);
template<class T> inline _number<T> acot(_number<T>);
template<class T> inline _number<T> asec(_number<T>);
template<class T> inline _number<T> acsc(_number<T>);

template<class T> inline _number<T> sinh(_number<T>);
template<class T> inline _number<T> cosh(_number<T>);
template<class T> inline _number<T> tanh(_number<T>);
template<class T> inline _number<T> coth(_number<T>);
template<class T> inline _number<T> sech(_number<T>);
template<class T> inline _number<T> csch(_number<T>);

template<class T> inline _number<T> asinh(_number<T>);
template<class T> inline _number<T> acosh(_number<T>);
template<class T> inline _number<T> atanh(_number<T>);
template<class T> inline _number<T> acoth(_number<T>);
template<class T> inline _number<T> asech(_number<T>);
template<class T> inline _number<T> acsch(_number<T>);

}