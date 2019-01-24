#ifndef __N_H__
#define __N_H__

#include <iostream>
#include "constants.h"

using namespace std;

class N{
public:
    static int precision;
    double r, i;

    N(const double=0,const double=0);
    N(const N&);

    // get set parte real
    double real();
    double real(double);

    // get set parte imaginaria
    double imag();
    double imag(double);
    
    // Asignacion de un valor numerico
    operator=(double);

    template<class T>
    explicit operator T(){return (T)this->r;}

    // Incremento prefijo
    N operator ++();
    // Incremento postfijo
    N operator++(int);
    // Decremento prefijo
    N operator --();
    // Decremento postfijo
    N operator --(int);
    // Asignacion aditiva
    void operator+=(N);
    // Asignacion sustractiva
    void operator-=(N);
    // Asignacion multiplicativa
    void operator*=(N);
    // Asignacion divisiva
    void operator/=(N);
    // Residuo
    void operator%=(N);

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
N norm(const N&);
N arg(const N&);
N conjugate(const N&);

N pow2(N,N);
N pow(const N&,const N&);
N sqrt(const N&);
N ln(const N&);
//logs(N, base)
N log(const N&, const N &base=e);

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
#endif