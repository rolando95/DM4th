#include <math.h>
using namespace std;

class complex {
public:
    double r, i;
    complex(const double a=0,const double b=0);
    operator=(long double a);
};

// Suma de numeros complejos
complex operator+(const complex &n1,const complex &n2);

// Resta de numeros complejos
complex operator-(const complex &n1,const complex &n2);

// Multiplicacion de numeros complejos
complex operator*(const complex &n1,const complex &n2);

// Division de numeros complejos
complex operator/(const complex &n1,const complex &n2);


complex operator""i(long double a);