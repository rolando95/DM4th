#pragma once

#include "../Utils/Utils.h"
#include "../Number.h"

//#define BASEARRAY_STD_VECTOR

namespace DM4th
{

namespace Internal
{

using namespace DM4thUtils;

template<class T> 
class BaseArray
{
    private:
        int _size=0;
        int _capacity=0;
        T*  _data=nullptr;

        inline void allocArray(const int &size);
        inline void reallocArray(const int &size);
    public:
        inline BaseArray(const int &size=0);
        inline ~BaseArray();

        inline void _allocEmpty(const int &size);

        inline void resize(const int &size);
        inline void reserve(const int &size);

        inline const int size() const;
        inline const int capacity() const;

        inline T &operator[](const int &idx);
        inline T &operator()(const int &idx);
        inline const T &operator()(const int &idx) const ;
        inline T &item(const int &idx);
        inline const T &item(const int &idx) const;
        const inline T &get(const int &idx) const;
        void inline set(const int &idx, const T &value);

        void operator=(const BaseArray<T> &other)
        {
            other.copyDataTo(*this);
        }

        template<class U> bool operator==(const BaseArray<U> &other) const;
        template<class U> inline bool operator!=(const BaseArray<U> &other) const;
        
        inline const BaseArray<T> &iAdd(const BaseArray<T> &other, const DM4thParallelSettings &pSettings);
        inline const BaseArray<T> &iSub(const BaseArray<T> &other, const DM4thParallelSettings &pSettings);
        template<class U> inline const BaseArray<T> &iAdd(U other, const DM4thParallelSettings &pSettings);
        template<class U> inline const BaseArray<T> &iSub(U other, const DM4thParallelSettings &pSettings);
        template<class U> inline const BaseArray<T> &iMul(U other, const DM4thParallelSettings &pSettings);
        template<class U> inline const BaseArray<T> &iDiv(U other, const DM4thParallelSettings &pSettings);
        template<class U> inline const BaseArray<T> &iMod(U other, const DM4thParallelSettings &pSettings);
        
        template<class U> inline const BaseArray<T> &operator+=(const BaseArray<U> &other);
        template<class U> inline const BaseArray<T> &operator-=(const BaseArray<U> &other);
        template<class U> inline const BaseArray<T> &operator+=(const U &other);
        template<class U> inline const BaseArray<T> &operator-=(const U &other);
        template<class U> inline const BaseArray<T> &operator*=(const U &other);
        template<class U> inline const BaseArray<T> &operator/=(const U &other);
        template<class U> inline const BaseArray<T> &operator%=(const U &other);
        
        inline void clear();

        inline void moveDataTo(BaseArray<T> &other);
        inline void copyDataTo(BaseArray<T> &other) const;
        inline void copyNItemsTo(BaseArray<T> &other, const int &thisFrom, const int &otherFrom, const int &count) const;

        inline void push(const T &value, const int &idx);
        inline T pop(const int &idx);

        inline void swap(const int &idx1,const int &idx2)
        {
            T tmp = this->get(idx1);
            this->set(idx1, this->get(idx2));
            this->set(idx2, tmp);
        }

        inline T* data() { return this->_data; }
        inline const T* data() const { return this->_data; }
};

template<class T>
inline std::ostream& operator<<(std::ostream& stream, const BaseArray<T> &arr);

class ShapeData : public BaseArray<int>
{
    public:
        inline ShapeData(int size=1){ this->resize(size); }
};

template<class T>
class ArrayData
{
    private:
        int _ref = 0;
    public:

        ShapeData    shape;
        BaseArray<T> array;

        inline void incrRef();
        inline void decrRef();
        inline int refCount() const;

        inline void moveDataTo(ArrayData<T> &other);
};



template<class T>
class ArrayDataManager
{
    protected:
        ArrayData<T> *_data = nullptr;

        void incrRef();
        void decrRef();
        
    public:

        inline ArrayDataManager();
        inline ArrayDataManager(const ArrayDataManager<T> &other);
        inline ~ArrayDataManager();

        inline ArrayDataManager<T> const &operator=(const ArrayDataManager<T> &other);

        inline int rank();

        inline int shape(const int &axis);

        inline ArrayData<T> const &getArrayData() const;
        int refCount() const;

        inline void moveDataTo(ArrayDataManager<T> &other);
        inline void copyDataTo(ArrayDataManager<T> &other);
        inline bool isSameRef(ArrayDataManager<T> &other);
};

}

}