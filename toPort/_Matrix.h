#ifndef __MATRIX_H__
#define __MATRIX_H__

#include "_Vector.h"


class Matrix{
    int _rows=0, _cols=0;
    std::vector<Vector> data;
public:
    // Inicializacion sin valores
    Matrix();
    Matrix(const Matrix&);

    // Inicializacion con numero indefinido de vectores como argumento en el constructor
    template<class ... T>
    Matrix(const Vector& first, T... args){
        appendRow(first);
        appendRow(Matrix(args...));
    }

    Matrix(std::string);

    // Acceso a fila de matriz
    Vector& operator[](Number);

    // Resize matrix resize(rows, cols)
    void resize(const Number&, Number=-1);
    
    Number rowsLength() const;
    Number colsLength() const;
    
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

    // Asignacion aditiva
    Matrix operator+=(Matrix);
    // Asignacion sustractiva
    Matrix operator-=(Matrix);
    // Asignacion multiplicativa (por otra matriz)
    Matrix operator*=(Matrix);
    // Asignacion multiplicativa (por un escalar)
    Matrix operator*=(Number);
    // Asignacion divisiva (por un escalar)
    Matrix operator/=(Number);
    // Residuo
    Matrix operator%=(Number);

    // inicio y final de Matrix (De utilidad para for each de c++)
    std::vector<Vector>::iterator begin();
    std::vector<Vector>::iterator end();
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

template<class T>
/* 
    Conversion de Matrix a array de lenguaje C.      
    Si se desea adjuntar los numeros imaginarios de Matrix, imaginary=true       
    matrixToArray(array, Matrix, Numero de filas del C array, Numero de columnas del C array, incluirNumerosImaginarios);

    matrixToArray(array, Matrix, 2, 2, false)
    [[1+3i, 2+4i],  ==> {{1, 2},
     [5+7i, 6+8i]]       {5, 6}}

    matrixToArray(array, V, 4, 2, true)
    [[1+3i, 2+4i],  ==> {{1, 2},
     [5+7i, 6+8i]]       {5, 6},
                         {3, 4},
                         {7, 8}}

    NOTA: Es importante reservar memoria del array para la conversion 
    antes de llamar la funcion
*/
void matrixToArray(Matrix &m, T *CArray, int N, int M, bool imaginary=false);

template<class T>
/*
    Conversion de array de lenguaje C a Matrix
    Si la segunda mitad del array contiene el valor imaginario de la parte real, imaginary=true
    matrixToArray(Matrix, array, Numero de filas del C array, Numero de columnas del C array, incluirNumerosImaginarios);

    arrayToMatrix(array, Matrix, 2, 2, false)
    {{1, 2},  ==>  [[1, 2],
     {3, 4}}        [3, 4]]       

    arrayToMatrix(array, Matrix, 4, 2, true)
    {{1, 2},  ==>  [[1+3i, 2+4i], 
     {5, 6},        [5+7i, 6+8i]]
     {3, 4},
     {7, 8}}
*/
void arrayToMatrix(T *CArray, Matrix &m, int N, int M, bool imaginary=false);
#endif