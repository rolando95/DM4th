#pragma once

#include "_TemplateArray.h"
#include "_ArrayUtilities.h"


namespace DM4th
{

template<class T>
TemplateArray<T>::TemplateArray() {}

template<class T> template<class ... U>
TemplateArray<T>::TemplateArray(T *data, U ... args)
{
    *this = TemplateArray<T>(data, items<int>(args ...));
}

template<class T>
TemplateArray<T>::TemplateArray(T *data, const TemplateArray<int> &axisArray)
{
    DM4thAssert(axisArray.size()>0);
    DM4thAssert(axisArray.shapeSize()==1);

    this->resize(axisArray);
    int size = mult(axisArray);
    for(int j=0; j<size; ++j)
    {
        std::cout<<data[j]<<std::endl;
        this->data_item(j) = data[j];
    }
}

template<class T>
TemplateArray<T>::TemplateArray(const std::string &str) 
{    
    std::stringstream ss;
    ss << str;
    ss >> *this;
}

template<class T> template<class ... U>
inline void TemplateArray<T>::resize(int axis1, U ... args)
{
    TemplateArray<int> axisArray = items<int>(axis1, args...);
    this->resize(axisArray);
}

template<class T>
inline void TemplateArray<T>::resize(int axis1)
{
    if(this->shapeSize()<=1) this->_resize1DArray(axis1); // 0 || 1 dim to 1 dim
    else
    { // N dim to 1 dim
        int disp = this->_getAxisDisplacement(0);
        int end = _min(axis1, this->shape(0));
        //T* old = super::_data->array._allocAndReturnOldArray(axis1);
        DM4thInternal::_BaseArray<T> old;
        super::_data->array.moveReferenceTo(old);
        super::_data->array.resize(axis1);

        super::_data->shape.resize(1);
        super::_data->shape.set(0, axis1);
        int oldj=0; int newj=0;
        for(; newj<end; ++newj, oldj+=disp)
        {
            super::_data->array[newj] = old[oldj];
        }
        //delete[] old;
    }
}

template<class T>
void TemplateArray<T>::resize(const TemplateArray<int> &axisArray)
{
    DM4thAssert(axisArray.shapeSize()==1);

    if(this->shapeSize()==1)
    { //1 dim to N dim
        int oldShape = this->shape(0);

        DM4thInternal::_BaseArray<T> oldArray(this->_allocZeros(axisArray));

        int newDisp = this->_getAxisDisplacement(0);
        int end = _min(oldShape, this->shape(0));
        int newj = 0;
        for(int oldj=0; oldj<end; ++oldj, newj+=newDisp)
        {
            super::_data->array[newj] = oldArray[oldj];
        }
        //delete[] oldArray;
    }else
    { //N dim to M dim
        TemplateArray<int> oldShape = this->shape();
        TemplateArray<int> oldDisp = this->_getAxisDisplacement();

        DM4thInternal::_BaseArray<T> oldArray(this->_allocZeros(axisArray));

        TemplateArray<int> newShape = this->shape();
        TemplateArray<int> newDisp = this->_getAxisDisplacement();

        if(oldArray.size() == 0) return;

        int end = _min(oldShape.item(0), newShape.item(0));
        for(int j=0; j<end; ++j)
        {
            this->_resize(
                1, 
                oldDisp.item(0)*j, newDisp.item(0)*j, 
                oldDisp, newDisp,
                oldShape, newShape, 
                oldArray
            );
        }
        //delete[] oldArray;
    }
}

template<class T>
inline int TemplateArray<T>::shapeSize() const { return super::_data->shape.size(); }

template<class T>
int TemplateArray<T>::size() const { return super::_data->shape.get(0); }

// template<class T>
// int TemplateArray<T>::itemsCount() const { return super::_data->array.size(); }

template<class T>
TemplateArray<int> TemplateArray<T>::shape() const
{
    TemplateArray<int> result;
    result._resize1DArray(super::_data->shape.size());
    for(int j=0; j<super::_data->shape.size(); ++j)
    {
        result.item(j) = super::_data->shape.get(j);
    }
    return result;
}

template<class T>
inline int TemplateArray<T>::shape(int axis) const       
{
    return super::_data->shape.get(axis);
}

template<class T> template<class ... U>
const TemplateArray<T> &TemplateArray<T>::reshape(int axis1, U ... args)
{
    //int oldShapeMult = mult(this->shape().data(), this->shapeSize());
    int oldShapeMult = mult(super::_data->shape.data(), this->shapeSize());
    int newShapeMult = mult(axis1,args...);
    DM4thAssert(oldShapeMult==newShapeMult);
    
    super::_data->shape.resize(count(axis1,args...));
    this->_reshape(0, axis1, args...);

    return *this;
}

template<class T>
const TemplateArray<T> & TemplateArray<T>::reshape(TemplateArray<int> newShape)
{
    int oldShapeMult = mult(super::_data->shape.data(), this->shapeSize());
    int newShapeMult = mult(newShape.data(), newShape.size());     
    DM4thAssert(newShape.shapeSize()==1);    
    DM4thAssert(oldShapeMult==newShapeMult);

    super::_data->shape.resize(newShape.size());
    for(int j=0; j<newShape.size(); ++j)
    {
        super::_data->shape.set(j, newShape.item(j));
    }

    return *this;
}

template<class T>
TemplateArray<int> TemplateArray<T>::_getAxisDisplacement() const
{
    TemplateArray<int> result;
    result._resize1DArray(super::_data->shape.size());
    int disp = 1;
    for(int j=super::_data->shape.size()-1; j>=0; --j)
    {
        result.item(j) = disp;
        disp *= super::_data->shape.get(j);
    }

    return result;
}

template<class T>
int TemplateArray<T>::_getAxisDisplacement(int axis) const
{
    int disp = 1;
    for(int j=super::_data->shape.size()-1; j>axis; --j)
    {
        disp *= super::_data->shape.get(j);
    }
    return disp;
}

template<class T> template<class AXIS, class ... U>
T &TemplateArray<T>::item(AXIS axis, U ... args) const
{ 
    int x = (int)axis;
    const int pos = this->_item(1,x,args ...); 
    return super::_data->array(pos);
}

template<class T> template<class AXIS>
T &TemplateArray<T>::item(AXIS axis) const
{
    int x = (AXIS)axis;
    DM4thAssert(super::_data->shape.size()==1);
    DM4thAssert(x<super::_data->array.size());
    //DM4thAssert( super::_data->shape.size()==1 && x<super::_data->array.size() );
    return super::_data->array[x];
}

template<class T> template<class AXIS>
T &TemplateArray<T>::item(const TemplateArray<AXIS> &axisArray)
{
    DM4thAssert(axisArray.shapeSize()==1);
    DM4thAssert(axisArray.size()==this->shapeSize());

    int pos = (int)axisArray.data()[0];
    for(int j=1; j<this->shapeSize(); ++j)
    {
        pos = pos*super::_data->shape.get(j) + (int)axisArray.data()[j];
    }

    // int *iter = axisArray.data(); 
    // int pos = *iter;
    // for(int j=1; j<this->shapeSize(); ++j, ++iter)
    // {
    //     pos = pos*super::_data->shape(j) + *iter;
    // }
    return super::_data->array[pos];            
}

template<class T>
TemplateArray<T> TemplateArray<T>::getCopy() const
{
    TemplateArray<T> result;
    result.resize(this->shape());
    for(int j=0; j<this->data_size(); ++j)
    {
        result.data_item(j) = this->data_item(j);
    }
    return result;
}

template<class T> template<class U>
void TemplateArray<T>::push(const U &value, const int pos)
{
    DM4thAssert(this->shapeSize()<=1);
    DM4thAssert( (pos>=0 && pos<= this->shape(0)) || pos==END);
    this->resize(this->shape(0)+1);
    //Append
    if(pos >= this->shape(0) || pos==END) 
    {
        super::_data->array(this->shape(0)-1) = value;
    }
    //Insert
    else 
    {
        for(int j=this->shape(0)-1; j > pos; --j)
        {
            super::_data->array(j) = super::_data->array(j-1);
        }
        super::_data->array(pos) = value;
    }
}

template<class T> template<class U>
void TemplateArray<T>::pushArray(const TemplateArray<U> &other, const int pos){

    if(this->shapeSize()<=1 && other.shapeSize()==1)
    {
        int size = other.size();
        int end = this->shape(0);
        DM4thAssert( (pos>=0 && pos<=end) || pos==END);
        this->resize(end+size);

        //Append
        if(pos==END||pos==end)
        {
            for(int j=0; j<size; ++j)
            {
                super::_data->array(end+j) = (T)other.item(j);
            }
        //Insert
        }else
        {
            for(int j=end+size-1; j>=pos+size; --j)
            {
                super::_data->array(j) = super::_data->array(j-size);
            }
            for(int j=pos; j<pos+size; ++j)
            {
                super::_data->array(j) = (T)other.item(j-pos);
            }
        }
    }
    else if( (this->shapeSize()==0 || this->shapeSize()==2) && other.shapeSize()==1 ){
        int cols;
        if(this->shapeSize()==0) cols = other.shape(0);
        else cols = this->shape(1);

        int end = this->shape(0);
        DM4thAssert( (pos>=0 && pos<=this->shape(0)) || pos==END);
        DM4thAssert(cols==other.shape(0));

        this->resize(this->shape(0)+1, cols);

        //Append
        if(pos>=end || pos==END)
        {
            T *iter = &this->item(this->shape(0)-1,0);
            for(int j=0; j<cols; ++j)
            {
                iter[j] = (T)other.item(j);
            }
        }

        //Insert
        else
        {
            T *src = &this->item(0,0);
            T *dst = &this->item(1,0);
            for(int j=(this->shape(0)-1)*cols-1; j>=pos*cols ; --j){
                dst[j] = src[j];
            }

            T *iter = &this->item(pos,0);
            for(int j=0; j<cols; ++j)
            {
                iter[j] = (T)other.item(j);
            }
        }
    }
    else
    {
        DM4thAssert(false);
    }
}

template<class T>
T TemplateArray<T>::pop(const int idx)
{
    T result;
    DM4thAssert(this->shapeSize()==1 && this->shape(0)>0);
    DM4thAssert( (idx>=0 && idx<this->shape(0)) || idx==END ); 

    if(idx==END || idx==this->shape(0)-1)
    {
        result = this->item(this->shape(0)-1);
    }else{
        T *iter = &this->item(idx);
        result = *iter;
        for(int j=0; j<this->shape(0)-idx-1; ++j)
        {
            iter[j] = iter[j+1];
        }
    }
    this->resize(this->shape(0)-1);
    return result;
}

template<class T>
TemplateArray<T> TemplateArray<T>::popArray(const int pos)
{
    TemplateArray<T> result;
    DM4thAssert( (pos>=0 && pos<this->shape(0)) || pos==END ); 
    
    if(this->shapeSize()==1)
    {
        result = items<T>(this->pop(pos));
    }else 
    if(this->shapeSize()==2)
    {
        result.resize(this->shape(1));
        DM4thAssert(this->shape(0)>0);
        if(pos==this->shape(0)-1 || pos==END)
        {
            T *iter = &this->item(this->shape(0)-1,0);
            for(int j=0; j<this->shape(1); ++j)
            {
                result.item(j) = iter[j];
            }
        }else
        {
            T *iter = &this->item(pos,0);
            for(int j=0; j<this->shape(1); ++j)
            {
                result.item(j) =iter[j];
            }

            T *src = &this->item(pos+1, 0);
            T *dst = &this->item(pos, 0);
            //result = *iter;
            for(int j=0; j<(this->shape(0)-pos-1)*this->shape(1); ++j)
            {
                dst[j] = src[j];
            }
        }
        
    }else
    {
        DM4thAssert(false);
    }
    
    this->resize(this->shape(0)-1, this->shape(1));
    return result;
}

template<class T> template<class ... U>
inline T &TemplateArray<T>::operator()(U ... args){ return this->item(args...); }

template<class T> template<class ... U>
const inline T &TemplateArray<T>::operator()(U ... args) const { return this->item(args...); }

template<class T> template<class U>
inline T &TemplateArray<T>::operator()(TemplateArray<U> axisArray){ this->item(axisArray); }

template<class T> template<class U>
inline const TemplateArray<T> TemplateArray<T>::operator+=(const TemplateArray<U> &other)
{
    this->_data->array += other._arrayData()->array;
    return *this;
}

template<class T> template<class U>
inline TemplateArray<T> TemplateArray<T>::operator+(const TemplateArray<U> &other) const
{
    TemplateArray<T> result = this->getCopy();
    result += other;
    return result;
}

template<class T>
inline const TemplateArray<T> TemplateArray<T>::operator+=(const T &other)
{
    this->_data->array += other;
    return *this;
}

template<class T>
inline const TemplateArray<T> TemplateArray<T>::operator+(const T &other) const
{
    TemplateArray<T> result = this->getCopy();
    result += other;
    return result;
}

template<class T> template<class U>
inline const TemplateArray<T> TemplateArray<T>::operator-=(const TemplateArray<U> &other)
{
    DM4thAssert(super::_data->shape==other._arrayData()->shape);
    this->_data->array -= other._arrayData()->array;
    return *this;
}

template<class T> template<class U>
inline TemplateArray<T> TemplateArray<T>::operator-(const TemplateArray<U> &other) const
{
    TemplateArray<T> result = this->getCopy();
    result -= other;
    return result;
}

template<class T>
inline const TemplateArray<T> TemplateArray<T>::operator-=(const T &other)
{
    this->_data->array -= other;
    return *this;
}

template<class T>
inline const TemplateArray<T> TemplateArray<T>::operator-(const T &other) const
{
    TemplateArray<T> result = this->getCopy();
    result -= other;
    return result;
}

template<class T> template<class U>
const TemplateArray<T> TemplateArray<T>::operator*=(const TemplateArray<U> &other)
{   
    TemplateArray<T> result;
    if(this->data_size()()==1)
    {
        result = other * this->item(0);
    }
    else if(other.data_size()==1)
    {
        result = *this * other.item(0);
    }
    else
    if(this->shapeSize()==1 && other.shapeSize()==1)
    {
        DM4thAssert(this->shape(0)==other.shape(0));
        result.resize(1);

        #if defined DM4thOmpFor
            #pragma omp parallel for
        #endif
        for(int j=0; j<this->shape(0); ++j)
        {
            result.item(0) += this->item(j)*other.item(j);
        }
    }
    else if(this->shapeSize()<=2 && other.shapeSize()<=2)
    {
        DM4thAssert(this->shape(1) == other.shape(0));
        int maxX = this->shape(0);
        int maxY = other.shape(1);
        int maxZ = other.shape(0);

        result.resize(maxX,maxY);
        
        #if defined DM4thOmpFor
            #pragma omp parallel for
        #endif
        for(int x=0; x<maxX; ++x){
            for(int y=0; y<maxY; ++y){
                for(int z=0;z<maxZ; ++z){
                    result.item(x,y) += this->item(x,z) * other.item(z,y);
                }
            }
        }
    }
    else
    {
        DM4thAssert(false);
    }

    *this = result;
    return *this;
}

template<class T> template<class U>
inline TemplateArray<T> TemplateArray<T>::operator*(const TemplateArray<U> &other) const
{
    TemplateArray<T> result = this->getCopy();
    result *= other;
    return result;
}


template<class T>
const TemplateArray<T> TemplateArray<T>::operator*=(const T &other)
{
    this->_data->array *= other;
    return *this;
}

template<class T>
inline TemplateArray<T> TemplateArray<T>::operator*(const T &other) const
{
    TemplateArray<T> result = this->getCopy();
    result *= other;
    return result;
}

template<class T>
inline const TemplateArray<T> TemplateArray<T>::operator/=(const T &other)
{
    this->_data->array /= other;
    return *this;
}

template<class T>
inline TemplateArray<T> TemplateArray<T>::operator/(const T &other) const
{
    TemplateArray<T> result = this->getCopy();
    result /= other;
    return result;
}

template<class T>
inline const TemplateArray<T> TemplateArray<T>::operator%=(const T &other)
{
    this->_data->array %= other;
    return *this;
}

template<class T>
inline TemplateArray<T> TemplateArray<T>::operator%(const T &other)
{
    TemplateArray<T> result = this->getCopy();
    result %= other;
    return result;
}

template<class T> template<class U>
inline bool TemplateArray<T>::operator==(const TemplateArray<U> &other)
{
    return super::_data->shape==other._arrayData()->shape && other._arrayData()->array==super::_data->array;
}

template<class T> template<class U>
inline bool TemplateArray<T>::operator!=(const TemplateArray<U> &other){ return !(*this==other); }

template<class T> template<class U>
bool TemplateArray<T>::operator>(const TemplateArray<U> &other)
{
    const int sizeArr = this->data_size();
    const int oSizeArr = other.data_size();

    int size = _min(sizeArr,oSizeArr); 

    const T* data = this->data();
    const U* odata = other.data();

    for(int j=0; j<size; ++j)
    {
        if(data[j]>odata[j]) return true;
        if(data[j]<odata[j]) return false;
    }            

    if(oSizeArr>=sizeArr) return false;
    return true;
}

template<class T> template<class U>
inline bool TemplateArray<T>::operator<=(const TemplateArray<U> &other){ return !(*this>other); }

template<class T> template<class U>
bool TemplateArray<T>::operator>=(const TemplateArray<U> &other)
{
    const int sizeArr = this->data_size();
    const int oSizeArr = other.data_size();

    int size = _min(sizeArr,oSizeArr); 

    T* data = this->data();
    const U* odata = other.data();

    for(int j=0; j<size; ++j)
    {
        if(data[j]>odata[j]) return true;
        if(data[j]<odata[j]) return false;
    }            

    if(oSizeArr>sizeArr) return false;
    return true;
}

template<class T> template<class U>
inline bool TemplateArray<T>::operator<(TemplateArray<U> &other){ return !(*this>=other); }

template<class T>
std::ostream& TemplateArray<T>::ostream(std::ostream& stream, int ident, bool quotes) const
{
    int c_idx = 0;          
    this->_ostream(stream, 0, c_idx, ident, quotes);
    return stream;
}

template<class T>
std::istream& TemplateArray<T>::istream(std::istream& stream)
{
    int c_size = 0;
    std::queue<T> values;
    bool shapeAllocated = false;
    _handleIstreamSpacesAndNewLines(stream);

    DM4thAssert(stream.peek()=='['); stream.get();
    
    this->_istream(stream, values, 0, c_size, shapeAllocated);
    _handleIstreamSpacesAndNewLines(stream);

    DM4thAssert(stream.peek()==']'); stream.get();

    super::_data->array.resize(c_size);
    for(int j=0; j<c_size; ++j)
    {
        DM4thAssert(!values.empty());
        this->data()[j] = values.front(); 
        values.pop();
    }
    return stream;
}

template<class T>
void TemplateArray<T>::loadFile(std::string url){
    std::ifstream file;
    file.open(url);
    if(file.fail()) {
        // Validar que no existe fichero
        this->resize(0);
    }else{
        file>>*this;
    }
    file.close();
}

template<class T>
void TemplateArray<T>::saveFile(std::string url){
    // Crear ruta si no existe  
    std::ofstream file;
    file.open(url);
    file<<*this;
    file.close();
}

// namespace DM4thInternal {
//     template<class T>
//     int partition(TemplateArray<T> v, bool reverse, const int lo, const int hi)
//     {
//         T pivot = v.data_item(hi);
//         int i = lo;
//         for(int j=lo; j<=hi-1; ++j)
//         {
//             std::cout<<v.data_item(j)<<" "<<pivot<<std::endl;
//             if(reverse && v.data_item(j)>pivot){
//                 T tmp = v.data_item(i);
//                 v.data_item(i) = v.data_item(j);
//                 v.data_item(j) = tmp;
//                 i+=1;
//             }else if(!reverse && v.data_item(j)<pivot){
//                 T tmp = v.data_item(i);
//                 v.data_item(i) = v.data_item(j);
//                 v.data_item(j) = tmp;
//                 i+=1;
//             }
//         }
//         return i;
//     }
// }

// template<class T>
// const TemplateArray<T> TemplateArray<T>::sort(bool reverse, int lo, int hi)
// {
//     if(hi==(int)INF) hi = this->data_size()-1;
//     if(lo<hi){ 
//         int p = DM4thInternal::partition(*this, reverse, lo,hi);
//         this->sort(reverse, lo, p-1);
//         this->sort(reverse, p+1,hi);
//     }
//     return *this;
// }

template<class T>
inline void TemplateArray<T>::_resize1DArray(int size)
{
    //DM4thAssert(this->shapeSize()<=1); // Can be 0 || 1
    super::_data->array.resize(size);
    super::_data->shape.resize(1);
    super::_data->shape(0) = size;
}

template<class T>
inline T *TemplateArray<T>::data(){ return &super::_data->array[0]; }

template<class T>
inline const T *TemplateArray<T>::data() const { return &super::_data->array[0]; }

template<class T>
inline const int TemplateArray<T>::data_size() const { return super::_data->array.size(); }

template<class T>
inline T &TemplateArray<T>::data_item(int idx) { return super::_data->array[idx]; }

template<class T>
inline const T TemplateArray<T>::data_item(int idx) const { return super::_data->array.get(idx); }

template<class T>
void TemplateArray<T>::_resize(int axis, int oldDispCount, int newDispCount, 
            TemplateArray<int> &oldDisp,  TemplateArray<int> &newDisp, 
            TemplateArray<int> &oldShape,  TemplateArray<int> &newShape,
            const DM4thInternal::_BaseArray<T> &oldArray)
{
    int end = _min(oldShape.item(axis), newShape.item(axis));
    if(axis<oldShape.size()-1 && axis<newShape.size()-1){
        for(int j=0; j<end; ++j)
        {
            this->_resize(
                axis+1, 
                oldDispCount+oldDisp.item(axis)*j, newDispCount+newDisp.item(axis)*j,
                oldDisp, newDisp,
                oldShape, newShape,
                oldArray
            );
        }
    }else{
        for(int j=0; j<end; ++j)
        {
            super::_data->array[newDispCount+newDisp.item(axis)*j] = oldArray.get(oldDispCount+oldDisp.item(axis)*j);
        }
    }
}

template<class T> template<class ... U>
void TemplateArray<T>::_reshape(int axis, int first, U ... args)
{
    super::_data->shape.set(axis, first);
    this->_reshape(axis+1, args...);
}

template<class T>
void TemplateArray<T>::_reshape(int axis, int last)
{
    super::_data->shape.set(axis, last);
}

template<class T> template<class ... U>
int TemplateArray<T>::_item(int axis, int pos, int idx, U ... args) const
{
    pos = pos*super::_data->shape.get(axis) + idx;
    return _item(axis+1, pos, args ...);
}

template<class T>
int TemplateArray<T>::_item(int axis, int pos, int idx) const
{
    DM4thAssert(axis+1 == super::_data->shape.size());
    pos = pos*super::_data->shape.get(axis) + idx;
    return pos;
}

template<class T>
DM4thInternal::_BaseArray<T> TemplateArray<T>::_allocZeros(const TemplateArray<int> &axisArray)
{
    int count = 1;
    for(int j=0; j<axisArray.size(); ++j)
    {
        count*= axisArray.data()[j];
    }
    //T* oldArray = super::_data->array._allocAndReturnOldArray(count);
    DM4thInternal::_BaseArray<T> oldArray;
    super::_data->array.moveReferenceTo(oldArray);
    super::_data->array.resize(count);
    super::_data->shape.resize(axisArray.size());
    for(int j=0; j<axisArray.size(); ++j)
    {
        super::_data->shape.set(j,axisArray.data()[j]);
    }
    return oldArray;
}

template<class T>
void TemplateArray<T>::_ostream(std::ostream& stream, int shapeIdx, int& c_idx,  int ident, bool quotes) const       
{
    for(int j=0; j<shapeIdx; ++j)
    {
        for(int k=0; k<ident; ++k) stream<<" ";
    }
    stream << "[";
    if(this->shapeSize()>shapeIdx+1) 
    {
        stream<<"\n";
        for(int j=0; j<this->shape(shapeIdx); ++j)
        {
            
            if(j!=0) stream<<",\n";
            this->_ostream(stream, shapeIdx+1,c_idx, ident, quotes);
        }
        stream<<"\n";
        for(int j=0; j<shapeIdx; ++j)
        {
            for(int k=0; k<ident; ++k) stream<<" ";
        }
    }else
    {
        for(int j=0; j<this->shape(shapeIdx); ++j, ++c_idx)
        {
            if(j!=0) stream<<", ";
            if(quotes) stream<<"\"";
            stream<<this->data()[c_idx];
            if(quotes) stream<<"\"";
        }
    }
    stream << "]";
}

template<class T>
void TemplateArray<T>::_istream(std::istream& stream, std::queue<T> &values, int shapeIdx, int& c_size, bool &shapeAllocated)
{
    int size=0;
    _handleIstreamSpacesAndNewLines(stream);
    if(stream.peek()=='[')
    {
        while (true)
        {
            _handleIstreamSpacesAndNewLines(stream);
            DM4thAssert(stream.peek()=='['); stream.get();

            _handleIstreamSpacesAndNewLines(stream);
            if(stream.peek()==']') break; //This dim is empty

            this->_istream(stream, values, shapeIdx+1, c_size, shapeAllocated);
            size+=1;
            
            DM4thAssert(stream.peek()==']'); stream.get();

            _handleIstreamSpacesAndNewLines(stream);
            if(stream.peek()==']'){ break; }
            else if(stream.peek()==',') { stream.get(); }
            else DM4thAssert(false);
        }
    }else
    {
        T value;
        while (true)
        {
            _handleIstreamSpacesAndNewLines(stream);
            if(stream.peek()==']') break; //This dim is empty
            
            stream>>value;
            values.push(value);
            size += 1;
            c_size += 1;
            
            _handleIstreamSpacesAndNewLines(stream);
            if(stream.peek()==']'){ break; }
            else if(stream.peek()==',') { stream.get(); }
            else DM4thAssert(false);
        }

        if(!shapeAllocated)
        {
            for(int j=0; j<super::_data->shape.size(); ++j)
            {
                super::_data->shape.set(j, 0);
            }
            super::_data->shape.resize(shapeIdx+1);
            shapeAllocated = true;
        }
    }

    DM4thAssert(
        size > 0  && 
        (
            super::_data->shape.get(shapeIdx) == 0 ||
            super::_data->shape.get(shapeIdx) == size
        )
    );
    super::_data->shape.set(shapeIdx, size);
    //std::cout<<size<<" "<<shapeIdx+1<<std::endl;      
}

template<class T>
inline std::ostream& operator<<(std::ostream& stream, const TemplateArray<T> &arr)
{
    return arr.ostream(stream,4);
}

template<class T>
inline std::istream& operator>>(std::istream& stream, TemplateArray<T> &arr)
{
    return arr.istream(stream);
}

}