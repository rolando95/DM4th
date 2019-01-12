#include "number.h"

using namespace std;

number::number(const double a,const double b)
{
    this->r = a;
    this->i = b;
}

double number::real(){return this->r;}
double number::real(double a){this->r = a; return this->r;}

double number::imag(){return this->i;}
double number::imag(double a){this->i = a; return this->i;}

number::operator=(double a){
    this->r = a;
    return 0;
}
number::operator=(complex<double> n){
    this->r = n.real();
    this->i = n.imag();
}

/*/?????????
complex<double>& number::operator=(const number & a){
    std::complex<double> n;
    n.real(this->r);
    n.imag(this->i);
    return n;
}*/

number::operator const complex<double>(){
    std::complex<double> n;
    n.real(this->r);
    n.imag(this->i);
    return n;
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
    if(n.r == INFINITY) stream<<INFINITY;
    else if(isnan(n.r)) stream<<NAN;
    else if(n.i==0 && n.r==0) stream<<"0";
    else{
        if(n.r != 0) stream<<n.r;
        if(n.i > 0 && n.r!=0)  stream<<"+";
        if(n.i != 0) {
            if(n.i != 1 && n.i != -1) stream<<n.i;
            if(n.i == -1) stream<<"-";
            stream<<"i";
        }
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
    double denominator = pow(n2.r,2) + pow(n2.i,2);
    if(denominator != 0)
        return number(
            (n1.r*n2.r + n1.i*n2.i)/ denominator,
            (n1.i*n2.r - n1.r*n2.i)/ denominator  
        );
    else
        return number(INFINITY,0);

}

// Division de numeros complejos
number operator%(const number &n1,const number &n2)
{
    return number( int(n1.r) % int(n2.r),0);  
}

// Math
number rad(const number &n1){
    return number(n1.r*pi/180, n1.i*pi/(double)180.0);
}

number deg(const number &n1){
    return number(n1.r*pi/180, n1.i*(double)180.0/pi);
}

number pow(number n1,number n2){
    complex<double> n = pow((complex<double>)n1, (complex<double>)n2);
    return number(n.real(),n.imag());
}

number sin(number n1){
    complex<double> n = sin((complex<double>)n1);
    return number(n.real(),n.imag());
}

number tan(number n1){
    complex<double> n = tan((complex<double>)n1);
    return number(n.real(),n.imag());
}