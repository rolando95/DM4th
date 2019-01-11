#include "number.h"

using namespace std;

number::number(const double a,const double b)
{
    this->r = a;
    this->i = b;
}

number::operator=(double a){
    this->r = a;
    return 0;
}

number::operator+=(number n){
    *this = *this + n;
}

number::operator-=(number n){
    *this = *this - n;
}

number::operator*=(number n){
    *this = *this * n;
}

number::operator/=(number n){
    *this = *this / n;
}

number::operator%=(number n){
    *this = *this % n;
}


number operator""i(long double a){
    return number(0,a);
}

number operator""i(unsigned long long int a){
    return number(0,a);
}

number operator-(number a){
    return number(-a.r,-a.i);
}

//Impresion en pantalla de numeros complejos
ostream& operator<<(ostream& stream, number n){
    if(n.i==0 && n.r==0) stream<<"0";
    else{
        if(n.r != 0) stream<<n.r;
        if(n.i > 0 && n.r!=0)  stream<<"+";
        if(n.i != 0) stream<<n.i<<"i";
    }
    return stream;
}

//Lectura en pantalla de numeros complejos
istream& operator>>(istream& stream, number &n){
    double x;
    while(stream.peek()!='\n' && stream>>x){
        if(stream.peek()=='i')
            n.i = x;
        else
            n.r = x;
    }
    return stream;
}


// Suma de numeros complejos
number operator+(const number &n1,const number &n2)
{
    return number(n1.r + n2.r, n1.i + n2.i);
}

// Resta de numeros complejos
number operator-(const number &n1,const number &n2)
{
    return number(n1.r - n2.r, n1.i - n2.i);
}

// Multiplicacion de numeros complejos
number operator*(const number &n1,const number &n2)
{
    return number(
      n1.r*n2.r - n1.i*n2.i, 
      n1.r*n2.i + n1.i*n2.r
    );
}

// Division de numeros complejos
number operator/(const number &n1,const number &n2)
{
    return number(
        (n1.r*n2.r + n1.i*n2.i)/(pow(n2.r,2) + pow(n2.i,2)),
        (n1.i*n2.r - n1.r*n2.i)/(pow(n2.r,2) + pow(n2.i,2))  
    );
}

// Division de numeros complejos
number operator%(const number &n1,const number &n2)
{
    return number( int(n1.r) % int(n2.r),0);  
}