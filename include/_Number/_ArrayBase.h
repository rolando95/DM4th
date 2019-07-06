#include "_Constants.h"
#include "_Math.h"
#include <iostream>
#include <string>
#include <cassert>

template<class T> 
class _BaseArray
{
    protected:
        int _size=0;
        T *_array=nullptr;

        inline void allocArray(int size)
        {
            assert(!this->_array && size>0);
            this->_array = new T[size]();
            this->_size = size;
        }

        inline void reallocArray(int size)
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

    public:
        _BaseArray(int size=0)
        {
            if(size>0){ allocArray(size); }
        }

        inline void resize(int size)
        {
            if(this->_array==nullptr){ this->allocArray(size); }
            else{ this->reallocArray(size); }
        }

        inline T* _allocAndReturnOldArray(int size){
            assert(size>0);
            T* result = this->_array;
            this->_array = new T[size]();
            this->_size = size;
            return result;
        }

        inline int size() const { return this->_size; }
        inline T &operator[](int idx){ assert(idx<this->size()); return  this->_array[idx]; }
        inline T &operator()(int idx){ assert(idx<this->size()); return this->_array[idx]; }

        bool isFree(){
            return this->_array==nullptr; 
        }

        inline void freeArray()
        {
            assert(this->_array != nullptr);
            delete[] this->_array;
            this->_array = nullptr;
            this->_size=0;
        }
};


class _ShapeData
{
    protected:
        _BaseArray<int> _shape;
    public:
        _ShapeData(int size=1){ _shape.resize(size); }
        ~_ShapeData(){}
        inline void resize(int size){ _shape.resize(size); }
        inline const int size() { return _shape.size(); }
        inline const int getAxisIdx(int idx) { return _shape[idx]; }
        inline void setAxisIdx(int idx, int value){ _shape[idx] = value; }
        inline void freeArray() { 
            if(!this->_shape.isFree()){
                this->_shape.freeArray();
            }
        }
};

template<class T>
class _ArrayData
{
    private:
        volatile int _ref=0;
    public:
        _ShapeData shape;
        _BaseArray<T> array;
        
        void incrRef()
        {
            ++_ref;
            std::cout<<this<<" INCR REF: "<<_ref<<std::endl;
        }

        void decrRef()
        {
            _ref -= 1;
            std::cout<<this<<" DECR REF: "<<_ref<<std::endl;
            if(this->_ref <= 0 && !array.isFree()){ 
                array.freeArray(); 
                shape.freeArray();
            }
        }

        int refCount() const { return this->_ref; }
};

template<class T>
class _ArrayDataManager
{
    protected:
        _ArrayData<T> *_data = nullptr;
        
        template<class ... U>
        T &_item(int axis, int pos, int idx, U ... args){
            pos = pos*this->_data->shape.getAxisIdx(axis) + idx;
            return _item(axis+1, pos, args ...);
        }

        T &_item(int axis, int pos, int idx){
            assert(axis+1 == this->_data->shape.size());
            pos = pos*this->_data->shape.getAxisIdx(axis) + idx;
            return this->_data->array[pos];
        }

        template<class ... U>
        T* _allocZeros(int axis, int count, int idx, U ... args){
             count *= idx;
            T* oldArray = _allocZeros(axis+1, count, args ...);
            this->_data->shape.setAxisIdx(axis, idx);
            return oldArray;
        }

        T*  _allocZeros(int axis, int count, int idx){
            count*=idx;
            T* oldArray = this->_data->array._allocAndReturnOldArray(count);
            this->_data->shape.resize(axis+1);
            this->_data->shape.setAxisIdx(axis, idx);
            return oldArray;
        }

    public:
        
        _ArrayDataManager()
        {
            _data = new _ArrayData<T>();
            _data->incrRef();
        }
        ~_ArrayDataManager()
        { 
            _data->decrRef();
        }

        void const operator=(const _ArrayDataManager &other) 
        {
            _data->decrRef();
            if(_data->refCount() <= 0) 
            {
                delete _data;
                _data = nullptr;
            }
            
            _data = other._data;
            _data->incrRef();
        }

        int shapeSize(){
            return _data->shape.size();
        }

        int shape(int axis){
            return _data->shape.getAxisIdx(axis);
        }

        inline void _resize1DArray(int size){
            this->_data->array.resize(size);
            this->_data->shape.resize(1);
            this->_data->shape.setAxisIdx(0, size);
        }
        inline T *c_arr(){ return &_data->array[0]; }
        inline int c_arr_size() { return _data->array.size(); }
        inline T &c_arr_item(int idx) { return _data->array[idx];}
};