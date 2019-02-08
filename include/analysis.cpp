#include "analysis.h"

Number maximum(const Number a){return a;}
Number maximum(Vector v){
    Number value = -INF;
    if(v.length()>0){
        value = v[0];
        for(int j=1; j<v.length(); j++){
            if(v[j]>value) value = v[j];
        }
    }
    return value;
}
Number minimum(const Number a){return a;}
Number minimum(Vector v){
    Number value = INF;
    if(v.length()>0){
        value = v[0];
        for(int j=1; j<v.length(); j++){
            if(v[j]<value) value = v[j];
        }
    }
    return value;
}

Vector range(const Number &begin, const Number &end, Number value){
    Vector v;
    if(value>0 && end>begin){
        for(Number j=begin; j<end; j+=value){
            v.append(j);
        }
    }else if(value<0 && begin>end){
        for(Number j=begin; j>end; j+=value){
            v.append(j);
        }
    }
    return v;
}
Vector range(Vector v, const Number &begin, const Number &end, Number value){
    Vector result;
    if(value>0 && end>begin){
        for(Number j=begin; j<=end; j+=value){
            result.append(v[j]);
        }
    }else if(value<0 && begin>end){
        for(Number j=begin; j>=end; j+=value){
            result.append(v[j]);
        }
    }
    return result;
}
Vector range(Function f, const Number &begin, const Number &end, Number value){
        Vector result;
    if(value>0 && end>begin){
        for(Number j=begin; j<=end; j+=value){
            result.append(f(j));
        }
    }else if(value<0 && begin>end){
        for(Number j=begin; j>=end; j+=value){
            result.append(f(j));
        }
    }
    return result;
}

Number exp(Number x){
    return pow(e,x);
}

/*
Number zeta(Number s, Number tolerance){
}*/
Number PI(Number z, Number tolerance){
    return gamma(z+1,tolerance);
}
// From Wikipedia https://es.wikipedia.org/wiki/Aproximaci%C3%B3n_de_Lanczos
Number gamma(Number z, Number tolerance){
    Number result;
    Number x;
    Number t;
    Vector p(676.5203681218851,  
        -1259.1392167224028,  
        771.32342877765313,
        -176.61502916214059,     
        12.507343278686905, 
        -0.13857109526572012,
        9.9843695780195716e-6, 
        1.5056327351493116e-7
    );

    if(z<0.5) result = pi/(sin(pi*z)*gamma(1-z));
    else{
        z -= 1;
        x = 0.99999999999980993;
        for(Number j=0; j<p.length(); j++){
            x += p[j]/(z+j+1);
        }
        t = z + p.length() - 0.5;
        result = sqrt(2*pi) *pow(t,z+0.5) * exp(-t) * x;
    }

    if (abs(result.i - abs(result.i))<=tolerance){
        return result.r;
    }
    return result;
}
Number factorial(const Number &n){
    Number x = 1;
    if(floor(n.r)==n && n>=0){ // Es numero entero positivo 
        for(auto i=1; i<=n; i++){
            x *= i;
        }
    }else{
        x = gamma(n+1);
    }
    return x;
}
Number sumatory(Function f, Vector v, const Number interval){
    Number x=0;
    for(Number j=0; j>=0 && j<v.length(); j+=interval){
        x += f(v[j]);
    }
    return x;
}
Number sumatory(Function f, const Number &begin, const Number &end, const Number interval){
    Number x=0;
    for(Number j=begin; j>=begin && j<=end; j+=interval){
        x += f(j);
    }
    return x;
}
Number sumatory(Vector v, Number begin, Number end, Number interval){
    Number x=0;
    if(v.length()>0){
        if(begin<0) begin = 0;
        if(end<0 || end>v.length()) end = v.length();
        for(Number j=begin; j>=begin && j<end; j+= interval){
            x += v[j];
        }
    }
    return x;
}
Number product(Function f, Vector v, const Number interval){
    Number x=1;
    for(Number j=0; j>=0 && j<v.length(); j+=interval){
        x *= f(v[j]);
    }
    return x;
}
Number product(Function f, const Number &begin, const Number &end, const Number interval){
    Number x=1;
    for(Number j=begin; j>=begin && j<=end; j+=interval){
        x *= f(j);
    }
    return x;
}
Number product(Vector v, Number begin, Number end, Number interval){
    Number x=1;
    if(v.length()>0){
        if(begin<0) begin = 0;
        if(end<0 || end>v.length()) end = v.length();
        for(Number j=begin; j>=begin && j<end; j+= interval){
            x *= v[j];
        }
    }
    return x;
}
// Derivative
Number derivative(Function f, const Number &x0, const Number order, const Number h){
    Number o(abs(floor(order.r)));
    if(order<=0){
        return f(x0);
    }else if(order==1){
        return (f(x0+h)-f(x0-h))/(2*h);
    }else if(order==2){
        return (f(x0+h) - 2*f(x0) + f(x0-h))/pow(h,2);
    }else{
        return (derivative(f,x0+h/2,o-1,2*h) - derivative(f,x0-h/2,o-1,2*h) )/h;
    }
}
Vector diff(Vector v, Number iter){
    if(iter<=0) return v;
    else{
        Vector diffV;
        if(v.length().r >= 2){
            for(auto j=0; j<v.length().r -1; j++){
                diffV.append(v[j+1] - v[j]);
            }
            return diff(diffV,iter - 1);
        }else{
            return Vector(0);
        }
    }
}
// Integral
Number integral(Function f, const Number &a, const Number &b, const Number subintervals){
    Number n = int(round(subintervals).r)/3*3;
    Number h = (b-a)/n;
    
    Number s=0;
    for(Number i=0; i<n; i++){
        s+=f(a+h*(i+0.5));
    }
    return s*h;
    
    /*
    N x1 = a+h;
    N x2 = x1+h;
    N x3 = x2+h; 

    N s = f(a);
    for(N i=0; i<n-2; i+=3){
        s += 3*f(x1);
        s += 3*f(x2);
        s += 2*f(x3);

        x1 = x3+h;
        x2 = x1+h;
        x3 = x2+h;
    }
    s+=f(b);
    return 3*h/8*s;
    */
}
// cuadratica
Vector quadratic(const Number &a, const Number &b, const Number &c){
    Vector roots;
    Number square = sqrt(b*b - 4*a*c);
    roots.append((-b+square)/(2*a));
    roots.append((-b-square)/(2*a));
    return roots;
}
// Aproximaciones de raices
Number newtonRaphson(Function f, Number x1, Number maxIter, Number tolerance){
    x1 = x1.r;
    Number y1 = (x1.i==0)? 1.00i : x1.i;
    
    for(int n=0; n<maxIter.r && abs(f(x1))>tolerance; n++){
        x1 = x1 - f(x1)/derivative(f,x1);
    }
    if(abs(f(x1))>tolerance){
        for(int n=0; n<maxIter.r && abs(f(y1))>tolerance; n++){
            y1 = y1 - f(y1)/derivative(f,y1);
        }
        if(abs(f(y1))>tolerance) x1 = NAN;
        else x1 = y1;
    }
    return x1;
}
Number newtonRaphson(Function f, Function fd, Number x1, Number maxIter, Number tolerance){
    x1 = x1.r;
    Number y1 = (x1.i==0)? 1.00i : x1.i;
    
    for(int n=0; n<maxIter.r && abs(f(x1))>tolerance; n++){
        x1 = x1 - f(x1)/fd(x1);
    }
    if(abs(f(x1))>tolerance){
        for(int n=0; n<maxIter.r && abs(f(y1))>tolerance; n++){
            y1 = y1 - f(y1)/fd(y1);
        }
        if(abs(f(y1))>tolerance) x1 = NAN;
        else x1 = y1;
    }
    return x1;
}
Number secantMethod(Function f, Number x0, Number x1, Number maxIter, Number tolerance){
    x0 = x0.r; x1 = x1.r;
    Number x2;

    Number y0 = x0.i==0? 1.00i : x0.i;
    Number y1 = x1.i==0? 1.01i : x1.i;
    Number y2;

    for(int n=0; n<maxIter && abs(f(x1))>tolerance; n++){
        x2 = x1 - f(x1) * ((x0-x1)/(f(x0) - f(x1)));
        x0 = x1; x1 = x2;
    }

    if(abs(f(x2))>tolerance){
        for(int n=0; n<maxIter && abs(f(y1))>tolerance; n++){
            y2 = y1 - f(y1) * ((y0-y1)/(f(y0) - f(y1)));
            y0 = y1; y1 = y2;
        }
        if(abs(f(y2))>tolerance) x2 = NAN;
        else x2 = y2;
    }
    return x2;
}
Vector bairstowsMethod(Vector v, Number r, Number s, Number maxIter, Number tolerance){

    // Conserva los valores semilla iniciales para futuras iteraciones
    Number ra = r; 
    Number sa = s;
    Vector roots;
    Number degree = v.length()-1;
    
    if(degree==1) roots = Vector(-v[1]/v[0]); // Polinomio de grado 1
    else if(degree==2) roots = quadratic(v[0],v[1],v[2]); // Polinomio de grado 2
    else if(degree>2){ // Polinomio de grado superior a 2
        
        // 
        Vector b; b.resize(v.length());
        Vector c; c.resize(v.length()-1);
        Number errorR, errorS;
        Number dr, ds;

        // Empieza el ciclo para calcular las nuevas raices
        for(int k=0; k<maxIter; k++){
            
            // Calcula los coeficientes de b
            b[0] = v[0];
            b[1] = v[1] + b[0]*r;
            for(int j=2; j<=degree; j++){
                b[j] = v[j] + b[j-1]*r + b[j-2]*s;
            }

            // Calcula los coeficientes de c
            c[0] = b[0];
            c[1] = b[1] + c[0]*r;
            for(int j=2; j< degree; j++){
                c[j] = b[j] + c[j-1]*r + c[j-2]*s;  
            }

            // Calcula delta s y delta r
            dr = (b[degree]  *c[degree-3] - b[degree-1]*c[degree-2])/
                (c[degree-2]*c[degree-2] - c[degree-1]*c[degree-3]);
            ds = (b[degree-1]*c[degree-1] - b[degree]  *c[degree-2])/
                (c[degree-2]*c[degree-2] - c[degree-1]*c[degree-3]);
            
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

        b.resize(b.length()-2);
        roots.append(bairstowsMethod(b,ra,sa,maxIter,tolerance)); // Adjunta las raices que calculara en la llamada recursiva

    }

    return roots;
}