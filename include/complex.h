#include <math.h>
#include <iostream>
using namespace std;

class complex {
public:
    double r, i;
    complex(const double a=0,const double b=0);
    //Asignacion de un valor numerico
    operator=(long double a);
};

//Impresion en pantalla de numeros complejos
ostream& operator<<(ostream& stream, complex n);

//Lectura en pantalla de numeros complejos
istream& operator>>(istream& stream, complex &n);

// Suma de numeros complejos
complex operator+(const complex &n1,const complex &n2);

// Resta de numeros complejos
complex operator-(const complex &n1,const complex &n2);

// Multiplicacion de numeros complejos
complex operator*(const complex &n1,const complex &n2);

// Division de numeros complejos
complex operator/(const complex &n1,const complex &n2);


complex operator""i(long double a);