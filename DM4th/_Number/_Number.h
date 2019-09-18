#pragma once

#include <iostream>
#include "../_Utilities/_Utilities.h"
#include "../_Math/_Math.h"
#pragma GCC diagnostic ignored "-Wliteral-suffix"

namespace DM4th
{

class number{
   double r, i;
public:

    number(const double=0,const double=0);
    //number(number);
    number(std::string);

    // get set parte real
    const double real() const;
    double real(double);
    double &real();

    // get set parte imaginaria
    const double imag() const;
    double imag(double);
    double &imag();
    
    // Asignacion de un valor numerico
    number operator=(double);

    template<class T>
    explicit operator T(){return (T)this->r;}
    inline explicit operator int () { return (int)round(this->r); }
    explicit operator char *();
    explicit operator std::string();

    void loadFile(std::string url);
    void saveFile(std::string url);

    // Incremento prefijo
    number operator ++();
    // Incremento postfijo
    number operator ++(int);
    // Decremento prefijo
    number operator --();
    // Decremento postfijo
    number operator --(int);
    // Asignacion aditiva
    number operator +=(number);
    // Asignacion sustractiva
    number operator -=(number);
    // Asignacion multiplicativa
    number operator *=(number);
    // Asignacion divisiva
    number operator /=(number);
    // Residuo
    number operator %=(number);
};

// Define como constante el valor de i
static const number i(0,1);
static const number _i(0,1);

// Convert string to number
number strTonumber(std::string);

// Conversion de expresion literal <double>i a tipo numero
number operator""_i(long double);

// Conversion de expresion literal <entero>i a tipo numero
number operator""_i(unsigned long long int);

// Conversion de expresion literal <double>i a tipo numero
number operator""i(long double);

// Conversion de expresion literal <entero>i a tipo numero
number operator""i(unsigned long long int);

// Cambio a signo negativo
number operator-(number);

// Impresion en pantalla de numeros complejos
std::ostream& operator<<(std::ostream&, number);

// Lectura en pantalla de numeros complejos
std::istream& operator>>(std::istream&, number&);

// Suma de numeros complejos
number operator+(const number&,const number&);

// Resta de numeros complejos
number operator-(const number&,const number&);

// Multiplicacion de numeros complejos
number operator*(const number&,const number&);

// Division de numeros complejos
number operator/(const number&,const number&);

// Residuo de numeros complejos (Solo trabaja como numeros enteros)
number operator%(const number&,const number&);

// Relacional
bool operator==(const number&, const number&);
bool operator!=(const number&, const number&);
bool operator>=(const number&, const number&);
bool operator<=(const number&, const number&);
bool operator>(const number&, const number&);
bool operator<(const number&, const number&);

// Math
number rad(number);
number deg(number);

number round(number, int p=0);
number ceil(number, int p=0);
number floor(number, int p=0);
number truncate(number, int p=0);
inline number trunc(const number&value, int p=0) { return truncate(value,p); }

number abs(number);
number norm(number);
number arg(number);
number conjugate(number);

number pow(number,number);
number sqrt(number);
number ln(number);
//logs(N, base)
number log(number, number base=e);

number sin(number);
number cos(number);
number tan(number);
number cot(number);
number sec(number);
number csc(number);

number asin(number);
number acos(number);
number atan(number);
number acot(number);
number asec(number);
number acsc(number);

number sinh(number);
number cosh(number);
number tanh(number);
number coth(number);
number sech(number);
number csch(number);

number asinh(number);
number acosh(number);
number atanh(number);
number acoth(number);
number asech(number);
number acsch(number);

}