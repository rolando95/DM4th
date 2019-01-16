#pragma once
#include <cmath>
#include <iostream>
#include <float.h>
#include <stdio.h>

using namespace std;

constexpr double pi = 3.141592653589793238462;
constexpr double e  = 2.718281828459045235360;

class number{
public:
    static int precision;
    double r, i;

    number(const double=0,const double=0);

    // get set parte real
    double real();
    double real(double);

    // get set parte imaginaria
    double imag();
    double imag(double);
    
    // Asignacion de un valor numerico
    operator=(double);

    // Incremento prefijo
    number operator ++();

    // Incremento postfijo
    number operator++(int);

    // Decremento prefijo
    number operator --();

    // Decremento postfijo
    number operator --(int);

    // Asignacion aditiva
    operator+=(number);

    // Asignacion sustractiva
    operator-=(number);

    // Asignacion multiplicativa
    operator*=(number);

    // Asignacion divisiva
    operator/=(number);

    // Residuo
    operator%=(number);
};

// Define como constante el valor de i
static const number i(0,1);
static const number _i(0,1);


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
ostream& operator<<(ostream&, number);

// Lectura en pantalla de numeros complejos
istream& operator>>(istream&, number&);

// Suma de numeros complejos
number operator+(const number&,const number&);

// Resta de numeros complejos
number operator-(const number&,const number&);

// Multiplicacion de numeros complejos
number operator*(const number&,const number&);

// Division de numeros complejos
number operator/(const number&,const number&);

// Residuo de numeros enteros?
number operator%(const number&,const number&);

// Relacional
bool operator==(const number&, const number&);

// Math
number rad(const number&);
number deg(const number&);

number round(const number&, int p=0);

number mod(const number&);
number norm(const number&);
number arg(const number&);

number pow2(number,number);
number pow(const number&,const number&);
number sqrt(const number&);
number ln(const number&);
//logn(number, base)
number logn(const number&, const number &base=10);

number sin(const number&);
number cos(const number&);
number tan(const number&);
number cot(const number&);
number sec(const number&);
number csc(const number&);
