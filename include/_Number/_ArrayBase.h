#include "_Assert.h"
#include "_Constants.h"
#include "_Math.h"
#include <iostream>
#include <string>

template<class T> 
class _BaseArray
{
    protected:
        int _size=0;
        T *_array=nullptr;

        inline void allocArray(int size){
            nAssert(!this->_array && size>0);
            this->_array = new T[size]();
            this->_size = size;
        }

        inline void reallocArray(int size){
            nAssert(this->_array && size>0);
            if(size!=_size){
                T *tmp = new T[size]();
                int min = _min(size, this->_size);
                for(int j=0; j<min; ++j){
                    tmp[j] = _array[j];
                }
                delete[] _array;
                _array = tmp;
                tmp = nullptr;
                _size = size;
            }
        }
        
        inline void freeArray(){
            nAssert(_array != nullptr);
            delete[] _array;
            _array = nullptr;
            _size=0;
        }

    public:
        _BaseArray(int size=0){
            if(size>0){
                allocArray(size);
            }
        }
        inline void resize(int size){
            if(this->_array==nullptr){
                this->allocArray(size);
            }else{
                this->reallocArray(size);
            }
        }

        inline int arraySize() const { return this->_size; }
        inline T &operator[](int idx){return this->_array[idx];}
        inline T &operator()(int idx){return this->_array[idx];}
};

template<class T>
class _RefArray: public _BaseArray<T>
{
    private:
        int _numRef=0;
    public:
        void incrRef(){
            ++_numRef;
            std::cout<<this<<" INCR REF: "<<_numRef<<std::endl;
        }

        void decrRef(){
            _numRef -= 1;
            std::cout<<this<<" DECR REF: "<<_numRef<<std::endl;
            if(this->_numRef <= 0){
                this->freeArray();
            }
        }

        int getNumRef() const {return this->_numRef;}
};

template<class T>
class _MultidimRefArray: public _RefArray<T>
{
    protected:
        _BaseArray<int> _shape;
    public:
        _MultidimRefArray(){ _shape.resize(1); }
        ~_MultidimRefArray(){}
        void resizeShape(int size){ _shape.resize(size); }
        const int shapeSize() { return _shape.arraySize(); }
        const int getShape(int idx) { return _shape[idx]; }
        void setShape(int idx, int value){ _shape[idx] = value; }
};

template<class T>
class _ArrayManager
{
    protected:
        _MultidimRefArray<T> *_array = nullptr;
    public:
        
        _ArrayManager(){
            _array = new _MultidimRefArray<T>();
            _array->incrRef();
        }

        ~_ArrayManager(){
            _array->decrRef();
        }

        //EDIT
        void resizeArray(int size){
            _array->resize(size);
            _array->setShape(1,size);
        }

        inline int size() const {
            return _array->arraySize();
        }

        T &operator()(int idx){
            nAssert(idx<_array->arraySize());
            return (*_array)[idx];
        }

        void const operator=(_ArrayManager &other){
            _array->decrRef();
            if(_array->getNumRef() <= 0) {
                delete _array;
                _array = nullptr;
            }
            _array = other._array;
            _array->incrRef();
        }
};