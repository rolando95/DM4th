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
        
        inline void freeArray()
        {
            assert(_array != nullptr);
            delete[] _array;
            _array = nullptr;
            _size=0;
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

        inline int size() const { return this->_size; }
        inline T &operator[](int idx){ return this->_array[idx]; }
        inline T &operator()(int idx){ return this->_array[idx]; }

        
};

template<class T>
class _RefArray: public _BaseArray<T>
{
    private:
        volatile int _ref=0;
    public:
        void incrRef()
        {
            ++_ref;
            std::cout<<this<<" INCR REF: "<<_ref<<std::endl;
        }

        void decrRef()
        {
            _ref -= 1;
            std::cout<<this<<" DECR REF: "<<_ref<<std::endl;
            if(this->_ref <= 0 && this->_array!=nullptr){ this->freeArray(); }
        }

        int refCount() const { return this->_ref; }

        inline T *c_arr(){ return this->_array; }
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
};

template<class T>
struct _ArrayData
{
    _ShapeData shape;
    _RefArray<T> array;
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
        void _resize(int axis, int count, int idx, U ...args){
            count *= idx;
            _resize(axis+1, count, args ...);
            this->_data->shape.setAxisIdx(axis, idx);
        }

        void _resize(int axis, int count, int idx){
            count*=idx;
            this->_data->array.resize(count);
            this->_data->shape.resize(axis+1);
            this->_data->shape.setAxisIdx(axis, idx);
        }

    public:
        
        _ArrayDataManager()
        {
            _data = new _ArrayData<T>();
            _data->array.incrRef();
        }
        ~_ArrayDataManager()
        { 
            _data->array.decrRef();
        }

        void const operator=(const _ArrayDataManager &other) 
        {
            _data->array.decrRef();
            if(_data->array.refCount() <= 0) 
            {
                delete _data;
                _data = nullptr;
            }
            
            _data = other._data;
            _data->array.incrRef();
        }

        inline void _resize1DArray(int size){ _resize(0,1,size); }
        inline T *c_arr(){ return _data->array.c_arr(); }
};