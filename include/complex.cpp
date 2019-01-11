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

//Impresion en pantalla de numeros complejos
ostream& operator<<(ostream& stream, complex n){
    if(n.i==0 && n.r==0) stream<<"0";
    else{
        if(n.r != 0) stream<<n.r;
        if(n.i > 0 && n.r!=0)  stream<<"+";
        if(n.i != 0) stream<<n.i<<"i";
    }
    return stream;
}

//Lectura en pantalla de numeros complejos
istream& operator>>(istream& stream, complex &n){
    long double x;
    while(stream.peek()!='\n' && stream>>x){
        if(stream.peek()=='i')
            n.i = x;
        else
            n.r = x;
    }
    return stream;
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
