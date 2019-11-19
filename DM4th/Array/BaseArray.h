#pragma once
#include "../Utilities/_Constants.h"
//#include "../Math/Math.h"
#include "../Utilities/Utilities.h"
#include "../Utilities/_c_arr_Utilities.h"
#include "../Number.h"

//#define BASEARRAY_STD_VECTOR

namespace DM4th
{

namespace DM4thInternal
{
#if defined BASEARRAY_STD_VECTOR
template<class T>
class BaseArray
{
    std::vector<T> Array;
    private:

    public:
    BaseArray(int size=0){
        this->resize(size);
    }

    inline void resize(int size);
    inline const int size() const;

    inline T &operator[](int idx);
    inline T &operator()(int idx);
    const inline T get(int idx) const;
    void inline set(int idx, T value);



    template<class U> bool operator==(const BaseArray<U> &other) const;
    template<class U> inline bool operator!=(const BaseArray<U> &other) const;

    inline void clear();

    inline void moveReferenceTo(BaseArray<T> &other);
};
#else 

template<class T> 
class BaseArray
{
    private:
        int _size=0;
        int _top=0; // Real size of array
        T *Array=nullptr;

        inline void allocArray(int size);
        inline void reallocArray(int size);
    public:
        BaseArray(int size=0);
        ~BaseArray() {
            this->clear();
        }
        inline void resize(int size);

        inline const int size() const;
        inline T &operator[](int idx);
        inline T &operator()(int idx);
        const inline T get(int idx) const;
        void inline set(int idx, T value);

        void operator=(const BaseArray<T> &other)
        {
            other.copyReferenceTo(*this);
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
        inline void moveReferenceTo(BaseArray<T> &other);
        inline void copyReferenceTo(BaseArray<T> &other) const;

        inline void swap(int idx1, int idx2)
        {
            T tmp = this->get(idx1);
            this->set(idx1, this->get(idx2));
            this->set(idx2, tmp);
        }

        void log() const
        {
            std::cout<<"[";
            for(int j=0; j<this->size();++j)
            {
                if(j!=0) std::cout<<", ";
                std::cout<<this->get(j);
            }
            std::cout<<"]\n";
        }
};
#endif

class ShapeData
{
    protected:
        BaseArray<int> _shape;
    public:
        inline ShapeData(int size=1);
        inline ~ShapeData();

        inline void resize(int size);
        inline const int size();

        inline void clear();
        
        inline int &operator[](int idx);
        inline int &operator()(int idx);

        inline bool operator==(const ShapeData &other) const;
        inline bool operator!=(const ShapeData &other) const;

        inline const int get(int idx) const;
        inline void set(int idx, int value);

        inline const int *data();

        inline void moveReferenceTo(ShapeData &other) { this->_shape.moveReferenceTo(other._shape); }
};

template<class T>
class ArrayData
{
    private:
        std::atomic<int> _ref{0};
    public:

        ShapeData    shape;
        BaseArray<T> array;

        void incrRef();
        void decrRef();
        int refCount() const;

        void moveReferenceTo(ArrayData<T> &other);
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

        int shapeSize();

        int shape(int axis);

        ArrayData<T> const &getArrayData() const;
        int refCount() const;

        inline void _moveDataRefTo(ArrayDataManager<T> &other);
        inline bool isSameRef(ArrayDataManager<T> &other);
};

}

}