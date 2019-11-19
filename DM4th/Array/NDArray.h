#pragma once

#include "BaseArray_impl.h"
#include "../Utilities/Utilities.h"

namespace DM4th
{

template<class T> class range;

template<typename T>
class NDArray: public DM4thInternal::ArrayDataManager<T>
{
    public:
        class iterator;
        class iterator_const;
        class SubArray;

        NDArray();
        template<class ... U> NDArray(T *data, U ... args);
        NDArray(T *data, const NDArray<int> &axisArray);
        //NDArray(const typename NDArray<T>::SubArray &other) { *this = NDArray(other); }
        explicit NDArray(const std::string &other);
        //explicit NDArray(const char *other) { *this = std::string(other); }
        template<class U>
        explicit operator NDArray<U>();
        
        template<class ... U>
        inline void resize(int axis1, U ... args);
        inline void resize(int axis1);

        void resize(const NDArray<int> &axisArray);

        inline int shapeSize() const;

        int size() const;

        NDArray<int> shape() const;
        inline int shape(int axis) const;

        template<class ... U>
        const NDArray<T> & reshape(int axis1, U ... args);
        const NDArray<T> & reshape(NDArray<int> newShape);
        
        NDArray<T> flatten();
        void sort(bool reverse=false, int lo=0, int hi=END);
        template<class U, class V> inline void swap(U idx1, V idx2);

        template<class AXIS, class ... U> T &item(AXIS x, U ... args) const;
        template<class AXIS> T &item(AXIS x) const;
        template<class AXIS> T &item(const NDArray<AXIS> &axisArray);

        NDArray<T> getCopy() const;

        template<class U>
        void push(const U &value, const int idx=END);
        template<class U>
        void pushArray(const NDArray<U> &other, const int idx=END);

        T pop(const int idx=END);
        NDArray<T> popArray(const int idx=END);

        // template<class U, enable_if_is_number(U, _number<U>)>
        // explicit operator U()
        // {
        //     return (U)this->data_item(0);
        // }

        void operator=(const T &other){ this->resize(1); this->item(0)=other; } 
        
        template<class ... U> inline T &operator()(U ... args);
        template<class ... U> const inline T &operator()(U ... args) const;
        template<class U> inline T &operator()(NDArray<U> axisArray);

        // template<class U> NDArray<T>::SubArray operator[](NDArray<U> idx);
        // NDArray<T>::SubArray operator[](number idx);
        
        template<class U> inline const NDArray<T> operator+=(const NDArray<U> &other);
        template<class U> inline NDArray<T> operator+(const NDArray<U> &other) const;
        inline const NDArray<T>  operator+=(const T &other);
        inline const NDArray<T> operator+(const T &other) const;

        template<class U> inline const NDArray<T> operator-=(const NDArray<U> &other);
        template<class U> inline NDArray<T> operator-(const NDArray<U> &other) const;
        inline const NDArray<T>  operator-=(const T &other);
        inline const NDArray<T> operator-(const T &other) const;

        template<class U> const NDArray<T> operator*=(const NDArray<U> &other);
        template<class U> inline NDArray<T> operator*(const NDArray<U> &other) const;
        inline const NDArray<T>  operator*=(const T &other);
        inline NDArray<T> operator*(const T &other) const;

        inline const NDArray<T> operator/=(const T &other);
        inline NDArray<T> operator/(const T &other) const;

        inline const NDArray<T> operator%=(const T &other);
        inline NDArray<T> operator%(const T &other);

        // template<class U> inline bool operator==(const NDArray<U> &other);
        template<class U> inline bool isEqualTo(const NDArray<U> &other) const;

        NDArray<bool> operator==(T other) const;
        NDArray<bool> operator!=(T other) const;
        NDArray<bool> operator> (T other) const;
        NDArray<bool> operator<=(T other) const;
        NDArray<bool> operator>=(T other) const;
        NDArray<bool> operator< (T other) const;

        NDArray<bool> operator==(const NDArray<T> &other) const;
        NDArray<bool> operator!=(const NDArray<T> &other) const;
        NDArray<bool> operator> (const NDArray<T> &other) const;
        NDArray<bool> operator<=(const NDArray<T> &other) const;
        NDArray<bool> operator>=(const NDArray<T> &other) const;
        NDArray<bool> operator< (const NDArray<T> &other) const;
        template<class U=T> inline typename std::enable_if<std::is_same<U,bool>::value, NDArray<bool>>::type operator&&(const NDArray<bool> &other) const;
        template<class U=T> inline typename std::enable_if<std::is_same<U,bool>::value, NDArray<bool>>::type operator||(const NDArray<bool> &other) const;
        template<class U=T> inline typename std::enable_if<std::is_same<U,bool>::value, NDArray<bool>>::type operator!() const;

        bool any(T value);
        bool all(T value);
        template<class U=T> inline typename std::enable_if<std::is_same<U,bool>::value,  bool>::type any() { return this->any(true); }
        template<class U=T> inline typename std::enable_if<std::is_same<U,bool>::value,  bool>::type all() { return this->all(true); }

        std::ostream& ostream(std::ostream& stream, int ident=2, bool quotes=false) const;
        std::istream& istream(std::istream& stream);

        void loadFile(std::string path);
        void saveFile(std::string path);

        inline void _resize1DArray(int size);
        inline T *data();
        inline const T *data() const;
        inline T *data_copy();
        inline const int data_size() const;
        inline T &data_item(int idx);
        inline const T data_item(int idx) const;
        
        NDArray<int> _getAxisDisplacement() const;
        int _getAxisDisplacement(int axis) const;

        iterator begin(){ return iterator(*this); }
        iterator end(){ return iterator(*this, this->data_size()); }
        iterator_const begin() const{ return iterator(*this); }
        iterator_const end() const{ return iterator(*this, this->data_size()); }

        class iterator
        {
        private:
            NDArray<T> _data;
            int _ptr;
        public:
            iterator(NDArray<T> &data, int idx=0) : _data(data), _ptr(idx) {};
            bool operator==(iterator other){ return (this->_ptr == other._ptr); }
            bool operator!=(iterator other){ return !(*this==other); }
            const T &operator=(const T value){ return this->_data.data_item(this->_ptr) = value; }
            iterator &operator++(){ ++this->_ptr; return *this; }
            iterator operator++(int){ iterator result(this->_data, this->_ptr); ++this->_ptr; return result; }
            T &operator*(){ return this->_data.data_item(this->_ptr); }
        };

        class iterator_const
        {
        private:
            const NDArray<T> _data;
            int _ptr;
        public:
            iterator_const(const NDArray<T> &data, int idx=0) : _data(data), _ptr(idx) {};
            bool operator==(iterator_const other) const { return (this->_ptr == other._ptr); }
            bool operator!=(iterator_const other) const { return !(*this==other); }
            const T &operator=(const T value) const { return this->_data.data_item(this->_ptr) = value; }
            iterator_const &operator++(){ ++this->_ptr; return *this; }
            iterator_const operator++(int){ iterator_const result(this->_data, this->_ptr); ++this->_ptr; return result; }
            const T &operator*()  { return this->_data.data_item(this->_ptr); }
        };


        class SubArray
        {
            NDArray<T> _ptr;
            NDArray<T*> _subArray;

        public:
            template<class ... U>
            SubArray(NDArray<T> &data, U ... args);
            
            operator NDArray<T>() const;
            const SubArray &operator=(const SubArray &other);
            const SubArray &operator=(const T &other);
            const SubArray &operator=(const NDArray<T> &other);

            template<class ... U> NDArray<T>::SubArray operator()(U ... args);
            template<class U> NDArray<T>::SubArray operator[](U idx);

        private:
            template<class U, class ... V>
            void setRef(NDArray<U> first, V... args);

            template<class U, class ... V>
            void setShapeRef(int axis, NDArray<int> &shape, NDArray<U> first, V ... args);

            void setShapeRef(int axis, NDArray<int> &shape);

            template<class U, class ... V>
            void slider(                
                int axis,
                int oldDispCount, int newDispCount,
                NDArray<int> oldDisp, NDArray<int> newDisp, NDArray<U> first, V ... args
            );
            void slider(                
                int axis,
                int oldDispCount, int newDispCount,
                NDArray<int> oldDisp, NDArray<int> newDisp
            );

            void _1DSlider(int oldDisp, int newDisp);

            template<class U>
            NDArray<int> castToNDArray(NDArray<U> value){ return NDArray<int>(value); }

            template<class U>
            NDArray<int> castToNDArray(range<U> value){ return NDArray<int>(value); }

            NDArray<int> castToNDArray(number value)
            { 
                NDArray<int> result;
                result.resize(1);
                result(0) = (int)value;
                return result; 
            }
        };

        template<class ...U>
        SubArray subArr(U ... args)
        {
            SubArray result(*this, args ...);
            return result;
        }

        template<class ...U>
        SubArray subArray(U ... args)
        {
            SubArray result(*this, args ...);
            return result;
        }

        friend std::ostream& operator<<(std::ostream& stream, const NDArray<T>::SubArray &arr){
            stream<<NDArray<T>(arr);
            return stream;
        }
    private:
        int _partition(bool reverse, const int lo, const int hi);

        void _resize(int axis, int oldDispCount, int newDispCount,
            NDArray<int> &oldDisp,  NDArray<int> &newDisp,
            NDArray<int> &oldShape,  NDArray<int> &newShape,
            const DM4thInternal::BaseArray<T> &oldArray);

        template<class ... U>
        void _reshape(int axis, int first, U ... args);
        void _reshape(int axis, int last);

        template<class ... U>
        int _item(int axis, int pos, int idx, U ... args) const;
        int _item(int axis, int pos, int idx) const;

        DM4thInternal::BaseArray<T> _allocZeros(const NDArray<int> &axisArray);

        void _ostream(std::ostream& stream, int shapeIdx, int& c_idx, int ident, bool quotes) const;
        void _istream(std::istream& stream, std::queue<T> &values, int shapeIdx, int& c_size, bool &shapeAllocated);
};

template<class T>
inline std::ostream& operator<<(std::ostream& stream, const NDArray<T> &arr);
template<class T>
inline std::istream& operator>>(std::istream& stream, NDArray<T> &arr);

}