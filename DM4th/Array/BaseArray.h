#pragma once
#include "../Utils/_Constants.h"
//#include "../Math/Math.h"
#include "../Utils/Utils.h"
#include "../Utils/_c_arr_Utils.h"
#include "../Number.h"

//#define BASEARRAY_STD_VECTOR

namespace DM4th
{

namespace DM4thInternal
{

template<class T> 
class BaseArray
{
    private:
        int _size=0;
        int _top=0;
        T*  _data=nullptr;

        inline void allocArray(int size);
        inline void reallocArray(int size);
    public:
        BaseArray(int size=0);
        ~BaseArray() { this->clear(); }
        inline void resize(int size);

        inline const int size() const;
        inline T &operator[](int idx);
        inline T &operator()(int idx);
        const inline T &get(int idx) const;
        void inline set(int idx, T value);

        void operator=(const BaseArray<T> &other)
        {
            other.copyDataTo(*this);
        }

        template<class U> bool operator==(const BaseArray<U> &other) const;
        template<class U> inline bool operator!=(const BaseArray<U> &other) const;
        
        
        template<class U> const BaseArray<T> &operator+=(const BaseArray<U> &other);
        template<class U> const BaseArray<T> &operator-=(const BaseArray<U> &other);
        template<class U> const BaseArray<T> &operator+=(const U &other);
        template<class U> const BaseArray<T> &operator-=(const U &other);
        template<class U> const BaseArray<T> &operator*=(const U &other);
        template<class U> const BaseArray<T> &operator/=(const U &other);
        template<class U> const BaseArray<T> &operator%=(const U &other);
        
        inline void clear();
        inline void moveDataTo(BaseArray<T> &other);
        inline void copyDataTo(BaseArray<T> &other) const;

        inline void swap(int idx1, int idx2)
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

        void incrRef();
        void decrRef();
        int refCount() const;

        void moveDataTo(ArrayData<T> &other);
};



template<class T>
class ArrayDataManager
{
    protected:
        ArrayData<T> *_data = nullptr;

        void incrRef();
        void decrRef();
        
    public:

        ArrayDataManager();
        ArrayDataManager(const ArrayDataManager<T> &other);
        ~ArrayDataManager();

        ArrayDataManager<T> const &operator=(const ArrayDataManager<T> &other);

        int rank();

        int shape(int axis);

        ArrayData<T> const &getArrayData() const;
        int refCount() const;

        inline void moveDataTo(ArrayDataManager<T> &other);
        inline void copyDataTo(ArrayDataManager<T> &other);
        inline bool isSameRef(ArrayDataManager<T> &other);
};

}

}