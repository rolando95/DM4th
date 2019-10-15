#pragma once
#include "../_Utilities/_Constants.h"
//#include "../_Math/_Math.h"
#include "../_Utilities/_Utilities.h"
#include "../_Utilities/_c_arr_Utilities.h"
#include "../_Number/_Number.h"

#include <string>

#include <memory>
#include <atomic>
#include <sstream>

//#define BASEARRAY_STD_VECTOR

namespace DM4th
{

namespace DM4thInternal
{
#if defined BASEARRAY_STD_VECTOR
template<class T>
class _BaseArray
{
    std::vector<T> _array;
    private:

    public:
    _BaseArray(int size=0){
        this->resize(size);
    }

    inline void resize(int size);
    inline const int size() const;

    inline T &operator[](int idx);
    inline T &operator()(int idx);
    const inline T get(int idx) const;
    void set(int idx, T value);



    template<class U> bool operator==(const _BaseArray<U> &other) const;
    template<class U> inline bool operator!=(const _BaseArray<U> &other) const;

    inline void clear();

    inline void moveReferenceTo(_BaseArray<T> &other);
};
#else 

template<class T> 
class _BaseArray
{
    private:
        int _size=0;
        T *_array=nullptr;

        inline void allocArray(int size);
        inline void reallocArray(int size);
    public:
        _BaseArray(int size=0);
        ~_BaseArray() {
            this->clear();
        }
        inline void resize(int size);

        inline const int size() const;
        inline T &operator[](int idx);
        inline T &operator()(int idx);
        const inline T get(int idx) const;
        void set(int idx, T value);



        template<class U> bool operator==(const _BaseArray<U> &other) const;
        template<class U> inline bool operator!=(const _BaseArray<U> &other) const;
        
        
        template<class U> const _BaseArray<T> &operator+=(const _BaseArray<U> &other);
        template<class U> const _BaseArray<T> &operator-=(const _BaseArray<U> &other);
        template<class U> const _BaseArray<T> &operator+=(const U &other);
        template<class U> const _BaseArray<T> &operator-=(const U &other);
        template<class U> const _BaseArray<T> &operator*=(const U &other);
        template<class U> const _BaseArray<T> &operator/=(const U &other);
        template<class U> const _BaseArray<T> &operator%=(const U &other);

        inline void clear();

        inline void moveReferenceTo(_BaseArray<T> &other);
};
#endif

class _ShapeData
{
    protected:
        _BaseArray<int> _shape;
    public:
        inline _ShapeData(int size=1);
        inline ~_ShapeData();

        inline void resize(int size);
        inline const int size();

        inline void clear();
        
        inline int &operator[](int idx);
        inline int &operator()(int idx);

        inline bool operator==(const _ShapeData &other) const;
        inline bool operator!=(const _ShapeData &other) const;

        inline const int get(int idx) const;
        inline void set(int idx, int value);

        inline const int *data();
};

template<class T>
class _ArrayData
{
    private:
        std::atomic<int> _ref{0};
    public:

        _ShapeData    shape;
        _BaseArray<T> array;
        void incrRef();
        void decrRef();
        int refCount() const;
};



template<class T>
class _ArrayDataManager
{
    protected:
        _ArrayData<T> *_data = nullptr;

        void incrRef();
        void decrRef();

    public:
        
        _ArrayDataManager();
        _ArrayDataManager(const _ArrayDataManager<T> &other);
        ~_ArrayDataManager();

        _ArrayDataManager<T> const &operator=(const _ArrayDataManager<T> &other);

        int shapeSize();

        int shape(int axis);

        _ArrayData<T> const *_arrayData() const;

};

}

}