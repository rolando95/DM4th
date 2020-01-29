#pragma once

#include "BaseArray.h"

namespace DM4th
{

namespace Internal
{

//#define sizeAligned<T>(x)   (x + 3) & -4
//#define sizeAligned<T>(x) (x + 3) & ~0x03

template<class T>
inline int sizeAligned(int n)
{ 
    if(n<= DM4th::SIMD::Vec<T>::size()) return  DM4th::SIMD::Vec<T>::size();
    
    n--; 
    n |= n >> 1; 
    n |= n >> 2; 
    n |= n >> 4; 
    n |= n >> 8; 
    n |= n >> 16; 
    n++; 
    return n; 
}  
//////////////////// BaseArray


template <class T>
inline void BaseArray<T>::allocArray(const int &size)
{
    DM4thAssert(!this->_data && size > 0);
    this->_capacity = sizeAligned<T>(size);
    this->_data = new T[this->_capacity]();
    this->_size = size;
}

template <class T>
inline void BaseArray<T>::reallocArray(const int &size)
{
    DM4thAssert(this->_data && size > 0);
    if (size != _size)
    {
        if (size > this->_capacity)
        {
            this->_capacity = sizeAligned<T>(size);   
            T *tmp = new T[this->_capacity];     
            int min = (size < this->_size) ? size : this->_size;

            std::copy_n(this->_data, min, tmp);
            delete[] this->_data;

            if(std::is_arithmetic<T>::value) { 
                std::fill_n(tmp+min, size-min, T()); 
            }
            
            this->_data = tmp;
            tmp = nullptr;
        }else{
            if(std::is_arithmetic<T>::value) { 
                std::fill_n(_data+this->_size, size-this->_size, T()); 
            }  
        }
        this->_size = size;
    }
}

template <class T>
inline BaseArray<T>::BaseArray(const int &size)
{
    if (size > 0)
    {
        allocArray(size);
    }
}

template<class T>
inline BaseArray<T>::~BaseArray()
{
    this->clear();
}

template <class T>
inline void BaseArray<T>::_allocEmpty(const int &size)
{
    DM4thAssert(!this->_data && size > 0);
    this->_data = new T[size];
    this->_size = size;
    this->_capacity = this->_size;
}

template <class T>
inline void BaseArray<T>::resize(const int &size)
{
    if (size == 0)
    {
        this->clear();
        return;
    }
    if (this->_data == nullptr)
    {
        this->allocArray(size);
    }
    else
    {
        this->reallocArray(size);
    }
}

template<class T>
inline void BaseArray<T>::reserve(const int &size)
{
    if(size>this->_capacity)
    {
        this->_capacity = sizeAligned<T>(size);   
        T *tmp = new T[this->_capacity];     

        std::copy_n(this->_data, this->_size, tmp);
        delete[] this->_data;

        this->_data = tmp;
        tmp = nullptr;
    }
}

template <class T>
inline const int BaseArray<T>::size() const { return this->_size; }

template <class T>
inline const int BaseArray<T>::capacity() const { return this->_capacity; }


template <class T>
inline T &BaseArray<T>::operator[](const int &idx)
{
    DM4thAssert(idx < this->size());
    return this->_data[idx];
}

template <class T>
inline T &BaseArray<T>::operator()(const int &idx)
{
    DM4thAssert(idx < this->size());
    return this->_data[idx];
}

template <class T>
inline const T &BaseArray<T>::operator()(const int &idx) const
{
    DM4thAssert(idx < this->size());
    return this->_data[idx];
}

template<class T>
inline T &BaseArray<T>::item(const int &idx)
{
    DM4thAssert(idx < this->size());
    return this->_data[idx];
}

template<class T>
inline const T &BaseArray<T>::item(const int &idx) const
{
    DM4thAssert(idx < this->size());
    return this->_data[idx];
}

template <class T>
const inline T &BaseArray<T>::get(const int &idx) const
{
    DM4thAssert(idx < this->size());
    return this->_data[idx];
}

template <class T>
void inline BaseArray<T>::set(const int &idx, const T &value)
{
    this->_data[idx] = value;
}

template <class T>
template <class U>
bool BaseArray<T>::operator==(const BaseArray<U> &other) const
{
    if (this->size() != other.size())
    {
        return false;
    }
    
    bool result;
     DM4th::Parallel::loopCond<int>(
        EDM4thParallelSettings::OMP_PARALLEL,
        0, this->_size, 1, //from, to, step

        [&](const int &j)->bool 
        {
            return this->get(j) == other.get(j);
        },
        result
    );
    return result;
}

template <class T>
template <class U>
inline bool BaseArray<T>::operator!=(const BaseArray<U> &other) const
{
    return !(*this == other);
}


template <class T>
inline const BaseArray<T> &BaseArray<T>::iAdd(const BaseArray<T> &other, const DM4thParallelSettings &pSettings)
{
    DM4thAssert(this->size() == other.size());

     DM4th::Parallel::loop<int>(
        pSettings,
        0, this->size(),  DM4th::SIMD::Vec<T>::size(), // from, to, step
        
        [&](const int &j) 
        {
             DM4th::SIMD::addArray(&this->item(j), &this->item(j), &other.item(j));
        }
       
    );

    return *this;
}

template <class T>
template <class U>
inline const BaseArray<T> &BaseArray<T>::iAdd(U other, const DM4thParallelSettings &pSettings)
{
     DM4th::Parallel::loop<int>(
        pSettings,
        0, this->size(),  DM4th::SIMD::Vec<T>::size(), // from, to, step
        
        [&](const int &j) 
        {
            //this->item(j) += other;
             DM4th::SIMD::addScalar(&this->item(j), &this->item(j), (T)other);
        }
    );

    return *this;
}

template <class T>
template <class U>
inline const BaseArray<T> &BaseArray<T>::iSub(U other, const DM4thParallelSettings &pSettings)
{
     DM4th::Parallel::loop<int>(
        pSettings,
        0, this->size(),  DM4th::SIMD::Vec<T>::size(), // from, to, step
        
        [&](const int &j) 
        {
             DM4th::SIMD::subScalar(&this->item(j), &this->item(j), (T)other);
        }
        
    );

    return *this;
}

template <class T>
inline const BaseArray<T> &BaseArray<T>::iSub(const BaseArray<T> &other, const DM4thParallelSettings &pSettings)
{
    DM4thAssert(this->size() == other.size());

     DM4th::Parallel::loop<int>(
        pSettings,
        0, this->size(),  DM4th::SIMD::Vec<T>::size(), // from, to, step
        
        [&](const int &j) 
        {
             DM4th::SIMD::subArray(&this->item(j), &this->item(j), &other.item(j));
        }

    );

    return *this;
}

template <class T>
template <class U>
inline const BaseArray<T> &BaseArray<T>::iMul(U other, const DM4thParallelSettings &pSettings)
{

     DM4th::Parallel::loop<int>(
        pSettings,
        0, this->size(),  DM4th::SIMD::Vec<T>::size(), // from, to, step
        
        [&](const int &j) 
        {
             DM4th::SIMD::mulScalar(&this->item(j), &this->item(j), (T)other);
        }

    );

    return *this;
}

template <class T>
template <class U>
inline const BaseArray<T> &BaseArray<T>::iDiv(U other, const DM4thParallelSettings &pSettings)
{
     DM4th::Parallel::loop<int>(
        pSettings,
        0, this->size(),  DM4th::SIMD::Vec<T>::size(), // from, to, step
        
        [&](const int &j) 
        {
             DM4th::SIMD::divScalar(&this->item(j), &this->item(j), (T)other);
        }
    
    );

    return *this;
}

template <class T>
template <class U>
inline const BaseArray<T> &BaseArray<T>::iMod(U other, const DM4thParallelSettings &pSettings)
{

     DM4th::Parallel::loop<int>(
        pSettings,
        0, this->size(), 1, // from, to, step
        
        [&](const int &j) 
        {
            this->set(j, std::fmod(this->item(j), (T)other));
        }

    );

    return *this;
}

template <>
template <class U>
inline const BaseArray<number> &BaseArray<number>::iMod(U other, const DM4thParallelSettings &pSettings)
{

     DM4th::Parallel::loop<int>(
        pSettings,
        0, this->size(), 1, // from, to, step
        
        [&](const int &j) 
        {
            this->set(j, DM4th::fmod(this->item(j), (number)other));
        }

    );

    return *this;
}


template<class T> 
template<class U> inline const BaseArray<T> &BaseArray<T>::operator+=(const BaseArray<U> &other)
{
    this->iAdd(other, EDM4thParallelSettings::DEFAULT);
    return *this;
}

template<class T> 
template<class U> inline const BaseArray<T> &BaseArray<T>::operator-=(const BaseArray<U> &other)
{
    this->iSub(other, EDM4thParallelSettings::DEFAULT);
    return *this;
}

template<class T> 
template<class U> inline const BaseArray<T> &BaseArray<T>::operator+=(const U &other)
{
    this->iAdd(other, EDM4thParallelSettings::DEFAULT);
    return *this;
}

template<class T> 
template<class U> inline const BaseArray<T> &BaseArray<T>::operator-=(const U &other)
{
    this->iSub(other, EDM4thParallelSettings::DEFAULT);
    return *this;
}

template<class T> 
template<class U> inline const BaseArray<T> &BaseArray<T>::operator*=(const U &other)
{
    this->iMul(other, EDM4thParallelSettings::DEFAULT);
    return *this;
}

template<class T> 
template<class U> inline const BaseArray<T> &BaseArray<T>::operator/=(const U &other)
{
    this->iDiv(other, EDM4thParallelSettings::DEFAULT);
    return *this;
}

template<class T> 
template<class U> inline const BaseArray<T> &BaseArray<T>::operator%=(const U &other)
{
    this->iMod(other, EDM4thParallelSettings::DEFAULT);
    return *this;
}

template <class T>
inline void BaseArray<T>::clear()
{
    this->_size = 0;
    this->_capacity = 0;
    if (this->_data == nullptr) return;
    delete[] this->_data;
    this->_data = nullptr;
}

template <class T>
inline void BaseArray<T>::moveDataTo(BaseArray<T> &other)
{
    other.clear();
    other._data = this->_data;
    other._size = this->_size;
    this->_data = nullptr;
    this->_size = 0;
}

template<class T>
inline void BaseArray<T>::copyDataTo(BaseArray<T> &other) const
{
    other.resize(this->size());
    std::copy_n(this->_data, this->_size, other._data);
}

template<class T>
inline void BaseArray<T>::copyNItemsTo(BaseArray<T> &other, const int &thisFrom, const int &otherFrom, const int &count) const
{
    std::cout<<this->size()<<" " <<other.size()<<" "<<thisFrom<< " "<<otherFrom<<" "<<count<<std::endl;
    DM4thAssert(this->size()>=thisFrom+count && other.size()>=otherFrom+count);
    std::copy_n(this->_data + thisFrom, count, other._data + otherFrom);
}

template<class T>
inline void BaseArray<T>::push(const T &value, const int &idx)
{
    DM4thAssert(idx>=0 && idx<=this->size());
    if(idx==this->size() && this->capacity()>idx)
    {
        this->_size += 1;
        this->set(idx, value);
    }else if(this->capacity()>this->size()+1)
    {
        this->_size += 1;
        std::copy_backward(this->_data+idx, this->_data+_size-1, this->_data+_size);
        this->set(idx, value);
        
    }else{
        T* tmp = this->_data;

        this->_capacity = sizeAligned<T>(this->size()+1);
        this->_data = new T[this->_capacity];
        this->_size += 1;

        std::copy_n(tmp, idx, this->_data);
        this->set(idx, value);
        std::copy_n(tmp+idx, this->size()-idx-1, this->_data+idx+1);

        delete[] tmp;
    }
}

template<class T>
inline T BaseArray<T>::pop(const int &idx)
{
    DM4thAssert(idx>=0 && idx<=this->size()-1);
    T result = this->get(idx);

    std::copy_n(this->_data+idx+1, this->size()-idx-1, this->_data+idx);
    this->_size -= 1;

    return result;
}


template<class T>
inline std::ostream& operator<<(std::ostream& stream, const BaseArray<T> &arr)
{
    stream<<"[";
    for(int j=0; j<arr.size();++j)
    {
        if(j!=0) stream<<", ";
        stream<<arr.get(j);
    }
    stream<<"]";
    return stream;
}

//////////////////// ArrayData

template <class T>
inline void ArrayData<T>::incrRef()
{
    ++_ref;
    //std::cout<<this<<" INCR+ REF: "<<_ref<<std::endl;
}

template <class T>
inline void ArrayData<T>::decrRef()
{
    _ref -= 1;
    //std::cout<<this<<" DECR REF: "<<_ref<<std::endl;
    if (this->_ref <= 0)
    {
        array.clear();
        shape.clear();
    }
}

template <class T>
inline int ArrayData<T>::refCount() const
{
    return this->_ref;
}

template<class T>
inline void ArrayData<T>::moveDataTo(ArrayData<T> &other)
{
    this->shape.moveDataTo(other.shape);
    this->array.moveDataTo(other.array);
    this->shape.resize(1);
    this->shape.set(0,0);
}

//////////////////// ArrayDataManager

template <class T>
void ArrayDataManager<T>::incrRef()
{
     DM4th::Parallel::criticalSection(DEFAULT,
    [&]{
        if (this->_data == nullptr)
        {
            this->_data = new ArrayData<T>();
        }
        this->_data->incrRef();
    });
}

template <class T>
void ArrayDataManager<T>::decrRef()
{
     DM4th::Parallel::criticalSection(DEFAULT,
    [&]{
        this->_data->decrRef();
        if (this->_data->refCount() <= 0)
        {
            delete this->_data;
            this->_data = nullptr;
        }
    });
}

template <class T>
int ArrayDataManager<T>::refCount() const
{
    if(this->_data!=nullptr) return this->_data->refCount();
    else return 0;
}

template <class T>
inline ArrayDataManager<T>::ArrayDataManager()
{
    this->incrRef();
}

template <class T>
inline ArrayDataManager<T>::ArrayDataManager(const ArrayDataManager<T> &other)
{
    _data = other._data;
    this->incrRef();
}
template <class T>
inline ArrayDataManager<T>::~ArrayDataManager()
{
    this->decrRef();
}

template <class T>
inline ArrayDataManager<T> const &ArrayDataManager<T>::operator=(const ArrayDataManager<T> &other)
{
    if (this->_data == other._data)
        return *this;
    this->decrRef();
    this->_data = other._data;
    this->incrRef();
    return *this;
}

template <class T>
inline int ArrayDataManager<T>::rank()
{
    return this->_data->shape.size();
}

template <class T>
inline int ArrayDataManager<T>::shape(const int &axis)
{
    return this->_data->shape(axis);
}

template <class T>
inline ArrayData<T> const &ArrayDataManager<T>::getArrayData() const
{
    return *_data;
}

template<class T>
inline void ArrayDataManager<T>::moveDataTo(ArrayDataManager<T> &other)
{
    if(this->_data != nullptr)
    {
        if(other._data == nullptr) other._data = new ArrayData<T>();
        this->_data->shape.moveDataTo(other._data->shape);
        this->_data->array.moveDataTo(other._data->array);
        this->_data->shape.resize(1);
        this->_data->shape(0) = 0;
    }
    else if(other._data != nullptr)
    {
        other._data->array.resize(0);
        other._data->shape.resize(1);
        other._data->shape(0) = 0;
    }
}

template<class T>
inline void ArrayDataManager<T>::copyDataTo(ArrayDataManager<T> &other)
{
    if(this->_data != nullptr)
    {
        if(other._data == nullptr) other._data = new ArrayData<T>();
        this->_data->shape.copyDataTo(other._data->shape);
        this->_data->array.copyDataTo(other._data->array);
    }
    else if(other._data != nullptr)
    {
        other._data->array.resize(0);
        other._data->shape.resize(1);
        other._data->shape(0) = 0;
    }
}

template<class T>
inline bool ArrayDataManager<T>::isSameRef(ArrayDataManager<T> &other)
{
    return (this->_data == other._data);
}
} // namespace Internal

} // namespace DM4th