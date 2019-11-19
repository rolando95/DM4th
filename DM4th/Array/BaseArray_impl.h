#pragma once

#include "BaseArray.h"

namespace DM4th
{

namespace DM4thInternal
{

//#define sizeAligned(x)   (x + 3) & -4
#define sizeAligned(x) (x + 3) & ~0x03

//////////////////// BaseArray
#if defined BASEARRAY_STD_VECTOR

template <class T>
inline void BaseArray<T>::resize(int size)
{
    this->Array.resize(size);
}

template <class T>
inline const int BaseArray<T>::size() const
{
    return this->Array.size();
}

template <class T>
inline T &BaseArray<T>::operator[](int idx)
{
    return this->Array[idx]; //// FIX THIS
}

template <class T>
inline T &BaseArray<T>::operator()(int idx)
{
    return this->Array[idx]; /// FIX THIS
}

template <class T>
const inline T BaseArray<T>::get(int idx) const
{
    return this->Array[idx];
}

template <class T>
void inline BaseArray<T>::set(int idx, T value)
{
    this->Array[idx] = value;
}

template <class T>
template <class U>
bool BaseArray<T>::operator==(const BaseArray<U> &other) const
{
    if (this->size() != other.size())
    {
        return false;
    }
    for (int j = 0; j < this->size(); ++j)
    {
        if (this->get(j) != other.get(j))
        {
            return false;
        }
    }
    return true;
}
template <class T>
template <class U>
inline bool BaseArray<T>::operator!=(const BaseArray<U> &other) const
{
    return !(*this == other);
}

template <class T>
inline void BaseArray<T>::clear()
{
    this->Array.clear();
}

template <class T>
inline void BaseArray<T>::moveReferenceTo(BaseArray<T> &other)
{
    other.Array = std::move(this->Array);
}
#else

template <class T>
inline void BaseArray<T>::allocArray(int size)
{
    DM4thAssert(!this->Array && size > 0);
    this->Array = new T[size]();
    this->_size = size;
    this->_top = this->_size;
}

template <class T>
inline void BaseArray<T>::reallocArray(int size)
{
    DM4thAssert(this->Array && size > 0);
    if (size != _size)
    {
        if (size > this->_top)
        {

            this->_top = sizeAligned(size);
            T *tmp = new T[this->_top];
            int min = (size < this->_size) ? size : this->_size;

            //memcpy((void*)tmp, (void*)this->Array, sizeof(T)*min);
            for (int j = 0; j < min; ++j)
            {
                tmp[j] = this->Array[j];
            }

            for (int j = min; j < size; ++j)
            {
                tmp[j] = T();
            }

            delete[] this->Array;
            this->Array = tmp;
            tmp = nullptr;
            this->_size = size;
        }
        else
        {
            this->_size = size;
        }
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
    if (this->Array == nullptr)
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
    return this->Array[idx];
}

template <class T>
inline T &BaseArray<T>::operator()(int idx)
{
    DM4thAssert(idx < this->size());
    return this->Array[idx];
}

template <class T>
const inline T BaseArray<T>::get(int idx) const
{
    DM4thAssert(idx < this->size());
    return this->Array[idx];
}

template <class T>
void inline BaseArray<T>::set(int idx, T value)
{
    this->Array[idx] = value;
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
            if (this->Array[j] != other.get(j))
            {
                result = false;
            }
            j += threads;
        }
    }
#else
    for (int j = 0; j < this->size(); ++j)
    {
        if (this->Array[j] != other.get(j))
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
    if (this->Array == nullptr)
        return;
    delete[] this->Array;
    this->Array = nullptr;
}

template <class T>
inline void BaseArray<T>::moveReferenceTo(BaseArray<T> &other)
{
    other.clear();
    other.Array = this->Array;
    other._size = this->_size;
    this->Array = nullptr;
    this->_size = 0;
}

template<class T>
inline void BaseArray<T>::copyReferenceTo(BaseArray<T> &other) const
{
    other.resize(this->size());
    for(int j=0; j<this->size(); ++j)
    {
        other.set(j,this->get(j));
    }
}
#endif
//////////////////// ShapeData

inline ShapeData::ShapeData(int size) { _shape.resize(size); }
inline ShapeData::~ShapeData() {}
inline void ShapeData::resize(int size) { _shape.resize(size); }
inline const int ShapeData::size() { return _shape.size(); }
inline void ShapeData::clear() { this->_shape.clear(); }
inline int &ShapeData::operator[](int idx) { return this->_shape[idx]; }
inline int &ShapeData::operator()(int idx) { return this->_shape[idx]; }
inline bool ShapeData::operator==(const ShapeData &other) const { return this->_shape == other._shape; }
inline bool ShapeData::operator!=(const ShapeData &other) const { return this->_shape != other._shape; }
inline const int ShapeData::get(int idx) const { return this->_shape.get(idx); }
inline void ShapeData::set(int idx, int value) { this->_shape.set(idx, value); }
inline const int *ShapeData::data() { return &_shape[0]; }

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
void ArrayData<T>::moveReferenceTo(ArrayData<T> &other)
{
    this->shape.moveReferenceTo(other.shape);
    this->array.moveReferenceTo(other.array);
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
int ArrayDataManager<T>::shapeSize()
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
inline void ArrayDataManager<T>::_moveDataRefTo(ArrayDataManager<T> &other)
{
    if(this->_data == nullptr) this->_data = new ArrayData<T>();
    this->_data->moveReferenceTo(*other._data);
}

template<class T>
inline bool ArrayDataManager<T>::isSameRef(ArrayDataManager<T> &other)
{
    return (this->_data == other._data);
}
} // namespace DM4thInternal

} // namespace DM4th