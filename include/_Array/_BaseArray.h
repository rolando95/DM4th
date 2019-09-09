#pragma once

#include "../_Utilities/_Constants.h"
#include "../_Utilities/_Math.h"
#include "../_Utilities/_Utilities.h"
#include "../_Utilities/_c_arr_Utilities.h"

#include <iostream>
#include <string>
#include <cassert>
#include <memory>
#include <atomic>

template<class T> 
class _BaseArray
{
    protected:
        int _size=0;
        T *_array=nullptr;

        inline void allocArray(int size);
        inline void reallocArray(int size);

    public:
        _BaseArray(int size=0);

        inline void resize(int size);

        inline T* _allocAndReturnOldArray(int size);

        inline const int size() const;
        inline T &operator[](int idx);
        inline T &operator()(int idx);
        const inline T get(int idx) const;
        void set(int idx, T value);

        bool isFree();

        template<class U> bool operator==(const _BaseArray<U> &other) const;
        template<class U> inline bool operator!=(const _BaseArray<U> &other) const;

        inline void freeArray();
};


class _ShapeData
{
    protected:
        _BaseArray<int> _shape;
    public:
        inline _ShapeData(int size=1);
        inline ~_ShapeData();

        inline void resize(int size);
        inline const int size();

        inline void freeArray();
        
        inline int &operator[](int idx);
        inline int &operator()(int idx);

        inline bool operator==(const _ShapeData &other) const;
        inline bool operator!=(const _ShapeData &other) const;

        inline const int get(int idx) const;
        inline void set(int idx, int value);

        inline const int *c_arr();
};

template<class T>
class _ArrayData
{
    private:
        std::atomic<int> _ref{0};
    public:

        _ShapeData shape;
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