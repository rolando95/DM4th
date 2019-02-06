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
    
    Number lengthRows() const;
    Number lengthCols() const;
};

// Impresion en pantalla de la Matriz
std::ostream& operator<<(std::ostream&, Matrix);



// Lectura en pantalla de la Matriz
std::istream& operator>>(std::istream&, Matrix&);

#endif