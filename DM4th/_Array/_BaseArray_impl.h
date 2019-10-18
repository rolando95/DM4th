#pragma once

#include "_BaseArray.h"


namespace DM4th
{

namespace DM4thInternal
{

//#define sizeAligned(x)   (x + 3) & -4
#define sizeAligned(x)   (x + 3) & ~0x03

//////////////////// _BaseArray
#if defined BASEARRAY_STD_VECTOR


template<class T>
inline void _BaseArray<T>::resize(int size)
{
    this->_array.resize(size);
}

template<class T>
inline const int _BaseArray<T>::size() const 
{
    return this->_array.size();
}

template<class T>
inline T &_BaseArray<T>::operator[](int idx) 
{
    return this->_array[idx]; //// FIX THIS
}

template<class T>
inline T &_BaseArray<T>::operator()(int idx)
{
    return this->_array[idx]; /// FIX THIS
}

template<class T>
const inline T _BaseArray<T>::get(int idx) const
{
    return this->_array[idx];
}

template<class T>
void inline _BaseArray<T>::set(int idx, T value)
{
    this->_array[idx] = value;
}

template<class T> template<class U> 
bool _BaseArray<T>::operator==(const _BaseArray<U> &other) const
{
    if(this->size()!=other.size())
    {
        return false;
    }
    for(int j=0; j<this->size(); ++j)
    {
        if(this->get(j) != other.get(j))
        {
            return false;
        }
    }
    return true;
}
template<class T> template<class U> 
inline bool _BaseArray<T>::operator!=(const _BaseArray<U> &other) const
{
    return !(*this==other);
}

template<class T>
inline void _BaseArray<T>::clear()
{
    this->_array.clear();
}

template<class T>
inline void _BaseArray<T>::moveReferenceTo(_BaseArray<T> &other)
{
    other._array = std::move(this->_array);
}
#else 

template<class T>
inline void _BaseArray<T>::allocArray(int size)
{
    DM4thAssert(!this->_array && size>0);
    this->_array = new T[size]();
    this->_size = size;
}

template<class T>
inline void _BaseArray<T>::reallocArray(int size, bool useMemcpy)
{
    DM4thAssert(this->_array && size>0);
    if(size!=_size)
    {
        T *tmp = new T[sizeAligned(size)]();
        int min = _min(size, this->_size);

        if(useMemcpy) memcpy((void*)tmp, (void*)this->_array, sizeof(T)*min); 
        else for(int j=0; j<min; ++j){ tmp[j] = _array[j]; }
        
        delete[] _array;
        _array = tmp;
        tmp = nullptr;
        _size = size;
    }
}

template<class T>
_BaseArray<T>::_BaseArray(int size)
{
    if(size>0){ allocArray(size); }
}

template<class T>
inline void _BaseArray<T>::resize(int size, bool useMemcpy)
{
    if(size==0) 
    {
        this->clear();
        return;
    }
    if(this->_array==nullptr){ this->allocArray(size); }
    else{ this->reallocArray(size, useMemcpy); }
}

template<class T>
inline const int _BaseArray<T>::size() const { return this->_size; }

template<class T>
inline T &_BaseArray<T>::operator[](int idx)
{ 
    DM4thAssert(idx<this->size()); 
    return  this->_array[idx]; 
}

template<class T>
inline T &_BaseArray<T>::operator()(int idx)
{ 
    DM4thAssert(idx<this->size()); 
    return this->_array[idx]; 
}

template<class T>
const inline T _BaseArray<T>::get(int idx) const 
{ 
    DM4thAssert(idx<this->size()); 
    return this->_array[idx]; 
}

template<class T>
void inline _BaseArray<T>::set(int idx, T value) 
{  
    this->_array[idx]=value;
}


template<class T> template<class U>
bool _BaseArray<T>::operator==(const _BaseArray<U> &other) const 
{
    bool result = true;
    if(this->size()!=other.size())
    {
        return false;
    }

    #if defined DM4thOmpFor
        #pragma omp parallel shared(result)
        {
            int threads = omp_get_num_threads();
            int j = omp_get_thread_num();
            while(j<this->size() && result)
            {
                if(this->_array[j] != other.get(j))
                {
                    result = false;
                }
                j+= threads;
            }
        }
    #else
        for(int j=0; j<this->size(); ++j)
        {
            if(this->_array[j] != other.get(j))
            {
                result = false;
                break;
            }
        }
    #endif

    return result;
}

template<class T> template<class U>
inline bool _BaseArray<T>::operator!=(const _BaseArray<U> &other) const 
{ 
    return !(*this==other); 
}

template<class T> template<class U>
const _BaseArray<T> &_BaseArray<T>::operator+=(const _BaseArray<U> &other) 
{
    DM4thAssert(this->size()==other.size());
    
    #if defined DM4thOmpFor
        #pragma omp parallel
        {
            
            #pragma omp for
            for(int j=0; j<this->size(); ++j)
            {
                this->set(j, this->get(j) + other.get(j));
            }
        }
    #else
        for(int j=0; j<this->size(); ++j)
        {
            this->set(j, this->get(j) + other.get(j));
        }
    #endif
    return *this;
}

template<class T> template<class U>
const _BaseArray<T> &_BaseArray<T>::operator+=(const U &other) 
{
    #if defined DM4thOmpFor
        #pragma omp parallel
        {
            #pragma omp parallel for shared(other)
            for(int j=0; j<this->size(); ++j)
            {
                this->set(j, this->get(j) + (T)other);
            }
        }
        
    #else
        for(int j=0; j<this->size(); ++j)
        {
            this->set(j, this->get(j) + (T)other);
        }
    #endif
    return *this;
}

template<class T> template<class U>
const _BaseArray<T> &_BaseArray<T>::operator-=(const U &other) 
{
    #if defined DM4thOmpFor
        #pragma omp parallel for
    #endif
    for(int j=0; j<this->size(); ++j)
    {
        this->set(j, this->get(j) - (T)other);
    }
    return *this;
}

template<class T> template<class U>
const _BaseArray<T> &_BaseArray<T>::operator-=(const _BaseArray<U> &other) 
{
    DM4thAssert(this->size()==other.size());
    
    #if defined DM4thOmpFor
        #pragma omp parallel for
    #endif
    for(int j=0; j<this->size(); ++j)
    {
        this->set(j, this->get(j) - (T)other.get(j));
    }
    return *this;
}

template<class T> template<class U>
const _BaseArray<T> &_BaseArray<T>::operator*=(const U &other) 
{
    #if defined DM4thOmpFor
        #pragma omp parallel for
    #endif
    for(int j=0; j<this->size(); ++j)
    {
        this->set(j, this->get(j) * (T)other);
    }
    return *this;
}

template<class T> template<class U>
const _BaseArray<T> &_BaseArray<T>::operator/=(const U &other) 
{
    #if defined DM4thOmpFor
        #pragma omp parallel for
    #endif
    for(int j=0; j<this->size(); ++j)
    {
        this->set(j, this->get(j) / (T)other);
    }
    return *this;
}

template<class T> template<class U>
const _BaseArray<T> &_BaseArray<T>::operator%=(const U &other) 
{
    #if defined DM4thOmpFor
        #pragma omp parallel for
    #endif
    for(int j=0; j<this->size(); ++j)
    {
        this->set(j, fmod(this->get(j),(T)other));
    }
    return *this;
}


template<class T>
inline void _BaseArray<T>::clear()
{
    this->_size=0;
    if(this->_array == nullptr) return;
    delete[] this->_array;
    this->_array = nullptr;
}

template<class T>
inline void _BaseArray<T>::moveReferenceTo(_BaseArray<T> &other)
{
    other.clear();
    other._array = this->_array;
    other._size = this->_size;
    this->_array = nullptr;
    this->_size = 0;
}
#endif
//////////////////// _ShapeData

inline _ShapeData::_ShapeData(int size){ _shape.resize(size); }
inline _ShapeData::~_ShapeData(){}
inline void _ShapeData::resize(int size){ _shape.resize(size); }
inline const int _ShapeData::size() { return _shape.size(); }
inline void _ShapeData::clear() { this->_shape.clear(); }
inline int &_ShapeData::operator[](int idx){ return  this->_shape[idx]; }
inline int &_ShapeData::operator()(int idx){ return this->_shape[idx]; }
inline bool _ShapeData::operator==(const _ShapeData &other) const { return this->_shape==other._shape; }
inline bool _ShapeData::operator!=(const _ShapeData &other) const { return this->_shape!=other._shape; }
inline const int _ShapeData::get(int idx) const { return this->_shape.get(idx); }
inline void _ShapeData::set(int idx, int value) { this->_shape.set(idx,value); }
inline const int *_ShapeData::data(){ return &_shape[0]; }

//////////////////// _ArrayData

template<class T>
void _ArrayData<T>::incrRef()
{
    ++_ref;
    //std::cout<<this<<" INCR+ REF: "<<_ref<<std::endl;
}

template<class T>
void _ArrayData<T>::decrRef()
{
    _ref -= 1;
    //std::cout<<this<<" DECR REF: "<<_ref<<std::endl;
    if(this->_ref <= 0)
    { 
        array.clear(); 
        shape.clear();
    }
}

template<class T>
int  _ArrayData<T>::refCount() const 
{ 
    return this->_ref;
}

//////////////////// _ArrayDataManager

template<class T>
void _ArrayDataManager<T>::incrRef()
{
    if(this->_data == nullptr)
    {
        this->_data = new _ArrayData<T>();
    }
    this->_data->incrRef();
}

template<class T>
void _ArrayDataManager<T>::decrRef()
{
    this->_data->decrRef();
    if(this->_data->refCount() <= 0) 
    {
        delete this->_data;
        this->_data = nullptr;
    }
    
}

template<class T>
_ArrayDataManager<T>::_ArrayDataManager(){ 
    this->incrRef(); 
}

template<class T>
_ArrayDataManager<T>::_ArrayDataManager(const _ArrayDataManager<T> &other)
{
    _data = other._data;
    this->incrRef();
}
template<class T>
_ArrayDataManager<T>::~_ArrayDataManager()
{ 
    this->decrRef(); 
}

template<class T>
_ArrayDataManager<T> const &_ArrayDataManager<T>::operator=(const _ArrayDataManager<T> &other) 
{
    if(this->_data==other._data) return *this;
    this->decrRef();
    this->_data = other._data;
    this->incrRef();
    return *this;
}

template<class T>
int _ArrayDataManager<T>::shapeSize(){
    return this->_data->shape.size();
}

template<class T>
int _ArrayDataManager<T>::shape(int axis){
    return this->_data->shape(axis);
}

template<class T>
_ArrayData<T> const *_ArrayDataManager<T>::_arrayData() const
{
    return _data;
}

}

}