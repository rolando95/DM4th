#include "_Number.h"

using namespace std;

Number::Number(const double a,const double b){
    this->r = a;
    this->i = b;
}

Number::Number(const Number& n){
    this->r = n.r;
    this->i = n.i;
}

int Number::precision =  5;

double Number::real(){return this->r;}
double Number::real(double a){this->r = a; return this->r;}

double Number::imag(){return this->i;}
double Number::imag(double a){this->i = a; return this->i;}

Number Number::operator=(double a){
    this->r = a;
    this->i = 0;
    return *this;
}

Number::operator char*(){
    std::string str = (string)*this;
    char *cstr = new char[str.length()+1];
    sprintf(cstr,"%s",str.c_str());
    return cstr;
}
Number::operator std::string(){
    std::ostringstream strs;
    strs << *this;
    std::string str = strs.str();
    return str;
}

// Incremento prefijo
Number Number::operator ++(){
    this->r += 1;
    return *this;
}
// Incremento postfijo
Number Number::operator ++(int){
    Number a = *this;
    this->r += 1;
    return a;
}
// Decremento prefijo
Number Number::operator --(){
    this->r -= 1;
    return *this;
}
// Decremento postfijo
Number Number::operator --(int){
    Number a = *this;
    this->r -= 1;
    return a;
}
Number Number::operator+=(Number n){
    *this = *this + n;
    return *this;
}
Number Number::operator-=(Number n){
    *this = *this - n;
    return *this;
}
Number Number::operator*=(Number n){
    *this = *this * n;
    return *this;
}
Number Number::operator/=(Number n){
    *this = *this / n;
    return *this;
}
Number Number::operator%=(Number n){
    *this = *this % n;
    return *this;
}

Number strToNumber(std::string str){
    Number result;
    stringstream ss(str);
    ss>>result;
    return result;
}

Number operator""_i(long double a){
    return Number(0,a);
}
Number operator""_i(unsigned long long int a){
    return Number(0,a);
}
Number operator""i(unsigned long long int a){
    return Number(0,a);
}
Number operator""i(long double a){
    return Number(0,a);
}
Number operator-(Number a){
    return Number(-a.r,-a.i);
}
//Impresion en pantalla de numeros complejos
std::ostream& operator<<(std::ostream& stream, Number n){
    if(n.r == INF) stream<<"INF";
    else if(n.r == -INF) stream<<"-INF";
    else if(isnan(n.r)) stream<<"NAN";
    else{
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
std::istream& operator>>(std::istream& stream, Number &n){
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
            if(nextState==9) n.i =  strtod(value,NULL);
            else n.r = strtod(value,NULL);
            count = 0;

            //Vuelve a estados anteriores si es un numero complejo
            if(next=='\n' || next==',') nextState = -1;
            else if(next==' ') nextState = 1;
            else if(next=='+'||next=='-')nextState = 2;
        }

        if(nextState >= 0 && count<100 ){
            state = nextState;
            if(next!='\n' && next!=',') stream>>value[count++];
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
Number operator+(const Number &n1,const Number &n2){
    return Number(n1.r + n2.r, n1.i + n2.i);
}
// Resta de numeros complejos
Number operator-(const Number &n1,const Number &n2){
    return Number(n1.r - n2.r, n1.i - n2.i);
}
// Multiplicacion de numeros complejos
Number operator*(const Number &n1,const Number &n2){
    //real*real
    if(n1.i==0 && n2.i==0){
        return n1.r*n2.r;
    }
    //im*im
    else{
        return Number(
            n1.r*n2.r - n1.i*n2.i, 
            n1.r*n2.i + n1.i*n2.r
        );
    }
}
// Division de numeros complejos
Number operator/(const Number &n1,const Number &n2){

    // n/INF
    if(n2.r == INF && n1.r != INF)
        return Number(0,0);
    // real/real
    else if(n1.i==0 && n2.i==0 && n2.r != 0){
        return Number(n1.r/n2.r,0);
    // im/im
    }else{
        double denominator = pow(n2.r,2) + pow(n2.i,2);
        
        // n1/n2
        if(denominator != 0)
            return Number(
                (n1.r*n2.r + n1.i*n2.i)/ denominator,
                (n1.i*n2.r - n1.r*n2.i)/ denominator  
            );
        // n/0
        else
            if(n1.r != INF && n1 != 0){
                if(n1.r>0)
                    return Number(INF,0);
                else    
                    return Number(-INF,0);
            }else
                return Number(NAN,0);
    }
}
// Residuo de numeros complejos (Solo trabaja como numeros enteros)
Number operator%(const Number &n1,const Number &n2){
    if(floor(n1.r)==n1.r && floor(n2.r)==n2.r && n1.i==0 && n2.i==0){
        if(n2.r != 0)
            return int(n1.r)%int(n2.r);
        else
            return 0;
    }else{
        return 0;
    }
}

// Relacional
bool operator==(const Number &n1, const Number &n2){
    return (n1.r==n2.r && n1.i==n2.i);
}
bool operator!=(const Number &n1, const Number &n2){
    return (n1.r!=n2.r || n1.i!=n2.i);
}
bool operator>(const Number &n1, const Number &n2){
    bool result=false; 
    if(n1.r > n2.r) result=true;
    else if(n1.r==n2.r && n1.i > n2.i) result=true;
    return result;
}
bool operator<(const Number &n1, const Number &n2){
    return !(n1>=n2);
}
bool operator>=(const Number &n1, const Number &n2){
    return n1>n2||n1==n2;
}
bool operator<=(const Number &n1, const Number &n2){
    return !(n1>n2);
}

// Math
Number rad(const Number &n1){
    return Number(n1.r*pi/180, n1.i*pi/(double)180.0);
}
Number deg(const Number &n1){
    return Number(n1.r*180/pi, n1.i*(double)180.0/pi);
}
Number round(const Number &n, int p){
        Number n1 = Number(
            round(n.r * pow(10,p)) / pow(10,p),
            round(n.i * pow(10,p)) / pow(10,p)
        );
        return n1;
}
Number abs(const Number &n){
    return sqrt(norm(n));
}
Number norm(const Number &n){
    return n.r*n.r + n.i*n.i;
}
Number arg(const Number &n){
    if(n.r>0 || n.i != 0){
        return Number(2*atan(n.i/(sqrt(n.r*n.r + n.i*n.i)+n.r)),0);
    }else if(n.r<0 && n.i == 0){
        return Number(pi,0);
    }
    return Number(NAN, 0);
}
Number conjugate(const Number &n){
    return Number(n.r, -n.i);
}
Number pow(const Number &n1,const Number &n2){
    if(n1.i==0 && n2.i==0 && n1.r >= 0)
        return pow(n1.r,n2.r);
    else{
        Number exponent = n2*ln(n1);
        return pow(e,exponent.r)*(cos(exponent.i)+sin(exponent.i)*i);
    }
}
Number sqrt(const Number &n){
    return pow(n,0.5);
}
Number ln(const Number &n){
    if(n==0) return Number(-INF,0);
    else{
        return log(abs(n).r)+arg(n)*i;
    }
}
Number log(const Number &n, const Number &base){return ln(n)/ln(base);}

Number sin(const Number &n){return (n.i==0)?sin(n.r) : (pow(e,i*n)-pow(e,-i*n))/(2*i);}
Number cos(const Number &n){return (n.i==0)?cos(n.r) : (pow(e,i*n)+pow(e,-i*n))/2;}
Number tan(const Number &n){
    Number c = cos(n);
    if(round(c,15)==0){
        return Number(INF,0);
    }else
        return sin(n)/c;}
Number cot(const Number &n){return 1/tan(n);}
Number sec(const Number &n){return 1/cos(n);}
Number csc(const Number &n){return 1/sin(n);}

Number asin(const Number &n){return -i*ln(i*n+sqrt(1-n*n));}
Number acos(const Number &n){return pi/2-asin(n);}
Number atan(const Number &n){return i/2*(ln(1-i*n)-ln(1+i*n));}
Number acot(const Number &n){return atan(1/n);}
Number asec(const Number &n){return acos(1/n);}
Number acsc(const Number &n){return asin(1/n);}

Number sinh(const Number &n){return (pow(e,n)-pow(e,-n))/2;}
Number cosh(const Number &n){return (pow(e,n)+pow(e,-n))/2;}
Number tanh(const Number &n){return sinh(n)/cosh(n);}
Number coth(const Number &n){return cosh(n)/sinh(n);}
Number sech(const Number &n){return 1/cosh(n);}
Number csch(const Number &n){return 1/sinh(n);}

Number asinh(const Number &n){return ln(n+sqrt(n*n+1));}
Number acosh(const Number &n){return ln(n+sqrt(n*n-1));}
Number atanh(const Number &n){return 0.5*ln((1+n)/(1-n));}
Number acoth(const Number &n){return atanh(1/n);}
Number asech(const Number &n){return acosh(1/n);}
Number acsch(const Number &n){return asinh(1/n);}