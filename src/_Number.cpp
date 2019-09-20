#include "../DM4th/Number.h"

namespace DM4th
{

number::number(const double a,const double b){
    this->r = a;
    this->i = b;
}

// number::number(number n){
//     *this = n;
// }

number::number(std::string str){
    std::stringstream ss;
    ss << str;
    ss >> *this;
}

int precision =  5;

// const double number::real()const {return this->r;}
// double number::real(double a){this->r = a; return this->r;}
// double &number::real() { return this->r; }

// const double number::imag()const {return this->i;}
// double number::imag(double a){this->i = a; return this->i;}
// double &number::imag() { return this->i; }

number number::operator=(double a){
    this->real(a);
    this->imag(0);
    return *this;
}

number::operator char*(){
    std::string str = (std::string)*this;
    char *cstr = new char[str.length()+1];
    sprintf(cstr,"%s",str.c_str());
    return cstr;
}

number::operator std::string(){
    std::ostringstream strs;
    strs << *this;
    std::string str = strs.str();
    return str;
}

void number::loadFile(std::string url){
    std::ifstream file;
    file.open(url);
    if(file.fail()) {
        *this = 0;
    }else{
        file>>*this;
    }
    file.close();
}
void number::saveFile(std::string url){
    std::ofstream file;
    file.open(url);
    file<<*this;
    file.close();
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
number number::operator+=(number n){
    *this = *this + n;
    return *this;
}
number number::operator-=(number n){
    *this = *this - n;
    return *this;
}
number number::operator*=(number n){
    *this = *this * n;
    return *this;
}
number number::operator/=(number n){
    *this = *this / n;
    return *this;
}
number number::operator%=(number n){
    *this = *this % n;
    return *this;
}

number strTonumber(std::string str){
    number result;
    std::stringstream ss(str);
    ss>>result;
    return result;
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
    return number(-a.real(),-a.imag());
}
//Impresion en pantalla de numeros complejos
std::ostream& operator<<(std::ostream& stream, number n){
    if(n.real() == INF) stream<<"INF";
    else if(n.real() == -INF) stream<<"-INF";
    else if(std::isnan(n.real())) stream<<"NAN";
    else{
        n = round(n,precision); // Es necesario corregir problemas de redondeo
        //stream
        if(n==0) stream<<"0";
        else{
            if(n.real() != 0) stream<<n.real();
            if(n.imag() > 0 && n.real()!=0)  stream<<"+";
            if(n.imag() != 0) {
                if(n.imag() != 1 && n.imag() != -1) stream<<n.imag();
                if(n.imag() == -1) stream<<"-";
                stream<<"i";
            }
        }
    }
    return stream;
}
//Entrada de numeros complejos
std::istream& operator>>(std::istream& stream, number &n){
    n=0;
    int state = 1;
    int nextState;
    char next;
    int count=0;
    char value[100];
    bool ok = true;
    //stream>>std::ws;
    //Maquina de estado para la lectura de valores complejos
    while(ok){
        if(stream.peek()==' ')stream>>std::ws;
        next = stream.peek();
        nextState = -1;
        switch (state){
            case 1:
                if(next==' ') nextState = 1;
                if(next=='+' || next=='-') nextState = 2;
                else if(next=='.') nextState = 3;
                else if(next>='0' && next<='9') nextState = 4;
                else if(next=='i'){ value[count++] = '1'; nextState = 9;}
            break;

            case 2:
                if(next=='.') nextState = 3;
                else if(next>='0' && next<='9') nextState = 4;
                else if(next=='i'){ value[count++] = '1'; nextState = 9;}
            break;

            case 3:
                if(next>='0' && next<='9') nextState = 5;
            break;

            case 4:
                if(next=='.')nextState = 3;
                else if(next>='0' && next<='9') nextState = 4;
                else if(next=='e' || next=='E') nextState = 6;
                else if(next=='i') nextState = 9;
                else nextState = 10;
            break;
        
            case 5:
                if(next>='0'&& next<='9') nextState = 5;
                else if(next=='e' || next=='E') nextState = 6;
                else if(next=='i') nextState = 9;
                else nextState = 10;
            break;

            case 6:
                if(next=='+'||next=='-') nextState = 7;
                else if(next>='0' && next<='9') nextState = 8;
            break;

            case 7:
                if(next>='0' && next<='9') nextState = 8;
            break;

            case 8:
                if(next>='0' && next<='9') nextState = 8;
                else if(next=='i') nextState = 9;
                else nextState = 10;
            break;

        }
        //std::cout<<state<<" '"<<next<<"' "<<nextState<<std::endl;
        //El proximo estado es de aceptacion
        if(nextState==9 || nextState==10){
            value[count] = '\0';
            if(nextState==9) n.imag(strtod(value,NULL));
            else n.real(strtod(value,NULL));
            count = 0;

            //Vuelve a estados anteriores si es un numero complejo
            if(next=='\n' || next==',') nextState = -1;
            else if(next==' ') nextState = 1;
            else if(next=='+'||next=='-')nextState = 2;
        }

        if(nextState >= 0 && count<100 ){
            state = nextState;
            if(next!='\n' && next!=',' && next!=']') stream>>value[count++];
            else value[count++] = '\0'; // Fuerza fin de lectura de numero complejo
        }else{
            ok = false;
        }
    }
    if(stream.peek()==' ')stream>>std::ws;
    if(stream.peek()=='\n') stream.get();
    return stream;

}
// Suma de numeros complejos
number operator+(const number &n1,const number &n2){
    return number(n1.real() + n2.real(), n1.imag() + n2.imag());
}
// Resta de numeros complejos
number operator-(const number &n1,const number &n2){
    return number(n1.real() - n2.real(), n1.imag() - n2.imag());
}
// // Multiplicacion de numeros complejos
// number operator*(const number &n1,const number &n2){
//     //real*real
//     if(n1.imag()==0 && n2.imag()==0){
//         return n1.real()*n2.real();
//     }
//     //im*im
//     else{
//         return number(
//             n1.real()*n2.real() - n1.imag()*n2.imag(), 
//             n1.real()*n2.imag() + n1.imag()*n2.real()
//         );
//     }
// }
// Division de numeros complejos
number operator/(const number &n1,const number &n2){

    // n/INF
    if(n2.real() == INF && n1.real() != INF)
        return number(0,0);
    // real/real
    else if(n1.imag()==0 && n2.imag()==0 && n2.real() != 0){
        return number(n1.real()/n2.real(),0);
    // im/im
    }else{
        double denominator = std::pow(n2.real(),2) + std::pow(n2.imag(),2);
        
        // n1/n2
        if(denominator != 0)
            return number(
                (n1.real()*n2.real() + n1.imag()*n2.imag())/ denominator,
                (n1.imag()*n2.real() - n1.real()*n2.imag())/ denominator  
            );
        // n/0
        else
            if(n1.real() != INF && n1 != 0){
                if(n1.real()>0)
                    return number(INF,0);
                else    
                    return number(-INF,0);
            }else
                return number(NAN,0);
    }
}
// Residuo de numeros complejos
number operator%(const number &n1,const number &n2){
    number result;
    if(n2.real()!=0) result.real(std::fmod(n1.real(),n2.real()));
     else if(n1.real()==0) result.real(0);
    else return NAN;
    if(n2.imag()!=0) result.imag(std::fmod(n1.imag(),n2.imag()));
    else if(n1.imag()==0) result.imag(0);
    else return NAN;
    return result;
}

// Relacional
bool operator==(const number &n1, const number &n2){
    return (n1.real()==n2.real() && n1.imag()==n2.imag());
}
bool operator!=(const number &n1, const number &n2){
    return (n1.real()!=n2.real() || n1.imag()!=n2.imag());
}
bool operator>(const number &n1, const number &n2){
    bool result=false; 
    if(n1.real() > n2.real()) result=true;
    else if(n1.real()==n2.real() && n1.imag() > n2.imag()) result=true;
    return result;
}
bool operator<(const number &n1, const number &n2){
    return !(n1>=n2);
}
bool operator>=(const number &n1, const number &n2){
    return n1>n2||n1==n2;
}
bool operator<=(const number &n1, const number &n2){
    return !(n1>n2);
}

// Math
number rad(number n1){
    return number(n1.real()*pi/180, n1.imag()*pi/(double)180.0);
}
number deg(number n1){
    return number(n1.real()*180/pi, n1.imag()*(double)180.0/pi);
}

number fmod(number n1, number n2)
{
    return n1%n2;
}

number round(number n, int p){
        number n1 = number(
            std::round(n.real() * std::pow(10,p)) / std::pow(10,p),
            std::round(n.imag() * std::pow(10,p)) / std::pow(10,p)
        );
        return n1;
}

number ceil(number n, int p){
        number n1 = number(
            std::ceil(n.real() * std::pow(10,p)) / std::pow(10,p),
            std::ceil(n.imag() * std::pow(10,p)) / std::pow(10,p)
        );
        return n1;
}

number floor(number n, int p){
        number n1 = number(
            std::floor(n.real() * std::pow(10,p)) / std::pow(10,p),
            std::floor(n.imag() * std::pow(10,p)) / std::pow(10,p)
        );
        return n1;
}

number truncate(number n, int p){
        number n1 = number(
            std::trunc(n.real() * std::pow(10,p)) / std::pow(10,p),
            std::trunc(n.imag() * std::pow(10,p)) / std::pow(10,p)
        );
        return n1;
}
number abs(number n){
    return sqrt(norm(n));
}
number norm(number n){
    return n.real()*n.real() + n.imag()*n.imag();
}
number arg(number n){
    if(n.real()>0 || n.imag() != 0){
        return number(
            2*std::atan(n.imag()/(std::sqrt(n.real()*n.real() + n.imag()*n.imag())+n.real())), 
            0
        );
    }else if(n.real()<0 && n.imag() == 0){
        return number(pi,0);
    }
    return number(NAN, 0);
}
number conjugate(number n){
    return number(n.real(), -n.imag());
}
number pow(number n1,number n2){
    if(n1.imag()==0 && n2.imag()==0 && n1.real() >= 0)
        return number(std::pow(n1.real(),n2.real()),0);
    else{
        number exponent = n2*ln(n1);
        return std::pow(e,exponent.real())*(std::cos(exponent.imag())+std::sin(exponent.imag())*i);
    }
}
number sqrt(number n){
    return pow(n,0.5);
}
number ln(number n){
    if(n==0) return number(-INF,0);
    else{
        return std::log(abs(n).real())+arg(n)*i;
    }
}
number log(number n,number base){return ln(n)/ln(base);}

number sin(number n){return (n.imag()==0)?std::sin(n.real()) : (pow(e,i*n)-pow(e,-i*n))/(2*i);}
number cos(number n){return (n.imag()==0)?std::cos(n.real()) : (pow(e,i*n)+pow(e,-i*n))/2;}
number tan(number n){
    number c = cos(n);
    if(round(c,15)==0){
        return number(INF,0);
    }else
        return sin(n)/c;}
number cot(number n){return 1/tan(n);}
number sec(number n){return 1/cos(n);}
number csc(number n){return 1/sin(n);}

number asin(number n){return -i*ln(i*n+sqrt(1-n*n));}
number acos(number n){return pi/2-asin(n);}
number atan(number n){return i/2*(ln(1-i*n)-ln(1+i*n));}
number acot(number n){return atan(1/n);}
number asec(number n){return acos(1/n);}
number acsc(number n){return asin(1/n);}

number sinh(number n){return (pow(e,n)-pow(e,-n))/2;}
number cosh(number n){return (pow(e,n)+pow(e,-n))/2;}
number tanh(number n){return sinh(n)/cosh(n);}
number coth(number n){return cosh(n)/sinh(n);}
number sech(number n){return 1/cosh(n);}
number csch(number n){return 1/sinh(n);}

number asinh(number n){return ln(n+sqrt(n*n+1));}
number acosh(number n){return ln(n+sqrt(n*n-1));}
number atanh(number n){return 0.5*ln((1+n)/(1-n));}
number acoth(number n){return atanh(1/n);}
number asech(number n){return acosh(1/n);}
number acsch(number n){return asinh(1/n);}

}