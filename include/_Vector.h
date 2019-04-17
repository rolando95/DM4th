#ifndef __VECTOR_H__
#define __VECTOR_H__

#include "_Number.h"

class Vector: protected _ArrayManager<Number>{
public:
    using _ArrayManager::operator=;
    // Inicializacion sin valores
    Vector();
    // Inicializacion con un vector como argumento en el constructor
    Vector(const Vector&);
    // Inicializacion con un numero indefinido de elementos en el constructor
    template<class ... T>
    Vector(Number first,T... args){  
        //this->_alloc();  
        this->append(first);
        this->append(Vector(args...));
    }
    Vector(std::string);
    ~Vector();
    
    // Acceso a elemento de vector
    inline Number& operator[](Number n){
        int pos = (int)n;
        assert(pos>=0 && pos<*_rows);
        return _data->array[pos];
    }
    /*
        obtiene un elemento de vector
        vector.getItem(position)
    */
    inline Number getItem(Number pos) const{
        assert(pos>=0 && pos<*_rows);
        return _data->array[(int)pos];
    }
    /*
        asigna un elemento de vector
        vector.setItem(position)
    */    
    inline Number setItem(Number pos, Number value){
         assert(pos>=0 && pos<*_rows);
         _data->array[(int)pos] = value;
         return value;
    }
    /* 
     Adjunta un numero en el vector
     vector.append(Number)           <- Adjunta el valor Number al final del Vector
     vector.append(Number, position) <- Adjunta el valor Number en la posicion dada dentro del Vector
    */
    void append(const Number&,Number=-1);
    /* 
     Adjunta un vector
     vector.append(Vector)           <- Adjunta el valor Vector al final del Vector
     vector.append(Vector, position) <- Adjunta el valor Vector en la posicion dada dentro del Vector
    */
    void append(Vector,Number=-1);
    /* 
     Elimina un elemento del vector
     vector.pop()         <- Elimina el ultimo elemento del vector
     vector.pop(position) <- Elimina el elemento del vector de la posicion dada
    */
    Number pop(const Number=-1);
    // Obtiene el numero de elementos que contiene el vector
    inline int length() const{ return *_rows;}
    /*
     Busca la posicion de los elementos en el vector que coincidan con el valor de argumento. 
     Devuelve un vector vacio de no encontrar coincidencias
    */
    int index(const Number&);
    /* 
     Reescala el vector con el numero de elementos dados.
     Definir un tamanio mayor al actual rellenara de ceros automaticamente, uno menor eliminara los ultimos elementos.
    */
    void resize(const Number&);
    /*
     Intercambia 2 elementos del vector
     vector.swap(index1, index2, count=-1);
    */
    void swap(Number, Number, Number=1);
    /*
     Ordena elementos del vector
    */
    Vector sort(bool reverse=false, Number begin=0, Number end=-1);
    /*
     Invierte los elementos del vector
    */
    Vector reverse();
     // Carga valor de tipo Vector desde un fichero
    Vector loadFile(std::string url);
    // Guarda valor de tipo Vector en un fichero
    Vector saveFile(std::string url);

    // Asignacion aditiva
    void operator+=(Vector);
    // Asignacion sustractiva
    void operator-=(Vector);
    // Asignacion multiplicativa
    void operator*=(Number);
    // Asignacion divisiva
    void operator/=(Number);
    // Residuo
    void operator%=(Number);
    /*
     Retorna una copia del Vector (Paso por valor)
    */
    Vector getCopy();
};

// Impresion en pantalla del vector
std::ostream& operator<<(std::ostream&, const Vector&);


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

bool operator==(Vector&,Vector&);
bool operator!=(Vector&,Vector&);
bool operator> (Vector&,Vector&);
bool operator< (Vector&,Vector&);
bool operator>=(Vector&,Vector&);
bool operator<=(Vector&,Vector&);

Vector zeros(const Number&);
//
Vector ones(const Number&);

// range(vector, pos begin, pos end, interval)
//Vector range(Vector, const Number&, const Number&, Number=1);
Vector range(const Number&, const Number&, Number=1);
Vector sort(Vector, bool reverse=false);
Vector reverse(Vector);

#endif