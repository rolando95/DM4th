#include "_Quaternion.h"

Quaternion::Quaternion(){
    _data->resizeArray(4);
    *_rows = 4;
    _data->array[0] = 1;
    _data->array[1] = 0;
    _data->array[2] = 0;
    _data->array[3] = 0;
}

Quaternion::Quaternion(const Quaternion &q){
    *this = q;
}

Quaternion::Quaternion(Vector v){
    assert(v.length()==4);
    *_rows = 4;
    _data->resizeArray(4);
    _data->array[0] = v[0];
    _data->array[1] = v[1];
    _data->array[2] = v[2];
    _data->array[3] = v[3];
}
Quaternion::Quaternion(Number n1, Number n2, Number n3, Number n4){
    _data->resizeArray(4);
    *_rows = 4;
    _data->array[0] = n1;
    _data->array[1] = n2;
    _data->array[2] = n3;
    _data->array[3] = n4;
}

void Quaternion::operator+=(Quaternion q){
    _data->array[0] += q[0];
    _data->array[1] += q[1];
    _data->array[2] += q[2];
    _data->array[3] += q[3];
} 

void Quaternion::operator-=(Quaternion q){
    _data->array[0] -= q[0];
    _data->array[1] -= q[1];
    _data->array[2] -= q[2];
    _data->array[3] -= q[3];
} 


Quaternion Quaternion::normalize(){
    Number result=0;
    for(int j=0; j<*_rows; j++){
        result += _data->array[j]*_data->array[j];
    }
    result = sqrt(result);
    for(int j=0; j<*_rows; j++){
        _data->array[j]/=result;
    }
    return *this;
}

std::ostream& operator<<(std::ostream& stream, Quaternion q){
    int len = 4;
    stream<<"[";
    for(int n=0; n<len; n++){
        if(n!=0) stream<<", ";
        stream<<q[n];
    }
    stream<<"]";
    return stream;
}

std::istream& operator>>(std::istream& stream, Quaternion &q){
    Number value;
    int pos = 0;
    if(stream.peek()==' ')stream>>std::ws;
    if(stream.peek()=='['){
        stream.get(); // Captura el corchete abierto
        while(stream>>value){
            q[pos] = value;
            if(stream.peek()==']')break;
            else if(stream.peek()==',')stream.get(); //Captura la comma
            else assert(false);
            pos++;
        }
        stream.get(); // Captura el corchete cerrado
    }
    assert(pos==3);
    if(stream.peek()=='\n')stream.get();
    return stream;
}
