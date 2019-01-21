#include "N.h"
#include <vector>

#ifndef _V_H
#define _V_H

class V{
    int count = 0;
public:
    V();
    V(const V&);
    V(const N& first,auto... args){    
        append(first);
        append(V(args...));
    }

    std::vector<N> data;


    N& operator[](N);
    /* 
     Adjunta un numero en el vector
     vector.append(N)           <- Adjunta el valor N al final del vector
     vector.append(N, position) <- Adjunta el valor N en la posicion dada dentro del vector
    */
    N append(const N&,N=-1);
    /* 
     Adjunta un vector
     vector.append(V)           <- Adjunta el valor V al final del vector
     vector.append(V, position) <- Adjunta el valor V en la posicion dada dentro del vector
    */
    V append(const V&,N=-1);
    /* 
     Elimina un elemento del vector
     vector.pop()         <- Elimina el ultimo elemento del vector
     vector.pop(position) <- Elimina el elemento del vector de la posicion dada
    */
    N pop(const N=-1);
    // Obtiene el numero de elementos que contiene el vector
    N length();
    /*
     Busca la posicion de los elementos en el vector que coincidan con el valor de argumento. 
     Devuelve un vector vacio de no encontrar coincidencias
    */
    V find(const N&);
    /*
     Busca la posicion de los elementos en el vector que coincidan con alguno de los valores del vector de argumento. 
     Devuelve un vector vacio de no encontrar coincidencias
    */
    V find(V);
    /* 
     Reescala el vector con el numero de elementos dados.
     Definir un tamanio mayor al actual rellenara de ceros automaticamente, uno menor eliminara los ultimos elementos.
    */
    void resize(const N&);
};

// Impresion en pantalla de vector
ostream& operator<<(ostream&, V);


// Lectura en pantalla del vector
istream& operator>>(istream&, V&);

V list();
V list(const N& first,auto... args){
    V n = list(args ...);
    n.append(first,0);
    return n;
}

V range(const N&, const N&, N=1);


/* 
    Conversion de V a array de lenguaje C 
    Si se desea adjuntar los numeros imaginarios de V, imaginary=true
    vToArray(array, V, incluirNumerosImaginarios?);

    vToArray(array, V, false)
    (1+3i, 2+4i) ==> [1, 2]

    vToArray(array, V, true)
    (1+3i, 2+4i) ==> [1, 2, 3, 4]

    NOTA: Es importante reservar memoria del array para la conversion 
    antes de llamar la funcion
*/
template<class T>
void vToArray(V &v, T *array, bool imaginary=false){
    int size, midSize;
    if(imaginary){
        size = v.length().r*2;
        midSize = size/2;
    }else{
        size = v.length().r;
        midSize = size;
    }

    for(int j=0; j<size; j++){
        if(j<midSize){ 
            array[j] = (T)v[j].r;
        }
        else array[j] = (T)v[j-midSize].i;
    }
}

/*
    Conversion de array en lenguaje C a V
    Si la segunda mitad del array contiene el valor imaginario de la parte real. imaginary=true
    arrayToV(array, V, tamanio, tieneNumerosImaginarios?);

    arrayToV(array, V, 4, false)
    [1,2,3,4] ==> (1, 2, 3, 4)

    arrayToV(array, V, 4, true)
    [1,2,3,4] ==> (1+3i, 2+4i)
*/
template<class T>
void arrayToV(T* array, V &v, int N, bool imaginary=false){
    v.resize(0);
    if(!imaginary){
        for(int j=0; j<N; j++){
            v.append(array[j]);
        }
    }else{
        for(int j=0; j<N/2; j++){
            v.append(array[j]+array[j+N/2]*i);
        }
    }
}
#endif