#ifndef __NUMBER_H__
#define __NUMBER_H__

#include <iostream>
#include "constants.h"
#include "_Data.h"
#include <sstream>
#include <fstream>
#pragma GCC diagnostic ignored "-Wliteral-suffix"

class Number{
    double r, i;
public:

    Number(const double=0,const double=0);
    Number(const Number&);
    Number(std::string);

    // get set parte real
    double real() const;
    double real(double);

    // get set parte imaginaria
    double imag() const;
    double imag(double);
    
    // Asignacion de un valor numerico
    Number operator=(double);

    template<class T>
    explicit operator T(){return (T)this->r;}
    explicit operator char *();
    explicit operator std::string();

    // Carga valor de tipo Number desde un fichero
    Number loadFile(std::string url);
    // Guarda valor de tipo Number en un fichero
    Number saveFile(std::string url);

    // Incremento prefijo
    Number operator ++();
    // Incremento postfijo
    Number operator ++(int);
    // Decremento prefijo
    Number operator --();
    // Decremento postfijo
    Number operator --(int);
    // Asignacion aditiva
    Number operator +=(Number);
    // Asignacion sustractiva
    Number operator -=(Number);
    // Asignacion multiplicativa
    Number operator *=(Number);
    // Asignacion divisiva
    Number operator /=(Number);
    // Residuo
    Number operator %=(Number);
};

// Define como constante el valor de i
static const Number i(0,1);
static const Number _i(0,1);

// Convert string to Number
Number strToNumber(std::string);

// Conversion de expresion literal <double>i a tipo numero
Number operator""_i(long double);

// Conversion de expresion literal <entero>i a tipo numero
Number operator""_i(unsigned long long int);

// Conversion de expresion literal <double>i a tipo numero
Number operator""i(long double);

// Conversion de expresion literal <entero>i a tipo numero
Number operator""i(unsigned long long int);

// Cambio a signo negativo
Number operator-(Number);

// Impresion en pantalla de numeros complejos
std::ostream& operator<<(std::ostream&, Number);

// Lectura en pantalla de numeros complejos
std::istream& operator>>(std::istream&, Number&);

// Suma de numeros complejos
Number operator+(const Number&,const Number&);

// Resta de numeros complejos
Number operator-(const Number&,const Number&);

// Multiplicacion de numeros complejos
Number operator*(const Number&,const Number&);

// Division de numeros complejos
Number operator/(const Number&,const Number&);

// Residuo de numeros complejos (Solo trabaja como numeros enteros)
Number operator%(const Number&,const Number&);

// Relacional
bool operator==(const Number&, const Number&);
bool operator!=(const Number&, const Number&);
bool operator>=(const Number&, const Number&);
bool operator<=(const Number&, const Number&);
bool operator>(const Number&, const Number&);
bool operator<(const Number&, const Number&);

// Math
Number rad(const Number&);
Number deg(const Number&);

Number round(const Number&, int p=0);

Number abs(const Number&);
Number norm(const Number&);
Number arg(const Number&);
Number conjugate(const Number&);

Number pow(const Number&,const Number&);
Number sqrt(const Number&);
Number ln(const Number&);
//logs(N, base)
Number log(const Number&, const Number &base=e);

Number sin(const Number&);
Number cos(const Number&);
Number tan(const Number&);
Number cot(const Number&);
Number sec(const Number&);
Number csc(const Number&);

Number asin(const Number&);
Number acos(const Number&);
Number atan(const Number&);
Number acot(const Number&);
Number asec(const Number&);
Number acsc(const Number&);

Number sinh(const Number&);
Number cosh(const Number&);
Number tanh(const Number&);
Number coth(const Number&);
Number sech(const Number&);
Number csch(const Number&);

Number asinh(const Number&);
Number acosh(const Number&);
Number atanh(const Number&);
Number acoth(const Number&);
Number asech(const Number&);
Number acsch(const Number&);
#endif