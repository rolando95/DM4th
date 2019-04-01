#ifndef __MATRIX_H__
#define __MATRIX_H__

#include "_Vector.h"

class Matrix{
private:
    int *_rows = nullptr;
    int *_cols = nullptr;
    int *_ref = nullptr;
    _Array<Vector> *_data = nullptr;

    void alloc();
    void free();
public:
    void _addRef();
    void _subRef();

    void operator=(const Matrix &D);
    // Inicializacion sin valores
    Matrix();
    // Inicializacion con un vector como argumento en el constructor
    Matrix(const Matrix&);
    // Inicializacion con un numero indefinido de elementos en el constructor
    template<class ... T>
    Matrix(Vector first,T... args){  
        this->alloc();  
        this->appendRow(first);
        this->appendRow(Matrix(args...));
    }
    Matrix(std::string);
    ~Matrix();
    // Acceso a elemento de matrix
    inline Vector& operator[](Number n){
        int pos = (int)n;
        if(pos<0) pos = 0;
        assert(pos<*_rows);
        return _data->array[pos];
    }
    /* 
     Adjunta como parametro Vector una fila en la matriz
     matrix.appendRow(Vector)           <- Adjunta el valor Vector al final de la matriz 
     matrix.appendRow(Vector, position) <- Adjunta el valor Vector en la posicion dada dentro de la matriz
    */
    Vector appendRow(const Vector&, Number=-1);
    /* 
     Adjunta como parametro Matrix filas en la matriz
     matrix.appendRow(Matrix)           <- Adjunta el valor Matrix al final de la matriz 
     matrix.appendRow(Matrix, position) <- Adjunta el valor Matrix en la posicion dada dentro de la matriz
    */
    Matrix appendRow(Matrix, Number=-1);
    /* 
     Adjunta como parametro Vector una columna en la matriz
     matrix.appendCol(Vector)           <- Adjunta el valor Vector al final de la matriz 
     matrix.appendCol(Vector, position) <- Adjunta el valor Vector en la posicion dada dentro de la matriz
    */
    Vector appendCol(const Vector&, Number=-1);
    /* 
     Adjunta como parametro Matrix columnas en la matriz
     matrix.appendCol(Matrix)           <- Adjunta el valor Matrix al final de la matriz 
     matrix.appendCol(Matrix, position) <- Adjunta el valor Matrix en la posicion dada dentro de la matriz
    */
    Matrix appendCol(Matrix, Number=-1);
    // Obtiene el numero de filas que contiene la matriz
    inline int length() const{ return *_rows;}
    // Obtiene el numero de files que contiene la matriz
    inline int rowsLength() const {return *_rows;}
    // Obtiene el numero de columnas que contiene la matriz
    inline int colsLength() const {return *_cols;}
    // Resize matrix (rows, cols)
    //void resize(const Number&, Number=-1);
    void resize(const Number&, Number);
};

// Impresion en pantalla de la Matriz
std::ostream& operator<<(std::ostream&, Matrix);

// Lectura en pantalla de la Matriz
std::istream& operator>>(std::istream&, Matrix&);

#endif