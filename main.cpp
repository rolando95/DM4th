//#include <number.h>
#include "_Vector.h"
#include <string>
#include <iostream>

using namespace std;

int main(){
    Vector a = Vector(1,3,2,4,5,7,6,8,9,10);
    std::cout<<a.pop(3)<<endl;
    a.swap(0,7,2);
    a.sort();
    a.reverse();
    cout<<a<<endl;
    /*
    Vector a;
    Vector b;
    a.append(10);
    a.append(12);
    a.append(15);
    cout<<a<<endl;
    b = a;
    a[0] = 17i;
    cout<<a<<" "<<b<<endl;;
    */
    /*
    Vector b;
    b.append(10);
    b.append(11);
    b.append(12);
    b.append(13);
    a.append(b);
    */
    //cout<<a<<endl;
    return 0;
}
