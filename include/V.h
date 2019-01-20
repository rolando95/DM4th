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
        push(first);
        push(V(args...));
    }

    std::vector<N> data;

    N& operator[](N);
    /* 
     Inserta un numero en el vector
     vector.pop(N)           <- Inserta el valor N al final del vector
     vector.pop(N, position) <- Inserta el valor N en la posicion dada dentro del vector
    */
    N push(const N&,N=-1);
    V push(const V&,N=-1);
    /* 
     Elimina un elemento del vector
     vector.pop()         <- Elimina el ultimo elemento del vector
     vector.pop(position) <- Elimina el elemento del vector de la posicion dada
    */
    N pop(const N=-1);
    // Obtiene el numero de elementos que contiene el vector
    N length();
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
    n.push(first,0);
    return n;
}

V range(const N&, const N&, N=1);
#endif