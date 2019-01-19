#include <string>
#include <iostream>
#include <number.h>

int main(){
    V array, array2;
    array.push(10);
    array.push(20);
    array.push(30);
    array.push(40,1);
    array.push(50,10);
    
    array2.push(60);
    array2.push(70);
    array2.push(80,1);
    for(auto n=0; n<array.length(); n++){
        cout<<array.data[n]<<endl;
    }
}