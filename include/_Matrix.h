#ifndef __MATRIX_H__
#define __MATRIX_H__

#include "_Vector.h"

class Matrix: protected _ArrayManager<Vector>{
public:
    using _ArrayManager::operator=;
    // Inicializacion sin valores
    Matrix();
    // Inicializacion con un vector como argumento en el constructor
    Matrix(const Matrix&);
    // Inicializacion con un numero indefinido de elementos en el constructor
    template<class ... T>
    Matrix(Vector first,T... args){  
        this->_alloc();  
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
    Vector appendCol(Vector&, Number=-1);
    /* 
     Adjunta como parametro Matrix columnas en la matriz
     matrix.appendCol(Matrix)           <- Adjunta el valor Matrix al final de la matriz 
     matrix.appendCol(Matrix, position) <- Adjunta el valor Matrix en la posicion dada dentro de la matriz
    */
    Matrix appendCol(Matrix, Number=-1);
        /* 
     Elimina una fila de la matriz
     matrix.popRow()         <- Elimina la ultima fila de la matriz
     matrix.popRow(position) <- Elimina la fila de la matriz de la posicion dada
    */
    Vector popRow(const Number=-1);
    /* 
     Elimina una columna de la matriz
     matrix.popCol()         <- Elimina la ultima columna de la matriz
     matrix.popCol(position) <- Elimina la columna de la matriz de la posicion dada
    */
    Vector popCol(const Number=-1);
    // Carga valor de tipo Matrix desde un fichero
    Matrix loadFile(std::string url);
    // Guarda valor de tipo Matrix en un fichero
    Matrix saveFile(std::string url);
    // Obtiene el numero de filas que contiene la matriz
    inline int length() const{ return *_rows;}
    // Obtiene el numero de files que contiene la matriz
    inline int rowsLength() const {return *_rows;}
    // Obtiene el numero de columnas que contiene la matriz
    inline int colsLength() const {return *_cols;}
    // Resize matrix (rows, cols)
    //void resize(const Number&, Number=-1);
    void resize(const Number&, Number);
       /*
     Retorna una copia de la Matriz (Paso por valor)
    */
    Matrix getCopy();
    
    // Asignacion aditiva
    void operator+=(Matrix);
    // Asignacion sustractiva
    void operator-=(Matrix);
    // Asignacion multiplicativa (por otra matriz)
    void operator*=(Matrix);
    // Asignacion multiplicativa (por un escalar)
    void operator*=(Number);
    // Asignacion divisiva (por un escalar)
    void operator/=(Number);
    // Residuo
    void operator%=(Number);
};

// Impresion en pantalla de la Matriz
std::ostream& operator<<(std::ostream&, Matrix);

// Lectura en pantalla de la Matriz
std::istream& operator>>(std::istream&, Matrix&);

// Suma de Matrices
Matrix operator+(Matrix,Matrix);
// Resta de Matrices
Matrix operator-(Matrix,Matrix);
// Multiplicacion de Matrices
Matrix operator*(Matrix,Matrix);
// Producto entre Matriz y escalar
Matrix operator*(Matrix,const Number&);
// Producto entre escalar y Matriz
Matrix operator*(const Number&,Matrix);
// Producto entre Vector y Matriz
Vector operator*(Vector, Matrix);
// Producto entre Matriz y Vector
Vector operator*(Matrix, Vector);
// Division entre Matriz y escalar
Matrix operator/(Matrix,const Number&);
// Residuo
Matrix operator%(Matrix,const Number&);
/*
 Devuelve una matriz de ceros con numero de filas y columnas dadas
 zeros(2,2) ==> [[0,0]
                 [0,0]]
*/
Matrix zeros(const Number&, const Number&);
/*
 Devuelve una matriz de unos con numero de filas y columnas dadas
 ones(2,2) ==> [[1,1]
                [1,1]]
*/
Matrix ones(const Number&, const Number&);
/*
 Devuelve la matriz identidad numero de filas y columnas dadas
 identity(2) ==> [[1,0]
                  [0,1]]
*/
Matrix identity(Number, Number c=-1);
#endif