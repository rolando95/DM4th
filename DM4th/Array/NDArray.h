#pragma once

#include "BaseArray_impl.h"
#include "../Utils/Utils.h"

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

        inline NDArray();

        template<class ... U> inline NDArray(T *data, U ... args);

        NDArray(T *data, const NDArray<int> &axisArray);

        explicit NDArray(const std::string &other);

        template<class U>
        explicit operator NDArray<U>();
        
        template<class ... U>
        inline void resize(const int &axis1, U ... args);
        inline void resize(const int &axis1);
        void resize(const NDArray<int> &axisArray);

        inline void reserve(const int &size);

        inline int rank() const;
        inline int capacity() const;
        inline int size() const;

        NDArray<int> shape() const;
        inline int shape(const int &axis) const;

        template<class ... U>
        const NDArray<T> & reshape(const int &axis1, U ... args);
        const NDArray<T> & reshape(const NDArray<int> &newShape);
        
        NDArray<T> flatten();
        void sort(const bool &reverse=false, int lo=0, int hi=END);
        template<class U, class V> inline void swap(U idx1, V idx2);

        T reduce(const std::function<T(T op1, T op2)> &f);
        NDArray<T> map(const std::function<T(T item,int idx)> &f);
        NDArray<T> filter(const std::function<bool(T item,int idx)> &f);

        template<class ... U> inline T &item(const int &axis1, U ... args) const;
        inline T &item(const int &axis1) const;

        template<class AXIS, class ... U> T &item(AXIS x, U ... args) const;
        template<class AXIS> inline T &item(AXIS x) const;
        template<class AXIS> inline T &item(const NDArray<AXIS> &axisArray) const;

        NDArray<T> getCopy() const;

        template<class U>
        void push(const U &value, const int &idx=END);
        template<class U>
        void pushArray(const NDArray<U> &other, const int &idx=END);

        T pop(const int &idx=END);
        NDArray<T> popArray(const int &idx=END);

        // template<class U, enable_if_is_number(U, _number<U>)>
        // explicit operator U()
        // {
        //     return (U)this->data_item(0);
        // }

        void operator=(const T &other){ this->resize(1); this->item(0)=other; } 
        
        template<class ... U> inline T &operator()(U ... args);
        template<class ... U> const inline T &operator()(U ... args) const;
        template<class U> inline T &operator()(const NDArray<U> &axisArray);

        template<class U> inline const NDArray<T> &iAdd(const NDArray<U> &other, const DM4thParallelSettings &pSettings=DEFAULT);
        template<class U> inline const NDArray<T> &iSub(const NDArray<U> &other, const DM4thParallelSettings &pSettings=DEFAULT);
        template<class U>        const NDArray<T> &iMul(const NDArray<U> &other, const DM4thParallelSettings &pSettings=DEFAULT);

        inline const NDArray<T> &iAdd(const T &other, const DM4thParallelSettings &pSettings=DEFAULT);
        inline const NDArray<T> &iSub(const T &other, const DM4thParallelSettings &pSettings=DEFAULT);
        inline const NDArray<T> &iMul(const T &other, const DM4thParallelSettings &pSettings=DEFAULT);
        inline const NDArray<T> &iDiv(const T &other, const DM4thParallelSettings &pSettings=DEFAULT);
        inline const NDArray<T> &iMod(const T &other, const DM4thParallelSettings &pSettings=DEFAULT);

        template<class U> inline const NDArray<T> &operator+=(const NDArray<U> &other);
        template<class U> inline const NDArray<T> &operator-=(const NDArray<U> &other);
        template<class U> inline const NDArray<T> &operator*=(const NDArray<U> &other);

        template<class U> inline NDArray<T> operator+(const NDArray<U> &other) const;
        template<class U> inline NDArray<T> operator-(const NDArray<U> &other) const;
        template<class U> inline NDArray<T> operator*(const NDArray<U> &other) const;

        inline const NDArray<T> &operator+=(const T &other);
        inline const NDArray<T> &operator-=(const T &other);
        inline const NDArray<T> &operator*=(const T &other);
        inline const NDArray<T> &operator/=(const T &other);
        inline const NDArray<T> &operator%=(const T &other);


        inline const NDArray<T> operator+(const T &other) const;
        inline const NDArray<T> operator-(const T &other) const;
        inline NDArray<T> operator*(const T &other) const;
        inline NDArray<T> operator/(const T &other) const;
        inline NDArray<T> operator%(const T &other);

        // template<class U> inline bool operator==(const NDArray<U> &other);
        template<class U> inline bool isEqualTo(const NDArray<U> &other) const;

        NDArray<bool> operator==(const T &other) const;
        NDArray<bool> operator!=(const T &other) const;
        NDArray<bool> operator> (const T &other) const;
        NDArray<bool> operator<=(const T &other) const;
        NDArray<bool> operator>=(const T &other) const;
        NDArray<bool> operator< (const T &other) const;

        NDArray<bool> operator==(const NDArray<T> &other) const;
        NDArray<bool> operator!=(const NDArray<T> &other) const;
        NDArray<bool> operator> (const NDArray<T> &other) const;
        NDArray<bool> operator<=(const NDArray<T> &other) const;
        NDArray<bool> operator>=(const NDArray<T> &other) const;
        NDArray<bool> operator< (const NDArray<T> &other) const;
        template<class U=T> inline typename std::enable_if<std::is_same<U,bool>::value, NDArray<bool>>::type operator&&(const NDArray<bool> &other) const;
        template<class U=T> inline typename std::enable_if<std::is_same<U,bool>::value, NDArray<bool>>::type operator||(const NDArray<bool> &other) const;
        template<class U=T> inline typename std::enable_if<std::is_same<U,bool>::value, NDArray<bool>>::type operator!() const;

        bool any(const T &value) const ;
        bool all(const T &value) const ;
        template<class U=T> inline typename std::enable_if<std::is_same<U,bool>::value,  bool>::type any() const { return this->any(true); }
        template<class U=T> inline typename std::enable_if<std::is_same<U,bool>::value,  bool>::type all() const { return this->all(true); }

        std::ostream& ostream(std::ostream& stream, const int &ident=2, const bool &quotes=false) const;
        std::istream& istream(std::istream& stream);

        void loadFile(const std::string &path);
        void saveFile(const std::string &path);

        inline void _resize1DArray(const int &size);
        inline T *data();
        inline const T *data() const;
        inline T *data_copy();
        inline const int data_size() const;
        inline T &data_item(const int &idx);
        inline const T &data_item(const int &idx) const;
        
        NDArray<int> _getAxisDisplacement() const;
        inline int _getAxisDisplacement(const int &axis) const;

        iterator begin(){ return iterator(*this); }
        iterator end(){ return iterator(*this, this->data_size()); }
        iterator_const begin() const{ return iterator_const(*this); }
        iterator_const end() const{ return iterator_const(*this, this->data_size()); }

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
            const T operator*() const { return this->_data.data_item(this->_ptr); }
        };


        class SubArray
        {
            NDArray<T> _ptr;
            NDArray<T*> _subArray;

        public:
            template<class ... U>
            inline SubArray(const NDArray<T> &data, U ... args);
            
            inline operator NDArray<T>() const;
            inline const SubArray &operator=(const SubArray &other);
            inline const SubArray &operator=(const T &other);
            inline const SubArray &operator=(const NDArray<T> &other);

            template<class ... U> NDArray<T>::SubArray operator()(U ... args);
            template<class U> NDArray<T>::SubArray operator[](const U &idx);

        private:
            template<class U, class ... V>
            void setRef(const NDArray<U> &first, V... args);

            template<class U, class ... V>
            void setShapeRef(const int &axis, NDArray<int> &shape, const NDArray<U> &first, V ... args);

            void setShapeRef(const int &axis, NDArray<int> &shape);

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

        
        template<class ... U>
        class SubArr
        {
            NDArray<T> _ptr;
            std::tuple<U ...> _query;
            public:

                SubArr(NDArray<T> &data, U... query): _ptr(data), _query(std::tuple<U...>(query ...)){}

                operator NDArray<T>() const
                {
                    NDArray<T> result;
                    
                    const int size = getStrideAxis<0>();
                    result.resize(size*queryAxisSize(std::get<0>(this->_query)));

                    int idx = 0;
                    setItems<0>(idx, 0, result);
                    if(result.data_size()>1) setShape<0>(result,0);
                    return result;
                }

                template<int axis>
                inline typename std::enable_if<(axis<std::tuple_size<std::tuple<U...>>::value),void>::type 
                setItems(int &idx, const int &disp, NDArray<T> &result) const
                {
                    const int ldisp = this->_ptr._getAxisDisplacement(axis);
                    iterateOverItems(std::get<axis>(this->_query), [&](const int &j){
                        setItems<axis+1>(idx, disp+ldisp*j, result);
                    });          
                }

                template<int axis>
                inline typename std::enable_if<(axis==std::tuple_size<std::tuple<U...>>::value),void>::type 
                setItems(int &idx, const int &disp, NDArray<T> &result) const
                {
                    const int size = this->_ptr._getAxisDisplacement(axis);
                    for(int j=0; j<size; ++j)
                    {
                        result.data_item(idx++) = this->_ptr.data_item(disp+j);
                    }
                    
                }

                void iterateOverItems(const int &iter, const std::function<void(int)> &f) const {f(iter);}
                void iterateOverItems(const NDArray<int> &iter, const std::function<void(int)> &f) const { for(int j=0; j<iter.data_size(); ++j) f(iter.data_item(j)); }
                void iterateOverItems(const NDArray<bool> &iter, const std::function<void(int)> &f) const { for(int j=0; j<iter.data_size(); ++j) if(iter.data_item(j)) f(j); }
                void iterateOverItems(const range<int> &iter, const std::function<void(int)> &f) const {for(int j=iter.beginValue(); j<iter.endValue(); j+=iter.stepValue()) f(j);
                }

                template<int axis>
                inline typename std::enable_if<(axis<std::tuple_size<std::tuple<U...>>::value-1),int>::type 
                getStrideAxis() const
                {
                    const int size = this->queryAxisSize(std::get<axis+1>(this->_query)); 
                    return size * this->getStrideAxis<axis+1>();
                }

                template<int axis>
                inline typename std::enable_if<(axis==std::tuple_size<std::tuple<U...>>::value-1),int>::type 
                getStrideAxis() const
                {
                    return this->_ptr._getAxisDisplacement(axis); 
                }

                template<int axis>
                inline typename std::enable_if<(axis<std::tuple_size<std::tuple<U...>>::value),void>::type 
                setShape(NDArray<T> &result, const int &rank) const
                {
                    const int size = queryAxisSize(std::get<axis>(this->_query));
                    if(size>1)
                    {
                        setShape<axis+1>(result, rank+1);
                        result._data->shape(rank) = size;
                    }else{
                        setShape<axis+1>(result, rank);
                    }

                }

                template<int axis>
                inline typename std::enable_if<(axis==std::tuple_size<std::tuple<U...>>::value),void>::type 
                setShape(NDArray<T> &result, const int &rank) const
                {
                    result._data->shape.resize(rank+this->_ptr.rank()-axis);

                    int k=rank;
                    for(int j=axis; j<this->_ptr.rank(); ++j, ++k)
                    {
                        result._data->shape(k) = this->_ptr.shape(j);
                    }
                }

                inline int queryAxisSize(const int &value) const;
                inline int queryAxisSize(const NDArray<int> &value) const;
                inline int queryAxisSize(const NDArray<bool> &value) const;
                inline int queryAxisSize(const range<int> &value) const;
            private:


        };

        template<class ... U>
        SubArr<U...> query(U ... args)
        {
            return SubArr<U ...>(*this, args...);
        }

        friend std::ostream& operator<<(std::ostream& stream, const NDArray<T>::SubArray &arr){
            stream<<NDArray<T>(arr);
            return stream;
        }
    private:
        int _partition(const bool &reverse, const int lo, const int hi);

        void _resize(const int &axis, int oldDispCount, int newDispCount,
            // NDArray<int> &oldDisp,  NDArray<int> &newDisp,
            NDArray<int> &oldShape,  NDArray<int> &newShape,
            const DM4thInternal::BaseArray<T> &oldArray);

        template<class ... U>
        void _reshape(const int &axis, int first, U ... args);
        void _reshape(const int &axis, int last);

        template<class AXIS, class ... U>
        inline int _item(const int &axis, int pos, AXIS idx, U ... args) const;
        template<class AXIS> inline int _item(const int &axis, int pos, AXIS idx) const;

        template<class ... U>
        inline int _item(const int &axis, int pos, const int &idx, U ... args) const;
        inline int _item(const int &axis, int pos, const int &idx) const;

        DM4thInternal::BaseArray<T> _allocZeros(const NDArray<int> &axisArray);
        
        template<class ... U>
        DM4thInternal::BaseArray<T> _allocZeros(const int &axis1, U ... args);

        void _ostream(std::ostream& stream, int shapeIdx, int& c_idx, int ident, bool quotes) const;
        void _istream(std::istream& stream, std::queue<T> &values, int shapeIdx, int& c_size, bool &shapeAllocated);
};

template<class T>
inline std::ostream& operator<<(std::ostream& stream, const NDArray<T> &arr);
template<class T>
inline std::istream& operator>>(std::istream& stream, NDArray<T> &arr);

}