using namespace std;

class complex {
public:
    double r, i;
    // constructor parametrizado
    complex(const double a=0,const double b=0);
    operator=(long double a);
};

// Sobrecarga del operador +
complex operator+(const complex &p1,const complex &p2);


complex operator""i(long double a);