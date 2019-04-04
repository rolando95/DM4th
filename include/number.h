#ifndef _NUMBER_H_
#define _NUMBER_H_

#include "constants.h"
#include "_Data.h"
#include "_Number.h"
#include "_Vector.h"
#include "_Matrix.h"
#include "analysis.h"
#include "console.h"

using std::string;
using std::cin;
using std::cout;
using std::endl;

// Esta funcion es llamada antes de entrar al main
void beforeMain()__attribute__((constructor));
// Esta funcion es llamada al salir del main
void afterMain()__attribute__((destructor));

//#define arrayToMatrix(b,a,N,M) arrayToMatrix(&b[0][0],a,N,M) 
//#define arrayToMatrix(b,a,N,M,I) arrayToMatrix(&b[0][0],a,N,M,I) 
//#define matrixToArray(a,b,N,M) matrixToArray(a,&b[0][0],N,M) 
//#define matrixToArray(a,b,N,M,I) matrixToArray(a,&b[0][0],N,M,I) 
#endif
