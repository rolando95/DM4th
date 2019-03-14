#ifndef _NUMBER_H_
#define _NUMBER_H_

#include "_Number.h"
#include "_Vector.h"
#include "_Matrix.h"
#include "analysis.h"
#include "data.h"

using std::string;
using std::cin;
using std::cout;
using std::endl;

#define arrayToMatrix(b,a,N,M) arrayToMatrix(&b[0][0],a,N,M) 
#define arrayToMatrix(b,a,N,M,I) arrayToMatrix(&b[0][0],a,N,M,I) 
#define matrixToArray(a,b,N,M) matrixToArray(a,&b[0][0],N,M) 
#define matrixToArray(a,b,N,M,I) matrixToArray(a,&b[0][0],N,M,I) 
#endif
