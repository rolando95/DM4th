#ifndef __QUATERNION_H__
#define __QUATERNION_H__
#include "_Matrix.h"

class Quaternion: protected _ArrayManager<Number>{
public:
    using _ArrayManager::operator=;

    Quaternion();
    Quaternion(const Quaternion&);
    Quaternion(Vector v);
    Quaternion(Number n1, Number n2, Number n3, Number n4);

    inline Number q0(){return _data->array[0];}
    inline Number q1(){return _data->array[1];}
    inline Number q2(){return _data->array[2];}
    inline Number q3(){return _data->array[3];}
    
    inline Number q0(Number n){_data->array[0]=n; return n;}
    inline Number q1(Number n){_data->array[1]=n; return n;}
    inline Number q2(Number n){_data->array[2]=n; return n;}
    inline Number q3(Number n){_data->array[3]=n; return n;}

    inline Number& operator[](Number n){
        int pos = (int)n;
        assert(pos>=0 && pos<*_rows);
        return _data->array[pos];
    }
    
    Quaternion getCopy();

    void operator+=(Quaternion);
    void operator-=(Quaternion);
    void operator*=(Quaternion);
    Quaternion normalize();
};

Quaternion operator*(Quaternion, Quaternion);
Quaternion operator+(Quaternion, Quaternion);
Quaternion operator-(Quaternion, Quaternion);

// Impresion en pantalla de la Matriz
std::ostream& operator<<(std::ostream&, Quaternion);

// Lectura en pantalla de la Matriz
std::istream& operator>>(std::istream&, Quaternion&);
#endif