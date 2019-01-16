#include "number.h"

using namespace std;

number::number(const double a,const double b)
{
    this->r = a;
    this->i = b;
}

int number::precision =  5;

double number::real(){return this->r;}
double number::real(double a){this->r = a; return this->r;}

double number::imag(){return this->i;}
double number::imag(double a){this->i = a; return this->i;}

number::operator=(double a){
    this->r = a;
    return 0;
}

// Incremento prefijo
number number::operator ++(){
    this->r += 1;
    return *this;
}

// Incremento postfijo
number number::operator ++(int){
    number a = *this;
    this->r += 1;
    return a;
}

// Decremento prefijo
number number::operator --(){
    this->r -= 1;
    return *this;
}

// Decremento postfijo
number number::operator --(int){
    number a = *this;
    this->r -= 1;
    return a;
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


number operator""_i(long double a){
    return number(0,a);
}

number operator""_i(unsigned long long int a){
    return number(0,a);
}


number operator""i(unsigned long long int a){
    return number(0,a);
}

number operator""i(long double a){
    return number(0,a);
}

number operator-(number a){
    return number(-a.r,-a.i);
}

//Impresion en pantalla de numeros complejos
ostream& operator<<(ostream& stream, number n){
    if(n.r == INFINITY) stream<<"INF";
    else if(n.r == -INFINITY) stream<<"-INF";
    else if(isnan(n.r)) stream<<"NAN";
    else{
        //Round
        n = round(n,number::precision);

        //stream
        if(n==0) stream<<"0";
        else{
            if(n.r != 0) stream<<n.r;
            if(n.i > 0 && n.r!=0)  stream<<"+";
            if(n.i != 0) {
                if(n.i != 1 && n.i != -1) stream<<n.i;
                if(n.i == -1) stream<<"-";
                stream<<"i";
            }
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
    // n/INF
    if(n2.r == INFINITY && n1.r != INFINITY)
        return number(0,0);
    else{

    double denominator = pow(n2.r,2) + pow(n2.i,2);
    // n1/n2
    if(denominator != 0)
        return number(
            (n1.r*n2.r + n1.i*n2.i)/ denominator,
            (n1.i*n2.r - n1.r*n2.i)/ denominator  
        );
    else
        // n/0
        if(n1.r != INFINITY)
            return number(INFINITY,0);
        else
            return number(NAN,0);
    }
}

// Division de numeros complejos
number operator%(const number &n1,const number &n2)
{
    return number( int(n1.r) % int(n2.r),0);  
}

// Relacional
bool operator==(const number &n1, const number &n2){
    return (n1.r==n2.r && n1.i==n2.i);
}

// Math
number rad(const number &n1){
    return number(n1.r*pi/180, n1.i*pi/(double)180.0);
}

number deg(const number &n1){
    return number(n1.r*pi/180, n1.i*(double)180.0/pi);
}

number round(const number &n, int p){
        number n1 = number(
            round(n.r * pow(10,p)) / pow(10,p),
            round(n.i * pow(10,p)) / pow(10,p)
        );
        return n1;
}

number mod(const number &n){
    return(sqrt(n.r*n.r + n.i*n.i));
}

number norm(const number &n){
    float module = mod(n).r;
    return(n.r/module, n.i/module);
}

number arg(const number &n){
    if(n.r>0 || n.i != 0){
        return number(2*atan(n.i/(sqrt(n.r*n.r + n.i*n.i)+n.r)),0);
    }else if(n.r<0 && n.i == 0){
        return number(pi,0);
    }
    return number(NAN, 0);
}

number pow(const number &n1,const number &n2){
    number exponent = n2*ln(n1);
    return pow(e,exponent.r)*(cos(exponent.i)+sin(exponent.i)*i);
}

number sqrt(const number &n){
    return pow(n,0.5);
}

number ln(const number &n){
    if(n==0) return number(-INFINITY,0);
    else{
        return log(mod(n).r)+arg(n)*i;
    }
}

number logn(const number &n, const number &base){
    return ln(n)/ln(base);
}

number sin(const number &n1){return sin(n1.r)*cosh(n1.i)+cos(n1.r)*sinh(n1.i)*i;}
number cos(const number &n1){return cos(n1.r)*cosh(n1.i)-sin(n1.r)*sinh(n1.i)*i;}
number tan(const number &n1){
    number c = cos(n1);
    if(round(c,15)==0){
        return number(INFINITY,0);
    }else
        return sin(n1)/c;}
number cot(const number &n1){return 1/tan(n1);}
number sec(const number &n1){return 1/cos(n1);}
number csc(const number &n1){return 1/sin(n1);}