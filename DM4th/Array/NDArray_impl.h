#pragma once

#include "NDArray.h"
#include "NDArrayUtils.h"


namespace DM4th
{

template<class T>
inline NDArray<T>::NDArray() {}

template<class T> template<class ... U>
inline NDArray<T>::NDArray(T *data, U ... args)
{
    *this = NDArray<T>(data, items<int>(args ...));
}

template<class T>
NDArray<T>::NDArray(T *data, const NDArray<int> &axisArray)
{
    DM4thAssert(axisArray.size()>0);
    DM4thAssert(axisArray.rank()==1);

    this->_resizeEmpty(axisArray);
    int size =  DM4th::NDArrayUtils::mul(axisArray);
    for(int j=0; j<size; ++j)
    {
        this->data_item(j) = data[j];
    }
}

template<class T>
NDArray<T>::NDArray(const DM4th::Internal::BaseArray<T> &other) 
{    
    this->_data->shape.resize(1);
    this->_data->shape(0) = other.size();
    other.copyDataTo(this->_data->array);
}

template<class T>
NDArray<T>::NDArray(const std::string &str) 
{    
    std::stringstream ss;
    ss << str;
    ss >> *this;
}

template<class T> template<class U>
NDArray<T>::operator NDArray<U>() const
{
    return this->getCopy<U>();
}

template<class T>
NDArray<T>::operator std::string() const
{
    std::stringstream ss;
    ss << *this;
    return ss.str();
}

template<class T> template<class ... U>
inline void NDArray<T>::resize(const int &axis1, U ... args)
{

    if(this->rank()==1)
    { //1 dim to N dim
        int oldShape = this->shape(0);

        DM4th::Internal::BaseArray<T> oldArray(this->_allocZeros(axis1, args...));

        int newDisp = this->_getAxisDisplacement(0);
        int end = DM4thUtils::min(oldShape, this->shape(0));
        int newj = 0;
        for(int oldj=0; oldj<end; ++oldj, newj+=newDisp)
        {
            this->_data->array[newj] = oldArray[oldj];
        }
        //delete[] oldArray;
    }else
    { //N dim to M dim
        DM4th::Internal::BaseArray<int> oldShape;
        this->data_shape().copyDataTo(oldShape);

        int oldDisp = this->_getAxisDisplacement(0);

        DM4th::Internal::BaseArray<T> oldArray(this->_allocZeros(axis1, args...));

        const DM4th::Internal::BaseArray<int> &newShape = this->data_shape();
        int newDisp = this->_getAxisDisplacement(0);

        if(oldArray.size() == 0) return;

        int end = DM4thUtils::min(oldShape.item(0), newShape.item(0));
        for(int j=0; j<end; ++j)
        {
            this->_resize(
                1, 
                oldDisp*j, newDisp*j, 
                // oldDisp, newDisp,
                oldShape, newShape, 
                oldArray
            );
        }
        //delete[] oldArray;
    }
}

template<class T>
inline void NDArray<T>::resize(const int &axis1)
{
    if(this->rank()<=1) this->_resize1DArray(axis1); // 0 || 1 dim to 1 dim
    else
    { // N dim to 1 dim
        int disp = this->_getAxisDisplacement(0);
        int end = DM4thUtils::min(axis1, this->shape(0));
        //T* old = this->_data->array._allocAndReturnOldArray(axis1);
        DM4th::Internal::BaseArray<T> old;
        this->_data->array.moveDataTo(old);
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
    DM4thAssert(axisArray.rank()==1);

    if(this->rank()==1)
    { //1 dim to N dim
        int oldShape = this->shape(0);

        DM4th::Internal::BaseArray<T> oldArray(this->_allocZeros(axisArray));

        int newDisp = this->_getAxisDisplacement(0);
        int end = DM4thUtils::min(oldShape, this->shape(0));
        int newj = 0;
        for(int oldj=0; oldj<end; ++oldj, newj+=newDisp)
        {
            this->_data->array[newj] = oldArray[oldj];
        }
        //delete[] oldArray;
    }else
    { //N dim to M dim
        Internal::BaseArray<int> oldShape;
        this->data_shape().copyDataTo(oldShape);
        int oldDisp = this->_getAxisDisplacement(0);

        DM4th::Internal::BaseArray<T> oldArray(this->_allocZeros(axisArray));

        const DM4th::Internal::BaseArray<int> &newShape = this->data_shape();
        int newDisp = this->_getAxisDisplacement(0);

        if(oldArray.size() == 0) return;

        int end = DM4thUtils::min(oldShape.item(0), newShape.item(0));
        for(int j=0; j<end; ++j)
        {
            this->_resize(
                1, 
                oldDisp*j, newDisp*j, 
                // oldDisp, newDisp,
                oldShape, newShape, 
                oldArray
            );
        }
        //delete[] oldArray;
    }
}

template<class T>
void NDArray<T>::resize(const DM4th::Internal::BaseArray<int> &axisArray)
{
    if(this->rank()==1)
    { //1 dim to N dim
        int oldShape = this->shape(0);

        DM4th::Internal::BaseArray<T> oldArray(this->_allocZeros(axisArray));

        int newDisp = this->_getAxisDisplacement(0);
        int end = DM4thUtils::min(oldShape, this->shape(0));
        int newj = 0;
        for(int oldj=0; oldj<end; ++oldj, newj+=newDisp)
        {
            this->_data->array[newj] = oldArray[oldj];
        }
        //delete[] oldArray;
    }else
    { //N dim to M dim
        DM4th::Internal::BaseArray<int> oldShape;
        this->data_shape().copyDataTo(oldShape);

        int oldDisp = this->_getAxisDisplacement(0);

        DM4th::Internal::BaseArray<T> oldArray(this->_allocZeros(axisArray));

        const DM4th::Internal::BaseArray<int> &newShape = this->data_shape();

        int newDisp = this->_getAxisDisplacement(0);

        if(oldArray.size() == 0) return;

        int end = DM4thUtils::min(oldShape.item(0), newShape.item(0));
        for(int j=0; j<end; ++j)
        {
            this->_resize(
                1, 
                oldDisp*j, newDisp*j, 
                // oldDisp, newDisp,
                oldShape, newShape, 
                oldArray
            );
        }
        //delete[] oldArray;
    }
}

template<class T>
inline void NDArray<T>::reserve(const int &size)
{
    this->_data->array.reserve(size);
}

template<class T>
inline int NDArray<T>::rank() const { return this->_data->shape.size(); }

template<class T>
inline int NDArray<T>::capacity() const { return this->_data->array.capacity(); }

template<class T>
int NDArray<T>::size() const { return this->_data->shape.get(0); }

// template<class T>
// int NDArray<T>::itemsCount() const { return this->_data->array.size(); }

template<class T>
NDArray<int> NDArray<T>::shape() const
{
    NDArray<int> result;
    result._resize1DArray(this->rank());
    for(int j=0; j<this->rank(); ++j)
    {
        result.item(j) = this->_data->shape.get(j);
    }
    return result;
}

template<class T>
const DM4th::Internal::BaseArray<int> &NDArray<T>::data_shape() const
{
    return this->_data->shape;
}

template<class T>
inline int NDArray<T>::shape(const int &axis) const       
{
    return this->_data->shape.get(axis);
}

template<class T> template<class ... U>
const NDArray<T> &NDArray<T>::reshape(const int &axis1, U ... args)
{
    //int oldShapeMult = mul(this->shape().data(), this->rank());
    int oldShapeMult = DM4thCArrayUtils::mul(this->_data->shape.data(), this->rank());
    int newShapeMult = DM4thUtils::mul(axis1,args...);
    
    if(oldShapeMult!=newShapeMult) this->_data->array.resize(newShapeMult);
    //DM4thAssert(oldShapeMult==newShapeMult);
    
    this->_data->shape.resize(DM4thUtils::count(axis1,args...));
    this->_reshape(0, axis1, args...);

    return *this;
}

template<class T>
const NDArray<T> & NDArray<T>::reshape(const NDArray<int> &newShape)
{
    int oldShapeMult = DM4thCArrayUtils::mul(this->_data->shape.data(), this->rank());
    int newShapeMult = DM4thCArrayUtils::mul(newShape.data(), newShape.size());     
    DM4thAssert(newShape.rank()==1);    
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
int NDArray<T>::_partition(const bool &reverse, const int lo, const int hi)
{
    T pivot = this->data_item(hi);
    int i = lo;
    for(int j=lo; j<=hi; ++j)
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
void NDArray<T>::sort(const bool &reverse, int lo, int hi)
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

template<class T>
T NDArray<T>::reduce(const std::function<T(T,T)> &f)
{
    if(this->data_size()==0) return 0;
    if(this->data_size()==1) return this->data_item(0);

    T result = this->data_item(0);

    for(int j=1; j<this->data_size(); ++j)
    {
        result = f(result, this->data_item(j));
    }
    return result;
}


template<class T>
NDArray<T> NDArray<T>::map(const std::function<T(T,int)> &f)
{
    NDArray<T> result;
    result._resizeEmpty(this->data_shape());

    for(int j=0; j<this->data_size(); ++j)
    {
        result.data_item(j) = f(this->data_item(j), j);
    }
    return result;
}

template<class T>
const NDArray<T> &NDArray<T>::iMap(const std::function<T(T,int)> &f)
{
    for(int j=0; j<this->data_size(); ++j)
    {
        this->data_item(j) = f(this->data_item(j), j);
    }

    return *this;
}

template<class T>
NDArray<T> NDArray<T>::filter(const std::function<bool(T, int)> &f)
{
    NDArray<T> result;
    result._resizeEmpty(this->data_shape());

    int top = 0;
    for(int j=0; j<this->data_size(); ++j)
    {
        if(f(this->data_item(j), j)){ 
            result.data_item(top) = this->data_item(j);
            ++top; 
        }
    }

    if(top != this->data_size())
    {
        result._resize1DArray(top);
    }

    return result;
}

template<class T> template<class AXIS, class ... U>
inline T &NDArray<T>::item(AXIS axis, U ... args) const
{ 
    DM4thAssert(DM4thUtils::count(axis,args...)==this->rank());
    const int x = int(axis);
    return this->_data->array(this->_item(1,x,args ...));
}

template<class T> template<class ... U>
inline T &NDArray<T>::item(const int &x, U ... args) const
{ 
    DM4thAssert(DM4thUtils::count(x,args...)==this->rank());
    return this->_data->array(this->_item(1,x,args ...));
}

template<class T> template<class AXIS>
inline T &NDArray<T>::item(AXIS axis) const
{
    const int x = int(axis);
    //if(this->_data->shape.size()>1) return this->_data->array(this->_item(1,x,0));
    DM4thAssert(this->rank()==1);
    DM4thAssert(x<this->_data->array.size());
    return this->_data->array[x];
}

template<class T>
inline T &NDArray<T>::item(const int &x) const
{
    //if(this->_data->shape.size()>1) return this->_data->array(this->_item(1,x,0));
    DM4thAssert(this->rank()==1);
    DM4thAssert(x<this->_data->array.size());
    return this->_data->array[x];
}

template<class T> template<class AXIS>
T &NDArray<T>::item(const NDArray<AXIS> &axisArray) const
{
    DM4thAssert(axisArray.rank()==1);
    DM4thAssert(axisArray.size()==this->rank());

    int pos = (int)axisArray.data_item(0);
    for(int j=1; j<this->rank(); ++j)
    {
        pos = pos*this->_data->shape.get(j) + (int)axisArray.data()[j];
    }

    // int *iter = axisArray.data(); 
    // int pos = *iter;
    // for(int j=1; j<this->rank(); ++j, ++iter)
    // {
    //     pos = pos*this->_data->shape(j) + *iter;
    // }
    return this->_data->array[pos];            
}

template<class T>
NDArray<T> NDArray<T>::getCopy() const
{
    NDArray<T> result;
    this->_data->shape.copyDataTo(result._data->shape);
    this->_data->array.copyDataTo(result._data->array);
    return result;
}

template<class T> template<class U>
inline NDArray<U> NDArray<T>::getCopy() const
{
    NDArray<U> result;
    result._resizeEmpty(this->data_shape());
    for(int j=0; j<this->data_size(); ++j)
    {
        result.data_item(j) = static_cast<const U>(this->data_item(j));
    }
    return result;
}
template<class T> template<class U>
void NDArray<T>::push(const U &value, const int &pos)
{
    if(this->rank()!=1)
    {
        this->reshape(this->data_size());
    }

    if(pos==END) this->_data->array.push((T)value, this->data_size());
    else this->_data->array.push((T)value, pos);

    this->_data->shape(0) += 1;

}

template<class T> template<class U>
void NDArray<T>::pushArray(const NDArray<U> &other, const int &pos){

    if(this->rank()<=1 && other.rank()==1)
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
    else if( (this->rank()==0 || this->rank()==2) && other.rank()==1 ){
        int cols;
        if(this->rank()==0) cols = other.shape(0);
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
T NDArray<T>::pop(const int &idx)
{
    
    DM4thAssert(this->rank()==1 && this->shape(0)>0);
    DM4thAssert( (idx>=0 && idx<this->shape(0)) || idx==END ); 

    // if(idx==END || idx==this->shape(0)-1)
    // {
    //     result = this->item(this->shape(0)-1);
    // }else{
    //     T *iter = &this->item(idx);
    //     result = *iter;
    //     for(int j=0; j<this->shape(0)-idx-1; ++j)
    //     {
    //         iter[j] = iter[j+1];
    //     }
    // }
    // this->resize(this->shape(0)-1);
    // return result;

    T result;
    if(idx==END) result = this->_data->array.pop(this->data_size()-1);
    else result = this->_data->array.pop(idx);

    this->_data->shape(0) -= 1;

    return result;
}

template<class T>
NDArray<T> NDArray<T>::popArray(const int &pos)
{
    NDArray<T> result;
    DM4thAssert( (pos>=0 && pos<this->shape(0)) || pos==(int)END ); 
    
    if(this->rank()==1)
    {
        result = items<T>(this->pop(pos));
    }else 
    if(this->rank()==2)
    {
        result._resizeEmpty(this->shape(1));
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
inline T &NDArray<T>::operator()(const NDArray<U> &axisArray){ return this->item(axisArray); }

// -------------------- NDArray-NDArray operations --------------------

template<class T> template<class U>
inline const NDArray<T> &NDArray<T>::iAdd(const NDArray<U> &other, const DM4thParallelSettings &pSettings)
{
    if(this->data_size()==1)
    {
        T value = this->data_item(0);
        this->resize(other.data_shape());

         DM4th::Parallel::loop<int>(
            pSettings,
            0, this->data_size(), 1, // from, to, step
            
            [&](const int &j) 
            {
                this->data_item(j) = value + (T)other.data_item(j);
            }
            
        );

    }else if(other.data_size()==1)
    {
        this->_data->array.iAdd(other.data_item(0), pSettings);
        //this->_data->array += other.data_item(0);
    }else
    {
        this->_data->array.iAdd(other.getArrayData().array, pSettings);
        //this->_data->array += other.getArrayData().array;
    }
    return *this;
}

template<class T> template<class U>
inline const NDArray<T> &NDArray<T>::iSub(const NDArray<U> &other, const DM4thParallelSettings &pSettings)
{
    if(this->data_size()==1)
    {
        T value = this->data_item(0);
        this->resize(other.data_shape());

         DM4th::Parallel::loop<int>(
            pSettings,
            0, this->data_size(), 1, // from, to, step
            
            [&](const int &j) 
            {
                this->data_item(j) = value - (T)other.data_item(j);
            }
            
        );

    }else if(other.data_size()==1)
    {
        this->_data->array.iSub(other.data_item(0), pSettings);
        //this->_data->array -= other.data_item(0);
    }else
    {
        this->_data->array.iSub(other.getArrayData().array, pSettings);
        //this->_data->array -= other.getArrayData().array;
    }
    return *this;
}

template<class T>
const NDArray<T> &NDArray<T>::mul_asig(const NDArray<T> &lhs, const NDArray<T> &rhs, const DM4thParallelSettings &pSettings)
{   
    DM4thAssert(this->_data!=lhs._data && this->_data!=rhs._data);
    if(lhs.data_size()==1)
    {
        DM4th::Parallel::singleThreadOperationIfWorkShared(
            pSettings,
            [&]{this->resize(rhs.data_shape());}
        );

         DM4th::Parallel::loop<int>(
            pSettings, // from, to, step
            0, rhs.data_size(), 1,
            [&](const int &j)
            {
                this->data_item(j) = lhs.data_item(0) * rhs.data_item(j);
            }
        );
    }
    else if(rhs.data_size()==1)
    {
        DM4th::Parallel::singleThreadOperationIfWorkShared(
            pSettings,
            [&]{this->resize(lhs.data_shape());}
        );

        DM4th::Parallel::loop<int>(
            pSettings, // from, to, step
            0, lhs.data_size(), 1,
            [&](const int &j)
            {
                this->data_item(j) = lhs.data_item(j) * rhs.data_item(0);
            }
        );
    }
    else if(lhs.rank()==1 && rhs.rank()==1)
    {
        DM4thAssert(lhs.shape(0)==rhs.shape(0));

        DM4th::Parallel::singleThreadOperationIfWorkShared(
            pSettings,
            [&]{ this->resize(1); }
        );
        

         DM4th::Parallel::loopReduce<T, int>(
            pSettings | EDM4thParallelSettings::ADD, 
            0, lhs.shape(0), 1, // from, to, step

            [&](const T &acum, const  int &j)
            {
                return acum + lhs.item(j)*rhs.item(j);
            },
            this->item(0)
        );
    }

    else if(lhs.rank()<=2 && rhs.rank()<=2)
    {
        DM4thAssert(lhs.shape(1) == rhs.shape(0));

        DM4th::Parallel::singleThreadOperationIfWorkShared(
            pSettings,
            [&]{ this->resize(lhs.shape(0),rhs.shape(1)); }
        );

        DM4th::Parallel::non_square_matrix_dot_operation(
            pSettings,
            lhs.data(), lhs.shape(0), lhs.shape(1),
            rhs.data(), rhs.shape(0), rhs.shape(1),
            this->data(), this->shape(0), this->shape(1)
        );
    }
    else
    {
        DM4thAssert(false);
    }

    return *this;
}

// -------------------- NDArray - Scalar operations --------------------

template<class T>
inline const NDArray<T> &NDArray<T>::iAdd(const T &other, const DM4thParallelSettings &pSettings)
{
    this->_data->array.iAdd(other, pSettings);
    return *this;
}

template<class T>
inline const NDArray<T> &NDArray<T>::iSub(const T &other, const DM4thParallelSettings &pSettings)
{
    this->_data->array.iSub(other, pSettings);
    return *this;
}

template<class T>
inline const NDArray<T> &NDArray<T>::iMul(const T &other, const DM4thParallelSettings &pSettings)
{
    this->_data->array.iMul(other, pSettings);
    return *this;
}

template<class T>
inline const NDArray<T> &NDArray<T>::iDiv(const T &other, const DM4thParallelSettings &pSettings)
{
    this->_data->array.iDiv(other, pSettings);
    return *this;
}

template<class T>
inline const NDArray<T> &NDArray<T>::iMod(const T &other, const DM4thParallelSettings &pSettings)
{
    this->_data->array.iMod(other, pSettings);
    return *this;
}

// -------------------- NDArray aritmethic operator overloading --------------------

template<class T> template<class U> 
inline const NDArray<T> &NDArray<T>::operator+=(const NDArray<U> &other)
{
    this->iAdd(other, EDM4thParallelSettings::DEFAULT);
    return *this;
}

template<class T> template<class U> 
inline const NDArray<T> &NDArray<T>::operator-=(const NDArray<U> &other)
{
    this->iSub(other, EDM4thParallelSettings::DEFAULT);
    return *this;
}

template<class T> template<class U> 
inline const NDArray<T> &NDArray<T>::operator*=(const NDArray<U> &other)
{
    //this->iMul(other, EDM4thParallelSettings::DEFAULT);
    NDArray<T> tmp;
    this->moveDataTo(tmp);
    this->mul_asig(tmp, other, EDM4thParallelSettings::DEFAULT);
    return *this;
}

template<class T> template<class U>
inline NDArray<T> NDArray<T>::operator+(const NDArray<U> &other) const
{
    NDArray<T> result = this->getCopy();
    result.iAdd(other, EDM4thParallelSettings::DEFAULT);
    return std::move(result);
}

template<class T>
inline const NDArray<T> &NDArray<T>::operator+=(const T &other)
{
    this->_data->array.iAdd(other, EDM4thParallelSettings::DEFAULT);
    return *this;
}

template<class T>
inline NDArray<T> NDArray<T>::operator+(const T &other) const
{
    NDArray<T> result = this->getCopy();
    result.iAdd(other, EDM4thParallelSettings::DEFAULT);
    return std::move(result);
}



template<class T> template<class U>
inline NDArray<T> NDArray<T>::operator-(const NDArray<U> &other) const
{
    NDArray<T> result = this->getCopy();
    result.iSub(other, EDM4thParallelSettings::DEFAULT);
    return std::move(result);
}

template<class T>
inline const NDArray<T> &NDArray<T>::operator-=(const T &other)
{
    this->_data->array.iSub(other, EDM4thParallelSettings::DEFAULT);
    return *this;
}

template<class T>
inline NDArray<T> NDArray<T>::operator-(const T &other) const
{
    NDArray<T> result = this->getCopy();
    result.iSub(other, EDM4thParallelSettings::DEFAULT);
    return std::move(result);
}

template<class T> template<class U>
inline NDArray<T> NDArray<T>::operator*(const NDArray<U> &other) const
{
    NDArray<T> result;
    result.mul_asig(*this, other, EDM4thParallelSettings::DEFAULT);
    return std::move(result);
}


template<class T>
const NDArray<T> &NDArray<T>::operator*=(const T &other)
{
    this->_data->array.iMul(other, EDM4thParallelSettings::DEFAULT);
    return *this;
}

template<class T>
inline NDArray<T> NDArray<T>::operator*(const T &other) const
{
    NDArray<T> result = this->getCopy();
    //result.mul_asig(*this, other, EDM4thParallelSettings::DEFAULT);
    result.iMul(other, EDM4thParallelSettings::DEFAULT);
    return std::move(result);
}

template<class T>
inline const NDArray<T> &NDArray<T>::operator/=(const T &other)
{
    this->_data->array.iDiv(other, EDM4thParallelSettings::DEFAULT);
    return *this;
}

template<class T>
inline NDArray<T> NDArray<T>::operator/(const T &other) const
{
    NDArray<T> result = this->getCopy();
    result.iDiv(other, EDM4thParallelSettings::DEFAULT);
    return std::move(result);
}

template<class T>
inline const NDArray<T> &NDArray<T>::operator%=(const T &other)
{
    this->_data->array.iMod(other, EDM4thParallelSettings::DEFAULT);
    return *this;
}

template<class T>
inline NDArray<T> NDArray<T>::operator%(const T &other) const
{
    NDArray<T> result = this->getCopy();
    result.iMod(other, EDM4thParallelSettings::DEFAULT);
    return std::move(result);
}

// template<class T> template<class U>
// inline bool NDArray<T>::operator==(const NDArray<U> &other)
template<class T> template<class U>
inline bool NDArray<T>::isEqualTo(const NDArray<U> &other) const
{
    return other.getArrayData().array==this->_data->array;
}

template<class T>
NDArray<bool> NDArray<T>::operator==(const T &other) const
{
    NDArray<bool> result;
    result._resizeEmpty(this->data_shape());

     DM4th::Parallel::loop<int>(
        EDM4thParallelSettings::OMP_PARALLEL,
        0, result.data_size(), 1, // from, to, step
        
        [&](const int &j) 
        {
            result.data_item(j) = this->data_item(j) == other;
        }

    );

    return result;
}

template<class T>
NDArray<bool> NDArray<T>::operator!=(const T &other) const
{
    NDArray<bool> result;
    result._resizeEmpty(this->data_shape());

     DM4th::Parallel::loop<int>(
        EDM4thParallelSettings::OMP_PARALLEL,
        0, result.data_size(), 1, // from, to, step
        
        [&](const int &j) 
        {
            result.data_item(j) = this->data_item(j) != other;
        }
        
    );


    return result;
}

template<class T>
NDArray<bool> NDArray<T>::operator> (const T &other) const
{
    NDArray<bool> result;
    result._resizeEmpty(this->data_shape());

     DM4th::Parallel::loop<int>(
        EDM4thParallelSettings::OMP_PARALLEL,
        0, result.data_size(), 1, // from, to, step
        
        [&](const int &j) 
        {
            result.data_item(j) = this->data_item(j) > other;
        }
        
    );

    return result;
}

template<class T>
NDArray<bool> NDArray<T>::operator<=(const T &other) const
{
    NDArray<bool> result;
    result._resizeEmpty(this->data_shape());

     DM4th::Parallel::loop<int>(
        EDM4thParallelSettings::OMP_PARALLEL,
        0, result.data_size(), 1, // from, to, step
        
        [&](const int &j) 
        {
            result.data_item(j) = this->data_item(j) <= other;
        }
        
    );

    return result;
}

template<class T>
NDArray<bool> NDArray<T>::operator>=(const T &other) const
{
    NDArray<bool> result;
    result._resizeEmpty(this->data_shape());

     DM4th::Parallel::loop<int>(
        EDM4thParallelSettings::OMP_PARALLEL,
        0, result.data_size(), 1, // from, to, step
        
        [&](const int &j) 
        {
            result.data_item(j) = this->data_item(j) >= other;
        }

    );


    return result;
}

template<class T>
NDArray<bool> NDArray<T>::operator<(const T &other) const
{
    NDArray<bool> result;
    result._resizeEmpty(this->data_shape());

     DM4th::Parallel::loop<int>(
        EDM4thParallelSettings::OMP_PARALLEL,
        0, result.data_size(), 1, // from, to, step
        
        [&](const int &j) 
        {
            result.data_item(j) = this->data_item(j) < other;
        }
        
    );

    return result;
}


template<class T>
NDArray<bool> NDArray<T>::operator==(const NDArray<T> &other) const
{
    NDArray<bool> result;
    if(this->data_size()==other.data_size())
    {
        result._resizeEmpty(this->data_shape());

         DM4th::Parallel::loop<int>(
            EDM4thParallelSettings::OMP_PARALLEL,
            0, result.data_size(), 1, // from, to, step
            
            [&](const int &j) 
            {
                result.data_item(j) = this->data_item(j) == other.data_item(j);
            }
            
        );

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
        result._resizeEmpty(this->data_shape());

         DM4th::Parallel::loop<int>(
            EDM4thParallelSettings::OMP_PARALLEL,
            0, result.data_size(), 1, // from, to, step
            
            [&](const int &j) 
            {
                result.data_item(j) = this->data_item(j) != other.data_item(j);
            }
            
        );

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
        result._resizeEmpty(this->data_shape());

         DM4th::Parallel::loop<int>(
            EDM4thParallelSettings::OMP_PARALLEL,
            0, result.data_size(), 1, // from, to, step
            
            [&](const int &j) 
            {
                result.data_item(j) = this->data_item(j) > other.data_item(j);
            }
            
        );


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
        result._resizeEmpty(this->data_shape());

         DM4th::Parallel::loop<int>(
            EDM4thParallelSettings::OMP_PARALLEL,
            0, result.data_size(), 1, // from, to, step
            
            [&](const int &j) 
            {
                result.data_item(j) = this->data_item(j) <= other.data_item(j);
            }
            
        );


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
        result._resizeEmpty(this->data_shape());

         DM4th::Parallel::loop<int>(
            EDM4thParallelSettings::OMP_PARALLEL,
            0, result.data_size(), 1, // from, to, step
            
            [&](const int &j) 
            {
                result.data_item(j) = this->data_item(j) >= other.data_item(j);
            }
            
        );

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
        result._resizeEmpty(this->data_shape());

         DM4th::Parallel::loop<int>(
            EDM4thParallelSettings::OMP_PARALLEL,
            0, result.data_size(), 1, // from, to, step
            
            [&](const int &j) 
            {
                result.data_item(j) = this->data_item(j) < other.data_item(j);
            }
            
        );

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
    result._resizeEmpty(this->data_shape());

     DM4th::Parallel::loop<int>(
        EDM4thParallelSettings::OMP_PARALLEL,
        0, result.data_size(), 1, // from, to, step
        
        [&](const int &j) 
        {
            result.data_item(j) = this->data_item(j) && other.data_item(j);
        }
        
    );

    return result;
}

template<> template<>
inline NDArray<bool> NDArray<bool>::operator||(const NDArray<bool> &other) const
{
    NDArray<bool> result;
    result._resizeEmpty(this->data_shape());

     DM4th::Parallel::loop<int>(
        EDM4thParallelSettings::OMP_PARALLEL,
        0, result.data_size(), 1, // from, to, step
        
        [&](const int &j) 
        {
            result.data_item(j) = this->data_item(j) || other.data_item(j);
        }
        
    );


    return result;
}

template<> template<>
inline NDArray<bool> NDArray<bool>::operator!() const
{
    NDArray<bool> result;
    result._resizeEmpty(this->data_shape());

     DM4th::Parallel::loop<int>(
        EDM4thParallelSettings::OMP_PARALLEL,
        0, result.data_size(), 1, // from, to, step
        
        [&](const int &j) 
        {
            result.data_item(j) = !this->data_item(j);
        }
        
    );

    return result;
}

template<class T>
T NDArray<T>::dot(const NDArray<T> &other, const DM4thParallelSettings &pSettings) const
{
    DM4thAssert(this->data_size()==other.data_size());

    T result;
    DM4th::Parallel::loopReduce<T, int>(
        pSettings | EDM4thParallelSettings::ADD, 
        0, this->data_size(), 1, // from, to, step

        [&](const T &acum, const  int &j)
        {
            return acum + this->data_item(j)*other.data_item(j);
        },
        result
    );

    return result;
}

template<class T>
T NDArray<T>::mean(const DM4thParallelSettings &pSettings) const
{
    T result;
    DM4th::Parallel::loopReduce<T, int>(
        pSettings | EDM4thParallelSettings::ADD, 
        0, this->data_size(), 1, // from, to, step

        [&](const T &acum, const  int &j)
        {
            return acum + this->data_item(j);
        },
        result
    );

    return result / this->data_size();
}

template<class T>
T NDArray<T>::max(const DM4thParallelSettings &pSettings) const
{
    T result;
    DM4th::Parallel::loopReduce<T, int>(
        pSettings | EDM4thParallelSettings::MAX, 
        0, this->data_size(), 1, // from, to, step

        [&](const T &acum, const  int &j)
        {
            return acum > this->data_item(j)? acum : this->data_item(j);
        },
        result, -INF
    );

    return result;
}

template<class T>
T NDArray<T>::min(const DM4thParallelSettings &pSettings) const
{
    T result;
    DM4th::Parallel::loopReduce<T, int>(
        pSettings | EDM4thParallelSettings::MIN, 
        0, this->data_size(), 1, // from, to, step

        [&](const T &acum, const  int &j)
        {
            return acum < this->data_item(j)? acum : this->data_item(j);
        },
        result, INF
    );

    return result;
}

template<class T>
const NDArray<T> &NDArray<T>::iSin(const DM4thParallelSettings &pSettings)
{
    DM4th::Parallel::loop<int>(
        pSettings,
        0, this->data_size(), 1, // from, to, step
        
        [&](const int &j) 
        {
            this->data_item(j) = sin(this->data_item(j));
        }
        
    ); 

    return *this;
}

template<class T>
const NDArray<T> &NDArray<T>::iCos(const DM4thParallelSettings &pSettings)
{
    DM4th::Parallel::loop<int>(
        pSettings,
        0, this->data_size(), 1, // from, to, step
        
        [&](const int &j) 
        {
            this->data_item(j) = cos(this->data_item(j));
        }
        
    ); 

    return *this;
}

template<class T>
const NDArray<T> &NDArray<T>::iTan(const DM4thParallelSettings &pSettings)
{
    DM4th::Parallel::loop<int>(
        pSettings,
        0, this->data_size(), 1, // from, to, step
        
        [&](const int &j) 
        {
            T item = this->data_item(j);
            this->data_item(j) = tan(item);
        }
        
    ); 

    return *this;
}

template<class T>
const NDArray<T> &NDArray<T>::iCot(const DM4thParallelSettings &pSettings)
{
    DM4th::Parallel::loop<int>(
        pSettings,
        0, this->data_size(), 1, // from, to, step
        
        [&](const int &j) 
        {
            this->data_item(j) = 1.0/tan(this->data_item(j));
        }
        
    ); 

    return *this;
}

template<class T>
const NDArray<T> &NDArray<T>::iSec(const DM4thParallelSettings &pSettings)
{
    DM4th::Parallel::loop<int>(
        pSettings,
        0, this->data_size(), 1, // from, to, step
        
        [&](const int &j) 
        {
            this->data_item(j) = 1.0/cos(this->data_item(j));
        }
        
    ); 

    return *this;
}

template<class T>
const NDArray<T> &NDArray<T>::iCsc(const DM4thParallelSettings &pSettings)
{
    DM4th::Parallel::loop<int>(
        pSettings,
        0, this->data_size(), 1, // from, to, step
        
        [&](const int &j) 
        {
            this->data_item(j) = 1.0/sin(this->data_item(j));
        }
        
    ); 

    return *this;
}

template<class T>
bool NDArray<T>::any(const T &value) const 
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
bool NDArray<T>::all(const T &value) const 
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
std::ostream& NDArray<T>::ostream(std::ostream& stream, const int &ident, const bool &quotes) const
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
    DM4th::Internal::_handleIstreamSpacesAndNewLines(stream);

    DM4thAssert(stream.peek()=='['); stream.get();
    
    this->_istream(stream, values, 0, c_size, shapeAllocated);
    DM4th::Internal::_handleIstreamSpacesAndNewLines(stream);

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
void NDArray<T>::loadFile(const std::string &url){
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
void NDArray<T>::saveFile(const std::string &url){
    // Crear ruta si no existe  
    std::ofstream file;
    file.open(url);
    file<<*this;
    file.close();
}

template<class T>
inline void NDArray<T>::_resize1DArray(const int &size)
{
    //DM4thAssert(this->rank()<=1); // Can be 0 || 1
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
inline T &NDArray<T>::data_item(const int &idx) { return this->_data->array[idx]; }

template<class T>
inline const T &NDArray<T>::data_item(const int &idx) const { return this->_data->array.get(idx); }

template<class T>
NDArray<int> NDArray<T>::_getAxisDisplacement() const
{
    NDArray<int> result;
    result._resize1DArray(this->rank());
    int disp = 1;
    for(int j=this->rank()-1; j>=0; --j)
    {
        result.item(j) = disp;
        disp *= this->_data->shape.get(j);
    }

    return result;
}

template<class T>
inline int NDArray<T>::_getAxisDisplacement(const int &axis) const
{
    int disp = 1;
    for(int j=this->rank()-1; j>axis; --j)
    {
        disp *= this->_data->shape.get(j);
    }
    return disp;
}

template<class T> template<class ...U>
inline void NDArray<T>::_resizeEmpty(const int &first, U... axisSize)
{   
    this->_data->shape.clear();
    this->_data->array.clear();
    
    this->_data->shape._allocEmpty(DM4thUtils::count(first, axisSize...));
    this->_data->array._allocEmpty(DM4thUtils::mul(first, axisSize...));

    int idx = 0;
    for(const int axis : {first, axisSize...})
    {
        this->_data->shape(idx++) = axis;
    }
}

template<class T>
inline void NDArray<T>::_resizeEmpty(const DM4th::Internal::BaseArray<int> &axisArray)
{
    this->_data->shape.clear();
    this->_data->array.clear();
    
    this->_data->shape._allocEmpty(axisArray.size());
    this->_data->array._allocEmpty(DM4thCArrayUtils::mul(axisArray.data(), axisArray.size()));

    for(int idx=0; idx<axisArray.size(); ++idx)
    {
        this->_data->shape(idx) = axisArray(idx);
    }
}


template<class T>
void NDArray<T>::_resize(const int &axis, int oldDispCount, int newDispCount, 
            // NDArray<int> &oldDisp,  NDArray<int> &newDisp, 
            const Internal::BaseArray<int> &oldShape,  const Internal::BaseArray<int> &newShape,
            const DM4th::Internal::BaseArray<T> &oldArray)
{
    int end = DM4thUtils::min(oldShape.item(axis), newShape.item(axis));

    int oldDisp = 1;
    for(int j=oldShape.size()-1; j>axis; --j)
    {
        oldDisp = oldDisp * oldShape(j);
    }

    int newDisp = 1;
    for(int j=newShape.size()-1; j>axis; --j)
    {
        oldDisp = oldDisp * newShape(j);
    }

    if(axis<oldShape.size()-1 && axis<newShape.size()-1){
        for(int j=0; j<end; ++j)
        {
            this->_resize(
                axis+1, 
                oldDispCount+oldDisp*j, newDispCount+newDisp*j,
                // oldDisp, newDisp,
                oldShape, newShape,
                oldArray
            );
        }
    }else{
        for(int j=0; j<end; ++j)
        {
            this->_data->array[newDispCount+newDisp*j] = oldArray.get(oldDispCount+oldDisp*j);
        }
    }
}

template<class T> template<class ... U>
void NDArray<T>::_reshape(const int &axis, int first, U ... args)
{
    this->_data->shape.set(axis, first);
    this->_reshape(axis+1, args...);
}

template<class T>
void NDArray<T>::_reshape(const int &axis, int last)
{
    this->_data->shape.set(axis, last);
}

template<class T> template<class AXIS, class ... U>
inline int NDArray<T>::_item(const int &axis, int pos, AXIS x, U ... args) const
{
    const int idx = int(x);
    pos = pos*this->_data->shape.get(axis) + idx;
    return _item(axis+1, pos, args ...);
}

template<class T> template<class ... U>
inline int NDArray<T>::_item(const int &axis, int pos, const int  &x, U ... args) const
{
    pos = pos*this->_data->shape.get(axis) + x;
    return _item(axis+1, pos, args ...);
}

template<class T> template<class AXIS>
inline int NDArray<T>::_item(const int &axis, int pos, AXIS x) const
{
    //DM4thAssert(axis+1 <= this->_data->shape.size());
    pos = pos*this->_data->shape.get(axis) + (int)x;

    // if(axis+1 < this->_data->shape.size())
    // {  
    //     return _item(axis+1, pos, 0);
    // } 
    return pos;
}

template<class T>
inline int NDArray<T>::_item(const int &axis, int pos, const int &x) const
{
    //DM4thAssert(axis+1 <= this->_data->shape.size());
    pos = pos*this->_data->shape.get(axis) + x;

    // if(axis+1 < this->_data->shape.size())
    // {  
    //     return _item(axis+1, pos, 0);
    // } 
    return pos;
}

template<class T>
Internal::BaseArray<T> NDArray<T>::_allocZeros(const NDArray<int> &axisArray)
{
    int count = 1;
    for(int j=0; j<axisArray.size(); ++j)
    {
        count*= axisArray.data_item(j);
    }
    //T* oldArray = this->_data->array._allocAndReturnOldArray(count);
    DM4th::Internal::BaseArray<T> oldArray;
    this->_data->array.moveDataTo(oldArray);
    this->_data->array.resize(count);
    this->_data->shape.resize(axisArray.size());
    for(int j=0; j<axisArray.size(); ++j)
    {
        this->_data->shape.set(j,axisArray.data_item(j));
    }
    return oldArray;
}

template<class T>
Internal::BaseArray<T> NDArray<T>::_allocZeros(const Internal::BaseArray<int> &axisArray)
{
    int count = 1;
    for(int j=0; j<axisArray.size(); ++j)
    {
        count*= axisArray(j);
    }
    //T* oldArray = this->_data->array._allocAndReturnOldArray(count);
    DM4th::Internal::BaseArray<T> oldArray;
    this->_data->array.moveDataTo(oldArray);
    this->_data->array.resize(count);
    this->_data->shape.resize(axisArray.size());
    for(int j=0; j<axisArray.size(); ++j)
    {
        this->_data->shape.set(j,axisArray(j));
    }
    return oldArray;
}

template<class T> template<class ... U>
Internal::BaseArray<T> NDArray<T>::_allocZeros(const int &axis1, U ... args)
{
    int size = DM4thUtils::mul(axis1, args...);
    int rank = DM4thUtils::count(axis1, args...);
    
    DM4th::Internal::BaseArray<T> oldArray;
    this->_data->array.moveDataTo(oldArray);
    this->_data->array._allocEmpty(size);

    this->_data->shape.resize(rank);
    DM4thUtils::initArray(this->_data->shape.data(), axis1, args...);
    // for(int j=0; j<axisArray.size(); ++j)
    // {
    //     this->_data->shape.set(j,axisArray.data()[j]);
    // }
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
    if(this->rank()>shapeIdx+1) 
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
    DM4th::Internal::_handleIstreamSpacesAndNewLines(stream);
    if(stream.peek()=='[')
    {
        while (true)
        {
            DM4th::Internal::_handleIstreamSpacesAndNewLines(stream);
            DM4thAssert(stream.peek()=='['); stream.get();

            DM4th::Internal::_handleIstreamSpacesAndNewLines(stream);
            if(stream.peek()==']') break; //This dim is empty

            this->_istream(stream, values, shapeIdx+1, c_size, shapeAllocated);
            size+=1;
            
            DM4thAssert(stream.peek()==']'); stream.get();

            DM4th::Internal::_handleIstreamSpacesAndNewLines(stream);
            if(stream.peek()==']'){ break; }
            else if(stream.peek()==',') { stream.get(); }
            else DM4thAssert(false);
        }
    }else
    {
        T value;
        while (true)
        {
            DM4th::Internal::_handleIstreamSpacesAndNewLines(stream);
            if(stream.peek()==']') { break;} //This dim is empty
            
            stream>>value;
            values.push(value);
            size += 1;
            c_size += 1;
            
            DM4th::Internal::_handleIstreamSpacesAndNewLines(stream);
            if(stream.peek()==']'){ break; }
            else if(stream.peek()==',') { stream.get(); }
            else DM4thAssert(false);
        }

        if(!shapeAllocated)
        {
            for(int j=0; j<this->rank(); ++j)
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