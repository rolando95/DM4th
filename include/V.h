#include "N.h"
#include <vector>

#ifndef _V_H
#define _V_H

class V{
    int count = 0;

public:
    V();
    std::vector<N> data;

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


V array();
V array(const N& first,auto... args){
    V n = array(args ...);
    n.push(first,0);
    return n;
}
#endif