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

    number(const double a=0,const double b=0);

    //Asignacion de un valor numerico
    operator=(double n);

    //Asignacion de un valor complex
    operator=(complex<double> n);

    //Asignacion de un valor complex 2 ?????????
    //complex<double>& operator=(const number & a);

    //Conversion al complex<double> de c++
    operator const complex<double>();

    //Asignacion aditiva
    operator+=(number n);

    //Asignacion sustractiva
    operator-=(number n);

    //Asignacion multiplicativa
    operator*=(number n);

    //Asignacion divisiva
    operator/=(number n);

    //Residuo
    operator%=(number n);
};

//Define como constante el valor de i
static const number i(0,1);

//Conversion de expresion literal <double>i a tipo numero
number operator""i(long double a);

//Conversion de expresion literal <entero>i a tipo numero
number operator""i(unsigned long long int a);

//Cambio a signo negativo
number operator-(number a);

//Impresion en pantalla de numeros complejos
ostream& operator<<(ostream& stream, number n);

//Lectura en pantalla de numeros complejos
istream& operator>>(istream& stream, number &n);

// Suma de numeros complejos
number operator+(const number &n1,const number &n2);

// Resta de numeros complejos
number operator-(const number &n1,const number &n2);

// Multiplicacion de numeros complejos
number operator*(const number &n1,const number &n2);

// Division de numeros complejos
number operator/(const number &n1,const number &n2);

// Residuo de numeros enteros?
number operator%(const number &n1,const number &n2);

// Math
number rad(const number &n1);
number deg(const number &n1);

number pow(number n1,number n2);

number sin(number n1);

number tan(number n1);
