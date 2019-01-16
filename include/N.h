#pragma once
#include <cmath>
#include <iostream>
#include <float.h>
#include <stdio.h>
#define INF INFINITY
using namespace std;

constexpr double pi = 3.141592653589793238462;
constexpr double e  = 2.718281828459045235360;

class N{
public:
    static int precision;
    double r, i;

    N(const double=0,const double=0);

    // get set parte real
    double real();
    double real(double);

    // get set parte imaginaria
    double imag();
    double imag(double);
    
    // Asignacion de un valor numerico
    operator=(double);

    // Incremento prefijo
    N operator ++();

    // Incremento postfijo
    N operator++(int);

    // Decremento prefijo
    N operator --();

    // Decremento postfijo
    N operator --(int);

    // Asignacion aditiva
    operator+=(N);

    // Asignacion sustractiva
    operator-=(N);

    // Asignacion multiplicativa
    operator*=(N);

    // Asignacion divisiva
    operator/=(N);

    // Residuo
    operator%=(N);

};

// Define como constante el valor de i
static const N i(0,1);
static const N _i(0,1);


// Conversion de expresion literal <double>i a tipo numero
N operator""_i(long double);

// Conversion de expresion literal <entero>i a tipo numero
N operator""_i(unsigned long long int);

// Conversion de expresion literal <double>i a tipo numero
N operator""i(long double);

// Conversion de expresion literal <entero>i a tipo numero
N operator""i(unsigned long long int);

// Cambio a signo negativo
N operator-(N);

// Impresion en pantalla de numeros complejos
ostream& operator<<(ostream&, N);

// Lectura en pantalla de numeros complejos
istream& operator>>(istream&, N&);

// Suma de numeros complejos
N operator+(const N&,const N&);

// Resta de numeros complejos
N operator-(const N&,const N&);

// Multiplicacion de numeros complejos
N operator*(const N&,const N&);

// Division de numeros complejos
N operator/(const N&,const N&);


// Residuo de numeros complejos (Solo trabaja como numeros enteros)
N operator%(const N&,const N&);

// Relacional
bool operator==(const N&, const N&);
bool operator!=(const N&, const N&);
bool operator>=(const N&, const N&);
bool operator<=(const N&, const N&);
bool operator>(const N&, const N&);
bool operator<(const N&, const N&);

// Math
N rad(const N&);
N deg(const N&);

N round(const N&, int p=0);
N abs(const N&);

N mod(const N&);
N norm(const N&);
N arg(const N&);

N pow2(N,N);
N pow(const N&,const N&);
N sqrt(const N&);
N ln(const N&);

//logn(N, base)
N logn(const N&, const N &base=10);

N sin(const N&);
N cos(const N&);
N tan(const N&);
N cot(const N&);
N sec(const N&);
N csc(const N&);

N asin(const N&);
N acos(const N&);
N atan(const N&);
N acot(const N&);
N asec(const N&);
N acsc(const N&);

N sinh(const N&);
N cosh(const N&);
N tanh(const N&);
N coth(const N&);
N sech(const N&);
N csch(const N&);

N asinh(const N&);
N acosh(const N&);
N atanh(const N&);
N acoth(const N&);
N asech(const N&);
N acsch(const N&);

// Aproximacion de raices
typedef N (* function)(N x);
//NewtonRaphson(f, f', x0=seed, max iterations, tolerance)
N newtonRaphson(function f, function fd, N x0=1.01, N maxIter=100, N tolerance=0.00001);
//NewtonRaphson(f, x0=seed, x1=seed2, max iterations, tolerance)
//N secantMethod(function f, N x0=0.01, N x1=1.01, N maxIter=100, N tolerance=0.0001);
