#ifndef _NUMBER_H_
#define _NUMBER_H_

#include "constants.h"
#include "_Data.h"
#include "_Number.h"
#include "_Vector.h"
#include "_Matrix.h"
#include "_Quaternion.h"
#include "_Tree.h"
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
 
#endif
