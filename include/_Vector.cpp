#include "_Vector.h"
//#define REFDEBUG
void Vector::_addRef(){
    if(_ref != nullptr){
        *_ref += 1;
        #ifdef REFDEBUG
        std::cout<<"Vector ref "<<*_ref-1<<" -> "<<*_ref<<std::endl;
        #endif
    }
}

void Vector::_subRef(){
    if(_ref != nullptr){
        *_ref -= 1;
        #ifdef REFDEBUG
        std::cout<<"Vector ref "<<*_ref+1<<" -> "<<*_ref<<std::endl;
        #endif
        if(*_ref<=0){ 
            this->free();
        }
    }
}

void Vector::alloc(){
    #ifdef REFDEBUG
    std::cout<<"New Vector  ---------- N(V)"<<std::endl;
    #endif
    _ref = new int(1);
    _rows = new int(0);
}

void Vector::free(){
    #ifdef REFDEBUG
    std::cout<<"Free Vector ---------- F(V)"<<std::endl;  
    #endif 
    //No resized vector (this->_data = nullptr)
    if(_data){
        _data->freeArray();
        delete _data;
        _data = nullptr;

        if(_ref){
            delete _ref;
            _ref = nullptr;
        }

        if(_rows){
            delete _rows;
            _rows = nullptr;
        }
    }else{
        //std::cout<<"!"<<std::endl;
    }
}

void Vector::operator=(const Vector &D) {
    this->_subRef();
    this->_data = D._data;
    this->_rows = D._rows;
    this->_ref = D._ref;
    this->_addRef();
}

Vector::Vector(){
    this->alloc();
}

Vector::Vector(const Vector &v){
    *this = v;
}


Vector::Vector(std::string str){
    this->alloc();
    std::stringstream ss;
    ss << str;
    ss >> *this;
}

Vector::~Vector(){
    this->_subRef();
}

Number Vector::append(const Number &n, Number idx){
    int pos = idx.real();
    assert(pos>=-1 && pos<= *_rows);
    this->resize(*_rows+1);
    //Append
    if(pos<0 || pos >= *_rows) {
        _data->array[*_rows-1] = n;
    }
    //Insert
    else {
        for(int j=*_rows-1; j > pos; j--){
            _data->array[j] = _data->array[j-1];
        }
        _data->array[pos] = n;
    }
    return n;
}

Vector Vector::append(Vector v,Number idx){
    int pos = (int)idx.real();
    int size = v.length();
    int end = *_rows;
    assert(pos>=-1 && pos<=*_rows);
    this->resize(*_rows+size);

    //Append
    if(pos<0||pos==*_rows){
        for(int j=0; j<size; j++){
            _data->array[end+j] = v[j];
        }
    //Insert
    }else{
        for(int j=end+size-1; j>=pos+size; j--){
            _data->array[j] = _data->array[j-size];
        }
        for(int j=pos; j<pos+size; j++){
            _data->array[j] = v[j-pos];
        }
    }

    return v;
}

Number Vector::pop(const Number idx){
    Number value;
    int pos = idx.real();
    assert(pos>=-1 && pos<=*_rows && *_rows>0);

    if(pos<0 || pos>=*_rows) {
        value = _data->array[*_rows-1];
    }else{
        value = _data->array[pos];
        for(int j=pos; j<*_rows-1; j++){
            _data->array[j] = _data->array[j+1];
        }
    }

    this->resize(*_rows-1);

    return value;
}

int Vector::index(const Number &value){
    int result = -1;
    for(int j=0; j<*_rows; j++){
        if(value==_data->array[j]) {
            result = j;
            break;
        }
    }
    return result;
}

void Vector::resize(const Number &pos){
    int size = (int)pos.real();
    assert(size>=0);
    if(size != *_rows){
        //Malloc data first time
        if(!this->_data){
            this->_data = new _Array<Number>();
            assert(_data);
            this->_data->allocArray(size);
        //Realloc data
        }else if(size>0){
            this->_data->resizeArray(size);
        }else if(size==0){
            this->_data->resizeArray(1);
        }
        //Initialize values
        if(size>*_rows){
            for(int j=*_rows; j<size;j++){
                _data->array[j] = 0 ;
            }
        }
        *_rows = size;
    }
}

void Vector::swap(Number p1, Number p2, Number c){
    int idx1 = (int)p1, idx2 = (int)p2, count = (int)c;
    int size = *_rows;
    
    assert(
        idx1>=0 && idx1+count <= size &&
        idx2>=0 && idx2+count <= size &&
        count>0
    );
    if(count == 1){
        Number tmp = _data->array[idx1];
        _data->array[idx1] = _data->array[idx2];
        _data->array[idx2] = tmp;
        //std::cout<<*this<<std::endl;
    }else{
        Vector tmp; tmp.resize(count);
        for(int j=0; j<count; j++){
            tmp[j] = _data->array[idx1+j];
            _data->array[idx1+j] = _data->array[idx2+j];
            _data->array[idx2+j] = tmp[j];
        }
    }
    
}

/*Quicksort*/
Number partition(Vector v, Number &lo, Number &hi){
    Number pivot = v[hi];
    Number i = lo;
    for(Number j=lo; j<=hi-1; j++){
        if(v[j]<pivot){
            v.swap(i,j);
            i+=1;
        }
    }
    v.swap(i,hi);
    return i;
}

Vector Vector::sort(Number lo, Number hi){
    if(hi<=-1) hi = *_rows-1;
    if(lo<hi){ 
        Number p = partition(*this,lo,hi);
        this->sort(lo, p-1);
        this->sort(p+1,hi);
    }
    return *this;
}

Vector Vector::reverse(){
    int size = *_rows/2;
    for(Number j=0; j<size; j++){
        this->swap(j,*_rows-j-1);
    }
    return *this;
}

Vector Vector::loadFile(std::string url){
    std::ifstream file;
    file.open(url);
    if(file.fail()) {
        // Validar que no existe fichero
        this->resize(0);
    }else{
        file>>*this;
    }
    file.close();
    return *this;
}
Vector Vector::saveFile(std::string url){
    // Crear ruta si no existe
    
    std::ofstream file;
    file.open(url);
    file<<*this;
    file.close();
    return *this;
}

void Vector::operator+=(Vector v){
    assert(*_rows == v.length());
    for(int j=0; j<*_rows; j++){ _data->array[j] += v[j];}
}

void Vector::operator-=(Vector v){
    assert(*_rows == v.length());
    for(int j=0; j<*_rows; j++){ _data->array[j] -= v[j];}
}

void Vector::operator*=(Number n){
    for(int j=0; j<*_rows; j++){ _data->array[j] *= n;}
}

void Vector::operator/=(Number n){
    for(int j=0; j<*_rows; j++){ _data->array[j] /= n;}
}

void Vector::operator%=(Number n){
    for(int j=0; j<*_rows; j++){ _data->array[j] %= n;}
}

Vector Vector::getCopy(){
    Vector result;
    result.resize(*_rows);
    int size = result.length();
    for(int j=0;j<size; j++){
        result[j] = _data->array[j];
    }
    return result;
}

std::ostream& operator<<(std::ostream& stream, Vector v){
    int size = v.length();
    stream<<"[";
    for(int n=0; n<size; n++){
        if(n!=0) stream<<", ";
        stream<<v[n];
    }
    stream<<"]";
    return stream;
}

std::istream& operator>>(std::istream& stream, Vector &v){
    v = Vector();
    Number value;
    if(stream.peek()==' ') stream>>std::ws;
    if(stream.peek()=='['){
        stream.get(); // Captura el corchete abierto
        while(stream>>value){
            v.append(value);
            if(stream.peek()==']')break;
            else if(stream.peek()==',') stream.get(); // Captura la comma
        }
        stream.get(); // Captura el corchete cerrado
    }
    //if(stream.peek()==' ') stream>>std::ws;
    if(stream.peek()=='\n') stream.get();
    return stream;   
}

// Suma de vectores
Vector operator+(Vector v1,Vector v2){
    Vector result = v1.getCopy();
    result += v2;
    return result;
}

// Resta de vectores
Vector operator-(Vector v1,Vector v2){
    Vector result = v1.getCopy();
    result -= v2;
    return result;
}

// Producto escalar
Number operator*(Vector v1,Vector v2){
    Number result = 0;
    assert(v1.length() == v2.length());
    for(int j=0; j<v1.length(); j++){
        result += v1[j]*v2[j];
    }
    return result;
}

// Producto entre vector y escalar
Vector operator*(Vector v,const Number &n){
    Vector result = v.getCopy();
    result*=n;
    return result;
}

Vector operator*(const Number &n, Vector v){
    return v*n;
}

// Division entre vector y escalar
Vector operator/(Vector v,const Number &n){
    Vector result = v.getCopy();
    result/=n;
    return result;
}
// Residuo
Vector operator%(Vector v,const Number &n){
    Vector result = v.getCopy();
    result%=n;
    return result;
}

Vector zeros(const Number &n){
    Vector z; z.resize(n);
    return z;
}

Vector ones(const Number &n){
    Vector o;
    o.resize(n);
    for(int j=0; j<n; j++) o[j] = 1;
    return o;
}

Vector range(Vector v, const Number &begin, const Number &end, Number value){
    Vector result;
    if(value>0 && end>begin){
        for(Number j=begin; j<=end; j+=value){
            result.append(v[j]);
        }
    }else if(value<0 && begin>end){
        for(Number j=begin; j>=end; j+=value){
            result.append(v[j]);
        }
    }
    return result;
}

Vector sort(Vector v){
    Vector result = v.getCopy();
    return result.sort();
}

Vector reverse(Vector v){
    Vector result = v.getCopy();
    return result.reverse();
}
