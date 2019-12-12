#pragma once

#include "BaseArray_impl.h"
#include "../Utils/Utils.h"

namespace DM4th
{

template<class T> class range;
template<class T, class ...U> class SubArray;

template<typename T>
class NDArray: public DM4thInternal::ArrayDataManager<T>
{
    public:
        class iterator;
        class iterator_const;
        //class SubArray;

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
    
        template<class ... U>
        class SubArray
        {
            NDArray<T> _ptr;
            std::tuple<U ...> _query;
            public:

                SubArray(NDArray<T> &data, U... query): _ptr(data), _query(std::tuple<U...>(query ...)){}

                operator NDArray<T>()
                {
                    NDArray<T> result;
                    result.resize(getDataSize());
                    
                    iterateOverSubArray([&](const int &j, T& item){
                        result.data_item(j) = item;
                    });

                    if(result.data_size()>1) setShape<0>(result,0);
                    return result;
                }

                template<class ... V>
                inline const NDArray<T>::SubArray<U...> &operator=(NDArray<T>::SubArray<V ...> &other)
                {
                    NDArray<T> tmp = NDArray<T>(other);

                    if(tmp.data_size()>=this->getDataSize())
                    {
                        iterateOverSubArray([&](const int &j, T& item){
                            item = tmp.data_item(j);
                        });
                    }else{
                        iterateOverSubArray([&](const int &j, T& item){
                            item = tmp.data_item(j%tmp.data_size());
                        });
                    }


                    return *this;
                }

                inline const NDArray<T>::SubArray<U...> &operator=(const T &other)
                {
                    iterateOverSubArray([&](const int &j, T& item){
                        item = other;
                    });

                    return *this;                   
                } 

                inline const NDArray<T>::SubArray<U...> &operator=(const NDArray<T> &other)
                {
                    if(other.data_size()>=this->getDataSize())
                    {
                        iterateOverSubArray([&](const int &j, T& item){
                            item = other.data_item(j);
                        });
                    }else{
                        iterateOverSubArray([&](const int &j, T& item){
                            item = other.data_item(j%other.data_size());
                        });
                    }


                    return *this;                   
                } 
                ///////////////////////////////////////////

                inline int getDataSize()
                {
                    const int size = getStrideAxis<0>();
                    return size*queryAxisSize<0>(std::get<0>(this->_query));
                }

                inline void iterateOverSubArray(const std::function<void(const int &, T&)> &f)
                {
                    int idx = 0;
                    _iterateOverSubArray<0>(idx, 0, f);
                }

                private:

                template<int axis>
                inline typename std::enable_if<(axis<std::tuple_size<std::tuple<U...>>::value),void>::type 
                _iterateOverSubArray(int &idx, const int &disp, const std::function<void(const int&, T&)> &f)
                {
                    const int ldisp = this->_ptr._getAxisDisplacement(axis);
                    iterateOverAxisIdxs<axis>(std::get<axis>(this->_query), [&](const int &j){
                        _iterateOverSubArray<axis+1>(idx, disp+ldisp*j, f);
                    });          
                }

                template<int axis>
                inline typename std::enable_if<(axis==std::tuple_size<std::tuple<U...>>::value),void>::type 
                _iterateOverSubArray(int &idx, const int &disp, const std::function<void(const int &, T&)> &f) 
                {
                    const int size = this->_ptr._getAxisDisplacement(axis-1);
                    for(int j=0; j<size; ++j)
                    {
                        f(idx, this->_ptr.data_item(disp+j));
                        ++idx;
                        //result.data_item(idx++) = this->_ptr.data_item(disp+j);
                    }
                    
                }

                template<int axis>
                inline void iterateOverAxisIdxs(const int &iter, const std::function<void(int)> &f) const {f(iter);}
                template<int axis>
                inline void iterateOverAxisIdxs(const NDArray<int> &iter, const std::function<void(int)> &f) const { for(int j=0; j<iter.data_size(); ++j) f(iter.data_item(j)); }
                template<int axis>
                inline void iterateOverAxisIdxs(const NDArray<bool> &iter, const std::function<void(int)> &f) const { for(int j=0; j<iter.data_size(); ++j) if(iter.data_item(j)) f(j); }
                template<int axis>
                inline void iterateOverAxisIdxs(const range<int> &iter, const std::function<void(int)> &f) const {for(int j=iter.beginValue(); j<iter.endValue(); j+=iter.stepValue()) f(j);
                }

                template<int axis>
                inline typename std::enable_if<(axis<std::tuple_size<std::tuple<U...>>::value-1),int>::type 
                getStrideAxis() const
                {
                    const int size = this->queryAxisSize<axis+1>(std::get<axis+1>(this->_query)); 
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
                    const int size = queryAxisSize<axis>(std::get<axis>(this->_query));
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

                template<int axis> inline int queryAxisSize(const int &value) const;
                template<int axis> inline int queryAxisSize(const NDArray<int> &value) const;
                template<int axis> inline int queryAxisSize(const NDArray<bool> &value) const;
                template<int axis> inline int queryAxisSize(const range<int> &value) const;
        };

        template<class V, class ... U>
        SubArray<V, U...> subArr(const V &first, U ... args)
        {
            return SubArray<V, U ...>(*this, first, args...);
        }

        SubArray<range<int>> subArr()
        {
            return SubArray<range<int>>(*this, range<int>(0,this->size()));
        }

        template<class V, class ... U>
        SubArray<V, U...> subArray(const V &first, U ... args)
        {
            return SubArray<V, U ...>(*this, first, args...);
        }

        SubArray<range<int>> subArray()
        {
            return SubArray<range<int>>(*this, range<int>(0,this->size()));
        }

        template<class ...U>
        friend std::ostream& operator<<(std::ostream& stream, const NDArray<T>::SubArray<U...> &arr){
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