#pragma once

#include "Roots.h"


namespace DM4th
{

    // cuadratica
    template<class A, class B, class C>
    NDArray<number> quadratic(const A &a, const B &b, const C &c) {
        NDArray<number> roots;
        roots._resizeEmpty(2);
        number square = sqrt(b*b - 4*a*c);
        roots(0) = (-b+square)/(2*a);
        roots(1) = (-b-square)/(2*a);
        return roots;
    }


    template<class T>
    NDArray<number> bairstowsMethod(NDArray<T> v, number r, number s, number maxIter, number tolerance) {

        // Conserva los valores semilla iniciales para futuras iteraciones
        number ra = r;
        number sa = s;
        NDArray<number> roots;
        number degree = v.size()-1;

        if (degree==1) roots = items<number>(-v.item(1)/v.item(0)); // Polinomio de grado 1
        else if (degree==2) roots = quadratic<number, number, number>(v(0), v(1), v(2)); // Polinomio de grado 2
        else if (degree>2) { // Polinomio de grado superior a 2

            // 
            NDArray<number> b; b.resize(v.size());
            NDArray<number> c; c.resize(v.size()-1);
            number errorR, errorS;
            number dr, ds;

            // Empieza el ciclo para calcular las nuevas raices
            for (int k=0; k<maxIter; ++k) {
                // Calcula los coeficientes de b
                b(0) = v(0);
                b(1) = v(1) + b(0)*r;

                for (int j=2; j<=degree; ++j) {
                    b(j) = v(j) + b(j-1)*r + b(j-2)*s;
                }

                // Calcula los coeficientes de c
                c(0) = b(0);
                c(1) = b(1) + c(0)*r;

                for (int j=2; j< degree; ++j) {
                    c(j) = b(j) + c(j-1)*r + c(j-2)*s;
                }

                // Calcula delta s y delta r
                dr = (b(degree)  *c(degree-3) - b(degree-1)*c(degree-2))/
                    (c(degree-2)*c(degree-2) - c(degree-1)*c(degree-3));
                ds = (b(degree-1)*c(degree-1) - b(degree)  *c(degree-2))/
                    (c(degree-2)*c(degree-2) - c(degree-1)*c(degree-3));

                // Calcula el error
                errorS = (s==0)?ds/(s+tolerance):ds/s;
                errorR = (r==0)?dr/(r+tolerance):dr/r;

                // Rompe el ciclo si el error es menor a la tolerancia, de otro modo asigna la nueva r y s
                if (abs(errorS)<tolerance && abs(errorR)<tolerance) {
                    roots = quadratic(1, -r, -s); // Obtiene las nuevas raices
                    break;
                }
                else {
                    r = r+dr; s=s+ds;
                }
            }

            b.resize(b.size()-2);
            roots.pushArray(bairstowsMethod(b, ra, sa, maxIter, tolerance)); // Adjunta las raices que calculara en la llamada recursiva
        }

        return roots;
    }

    // Aproximaciones de raices
    inline number newtonRaphson(const std::function<number(number)> &f, number seed, number maxIter, number tolerance) {

        if (abs(f(seed))<tolerance) // Input value is root of function
        {
            return seed;
        }

        number x1 = seed.real();
        number y1 = (seed.imag()==0)? number(0, 1) : number(0, seed.imag());

        DM4th::Parallel::sections(
            EDM4thParallelSettings::DEFAULT,

            // Real root
            [&]()
            {
                for (int n=0; n<maxIter.real() && abs(f(x1))>tolerance; ++n) {
                    x1 = x1 - f(x1)/derivative(f, x1);
                }
            },

            // Complex root
                [&]()
            {
                for (int n=0; n<maxIter.real() && (abs(f(y1))>tolerance && abs(f(x1))>tolerance); ++n) {
                    y1 = y1 - f(y1)/derivative(f, y1);
                }
            }
            );

        if (abs(f(x1))<tolerance) return x1;
        if (abs(f(y1))<tolerance) return y1;

        return NAN;
    }


    inline number newtonRaphson(const std::function<number(number)> &f, const std::function<number(number)> &fd, number seed, number maxIter, number tolerance) {

        if (abs(f(seed))<tolerance) // Input value is root of function
        {
            return seed;
        }

        number x1 = seed.real();
        number y1 = (seed.imag()==0)? number(0, 1) : number(0, seed.imag());

        DM4th::Parallel::sections(
            EDM4thParallelSettings::DEFAULT,

            // Real root
            [&]()
            {
                for (int n=0; n<maxIter.real() && abs(f(x1))>tolerance; ++n) {
                    x1 = x1 - f(x1)/fd(x1);
                }
            },

            // Complex Root
                [&]()
            {
                for (int n=0; n<maxIter.real() && abs(f(y1))>tolerance && abs(f(x1))>tolerance; ++n) {
                    y1 = y1 - f(y1)/fd(y1);
                }
            }
            );

        if (abs(f(x1))<tolerance) return x1;
        if (abs(f(y1))<tolerance) return y1;

        return NAN;

    }

    inline number secantMethod(const std::function<number(number)> &f, number seed0, number seed1, number maxIter, number tolerance) {

        if (abs(f(seed0))<tolerance) // Input value is root of function
        {
            return seed0;
        }
        if (abs(f(seed1))<tolerance) // Input value is root of function
        {
            return seed1;
        }

        number x0 = seed0.real();
        number x1 = seed1.real();
        number x2;

        number y0 = seed0.imag()==0? number(0, 1) : seed0.imag();
        number y1 = seed1.imag()==0? number(0, 1) : seed1.imag();
        number y2;

        DM4th::Parallel::sections(
            EDM4thParallelSettings::DEFAULT,

            // Real root
            [&]()
            {
                for (int n=0; n<maxIter && abs(f(x1))>tolerance; ++n) {
                    x2 = x1 - f(x1) * ((x0-x1)/(f(x0) - f(x1)));
                    x0 = x1; x1 = x2;

                }
            },

            // Complex root
                [&]()
            {
                for (int n=0; n<maxIter && abs(f(y1))>tolerance && abs(f(x1))>tolerance; ++n) {
                    y2 = y1 - f(y1) * ((y0-y1)/(f(y0) - f(y1)));
                    y0 = y1; y1 = y2;
                }
            }
            );

        if (abs(f(x2))<tolerance) return x2;
        if (abs(f(y2))<tolerance) return y2;

        return NAN;

    }

}