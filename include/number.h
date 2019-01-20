#include "N.h"
#include "V.h"
#include "analysis.h"

//Expresiones con numero de aurgumentos infinitos
void print(){;}
template<class T, class ... Types>
void print(const T& first, const Types& ... args){
    cout<<first<<" ";
    print(args...);
}
