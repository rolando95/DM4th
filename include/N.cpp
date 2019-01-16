#include "N.h"

using namespace std;

N::N(const double a,const double b)
{
    this->r = a;
    this->i = b;
}

int N::precision =  5;

double N::real(){return this->r;}
double N::real(double a){this->r = a; return this->r;}

double N::imag(){return this->i;}
double N::imag(double a){this->i = a; return this->i;}

N::operator=(double a){
    this->r = a;
    return 0;
}

// Incremento prefijo
N N::operator ++(){
    this->r += 1;
    return *this;
}

// Incremento postfijo
N N::operator ++(int){
    N a = *this;
    this->r += 1;
    return a;
}

// Decremento prefijo
N N::operator --(){
    this->r -= 1;
    return *this;
}

// Decremento postfijo
N N::operator --(int){
    N a = *this;
    this->r -= 1;
    return a;
}

N::operator+=(N n){
    *this = *this + n;
}

N::operator-=(N n){
    *this = *this - n;
}

N::operator*=(N n){
    *this = *this * n;
}

N::operator/=(N n){
    *this = *this / n;
}

N::operator%=(N n){
    *this = *this % n;
}


N operator""_i(long double a){
    return N(0,a);
}

N operator""_i(unsigned long long int a){
    return N(0,a);
}


N operator""i(unsigned long long int a){
    return N(0,a);
}

N operator""i(long double a){
    return N(0,a);
}

N operator-(N a){
    return N(-a.r,-a.i);
}

//Impresion en pantalla de numeros complejos
ostream& operator<<(ostream& stream, N n){
    if(n.r == INFINITY) stream<<"INF";
    else if(n.r == -INFINITY) stream<<"-INF";
    else if(isnan(n.r)) stream<<"NAN";
    else{
        //Round
        n = round(n,N::precision);

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
istream& operator>>(istream& stream, N &n){
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
N operator+(const N &n1,const N &n2)
{
    return N(n1.r + n2.r, n1.i + n2.i);
}

// Resta de numeros complejos
N operator-(const N &n1,const N &n2)
{
    return N(n1.r - n2.r, n1.i - n2.i);
}

// Multiplicacion de numeros complejos
N operator*(const N &n1,const N &n2)
{
    //real*real
    if(n1.i==0 && n2.i==0){
        return n1.r*n2.r;
    }
    //im*im
    else{
        return N(
            n1.r*n2.r - n1.i*n2.i, 
            n1.r*n2.i + n1.i*n2.r
        );
    }
}

// Division de numeros complejos
N operator/(const N &n1,const N &n2)
{
    // n/INF
    if(n2.r == INFINITY && n1.r != INFINITY)
        return N(0,0);
    // real/real
    else if(n1.i==0 && n2.i==0 && n2.r != 0){
        return N(n1.r/n2.r,0);
    // im/im
    }else{
        double denominator = pow(n2.r,2) + pow(n2.i,2);
        
        // n1/n2
        if(denominator != 0)
            return N(
                (n1.r*n2.r + n1.i*n2.i)/ denominator,
                (n1.i*n2.r - n1.r*n2.i)/ denominator  
            );
        // n/0
        else
            if(n1.r != INFINITY)
                return N(INFINITY,0);
            else
                return N(NAN,0);
    }
}

// Residuo de numeros complejos (Solo trabaja como numeros enteros)
N operator%(const N &n1,const N &n2)
{
    if(floor(n1.r)==n1.r && floor(n2.r)==n2.r && n1.i==0 && n2.i==0){
        if(n2.r != 0)
            return int(n1.r)%int(n2.r);
        else
            return 0;
    }else{
        return 0;
    }
    /*
    if(int(n2.r) != 0)
        return N( int(n1.r) % int(n2.r),0);  
    else
        return 0;
    */
}

// Relacional
bool operator==(const N &n1, const N &n2){
    return (n1.r==n2.r && n1.i==n2.i);
}

// Math
N rad(const N &n1){
    return N(n1.r*pi/180, n1.i*pi/(double)180.0);
}

N deg(const N &n1){
    return N(n1.r*pi/180, n1.i*(double)180.0/pi);
}

N round(const N &n, int p){
        N n1 = N(
            round(n.r * pow(10,p)) / pow(10,p),
            round(n.i * pow(10,p)) / pow(10,p)
        );
        return n1;
}

N abs(const N &n){
    return N(abs(n.r),abs(n.i));
}

N mod(const N &n){
    return(sqrt(n.r*n.r + n.i*n.i));
}

N norm(const N &n){
    float module = mod(n).r;
    return(n.r/module, n.i/module);
}

N arg(const N &n){
    if(n.r>0 || n.i != 0){
        return N(2*atan(n.i/(sqrt(n.r*n.r + n.i*n.i)+n.r)),0);
    }else if(n.r<0 && n.i == 0){
        return N(pi,0);
    }
    return N(NAN, 0);
}

N pow(const N &n1,const N &n2){
    if(n1.i==0 && n2.i==0 && n1.r >= 0)
        return pow(n1.r,n2.r);
    else{
        N exponent = n2*ln(n1);
        return pow(e,exponent.r)*(cos(exponent.i)+sin(exponent.i)*i);
    }
}

N sqrt(const N &n){
    return pow(n,0.5);
}

N ln(const N &n){
    if(n==0) return N(-INFINITY,0);
    else{
        return log(mod(n).r)+arg(n)*i;
    }
}

N logn(const N &n, const N &base){
    return ln(n)/ln(base);
}

N sin(const N &n){return (n.i==0)?sin(n.r) : sin(n.r)*cosh(n.i)+cos(n.r)*sinh(n.i)*i;}
N cos(const N &n){return (n.i==0)?cos(n.r) : cos(n.r)*cosh(n.i)-sin(n.r)*sinh(n.i)*i;}
N tan(const N &n){
    N c = cos(n);
    if(round(c,15)==0){
        return N(INFINITY,0);
    }else
        return sin(n)/c;}
N cot(const N &n){return 1/tan(n);}
N sec(const N &n){return 1/cos(n);}
N csc(const N &n){return 1/sin(n);}

// Aproximaciones de raices
N newtonRaphson(function f, function fd, N x1, N maxIter, N tolerance){
    x1 = x1.r;
    N y1 = (x1.i==0)?i:x1.i;

    N err(INFINITY,INFINITY);
    for(int n=0; n<maxIter.r && abs(f(x1)).r>tolerance.r && abs(f(y1)).r>tolerance.r ; n++){
        x1 = x1 - f(x1)/fd(x1);
        y1 = y1 - f(y1)/fd(y1);
    }
    if(f(x1).r > f(y1).r) x1 = y1;
    return x1;
}

/*
N secantMethod(function f, N x0,N x1, N maxIter, N tolerance){
    return x1;
}*/