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

void Quaternion::operator*=(Quaternion q1){
    *this = *this*q1;
}


Quaternion Quaternion::normalize(){
    Number result = sqrt(norm(*this));
    for(int j=0; j<*_rows; j++){
        _data->array[j]/=result;
    }
    return *this;
}

Quaternion Quaternion::getCopy(){
    Quaternion result;
    result[0] = _data->array[0];
    result[1] = _data->array[1];
    result[2] = _data->array[2];
    result[3] = _data->array[3];
    return result;
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

Quaternion operator+(Quaternion q1, Quaternion q2){
    Quaternion result = q1.getCopy();
    result+=q2;
    return result;
}
Quaternion operator-(Quaternion q1, Quaternion q2){
    Quaternion result = q1.getCopy();
    result-=q2;
    return result;
}

/*
Quaternion operator/(Quaternion q1, Quaternion q2){
    //Quaternion result = q2.getCopy();
    //return result;
}*/

Quaternion operator*(Quaternion q1, Quaternion q2){
    Quaternion result;
    result[0] = q1[0]*q2[0] - q1[1]*q2[1] - q1[2]*q2[2] - q1[3]*q2[3];
    result[1] = q1[1]*q2[0] + q1[0]*q2[1] + q1[2]*q2[3] - q1[3]*q2[2];
    result[2] = q1[0]*q2[2] - q1[1]*q2[3] + q1[2]*q2[0] + q1[3]*q2[1];
    result[3] = q1[0]*q2[3] + q1[1]*q2[2] - q1[2]*q2[1] + q1[3]*q2[0];
    return result;
}

Number norm(Quaternion q){
    Number result=0;
    for(int j=0; j<4; j++){
        result += q[j]*q[j];
    }   
    return result;
}