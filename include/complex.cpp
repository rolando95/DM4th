#include "complex.h"

using namespace std;

complex::complex(const double a,const double b)
{
     this->r = a;
    this->i = b;
}


complex::operator=(long double a){
    this->r = a;
    return 0;
}

// Suma de numeros complejos
complex operator+(const complex &n1,const complex &n2)
{
    return complex(n1.r + n2.r, n1.i + n2.i);
}

// Resta de numeros complejos
complex operator-(const complex &n1,const complex &n2)
{
    return complex(n1.r - n2.r, n1.i - n2.i);
}

// Multiplicacion de numeros complejos
complex operator*(const complex &n1,const complex &n2)
{
    return complex(
      n1.r*n2.r - n1.i*n2.i, 
      n1.r*n2.i + n1.i*n2.r
    );
}

// Division de numeros complejos
complex operator/(const complex &n1,const complex &n2)
{
    return complex(
        (n1.r*n2.r + n1.i*n2.i)/(pow(n2.r,2) + pow(n2.i,2)),
        (n1.i*n2.r - n1.r*n2.i)/(pow(n2.r,2) + pow(n2.i,2))  
    );
}


complex operator""i(long double a){
    return complex(0,a);
}
