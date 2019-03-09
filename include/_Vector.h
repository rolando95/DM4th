#ifndef __VECTOR_H__
#define __VECTOR_H__

#include "_Number.h"
#include <vector>

class Vector{
    int count = 0;
    std::vector<Number> data;
public:
    // Inicializacion sin valores
    Vector();
    // Inicializacion con un vector como argumento en el constructor
    Vector(const Vector&);
    // Inicializacion con un numero indefinido de elementos en el constructor
    template<class ... T>
    Vector(const Number& first,T... args){    
        append(first);
        append(Vector(args...));
    }

    Vector(std::string);

    // Acceso a elemento de vector
    Number& operator[](Number);
    const Vector operator[](Vector) const;

    /* 
     Adjunta un numero en el vector
     vector.append(Number)           <- Adjunta el valor Number al final del Vector
     vector.append(Number, position) <- Adjunta el valor Number en la posicion dada dentro del Vector
    */
    Number append(const Number&,Number=-1);
    /* 
     Adjunta un vector
     vector.append(Vector)           <- Adjunta el valor Vector al final del Vector
     vector.append(Vector, position) <- Adjunta el valor Vector en la posicion dada dentro del Vector
    */
    Vector append(const Vector&,Number=-1);
    /* 
     Elimina un elemento del vector
     vector.pop()         <- Elimina el ultimo elemento del vector
     vector.pop(position) <- Elimina el elemento del vector de la posicion dada
    */
    Number pop(const Number=-1);
    // Obtiene el numero de elementos que contiene el vector
    Number length() const;
    /*
     Busca la posicion de los elementos en el vector que coincidan con el valor de argumento. 
     Devuelve un vector vacio de no encontrar coincidencias
    */
    Vector index(const Number&);
    /*
     Busca la posicion de los elementos en el vector que coincidan con alguno de los valores del vector de argumento. 
     Devuelve un vector vacio de no encontrar coincidencias
    */
    Vector index(Vector);
    /* 
     Reescala el vector con el numero de elementos dados.
     Definir un tamanio mayor al actual rellenara de ceros automaticamente, uno menor eliminara los ultimos elementos.
    */
    void resize(const Number&);
    /*
     Intercambia 2 elementos del vector
    */
    void swap(Number, Number, Number=1);

    /*
     Ordena elementos del vector
    */
    Vector sort(Number begin=0, Number end=-1);

    /*
    Invierte los elementos del vector
    */
    Vector reverse();

    // Asignacion aditiva
    Vector operator+=(Vector);
    // Asignacion sustractiva
    Vector operator-=(Vector);
    // Asignacion multiplicativa
    Vector operator*=(Number);
    // Asignacion divisiva
    Vector operator/=(Number);
    // Residuo
    Vector operator%=(Number);

    // inicio y final de vector (De utilidad para for each de c++)
    std::vector<Number>::iterator begin();
    std::vector<Number>::iterator end();
};

// Impresion en pantalla del vector
std::ostream& operator<<(std::ostream&, Vector);


// Lectura en pantalla del vector
std::istream& operator>>(std::istream&, Vector&);

// Suma de vectores
Vector operator+(Vector,Vector);

// Resta de vectores
Vector operator-(Vector,Vector);

// Producto escalar
Number operator*(Vector,Vector);

// Producto entre vector y escalar
Vector operator*(Vector,const Number&);
Vector operator*(const Number&,Vector);
// Division entre vector y escalar
Vector operator/(Vector,const Number&);
// Residuo
Vector operator%(Vector,const Number&);

Vector zeros(const Number&);
//
Vector ones(const Number&);

// range(vector, pos begin, pos end, interval)
Vector range(Vector, const Number&, const Number&, Number=1);
Vector sort(Vector);
Vector reverse(Vector);

template<class T>
/* 
    Conversion de V a array de lenguaje C.      
    Si se desea adjuntar los numeros imaginarios de V, imaginary=true       
    vToArray(array, V, tamanio del array, incluirNumerosImaginarios);

    vectorToArray(array, Vector, 2, false)
    (1+3i, 2+4i) ==> [1, 2]

    vToArray(array, V, 4, true)
    (1+3i, 2+4i) ==> [1, 2, 3, 4]

    NOTA: Es importante reservar memoria del array para la conversion 
    antes de llamar la funcion
*/
void vectorToArray(Vector &v, T *array, int n, bool imaginary=false);


template<class T>
/*
    Conversion de array en lenguaje C a V
    Si la segunda mitad del array contiene el valor imaginario de la parte real. imaginary=true
    arrayToVector(array, V, tamanio del array, incluirNumerosImaginarios);

    arrayToVector(array, V, 4, false)
    [1,2,3,4] ==> (1, 2, 3, 4)

    arrayToVector(array, V, 4, true)
    [1,2,3,4] ==> (1+3i, 2+4i)
*/
void arrayToVector(T* array, Vector &v, int n, bool imaginary=false);

#endif