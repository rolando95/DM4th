#include "_Number/_Array.h"

using std::string;
using std::cin;
using std::cout;
using std::endl;


//Esta funcion es llamada antes de entrar al main
//dejar comentada para continuar automaticamente 
void beforeMain()__attribute__((constructor));

// Esta funcion es llamada al salir del main
//dejar comentada para salir automaticamente
void afterMain()__attribute__((destructor));