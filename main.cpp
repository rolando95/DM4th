#include <number.h>
#include <string>
#include <iostream>

using namespace std;
int main(){
    Vector a = range(2,10);
    std::string str = "10+7i";
    Number b = strToNumber(str);
    b = "15+18i";
    print(b);
    return 0;
}