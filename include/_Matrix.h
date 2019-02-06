#ifndef __MATRIX_H__
#define __MATRIX_H__

#include "_Vector.h"

class Matrix{
    int rows=0, cols=0;
    std::vector<Vector> data;
public:
    // Inicializacion sin valores
    Matrix();
    Matrix(const Matrix&);

    // Inicializacion con numero indefinido de vectores como argumento en el constructor
    /* -- TODO -- */

    // Acceso a fila de matriz
    Vector& operator[](Number);

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
     Adjunta como parametro Vector una columna en la matriz
     matrix.appendCol(Vector)           <- Adjunta el valor Vector al final de la matriz 
     matrix.appendCol(Vector, position) <- Adjunta el valor Vector en la posicion dada dentro de la matriz
    */
    Vector appendCol(const Vector&, Number=-1);
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
};

// Impresion en pantalla de la Matriz
std::ostream& operator<<(std::ostream&, Matrix);



// Lectura en pantalla de la Matriz
std::istream& operator>>(std::istream&, Matrix&);

#endif