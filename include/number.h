//#include <math.h>
#include <cmath>
#include <iostream>
#include <complex>
#include <float.h>
using namespace std::complex_literals;
using namespace std;

constexpr double pi = 3.14159265358979323846264338327950288419716939937510;

class number{
public:
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

    // Asignacion de un valor complex
    operator=(complex<double>);

    // Asignacion de un valor complex 2 ?????????
    // complex<double>& operator=(const number & a);

    // Conversion al complex<double> de c++
    operator const complex<double>();

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

// Math
number rad(const number&);
number deg(const number&);

number pow(number,number);

number sin(number);

number tan(number);
