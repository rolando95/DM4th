#pragma once

#include "NDArray.h"
#include "NDArrayUtilities.h"


namespace DM4th
{

template<class T>
NDArray<T>::NDArray() {}

template<class T> template<class ... U>
NDArray<T>::NDArray(T *data, U ... args)
{
    *this = NDArray<T>(data, items<int>(args ...));
}

template<class T>
NDArray<T>::NDArray(T *data, const NDArray<int> &axisArray)
{
    DM4thAssert(axisArray.size()>0);
    DM4thAssert(axisArray.shapeSize()==1);

    this->resize(axisArray);
    int size = DM4thNDArrayUtils::mult(axisArray);
    for(int j=0; j<size; ++j)
    {
        this->data_item(j) = data[j];
    }
}

template<class T>
NDArray<T>::NDArray(const std::string &str) 
{    
    std::stringstream ss;
    ss << str;
    ss >> *this;
}

template<class T> template<class U>
NDArray<T>::operator NDArray<U>()
{
    NDArray<U> result;
    result.resize(this->shape());
    for(int j=0; j<this->data_size(); ++j)
    {
        result.data_item(j) = (U)this->data_item(j);
    }
    return result;
}

template<class T> template<class ... U>
inline void NDArray<T>::resize(int axis1, U ... args)
{
    NDArray<int> axisArray = items<int>(axis1, args...);
    this->resize(axisArray);
}

template<class T>
inline void NDArray<T>::resize(int axis1)
{
    if(this->shapeSize()<=1) this->_resize1DArray(axis1); // 0 || 1 dim to 1 dim
    else
    { // N dim to 1 dim
        int disp = this->_getAxisDisplacement(0);
        int end = _min(axis1, this->shape(0));
        //T* old = this->_data->array._allocAndReturnOldArray(axis1);
        DM4thInternal::BaseArray<T> old;
        this->_data->array.moveReferenceTo(old);
        this->_data->array.resize(axis1);

        this->_data->shape.resize(1);
        this->_data->shape.set(0, axis1);
        int oldj=0; int newj=0;
        for(; newj<end; ++newj, oldj+=disp)
        {
            this->_data->array[newj] = old[oldj];
        }
        //delete[] old;
    }
}

template<class T>
void NDArray<T>::resize(const NDArray<int> &axisArray)
{
    DM4thAssert(axisArray.shapeSize()==1);

    if(this->shapeSize()==1)
    { //1 dim to N dim
        int oldShape = this->shape(0);

        DM4thInternal::BaseArray<T> oldArray(this->_allocZeros(axisArray));

        int newDisp = this->_getAxisDisplacement(0);
        int end = _min(oldShape, this->shape(0));
        int newj = 0;
        for(int oldj=0; oldj<end; ++oldj, newj+=newDisp)
        {
            this->_data->array[newj] = oldArray[oldj];
        }
        //delete[] oldArray;
    }else
    { //N dim to M dim
        NDArray<int> oldShape = this->shape();
        NDArray<int> oldDisp = this->_getAxisDisplacement();

        DM4thInternal::BaseArray<T> oldArray(this->_allocZeros(axisArray));

        NDArray<int> newShape = this->shape();
        NDArray<int> newDisp = this->_getAxisDisplacement();

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
inline int NDArray<T>::shapeSize() const { return this->_data->shape.size(); }

template<class T>
int NDArray<T>::size() const { return this->_data->shape.get(0); }

// template<class T>
// int NDArray<T>::itemsCount() const { return this->_data->array.size(); }

template<class T>
NDArray<int> NDArray<T>::shape() const
{
    NDArray<int> result;
    result._resize1DArray(this->_data->shape.size());
    for(int j=0; j<this->_data->shape.size(); ++j)
    {
        result.item(j) = this->_data->shape.get(j);
    }
    return result;
}

template<class T>
inline int NDArray<T>::shape(int axis) const       
{
    return this->_data->shape.get(axis);
}

template<class T> template<class ... U>
const NDArray<T> &NDArray<T>::reshape(int axis1, U ... args)
{
    //int oldShapeMult = mult(this->shape().data(), this->shapeSize());
    int oldShapeMult = DM4thCArrayUtils::mult(this->_data->shape.data(), this->shapeSize());
    int newShapeMult = DM4thUtils::mult(axis1,args...);
    DM4thAssert(oldShapeMult==newShapeMult);
    
    this->_data->shape.resize(DM4thUtils::count(axis1,args...));
    this->_reshape(0, axis1, args...);

    return *this;
}

template<class T>
const NDArray<T> & NDArray<T>::reshape(NDArray<int> newShape)
{
    int oldShapeMult = DM4thCArrayUtils::mult(this->_data->shape.data(), this->shapeSize());
    int newShapeMult = DM4thCArrayUtils::mult(newShape.data(), newShape.size());     
    DM4thAssert(newShape.shapeSize()==1);    
    DM4thAssert(oldShapeMult==newShapeMult);

    this->_data->shape.resize(newShape.size());
    for(int j=0; j<newShape.size(); ++j)
    {
        this->_data->shape.set(j, newShape.item(j));
    }

    return *this;
}

template<class T>
NDArray<T> NDArray<T>::flatten()
{
    NDArray<T> result = this->getCopy();
    result.reshape(this->data_size());
    return result;
}

template<class T>
int NDArray<T>::_partition(bool reverse, const int lo, const int hi)
{
    T pivot = this->data_item( (lo+hi)/2 );
    int i = lo;
    for(int j=lo; j<hi; ++j)
    {
        if(
            (reverse && this->data_item(j)>pivot) ||
            (!reverse && this->data_item(j)<pivot)
        )
        {
            this->_data->array.swap(i,j);
            i+=1;
        }
    }
    this->_data->array.swap(i,hi);
    return i;
}

template<class T>
void NDArray<T>::sort(bool reverse, int lo, int hi)
{
    if(hi==(int)END) hi = this->data_size()-1;
    if(lo<hi){ 
        int p = this->_partition(reverse, lo,hi);
        this->sort(reverse, lo, p-1);
        this->sort(reverse, p+1,hi);
    }
}

template<class T> template<class U, class V>
inline void NDArray<T>::swap(U idx1, V idx2)
{
    DM4thAssert(idx1<this->size() && idx2<this->size());
    int disp = this->_getAxisDisplacement(0);

    int pos1 = (int)idx1*disp;
    int pos2 = (int)idx2*disp;

    
    for(int j=0; j<disp; ++j)
    {
        this->_data->array.swap(pos1+j, pos2+j);
    }
}

template<class T> template<class AXIS, class ... U>
T &NDArray<T>::item(AXIS axis, U ... args) const
{ 
    int x = (int)axis;
    const int pos = this->_item(1,x,args ...); 
    return this->_data->array(pos);
}

template<class T> template<class AXIS>
T &NDArray<T>::item(AXIS axis) const
{
    int x = (AXIS)axis;
    DM4thAssert(this->_data->shape.size()==1);
    DM4thAssert(x<this->_data->array.size());
    //DM4thAssert( this->_data->shape.size()==1 && x<this->_data->array.size() );
    return this->_data->array[x];
}

template<class T> template<class AXIS>
T &NDArray<T>::item(const NDArray<AXIS> &axisArray)
{
    DM4thAssert(axisArray.shapeSize()==1);
    DM4thAssert(axisArray.size()==this->shapeSize());

    int pos = (int)axisArray.data()[0];
    for(int j=1; j<this->shapeSize(); ++j)
    {
        pos = pos*this->_data->shape.get(j) + (int)axisArray.data()[j];
    }

    // int *iter = axisArray.data(); 
    // int pos = *iter;
    // for(int j=1; j<this->shapeSize(); ++j, ++iter)
    // {
    //     pos = pos*this->_data->shape(j) + *iter;
    // }
    return this->_data->array[pos];            
}

template<class T>
NDArray<T> NDArray<T>::getCopy() const
{
    NDArray<T> result;
    result.resize(this->shape());
    for(int j=0; j<this->data_size(); ++j)
    {
        result.data_item(j) = this->data_item(j);
    }
    return result;
}

template<class T> template<class U>
void NDArray<T>::push(const U &value, const int pos)
{
    DM4thAssert(this->shapeSize()<=1);
    DM4thAssert( (pos>=0 && pos<= this->shape(0)) || pos==END);
    this->resize(this->shape(0)+1);
    //Append
    if(pos >= this->shape(0) || pos==END) 
    {
        this->_data->array(this->shape(0)-1) = value;
    }
    //Insert
    else 
    {
        for(int j=this->shape(0)-1; j > pos; --j)
        {
            this->_data->array(j) = this->_data->array(j-1);
        }
        this->_data->array(pos) = value;
    }
}

template<class T> template<class U>
void NDArray<T>::pushArray(const NDArray<U> &other, const int pos){

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
                this->_data->array(end+j) = (T)other.item(j);
            }
        //Insert
        }else
        {
            for(int j=end+size-1; j>=pos+size; --j)
            {
                this->_data->array(j) = this->_data->array(j-size);
            }
            for(int j=pos; j<pos+size; ++j)
            {
                this->_data->array(j) = (T)other.item(j-pos);
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
T NDArray<T>::pop(const int idx)
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
NDArray<T> NDArray<T>::popArray(const int pos)
{
    NDArray<T> result;
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
inline T &NDArray<T>::operator()(U ... args){ return this->item(args...); }

template<class T> template<class ... U>
const inline T &NDArray<T>::operator()(U ... args) const { return this->item(args...); }

template<class T> template<class U>
inline T &NDArray<T>::operator()(NDArray<U> axisArray){ return this->item(axisArray); }

// template<class T> template<class U>
// typename NDArray<T>::SubArray NDArray<T>::operator[](NDArray<U> idx)
// {
//     return this->subArr(idx);
// } 
// template<class T>
// typename NDArray<T>::SubArray NDArray<T>::operator[](number idx)
// {
//     return this->subArr(idx);
// } 


template<class T> template<class U>
inline const NDArray<T> NDArray<T>::operator+=(const NDArray<U> &other)
{
    if(this->data_size()==1)
    {
        T item = this->data_item(0);
        this->resize(other.shape());

        #if defined DM4thOmpFor
            #pragma omp parallel for shared(other)
        #endif 

        for(int j=0; j<other.data_size(); ++j)
        {
            this->data_item(j) = item + other.data_item(j);
        }

    }else if(other.data_size()==1)
    {
        this->_data->array += other.data_item(0);
    }else
    {
        this->_data->array += other.getArrayData().array;
    }
    return *this;
}

template<class T> template<class U>
inline NDArray<T> NDArray<T>::operator+(const NDArray<U> &other) const
{
    NDArray<T> result = this->getCopy();
    result += other;
    return result;
}

template<class T>
inline const NDArray<T> NDArray<T>::operator+=(const T &other)
{
    this->_data->array += other;
    return *this;
}

template<class T>
inline const NDArray<T> NDArray<T>::operator+(const T &other) const
{
    NDArray<T> result = this->getCopy();
    result += other;
    return result;
}

template<class T> template<class U>
inline const NDArray<T> NDArray<T>::operator-=(const NDArray<U> &other)
{
    if(this->data_size()==1)
    {
        T item = this->data_item(0);
        this->resize(other.shape());

        #if defined DM4thOmpFor
            #pragma omp parallel for shared(other)
        #endif 

        for(int j=0; j<other.data_size(); ++j)
        {
            this->data_item(j) = item - other.data_item(j);
        }

    }else if(other.data_size()==1)
    {
        this->_data->array -= other.data_item(0);
    }else
    {
        this->_data->array -= other.getArrayData().array;
    }
    return *this;
}

template<class T> template<class U>
inline NDArray<T> NDArray<T>::operator-(const NDArray<U> &other) const
{
    NDArray<T> result = this->getCopy();
    result -= other;
    return result;
}

template<class T>
inline const NDArray<T> NDArray<T>::operator-=(const T &other)
{
    this->_data->array -= other;
    return *this;
}

template<class T>
inline const NDArray<T> NDArray<T>::operator-(const T &other) const
{
    NDArray<T> result = this->getCopy();
    result -= other;
    return result;
}

template<class T> template<class U>
const NDArray<T> NDArray<T>::operator*=(const NDArray<U> &other)
{   
    NDArray<T> result;
    if(this->data_size()==1)
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

        result.item(0) = 0;
        
        #if defined DM4thOmpFor
           #pragma omp parallel for shared(other)
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
            #pragma omp parallel for shared(other)
        #endif

        for(int x=0; x<maxX; ++x){
            for(int y=0; y<maxY; ++y){
                result.item(x,y) = 0;
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
    result._moveDataRefTo(*this);
    return *this;
}

template<class T> template<class U>
inline NDArray<T> NDArray<T>::operator*(const NDArray<U> &other) const
{
    NDArray<T> result = this->getCopy();
    result *= other;
    return result;
}


template<class T>
const NDArray<T> NDArray<T>::operator*=(const T &other)
{
    this->_data->array *= other;
    return *this;
}

template<class T>
inline NDArray<T> NDArray<T>::operator*(const T &other) const
{
    NDArray<T> result = this->getCopy();
    result *= other;
    return result;
}

template<class T>
inline const NDArray<T> NDArray<T>::operator/=(const T &other)
{
    this->_data->array /= other;
    return *this;
}

template<class T>
inline NDArray<T> NDArray<T>::operator/(const T &other) const
{
    NDArray<T> result = this->getCopy();
    result /= other;
    return result;
}

template<class T>
inline const NDArray<T> NDArray<T>::operator%=(const T &other)
{
    this->_data->array %= other;
    return *this;
}

template<class T>
inline NDArray<T> NDArray<T>::operator%(const T &other)
{
    NDArray<T> result = this->getCopy();
    result %= other;
    return result;
}

// template<class T> template<class U>
// inline bool NDArray<T>::operator==(const NDArray<U> &other)
template<class T> template<class U>
inline bool NDArray<T>::isEqualTo(const NDArray<U> &other) const
{
    return other.getArrayData().array==this->_data->array;
}

template<class T>
NDArray<bool> NDArray<T>::operator==(T other) const
{
    NDArray<bool> result;
    result.resize(this->shape());

    #if defined DM4thOmpFor
        #pragma omp parallel for shared(other)
    #endif

    for(int j=0; j<this->data_size(); ++j)
    {
        result.data_item(j) = this->data_item(j) == other; 
    }
    return result;
}

template<class T>
NDArray<bool> NDArray<T>::operator!=(T other) const
{
    NDArray<bool> result;
    result.resize(this->shape());

    #if defined DM4thOmpFor
        #pragma omp parallel for shared(other)
    #endif

    for(int j=0; j<this->data_size(); ++j)
    {
        result.data_item(j) = this->data_item(j) != other; 
    }
    return result;
}

template<class T>
NDArray<bool> NDArray<T>::operator> (T other) const
{
    NDArray<bool> result;
    result.resize(this->shape());

    #if defined DM4thOmpFor
        #pragma omp parallel for shared(other)
    #endif

    for(int j=0; j<this->data_size(); ++j)
    {
        result.data_item(j) = this->data_item(j) > other; 
    }
    return result;
}

template<class T>
NDArray<bool> NDArray<T>::operator<=(T other) const
{
    NDArray<bool> result;
    result.resize(this->shape());

    #if defined DM4thOmpFor
        #pragma omp parallel for shared(other)
    #endif

    for(int j=0; j<this->data_size(); ++j)
    {
        result.data_item(j) = this->data_item(j) <= other; 
    }
    return result;
}

template<class T>
NDArray<bool> NDArray<T>::operator>=(T other) const
{
    NDArray<bool> result;
    result.resize(this->shape());

    #if defined DM4thOmpFor
        #pragma omp parallel for shared(other)
    #endif

    for(int j=0; j<this->data_size(); ++j)
    {
        result.data_item(j) = this->data_item(j) >= other; 
    }
    return result;
}

template<class T>
NDArray<bool> NDArray<T>::operator<(T other) const
{
    NDArray<bool> result;
    result.resize(this->shape());

    #if defined DM4thOmpFor
        #pragma omp parallel for shared(other)
    #endif

    for(int j=0; j<this->data_size(); ++j)
    {
        result.data_item(j) = this->data_item(j) < other; 
    }
    return result;
}

template<class T>
NDArray<bool> NDArray<T>::operator==(const NDArray<T> &other) const
{
    NDArray<bool> result;
    if(this->data_size()==other.data_size())
    {
        result.resize(this->shape());

        #if defined DM4thOmpFor
            #pragma omp parallel for shared(other)
        #endif

        for(int j=0; j<this->data_size(); ++j)
        {
            result.data_item(j) = this->data_item(j) == other.data_item(j);
        }
    }
    else if(this->data_size()==1)
    {
        result = other==this->data_item(0);
    }
    else if(other.data_size()==1)
    {
        result = *this==other.data_item(0);
    }
    else
    {
        DM4thAssert(false);
    }

    return result;
}

template<class T>
NDArray<bool> NDArray<T>::operator!=(const NDArray<T> &other) const
{
    NDArray<bool> result;
    if(this->data_size()==other.data_size())
    {
        result.resize(this->shape());

        #if defined DM4thOmpFor
            #pragma omp parallel for shared(other)
        #endif

        for(int j=0; j<this->data_size(); ++j)
        {
            result.data_item(j) = this->data_item(j) != other.data_item(j);
        }
    }
    else if(this->data_size()==1)
    {
        result = other!=this->data_item(0);
    }
    else if(other.data_size()==1)
    {
        result = *this!=other.data_item(0);
    }
    else
    {
        DM4thAssert(false);
    }

    return result;
}

template<class T>
NDArray<bool> NDArray<T>::operator>(const NDArray<T> &other) const
{
    NDArray<bool> result;
    if(this->data_size()==other.data_size())
    {
        result.resize(this->shape());

        #if defined DM4thOmpFor
            #pragma omp parallel for shared(other)
        #endif

        for(int j=0; j<this->data_size(); ++j)
        {
            result.data_item(j) = this->data_item(j) > other.data_item(j);
        }
    }
    else if(this->data_size()==1)
    {
        result = other>this->data_item(0);
    }
    else if(other.data_size()==1)
    {
        result = *this>other.data_item(0);
    }
    else
    {
        DM4thAssert(false);
    }

    return result;
}

template<class T>
NDArray<bool> NDArray<T>::operator<=(const NDArray<T> &other) const
{
    NDArray<bool> result;
    if(this->data_size()==other.data_size())
    {
        result.resize(this->shape());

        #if defined DM4thOmpFor
            #pragma omp parallel for shared(other)
        #endif

        for(int j=0; j<this->data_size(); ++j)
        {
            result.data_item(j) = this->data_item(j) <= other.data_item(j);
        }
    }
    else if(this->data_size()==1)
    {
        result = other<=this->data_item(0);
    }
    else if(other.data_size()==1)
    {
        result = *this<=other.data_item(0);
    }
    else
    {
        DM4thAssert(false);
    }

    return result;
}

template<class T>
NDArray<bool> NDArray<T>::operator>=(const NDArray<T> &other) const
{
    NDArray<bool> result;
    if(this->data_size()==other.data_size())
    {
        result.resize(this->shape());

        #if defined DM4thOmpFor
            #pragma omp parallel for shared(other)
        #endif

        for(int j=0; j<this->data_size(); ++j)
        {
            result.data_item(j) = this->data_item(j) >= other.data_item(j);
        }
    }
    else if(this->data_size()==1)
    {
        result = other>=this->data_item(0);
    }
    else if(other.data_size()==1)
    {
        result = *this!=other.data_item(0);
    }
    else
    {
        DM4thAssert(false);
    }

    return result;
}

template<class T>
NDArray<bool> NDArray<T>::operator<(const NDArray<T> &other) const
{
    NDArray<bool> result;
    if(this->data_size()==other.data_size())
    {
        result.resize(this->shape());

        #if defined DM4thOmpFor
            #pragma omp parallel for shared(other)
        #endif

        for(int j=0; j<this->data_size(); ++j)
        {
            result.data_item(j) = this->data_item(j) < other.data_item(j);
        }
    }
    else if(this->data_size()==1)
    {
        result = other<this->data_item(0);
    }
    else if(other.data_size()==1)
    {
        result = *this<other.data_item(0);
    }
    else
    {
        DM4thAssert(false);
    }

    return result;
}

template<> template<>
inline NDArray<bool> NDArray<bool>::operator&&(const NDArray<bool> &other) const
{
    NDArray<bool> result;
    result.resize(this->shape());

    #if defined DM4thOmpFor
        #pragma omp parallel for shared(other)
    #endif

    for(int j=0; j<this->data_size(); ++j)
    {
        result.data_item(j) = this->data_item(j) && other.data_item(j); 
    }
    return result;
}

template<> template<>
inline NDArray<bool> NDArray<bool>::operator||(const NDArray<bool> &other) const
{
    NDArray<bool> result;
    result.resize(this->shape());

    #if defined DM4thOmpFor
        #pragma omp parallel for shared(other)
    #endif

    for(int j=0; j<this->data_size(); ++j)
    {
        result.data_item(j) = this->data_item(j) || other.data_item(j); 
    }
    return result;
}

template<> template<>
inline NDArray<bool> NDArray<bool>::operator!() const
{
    NDArray<bool> result;
    result.resize(this->shape());

    #if defined DM4thOmpFor
        #pragma omp parallel for
    #endif

    for(int j=0; j<this->data_size(); ++j)
    {
        result.data_item(j) = !this->data_item(j); 
    }
    return result;
}

template<class T>
bool NDArray<T>::any(T value)
{
    bool result = false;
    for(int j=0; j<this->data_size(); ++j)
    {
        if(this->data_item(j)==value)
        {
            result = true;
            break;
        }
    }
    return result;
}

template<class T>
bool NDArray<T>::all(T value)
{
    bool result = true;
    for(int j=0; j<this->data_size(); ++j)
    {
        if(this->data_item(j)!=value)
        {
            result = false;
            break;
        }
    }
    return result;
}

template<class T>
std::ostream& NDArray<T>::ostream(std::ostream& stream, int ident, bool quotes) const
{
    int c_idx = 0;          
    this->_ostream(stream, 0, c_idx, ident, quotes);
    return stream;
}

template<class T>
std::istream& NDArray<T>::istream(std::istream& stream)
{
    int c_size = 0;
    std::queue<T> values;
    bool shapeAllocated = false;
    DM4thInternal::_handleIstreamSpacesAndNewLines(stream);

    DM4thAssert(stream.peek()=='['); stream.get();
    
    this->_istream(stream, values, 0, c_size, shapeAllocated);
    DM4thInternal::_handleIstreamSpacesAndNewLines(stream);

    DM4thAssert(stream.peek()==']'); stream.get();

    this->_data->array.resize(c_size);
    for(int j=0; j<c_size; ++j)
    {
        DM4thAssert(!values.empty());
        this->data()[j] = values.front(); 
        values.pop();
    }
    return stream;
}

template<class T>
void NDArray<T>::loadFile(std::string url){
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
void NDArray<T>::saveFile(std::string url){
    // Crear ruta si no existe  
    std::ofstream file;
    file.open(url);
    file<<*this;
    file.close();
}

template<class T>
inline void NDArray<T>::_resize1DArray(int size)
{
    //DM4thAssert(this->shapeSize()<=1); // Can be 0 || 1
    this->_data->array.resize(size);
    this->_data->shape.resize(1);
    this->_data->shape(0) = size;
}

template<class T>
inline T *NDArray<T>::data(){ return &this->_data->array[0]; }

template<class T>
inline const T *NDArray<T>::data() const { return &this->_data->array[0]; }

template<class T>
inline T *NDArray<T>::data_copy() 
{
    T *ptr = new T[this->data_size()];
    for(int j=0; j<data_size(); ++j)
    {
        ptr[j] = this->data_item(j);
    }
    return ptr;
}

template<class T>
inline const int NDArray<T>::data_size() const { return this->_data->array.size(); }

template<class T>
inline T &NDArray<T>::data_item(int idx) { return this->_data->array[idx]; }

template<class T>
inline const T NDArray<T>::data_item(int idx) const { return this->_data->array.get(idx); }

template<class T>
NDArray<int> NDArray<T>::_getAxisDisplacement() const
{
    NDArray<int> result;
    result._resize1DArray(this->_data->shape.size());
    int disp = 1;
    for(int j=this->_data->shape.size()-1; j>=0; --j)
    {
        result.item(j) = disp;
        disp *= this->_data->shape.get(j);
    }

    return result;
}

template<class T>
int NDArray<T>::_getAxisDisplacement(int axis) const
{
    int disp = 1;
    for(int j=this->_data->shape.size()-1; j>axis; --j)
    {
        disp *= this->_data->shape.get(j);
    }
    return disp;
}

///////////////////// SubArray
template<class T> template<class ...U>
NDArray<T>::SubArray::SubArray(NDArray<T> &ptr, U ... args) : _ptr(ptr) {
    this->setRef( castToNDArray(args) ...);
}

template<class T>
NDArray<T>::SubArray::operator NDArray<T>() const
{
    NDArray<T> result;
    result.resize(this->_subArray.shape());
    for(int j=0; j<this->_subArray.data_size(); ++j)
    {
        result.data_item(j) = *this->_subArray.data_item(j);
    }
    return result;
}

template<class T>
const typename NDArray<T>::SubArray &NDArray<T>::SubArray::operator=(const NDArray<T>::SubArray &other)
{
    DM4thAssert(this->_subArray.data_size()==other._subArray.data_size());
    if(&this->_ptr!=&other._ptr)
    {
        for(int j=0; j<this->_subArray.data_size(); ++j)
        {
            *this->_subArray.data_item(j) = *other._subArray.data_item(j);
        }
    }else{
        NDArray<T> tmp;
        tmp.resize(this->_subArray.shape());
        for(int j=0; j<this->_subArray.data_size(); ++j)
        {
            tmp.data_item(j) = *other._subArray.data_item(j);
        }
                for(int j=0; j<this->_subArray.data_size(); ++j)
        {
            *this->_subArray.data_item(j) = tmp.data_item(j);
        }
    }
    return *this;
}

template<class T>
const typename NDArray<T>::SubArray &NDArray<T>::SubArray::operator=(const T &other)
{
    for(int j=0; j<this->_subArray.data_size(); ++j)
    {
        *this->_subArray.data_item(j) = other;
    }
    return *this;
}

template<class T>
const typename NDArray<T>::SubArray &NDArray<T>::SubArray::operator=(const NDArray<T> &other)
{
    DM4thAssert(this->_subArray.data_size()==other.data_size());
    if(&this->_ptr!=&other)
    {
        for(int j=0; j<this->_subArray.data_size(); ++j)
        {
            *this->_subArray.data_item(j) = other.data_item(j);
        }
    }else{
        NDArray<T> tmp;
        tmp.resize(this->_subArray.shape());
        for(int j=0; j<this->_subArray.data_size(); ++j)
        {
            tmp.data_item(j) = other.data_item(j);
        }
                for(int j=0; j<this->_subArray.data_size(); ++j)
        {
            *this->_subArray.data_item(j) = tmp.data_item(j);
        }
    }
    return *this;
}


template<class T> template<class ... U>
typename NDArray<T>::SubArray NDArray<T>::SubArray::operator()(U ... args)
{
    return NDArray(*this).subArray(args...);
}

template<class T> template<class U>
typename NDArray<T>::SubArray NDArray<T>::SubArray::operator[](U idx)
{
    return NDArray(*this).subArray(idx);
}

template<class T> template<class U, class ... V>
void NDArray<T>::SubArray::setShapeRef(int axis, NDArray<int> &shape, NDArray<U> first, V ... args)
{
    shape(axis) = first.size();
    this->setShapeRef(axis+1, shape, castToNDArray(args) ...);
}

template<class T>
void NDArray<T>::SubArray::setShapeRef(int axis, NDArray<int> &shape)
{
    DM4thAssert(axis<=this->_ptr.shapeSize());

    for(int j=axis; j<this->_ptr.shapeSize(); ++j)
    {
        shape(j) = this->_ptr.shape(j); // All elemenents of these axis
    }
}

template<class T> template<class U, class ... V>
void NDArray<T>::SubArray::setRef(NDArray<U> first, V... args)
{
    NDArray<int> oldShape = this->_ptr.shape();
    NDArray<int> oldDisp = this->_ptr._getAxisDisplacement();

    NDArray<int> newShape;
    newShape.resize(this->_ptr.shapeSize());
    this->setShapeRef(0,newShape, castToNDArray(first), castToNDArray(args)...);
    this->_subArray.resize(newShape);
    
    NDArray<int> newDisp = this->_subArray._getAxisDisplacement();

    if(this->_ptr.shapeSize()>1)
    {
        for( int j=0; j<first.size(); ++j )
        {
            this->slider(
                1,
                oldDisp.item(0)*(int)first(j),
                newDisp.item(0)*j,
                oldDisp, newDisp,
                castToNDArray(args) ...
            );
        }
    }
    else{
        DM4thAssert(DM4thUtils::count(first, args...)==1);
        for( int j=0; j<first.size(); ++j )
        {
            this->_1DSlider(first(j),j);
        }
    }


    NDArray<int> realNewShape;
    int realSize=0;
    for(int j=0; j<newShape.size();++j)
    {
        if(newShape(j)>1) ++realSize;
    }

    if(realSize>1)
    {
        realNewShape.resize(realSize);
        realSize=0;
        for(int j=0; j<newShape.size(); ++j)
        {
            if(newShape(j)>1)
            {
                realNewShape(realSize) = newShape(j);
                ++realSize;
            }
        }
        this->_subArray.reshape(realNewShape);
    }else{
        this->_subArray.reshape(DM4thNDArrayUtils::mult(newShape));
    }


    
}

template<class T> template<class U, class ... V>
void NDArray<T>::SubArray::slider(
    int axis,
    int oldDispCount, int newDispCount,
    NDArray<int> oldDisp, NDArray<int> newDisp,
    NDArray<U> first, V ... args
)
{
    if(axis<this->_ptr.shapeSize()-1)
    {
        for(int j=0; j<first.size(); ++j)
        {
            this->slider(
                axis+1,
                oldDispCount+oldDisp.item(axis)*(int)first(j),
                newDispCount+newDisp.item(axis)*j,
                oldDisp, newDisp,
                castToNDArray(args) ...
            );
        }
    }else{
        for(int j=0; j<first.size(); ++j)
        {
            int to = newDispCount+newDisp.item(axis)*j;
            int from = oldDispCount+oldDisp.item(axis)*(int)first(j);
            this->_subArray.data_item(to) = &this->_ptr.data_item(from);
        }
    }
}

template<class T>
void NDArray<T>::SubArray::slider(
    int axis,
    int oldDispCount, int newDispCount,
    NDArray<int> oldDisp, NDArray<int> newDisp
)
{
    if(axis<this->_ptr.shapeSize()-1)
    {
        for(int j=0; j<this->_ptr.shape(axis); ++j)
        {
            this->slider(
                axis+1,
                oldDispCount+oldDisp.item(axis)*j,
                newDispCount+newDisp.item(axis)*j,
                oldDisp, newDisp
            );
        }
    }else{
        for(int j=0; j<this->_ptr.shape(axis); ++j)
        {
            int to = newDispCount+newDisp.item(axis)*j;
            int from = oldDispCount+oldDisp.item(axis)*j;
            this->_subArray.data_item(to) = &this->_ptr.data_item(from);
        }
    }
}

template<class T>
void NDArray<T>::SubArray::_1DSlider(int oldDisp, int newDisp)
{
    this->_subArray.data_item(newDisp) = &this->_ptr.data_item(oldDisp);
}

/////////////////////
template<class T>
void NDArray<T>::_resize(int axis, int oldDispCount, int newDispCount, 
            NDArray<int> &oldDisp,  NDArray<int> &newDisp, 
            NDArray<int> &oldShape,  NDArray<int> &newShape,
            const DM4thInternal::BaseArray<T> &oldArray)
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
            this->_data->array[newDispCount+newDisp.item(axis)*j] = oldArray.get(oldDispCount+oldDisp.item(axis)*j);
        }
    }
}

template<class T> template<class ... U>
void NDArray<T>::_reshape(int axis, int first, U ... args)
{
    this->_data->shape.set(axis, first);
    this->_reshape(axis+1, args...);
}

template<class T>
void NDArray<T>::_reshape(int axis, int last)
{
    this->_data->shape.set(axis, last);
}

template<class T> template<class ... U>
int NDArray<T>::_item(int axis, int pos, int idx, U ... args) const
{
    pos = pos*this->_data->shape.get(axis) + idx;
    return _item(axis+1, pos, args ...);
}

template<class T>
int NDArray<T>::_item(int axis, int pos, int idx) const
{
    DM4thAssert(axis+1 == this->_data->shape.size());
    pos = pos*this->_data->shape.get(axis) + idx;
    return pos;
}

template<class T>
DM4thInternal::BaseArray<T> NDArray<T>::_allocZeros(const NDArray<int> &axisArray)
{
    int count = 1;
    for(int j=0; j<axisArray.size(); ++j)
    {
        count*= axisArray.data()[j];
    }
    //T* oldArray = this->_data->array._allocAndReturnOldArray(count);
    DM4thInternal::BaseArray<T> oldArray;
    this->_data->array.moveReferenceTo(oldArray);
    this->_data->array.resize(count);
    this->_data->shape.resize(axisArray.size());
    for(int j=0; j<axisArray.size(); ++j)
    {
        this->_data->shape.set(j,axisArray.data()[j]);
    }
    return oldArray;
}

template<class T>
void NDArray<T>::_ostream(std::ostream& stream, int shapeIdx, int& c_idx,  int ident, bool quotes) const       
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
void NDArray<T>::_istream(std::istream& stream, std::queue<T> &values, int shapeIdx, int& c_size, bool &shapeAllocated)
{
    int size=0;
    DM4thInternal::_handleIstreamSpacesAndNewLines(stream);
    if(stream.peek()=='[')
    {
        while (true)
        {
            DM4thInternal::_handleIstreamSpacesAndNewLines(stream);
            DM4thAssert(stream.peek()=='['); stream.get();

            DM4thInternal::_handleIstreamSpacesAndNewLines(stream);
            if(stream.peek()==']') break; //This dim is empty

            this->_istream(stream, values, shapeIdx+1, c_size, shapeAllocated);
            size+=1;
            
            DM4thAssert(stream.peek()==']'); stream.get();

            DM4thInternal::_handleIstreamSpacesAndNewLines(stream);
            if(stream.peek()==']'){ break; }
            else if(stream.peek()==',') { stream.get(); }
            else DM4thAssert(false);
        }
    }else
    {
        T value;
        while (true)
        {
            DM4thInternal::_handleIstreamSpacesAndNewLines(stream);
            if(stream.peek()==']') { break;} //This dim is empty
            
            stream>>value;
            values.push(value);
            size += 1;
            c_size += 1;
            
            DM4thInternal::_handleIstreamSpacesAndNewLines(stream);
            if(stream.peek()==']'){ break; }
            else if(stream.peek()==',') { stream.get(); }
            else DM4thAssert(false);
        }

        if(!shapeAllocated)
        {
            for(int j=0; j<this->_data->shape.size(); ++j)
            {
                this->_data->shape.set(j, 0);
            }
            this->_data->shape.resize(shapeIdx+1);
            shapeAllocated = true;
        }
    }

    DM4thAssert(
        size > 0  && 
        (
            this->_data->shape.get(shapeIdx) == 0 ||
            this->_data->shape.get(shapeIdx) == size
        )
    );
    this->_data->shape.set(shapeIdx, size);
}

template<class T>
inline std::ostream& operator<<(std::ostream& stream, const NDArray<T> &arr)
{
    return arr.ostream(stream,4);
}

// Specialization methods
inline std::ostream& operator<<(std::ostream& stream, const NDArray<std::string> &arr){ 
    return arr.ostream(stream,4,true); 
}

inline std::ostream& operator<<(std::ostream& stream, const NDArray<bool> &arr){ 
    stream << std::boolalpha;
    arr.ostream(stream,4);
    stream << std::noboolalpha;
    return stream;
}

template<class T>
inline std::istream& operator>>(std::istream& stream, NDArray<T> &arr)
{
    return arr.istream(stream);
}

inline std::istream& operator>>(std::istream& stream, NDArray<bool> &arr)
{
    stream >> std::boolalpha;
    arr.istream(stream);
    stream >> std::noboolalpha;
    return stream;
}
}