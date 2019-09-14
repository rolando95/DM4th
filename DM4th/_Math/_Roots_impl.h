#pragma once

#include "_Roots.h"

namespace DM4th
{

// cuadratica
template<class A, class B, class C>
NDArray<number> quadratic(const A &a, const B &b, const C &c){
    NDArray<number> roots;
    number square = sqrt(b*b - 4*a*c);
    roots.push((-b+square)/(2*a));
    roots.push((-b-square)/(2*a));
    return roots;
}


template<class T>
NDArray<number> bairstowsMethod(NDArray<T> v, number r, number s, number maxIter, number tolerance){

    // Conserva los valores semilla iniciales para futuras iteraciones
    number ra = r; 
    number sa = s;
    NDArray<number> roots;
    number degree = v.size()-1;
    
    if(degree==1) roots = items<number>( -v.item(1)/v.item(0) ); // Polinomio de grado 1
    else if(degree==2) roots = quadratic<number,number,number>(v(0),v(1),v(2)); // Polinomio de grado 2
    else if(degree>2){ // Polinomio de grado superior a 2
        
        // 
        NDArray<number> b; b.resize(v.size());
        NDArray<number> c; c.resize(v.size()-1);
        number errorR, errorS;
        number dr, ds;

        // Empieza el ciclo para calcular las nuevas raices
        for(int k=0; k<maxIter; ++k){
            // Calcula los coeficientes de b
            b(0) = v(0);
            b(1) = v(1) + b(0)*r;
            for(int j=2; j<=degree; ++j){
                b(j) = v(j) + b(j-1)*r + b(j-2)*s;
            }

            // Calcula los coeficientes de c
            c(0) = b(0);
            c(1) = b(1) + c(0)*r;
            for(int j=2; j< degree; ++j){
                c(j) = b(j) + c(j-1)*r + c(j-2)*s;  
            }

            // Calcula delta s y delta r
            dr = (b(degree)  *c(degree-3) - b(degree-1)*c(degree-2))/
                (c(degree-2)*c(degree-2) - c(degree-1)*c(degree-3));
            ds = (b(degree-1)*c(degree-1) - b(degree)  *c(degree-2))/
                (c(degree-2)*c(degree-2) - c(degree-1)*c(degree-3));
            
            // Calcula el error
            errorS = (s==0)?(ds+0.01)/(s+0.01):ds/s;
            errorR = (r==0)?(dr+0.01)/(r+0.01):dr/r;

            // Rompe el ciclo si el error es menor a la tolerancia, de otro modo asigna la nueva r y s
            if(abs(errorS)<tolerance && abs(errorR)<tolerance){
                roots = quadratic(1,-r,-s); // Obtiene las nuevas raices
                break;
            }else{
                r = r+dr; s=s+ds;
            }
        }

        b.resize(b.size()-2);
        roots.pushArray(bairstowsMethod(b,ra,sa,maxIter,tolerance)); // Adjunta las raices que calculara en la llamada recursiva

    }

    return roots;
}

}