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
#endif