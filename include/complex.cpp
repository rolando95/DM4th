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

// Sobrecarga del operador +
complex operator+(const complex &p1,const complex &p2)
{
  return complex(p1.r + p2.r, p1.i + p2.i);
}


complex operator""i(long double a){
    return complex(0,a);
}
