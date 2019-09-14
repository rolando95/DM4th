#pragma once

#include "_BaseArray.h"

namespace DM4th
{

//////////////////// _BaseArray

template<class T>
inline void _BaseArray<T>::allocArray(int size)
{
    assert(!this->_array && size>0);
    this->_array = new T[size]();
    this->_size = size;
}

template<class T>
inline void _BaseArray<T>::reallocArray(int size)
{
    assert(this->_array && size>0);
    if(size!=_size)
    {
        T *tmp = new T[size]();
        int min = _min(size, this->_size);
        for(int j=0; j<min; ++j){ tmp[j] = _array[j]; }
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
inline void _BaseArray<T>::resize(int size)
{
    if(size==0) 
    {
        this->freeArray();
        return;
    }
    if(this->_array==nullptr){ this->allocArray(size); }
    else{ this->reallocArray(size); }
}

template<class T>
inline T* _BaseArray<T>::_allocAndReturnOldArray(int size)
{
    assert(size>0);
    T* result = this->_array;
    this->_array = new T[size]();
    this->_size = size;
    return result;
}

template<class T>
inline const int _BaseArray<T>::size() const { return this->_size; }

template<class T>
inline T &_BaseArray<T>::operator[](int idx)
{ 
    assert(idx<this->size()); 
    return  this->_array[idx]; 
}

template<class T>
inline T &_BaseArray<T>::operator()(int idx)
{ 
    assert(idx<this->size()); 
    return this->_array[idx]; 
}

template<class T>
const inline T _BaseArray<T>::get(int idx) const 
{ 
    assert(idx<this->size()); 
    return this->_array[idx]; 
}

template<class T>
void _BaseArray<T>::set(int idx, T value) 
{  
    this->_array[idx]=value;
}

template<class T>
bool _BaseArray<T>::isFree(){
    return this->_array==nullptr; 
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
        if(this->_array[j] != other.get(j))
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
inline void _BaseArray<T>::freeArray()
{
    this->_size=0;
    if(this->_array == nullptr) return;
    delete[] this->_array;
    this->_array = nullptr;
}

//////////////////// _ShapeData

inline _ShapeData::_ShapeData(int size){ _shape.resize(size); }
inline _ShapeData::~_ShapeData(){}
inline void _ShapeData::resize(int size){ _shape.resize(size); }
inline const int _ShapeData::size() { return _shape.size(); }
inline void _ShapeData::freeArray() { 
    if(!this->_shape.isFree()){
        this->_shape.freeArray();
    }
}
inline int &_ShapeData::operator[](int idx){ return  this->_shape[idx]; }
inline int &_ShapeData::operator()(int idx){ return this->_shape[idx]; }
inline bool _ShapeData::operator==(const _ShapeData &other) const { return this->_shape==other._shape; }
inline bool _ShapeData::operator!=(const _ShapeData &other) const { return this->_shape!=other._shape; }
inline const int _ShapeData::get(int idx) const { return this->_shape.get(idx); }
inline void _ShapeData::set(int idx, int value) { this->_shape.set(idx,value); }
inline const int *_ShapeData::c_arr(){ return &_shape[0]; }

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
    if(this->_ref <= 0 && !array.isFree())
    { 
        array.freeArray(); 
        shape.freeArray();
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