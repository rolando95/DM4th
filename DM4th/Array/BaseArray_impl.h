#pragma once

#include "BaseArray.h"

namespace DM4th
{

namespace DM4thInternal
{

//#define sizeAligned(x)   (x + 3) & -4
#define sizeAligned(x) (x + 3) & ~0x03

//////////////////// BaseArray


template <class T>
inline void BaseArray<T>::allocArray(int size)
{
    DM4thAssert(!this->_data && size > 0);
    this->_data = new T[size]();
    this->_size = size;
    this->_top = this->_size;
}

template <class T>
inline void BaseArray<T>::reallocArray(int size)
{
    DM4thAssert(this->_data && size > 0);
    if (size != _size)
    {
        if (size > this->_top)
        {
            this->_top = sizeAligned(size);   
            T *tmp = new T[this->_top];     
            int min = (size < this->_size) ? size : this->_size;

            std::copy_n(this->_data, min, tmp);
            delete[] this->_data;

            if(std::is_arithmetic<T>::value) { 
                std::fill_n(tmp+min, size-min, T()); 
            }
            
            this->_data = tmp;
            tmp = nullptr;
        }
        this->_size = size;
    }
}

template <class T>
BaseArray<T>::BaseArray(int size)
{
    if (size > 0)
    {
        allocArray(size);
    }
}

template <class T>
inline void BaseArray<T>::resize(int size)
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

template <class T>
inline const int BaseArray<T>::size() const { return this->_size; }

template <class T>
inline T &BaseArray<T>::operator[](int idx)
{
    DM4thAssert(idx < this->size());
    return this->_data[idx];
}

template <class T>
inline T &BaseArray<T>::operator()(int idx)
{
    DM4thAssert(idx < this->size());
    return this->_data[idx];
}

template <class T>
const inline T BaseArray<T>::get(int idx) const
{
    DM4thAssert(idx < this->size());
    return this->_data[idx];
}

template <class T>
void inline BaseArray<T>::set(int idx, T value)
{
    this->_data[idx] = value;
}

template <class T>
template <class U>
bool BaseArray<T>::operator==(const BaseArray<U> &other) const
{
    bool result = true;
    if (this->size() != other.size())
    {
        return false;
    }

#if defined DM4thOmpFor
    #pragma omp parallel shared(result)
    {
        int threads = omp_get_num_threads();
        int j = omp_get_thread_num();
        while (j < this->size() && result)
        {
            if (this->_data[j] != other.get(j))
            {
                result = false;
            }
            j += threads;
        }
    }
#else
    for (int j = 0; j < this->size(); ++j)
    {
        if (this->_data[j] != other.get(j))
        {
            result = false;
            break;
        }
    }
#endif

    return result;
}

template <class T>
template <class U>
inline bool BaseArray<T>::operator!=(const BaseArray<U> &other) const
{
    return !(*this == other);
}

template <class T>
template <class U>
const BaseArray<T> &BaseArray<T>::operator+=(const BaseArray<U> &other)
{
    DM4thAssert(this->size() == other.size());

    #if defined DM4thOmpFor
        #pragma omp parallel for shared(other)
    #endif

    for (int j = 0; j < this->size(); ++j)
    {
        this->set(j, this->get(j) + other.get(j));
    }

    return *this;
}

template <class T>
template <class U>
const BaseArray<T> &BaseArray<T>::operator+=(const U &other)
{
    #if defined DM4thOmpFor
        #pragma omp parallel for shared(other)
    #endif
    for (int j = 0; j < this->size(); ++j)
    {
        this->set(j, this->get(j) + (T)other);
    }

    return *this;
}

template <class T>
template <class U>
const BaseArray<T> &BaseArray<T>::operator-=(const U &other)
{
    #if defined DM4thOmpFor
        #pragma omp parallel for shared(other)
    #endif

    for (int j = 0; j < this->size(); ++j)
    {
        this->set(j, this->get(j) - (T)other);
    }

    return *this;
}

template <class T>
template <class U>
const BaseArray<T> &BaseArray<T>::operator-=(const BaseArray<U> &other)
{
    DM4thAssert(this->size() == other.size());

    #if defined DM4thOmpFor
        #pragma omp parallel for shared(other)
    #endif

    for (int j = 0; j < this->size(); ++j)
    {
        this->set(j, this->get(j) - (T)other.get(j));
    }

    return *this;

}

template <class T>
template <class U>
const BaseArray<T> &BaseArray<T>::operator*=(const U &other)
{

    #if defined DM4thOmpFor
        #pragma omp parallel for shared(other)
    #endif

    for (int j = 0; j < this->size(); ++j)
    {
        this->set(j, this->get(j) * (T)other);
    }
    return *this;
}

template <class T>
template <class U>
const BaseArray<T> &BaseArray<T>::operator/=(const U &other)
{
    #if defined DM4thOmpFor
        #pragma omp parallel for shared(other)
    #endif

    for (int j = 0; j < this->size(); ++j)
    {
        this->set(j, this->get(j) / (T)other);
    }
    return *this;
}

template <class T>
template <class U>
const BaseArray<T> &BaseArray<T>::operator%=(const U &other)
{
    #if defined DM4thOmpFor
        #pragma omp parallel for shared(other)
    #endif

    for (int j = 0; j < this->size(); ++j)
    {
        this->set(j, fmod(this->get(j), (T)other));
    }
    return *this;
}

template <class T>
inline void BaseArray<T>::clear()
{
    this->_size = 0;
    this->_top = 0;
    if (this->_data == nullptr)
        return;
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
void ArrayData<T>::incrRef()
{
    ++_ref;
    //std::cout<<this<<" INCR+ REF: "<<_ref<<std::endl;
}

template <class T>
void ArrayData<T>::decrRef()
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
int ArrayData<T>::refCount() const
{
    return this->_ref;
}

template<class T>
void ArrayData<T>::moveDataTo(ArrayData<T> &other)
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
    if (this->_data == nullptr)
    {
        this->_data = new ArrayData<T>();
    }
    this->_data->incrRef();
}

template <class T>
void ArrayDataManager<T>::decrRef()
{
    this->_data->decrRef();
    if (this->_data->refCount() <= 0)
    {
        delete this->_data;
        this->_data = nullptr;
    }
}

template <class T>
int ArrayDataManager<T>::refCount() const
{
    if(this->_data!=nullptr) return this->_data->refCount();
    else return 0;
}

template <class T>
ArrayDataManager<T>::ArrayDataManager()
{
    this->incrRef();
}

template <class T>
ArrayDataManager<T>::ArrayDataManager(const ArrayDataManager<T> &other)
{
    _data = other._data;
    this->incrRef();
}
template <class T>
ArrayDataManager<T>::~ArrayDataManager()
{
    this->decrRef();
}

template <class T>
ArrayDataManager<T> const &ArrayDataManager<T>::operator=(const ArrayDataManager<T> &other)
{
    if (this->_data == other._data)
        return *this;
    this->decrRef();
    this->_data = other._data;
    this->incrRef();
    return *this;
}

template <class T>
int ArrayDataManager<T>::rank()
{
    return this->_data->shape.size();
}

template <class T>
int ArrayDataManager<T>::shape(int axis)
{
    return this->_data->shape(axis);
}

template <class T>
ArrayData<T> const &ArrayDataManager<T>::getArrayData() const
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
} // namespace DM4thInternal

} // namespace DM4th