#include "_Number.h"



namespace DM4th
{

//template<class TYPE>
//using enable_if_is_number = typename std::enable_if< std::is_same< TYPE, double>::value, TYPE>;

template<class T>
_number<T>::_number(T a, T b){
    this->r = (T)a;
    this->i = (T)b;
}

template<class T> template<class U>
_number<T>::_number(U a, U b){
    this->r = (T)a;
    this->i = (T)b;
}
// _number<T>::number(_number<T>  n){
//     *this = n;
// }

template<class T>
_number<T>::_number(std::string str){
    std::stringstream ss;
    ss << str;
    ss >> *this;
}

static int precision =  5;

// const double _number<T>::real()const {return this->r;}
// double _number<T>::real(double a){this->r = a; return this->r;}
// double &_number<T>::real() { return this->r; }

// const double _number<T>::imag()const {return this->i;}
// double _number<T>::imag(double a){this->i = a; return this->i;}
// double &_number<T>::imag() { return this->i; }

template<class T>
_number<T> _number<T>::operator=(T a){
    this->real(a);
    this->imag(0);
    return *this;
}

template<class T>
_number<T>::operator char*(){
    std::string str = (std::string)*this;
    char *cstr = new char[str.length()+1];
    sprintf(cstr,"%s",str.c_str());
    return cstr;
}

template<class T>
_number<T>::operator std::string(){
    std::ostringstream strs;
    strs << *this;
    std::string str = strs.str();
    return str;
}

template<class T>
void _number<T>::loadFile(std::string url){
    std::ifstream file;
    file.open(url);
    if(file.fail()) {
        *this = 0;
    }else{
        file>>*this;
    }
    file.close();
}

template<class T>
void _number<T>::saveFile(std::string url){
    std::ofstream file;
    file.open(url);
    file<<*this;
    file.close();
}

// Incremento prefijo
template<class T>
_number<T>  _number<T>::operator ++(){
    this->r += 1;
    return *this;
}
// Incremento postfijo
template<class T>
_number<T>  _number<T>::operator ++(int){
    _number<T>  a = *this;
    this->r += 1;
    return a;
}
// Decremento prefijo
template<class T>
_number<T>  _number<T>::operator --(){
    this->r -= 1;
    return *this;
}
// Decremento postfijo
template<class T>
_number<T>  _number<T>::operator --(int){
    _number<T>  a = *this;
    this->r -= 1;
    return a;
}
template<class T>
_number<T>  _number<T>::operator+=(_number<T>  n){
    *this = *this + n;
    return *this;
}

template<class T>
_number<T>  _number<T>::operator-=(_number<T>  n){
    *this = *this - n;
    return *this;
}

template<class T>
_number<T>  _number<T>::operator*=(_number<T>  n){
    *this = *this * n;
    return *this;
}

template<class T>
_number<T>  _number<T>::operator/=(_number<T>  n){
    *this = *this / n;
    return *this;
}

template<class T>
_number<T>  _number<T>::operator%=(_number<T>  n){
    *this = *this % n;
    return *this;
}

inline _number<double>  strTonumber(std::string str){
    _number<double>  result;
    std::stringstream ss(str);
    ss>>result;
    return result;
}

inline _number<double> operator""_i(long double a){
    return _number<double> (0,a);
}

inline _number<double> operator""_i(unsigned long long int a){
    return _number<double>(0,a);
}

inline _number<double> operator""i(unsigned long long int a){
    return _number<double>(0,a);
}

inline _number<double> operator""i(long double a){
    return _number<double>(0,a);
}

template<class T>
inline _number<T> operator-(_number<T>  a){
    return _number<T>(-a.real(),-a.imag());
}

//Impresion en pantalla de numeros complejos
template<class T>
std::ostream& operator<<(std::ostream& stream, _number<T>  n){
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
template<class T>
std::istream& operator>>(std::istream& stream, _number<T>  &n){
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
template<class T>
inline _number<T>  operator+(_number<T> n1,_number<T> n2){
    return _number<T>(n1.real() + n2.real(), n1.imag() + n2.imag());
}

template<class  T, typename U, enable_if_is_number(U, _number<T>) > 
inline _number<T> operator+(_number<T> n1, U n2)
{
    return n1 + _number<T>(n2);
}
template<class  U, typename T, enable_if_is_number(U, _number<T>) > 
inline _number<T> operator+(U n1, _number<T> n2)
{
     return  _number<T>(n1) + n2;
}

// Resta de numeros complejos
template<class T>
inline _number<T>  operator-(_number<T>  n1,_number<T> n2){
    return _number<T>(n1.real() - n2.real(), n1.imag() - n2.imag());
}

template<class  T, typename U, enable_if_is_number(U, _number<T>) > 
inline _number<T> operator-(_number<T> n1, U n2)
{
    return n1 - _number<T>(n2);
}
template<class  U, typename T, enable_if_is_number(U, _number<T>) > 
inline _number<T> operator-(U n1, _number<T> n2)
{
    return  _number<T>(n1) - n2;
}

template<class T>
_number<T> operator*(_number<T> n1, _number<T> n2){
    //real*real
    if(n1.imag()==0 && n2.imag()==0){
        return n1.real()*n2.real();
    }
    //im*im
    else{
        return _number<T>(
            n1.real()*n2.real() - n1.imag()*n2.imag(), 
            n1.real()*n2.imag() + n1.imag()*n2.real()
        );
    }
}

template<class  T, typename U, enable_if_is_number(U, _number<T>) > 
inline _number<T> operator*(_number<T> n1, U n2)
{
    return n1 * _number<T>(n2);
}
template<class  U, typename T, enable_if_is_number(U, _number<T>) > 
inline _number<T> operator*(U n1, _number<T> n2)
{
    return  _number<T>(n1) * n2;
}

// Division de numeros complejos
template<class T>
_number<T>  operator/(_number<T> n1, _number<T> n2){

    // n/INF
    if(n2.real() == INF && n1.real() != INF)
        return _number<T>(0,0);
    // real/real
    else if(n1.imag()==0 && n2.imag()==0 && n2.real() != 0){
        return _number<T>(n1.real()/n2.real(),0);
    // im/im
    }else{
        double denominator = std::pow(n2.real(),2) + std::pow(n2.imag(),2);
        
        // n1/n2
        if(denominator != 0)
            return _number<T>(
                (n1.real()*n2.real() + n1.imag()*n2.imag())/ denominator,
                (n1.imag()*n2.real() - n1.real()*n2.imag())/ denominator  
            );
        // n/0
        else
            if(n1.real() != INF && n1 != 0){
                if(n1.real()>0)
                    return _number<T>(INF,0);
                else    
                    return _number<T>(-INF,0);
            }else
                return _number<T>(NAN,0);
    }
}

template<class  T, typename U, enable_if_is_number(U, _number<T>) > 
inline _number<T> operator/(_number<T> n1, U n2)
{
    return n1 / _number<T>(n2);
}

template<class  U, typename T, enable_if_is_number(U, _number<T>) > 
inline _number<T> operator/(U n1, _number<T> n2)
{
    return _number<T>(n1) / n2;
}

// Residuo de numeros complejos
template<class T>
_number<T>  operator%(_number<T> n1, _number<T> n2){
    _number<T>  result;
    if(n2.real()!=0) result.real(std::fmod(n1.real(),n2.real()));
     else if(n1.real()==0) result.real(0);
    else return NAN;
    if(n2.imag()!=0) result.imag(std::fmod(n1.imag(),n2.imag()));
    else if(n1.imag()==0) result.imag(0);
    else return NAN;
    return result;
}

template<class  T, typename U, enable_if_is_number(U, _number<T>) > 
inline _number<T> operator%(_number<T> n1, U n2)
{
    return n1 % _number<T>(n2);
}

template<class  U, typename T, enable_if_is_number(U, _number<T>) > 
inline _number<T> operator%(U n1, _number<T> n2)
{
    return _number<T>(n1) % n2;
}

// Relacional
template<class T>
inline bool operator==(_number<T>  n1, _number<T>  n2){
    return (n1.real()==n2.real() && n1.imag()==n2.imag());
}

template<class  T, typename U, enable_if_is_number(U, _number<T>) > 
inline _number<T> operator==(_number<T> n1, U n2)
{
    return n1 == _number<T>(n2);
}

template<class  U, typename T, enable_if_is_number(U, _number<T>) > 
inline _number<T> operator==(U n1, _number<T> n2)
{
    return _number<T>(n1) == n2;
}

template<class T>
inline bool operator!=(_number<T> n1, _number<T>  n2){
    return (n1.real()!=n2.real() || n1.imag()!=n2.imag());
}

template<class  T, typename U, enable_if_is_number(U, _number<T>) > 
inline _number<T> operator!=(_number<T> n1, U n2)
{
    return n1 != _number<T>(n2);
}

template<class  U, typename T, enable_if_is_number(U, _number<T>) > 
inline _number<T> operator!=(U n1, _number<T> n2)
{
    return _number<T>(n1) != n2;
}

template<class T>
inline bool operator>=(_number<T>  n1, _number<T> n2){
    return n1>n2||n1==n2;
}

template<class  T, typename U, enable_if_is_number(U, _number<T>) > 
inline _number<T> operator>=(_number<T> n1, U n2)
{
    return n1 >= _number<T>(n2);
}

template<class  U, typename T, enable_if_is_number(U, _number<T>) > 
inline _number<T> operator>=(U n1, _number<T> n2)
{
    return _number<T>(n1) >= n2;
}


template<class T>
inline bool operator<=(_number<T> n1, _number<T> n2){
    return !(n1>n2);
}

template<class  T, typename U, enable_if_is_number(U, _number<T>) > 
inline _number<T> operator<=(_number<T> n1, U n2)
{
    return n1 <= _number<T>(n2);
}

template<class  U, typename T, enable_if_is_number(U, _number<T>) > 
inline _number<T> operator<=(U n1, _number<T> n2)
{
    return _number<T>(n1) <= n2;
}


template<class T>
inline bool operator>(_number<T>  n1, _number<T> n2){
    bool result=false; 
    if(n1.real() > n2.real()) result=true;
    else if(n1.real()==n2.real() && n1.imag() > n2.imag()) result=true;
    return result;
}

template<class  T, typename U, enable_if_is_number(U, _number<T>) > 
inline _number<T> operator>(_number<T> n1, U n2)
{
    return n1 > _number<T>(n2);
}

template<class  U, typename T, enable_if_is_number(U, _number<T>) > 
inline _number<T> operator>(U n1, _number<T> n2)
{
    return _number<T>(n1) > n2;
}

template<class T>
inline bool operator<(_number<T> n1, _number<T> n2){
    return !(n1>=n2);
}


template<class  T, typename U, enable_if_is_number(U, _number<T>) > 
inline _number<T> operator<(_number<T> n1, U n2)
{
    return n1 < _number<T>(n2);
}

template<class  U, typename T, enable_if_is_number(U, _number<T>) > 
inline _number<T> operator<(U n1, _number<T> n2)
{
    return _number<T>(n1) < n2;
}


// Math
template<class T>
inline _number<T>  rad(_number<T>  n1){
    return _number<T>(n1.real()*pi/180, n1.imag()*pi/(double)180.0);
}

template<class T>
inline _number<T>  deg(_number<T>  n1){
    return _number<T>(n1.real()*180/pi, n1.imag()*(double)180.0/pi);
}

template<class T>
inline _number<T>  fmod(_number<T>  n1, _number<T>  n2)
{
    return n1%n2;
}

template<class  T, typename U, enable_if_is_number(U, _number<T>) > 
inline _number<T> fmod(_number<T> n1, U n2)
{
    return fmod(n1,_number<T>(n2));
}

template<class  U, typename T, enable_if_is_number(U, _number<T>) > 
inline _number<T> fmod(U n1, _number<T> n2)
{
    return fmod(_number<T>(n1),n2);
}

template<class T>
inline _number<T>  round(_number<T>  n, int p){
        _number<T>  n1 = _number<T>(
            std::round(n.real() * std::pow(10,p)) / std::pow(10,p),
            std::round(n.imag() * std::pow(10,p)) / std::pow(10,p)
        );
        return n1;
}

template<class T>
inline _number<T>  ceil(_number<T>  n, int p){
        _number<T>  n1 = _number<T>(
            std::ceil(n.real() * std::pow(10,p)) / std::pow(10,p),
            std::ceil(n.imag() * std::pow(10,p)) / std::pow(10,p)
        );
        return n1;
}

template<class T>
inline _number<T>  floor(_number<T>  n, int p){
        _number<T>  n1 = _number<T>(
            std::floor(n.real() * std::pow(10,p)) / std::pow(10,p),
            std::floor(n.imag() * std::pow(10,p)) / std::pow(10,p)
        );
        return n1;
}

template<class T>
inline _number<T>  truncate(_number<T>  n, int p){
        _number<T>  n1 = _number<T>(
            std::trunc(n.real() * std::pow(10,p)) / std::pow(10,p),
            std::trunc(n.imag() * std::pow(10,p)) / std::pow(10,p)
        );
        return n1;
}

template<class T>
inline _number<T>  abs(_number<T>  n){
    return std::sqrt(norm(n).real());
}

template<class T>
inline _number<T>  norm(_number<T>  n){
    return n.real()*n.real() + n.imag()*n.imag();
}

template<class T>
inline _number<T>  arg(_number<T>  n){
    if(n.real()>0 || n.imag() != 0){
        return _number<T>(
            2*std::atan(n.imag()/(std::sqrt(n.real()*n.real() + n.imag()*n.imag())+n.real())), 
            0
        );
    }else if(n.real()<0 && n.imag() == 0){
        return _number<T>(pi,0);
    }
    return _number<T>(NAN, 0);
}

template<class T>
inline _number<T>  conjugate(_number<T>  n){
    return _number<T>(n.real(), -n.imag());
}

template<class T>
inline _number<T>  pow(_number<T>  n1,_number<T>  n2){
    if(n1.imag()==0 && n2.imag()==0 && n1.real() >= 0)
        return _number<T>(std::pow(n1.real(),n2.real()),0);
    else{
        _number<T>  exponent = n2*ln(n1);
        return std::pow(e,exponent.real())*(std::cos(exponent.imag())+std::sin(exponent.imag())*i);
    }
}

template<class  T, typename U, enable_if_is_number(U, _number<T>) > 
inline _number<T> pow(_number<T> n1, U n2)
{
    return pow(n1,_number<T>(n2));
}

template<class  U, typename T, enable_if_is_number(U, _number<T>) > 
inline _number<T> pow(U n1, _number<T> n2)
{
    return pow(_number<T>(n1),n2);
}

template<class T>
inline _number<T>  sqrt(_number<T>  n){
    if(n.imag()==0 && n.real()>=0) return std::sqrt(n.real()); 
    return pow(n,0.5);
}

template<class T>
inline _number<T> ln(_number<T>  n){
    if(n==0) return _number<T>(-INF,0);
    else{
        return std::log(abs(n).real())+arg(n)*i;
    }
}

template<class T>
inline _number<T>  log(_number<T>  n,_number<T>  base){return ln(n)/ln(base);}

template<class  T, typename U, enable_if_is_number(U, _number<T>) > 
inline _number<T> log(const _number<T> &n1, const U &n2)
{
    return log(n1,_number<T>(n2));
}

template<class  U, typename T, enable_if_is_number(U, _number<T>) > 
inline _number<T> log(const U &n1, const _number<T> &n2)
{
    return log(_number<T>(n1),n2);
}

template<class T>
inline _number<T>  sin(_number<T>  n){return (n.imag()==0)?std::sin(n.real()) : (pow(e,i*n)-pow(e,-i*n))/(2*i);}

template<class T>
inline _number<T>  cos(_number<T>  n){return (n.imag()==0)?std::cos(n.real()) : (pow(e,i*n)+pow(e,-i*n))/2;}

template<class T>
inline _number<T>  tan(_number<T>  n){
    _number<T>  c = cos(n);
    if(round(c,15)==0){
        return _number<T>(INF,0);
    }else
        return sin(n)/c;}

template<class T> inline _number<T>  cot(_number<T>  n){return 1/tan(n);}
template<class T> inline _number<T>  sec(_number<T>  n){return 1/cos(n);}
template<class T> inline _number<T>  csc(_number<T>  n){return 1/sin(n);}

template<class T> inline _number<T>  asin(_number<T>  n){return -i*ln(i*n+sqrt(1-n*n));}
template<class T> inline _number<T>  acos(_number<T>  n){return pi/2-asin(n);}
template<class T> inline _number<T>  atan(_number<T>  n){return i/2*(ln(1-i*n)-ln(1+i*n));}
template<class T> inline _number<T>  acot(_number<T>  n){return atan(1/n);}
template<class T> inline _number<T>  asec(_number<T>  n){return acos(1/n);}
template<class T> inline _number<T>  acsc(_number<T>  n){return asin(1/n);}

template<class T> inline _number<T>  sinh(_number<T>  n){return (pow(e,n)-pow(e,-n))/2;}
template<class T> inline _number<T>  cosh(_number<T>  n){return (pow(e,n)+pow(e,-n))/2;}
template<class T> inline _number<T>  tanh(_number<T>  n){return sinh(n)/cosh(n);}
template<class T> inline _number<T>  coth(_number<T>  n){return cosh(n)/sinh(n);}
template<class T> inline _number<T>  sech(_number<T>  n){return 1/cosh(n);}
template<class T> inline _number<T>  csch(_number<T>  n){return 1/sinh(n);}

template<class T> inline _number<T>  asinh(_number<T>  n){return ln(n+sqrt(n*n+1));}
template<class T> inline _number<T>  acosh(_number<T>  n){return ln(n+sqrt(n*n-1));}
template<class T> inline _number<T>  atanh(_number<T>  n){return 0.5*ln((1+n)/(1-n));}
template<class T> inline _number<T>  acoth(_number<T>  n){return atanh<T>(1/n);}
template<class T> inline _number<T>  asech(_number<T>  n){return acosh<T>(1/n);}
template<class T> inline _number<T>  acsch(_number<T>  n){return asinh<T>(1/n);}

}