#include "analysis.h"

N maximum(const N a){return a;}
N maximum(V v){
    N value = -INF;
    if(v.length()>0){
        value = v[0];
        for(int j=1; j<v.length(); j++){
            if(v[j]>value) value = v[j];
        }
    }
    return value;
}
N minimum(const N a){return a;}
N minimum(V v){
    N value = INF;
    if(v.length()>0){
        value = v[0];
        for(int j=1; j<v.length(); j++){
            if(v[j]<value) value = v[j];
        }
    }
    return value;
}
V zeros(const N &n){
    V z; z.resize(n);
    return z;
}

V ones(const N &n){
    V o;
    for(int j=0; j<n; j++) o.append(1);
    return o;
}

V range(const N &begin, const N &end, N value){
    V v;
    if(value>0 && end>begin){
        for(N j=begin; j<=end; j+=value){
            v.append(j);
        }
    }else if(value<0 && begin>end){
        for(N j=begin; j>=end; j+=value){
            v.append(j);
        }
    }
    return v;
}
V range(V v, const N &begin, const N &end, N value){
    V result;
    if(value>0 && end>begin){
        for(N j=begin; j<=end; j+=value){
            result.append(v[j]);
        }
    }else if(value<0 && begin>end){
        for(N j=begin; j>=end; j+=value){
            result.append(v[j]);
        }
    }
    return result;
}
V range(function f, const N &begin, const N &end, N value){
        V result;
    if(value>0 && end>begin){
        for(N j=begin; j<=end; j+=value){
            result.append(f(j));
        }
    }else if(value<0 && begin>end){
        for(N j=begin; j>=end; j+=value){
            result.append(f(j));
        }
    }
    return result;
}

N exp(N x){
    return pow(e,x);
}

// From Wikipedia https://es.wikipedia.org/wiki/Aproximaci%C3%B3n_de_Lanczos
N gamma(N z){
    N result;
    N x;
    N t;
    V p(676.5203681218851,  
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
        for(N j=0; j<p.length(); j++){
            x += p[j]/(z+j+1);
        }
        t = z + p.length() - 0.5;
        result = sqrt(2*pi) *pow(t,z+0.5) * exp(-t) * x;
    }

    if (abs(result.i - abs(result.i))<=0.0000001){
        return result.r;
    }
    return result;
}
N factorial(const N &n){
    N x = 1;
    if(floor(n.r)==n && n>=0){ // Es numero entero positivo 
        for(auto i=1; i<=n; i++){
            x *= i;
        }
    }else{
        x = gamma(n+1);
    }
    return x;
}
N sumatory(function f, V v, const N interval){
    N x=0;
    for(N j=0; j>=0 && j<v.length(); j+=interval){
        x += f(v[j]);
    }
    return x;
}
N sumatory(function f, const N &begin, const N &end, const N interval){
    N x=0;
    for(N j=begin; j>=begin && j<=end; j+=interval){
        x += f(j);
    }
    return x;
}
N sumatory(V v, N begin, N end, N interval){
    N x=0;
    if(v.length()>0){
        if(begin<0) begin = 0;
        if(end<0 || end>v.length()) end = v.length();
        for(N j=begin; j>=begin && j<end; j+= interval){
            x += v[j];
        }
    }
    return x;
}
N product(function f, V v, const N interval){
    N x=1;
    for(N j=0; j>=0 && j<v.length(); j+=interval){
        x *= f(v[j]);
    }
    return x;
}
N product(function f, const N &begin, const N &end, const N interval){
    N x=1;
    for(N j=begin; j>=begin && j<=end; j+=interval){
        x *= f(j);
    }
    return x;
}
N product(V v, N begin, N end, N interval){
    N x=1;
    if(v.length()>0){
        if(begin<0) begin = 0;
        if(end<0 || end>v.length()) end = v.length();
        for(N j=begin; j>=begin && j<end; j+= interval){
            x *= v[j];
        }
    }
    return x;
}
// Derivative
N derivative(function f, const N &x0, const N order, const N h){
    N o(abs(floor(order.r)));
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
V diff(V v, N iter){
    if(iter<=0) return v;
    else{
        V diffV;
        if(v.length().r >= 2){
            for(auto j=0; j<v.length().r -1; j++){
                diffV.append(v[j+1] - v[j]);
            }
            return diff(diffV,iter - 1);
        }else{
            return V(0);
        }
    }
}
// Integral
N integral(function f, const N &a, const N &b, const N subintervals){
    N n = int(round(subintervals).r)/3*3;
    N h = (b-a)/n;
    
    N s=0;
    for(N i=0; i<n; i++){
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
V quadratic(const N &a, const N &b, const N &c){
    V roots;
    N square = sqrt(b*b - 4*a*c);
    roots.append((-b+square)/(2*a));
    roots.append((-b-square)/(2*a));
    return roots;
}
// Aproximaciones de raices
N newtonRaphson(function f, N x1, N maxIter, N tolerance){
    x1 = x1.r;
    N y1 = (x1.i==0)? 1.00i : x1.i;
    
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
N newtonRaphson(function f, function fd, N x1, N maxIter, N tolerance){
    x1 = x1.r;
    N y1 = (x1.i==0)? 1.00i : x1.i;
    
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
N secantMethod(function f, N x0, N x1, N maxIter, N tolerance){
    x0 = x0.r; x1 = x1.r;
    N x2;

    N y0 = x0.i==0? 1.00i : x0.i;
    N y1 = x1.i==0? 1.01i : x1.i;
    N y2;

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
V bairstowsMethod(V v,N r,N s, N maxIter, N tolerance){

    // Conserva los valores semilla iniciales para futuras iteraciones
    N ra = r; 
    N sa = s;
    V roots;
    N degree = v.length()-1;
    
    if(degree==1) roots = V(-v[1]/v[0]); // Polinomio de grado 1
    else if(degree==2) roots = quadratic(v[0],v[1],v[2]); // Polinomio de grado 2
    else if(degree>2){ // Polinomio de grado superior a 2
        
        // 
        V b; b.resize(v.length());
        V c; c.resize(v.length()-1);
        N errorR, errorS;
        N dr, ds;

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