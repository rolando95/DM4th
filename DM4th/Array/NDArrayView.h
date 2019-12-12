#include "NDArray_impl.h"

namespace DM4th
{

    template<class T, class ... U>
    class NDArrayView
    {
        NDArray<T> _ptr;
        std::tuple<U ...> _query;

        public:

            NDArrayView(NDArray<T> &data, U... query): _ptr(data), _query(std::tuple<U...>(query ...)){}

            operator NDArray<T>();

            inline const NDArrayView<T, U ...> &operator=(NDArrayView<T, U ...> &other);
            inline const NDArrayView<T, U...> &operator=(const T &other);
            inline const NDArrayView<T, U ...> &operator=(const NDArray<T> &other);

            template<class ... V> inline const NDArrayView<T, U ...> &operator=(NDArrayView<T, V ...> &other);
            
            inline void iterateOverNDArrayView(const std::function<void(const int &, T&)> &f);

            inline int getDataSize();

        private:
            
            template<int axis>
            inline typename std::enable_if<(axis<std::tuple_size<std::tuple<U...>>::value),void>::type 
            _iterateOverNDArrayView(int &idx, const int &disp, const std::function<void(const int&, T&)> &f)
            {
                const int ldisp = this->_ptr._getAxisDisplacement(axis);
                iterateOverAxisIdxs<axis>(std::get<axis>(this->_query), [&](const int &j){
                    _iterateOverNDArrayView<axis+1>(idx, disp+ldisp*j, f);
                });          
            }

            template<int axis>
            inline typename std::enable_if<(axis==std::tuple_size<std::tuple<U...>>::value),void>::type 
            _iterateOverNDArrayView(int &idx, const int &disp, const std::function<void(const int &, T&)> &f) 
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
                for(int j=axis; j<this->_ptr.rank(); ++j)
                {
                    if(this->_ptr.shape(j)>1)
                    {
                        result._data->shape(k) = this->_ptr.shape(j);
                        ++k;
                    }
                }

                result._data->shape.resize(k);
            }

            template<int axis> inline int queryAxisSize(const int &value) const;
            template<int axis> inline int queryAxisSize(const NDArray<int> &value) const;
            template<int axis> inline int queryAxisSize(const NDArray<bool> &value) const;
            template<int axis> inline int queryAxisSize(const range<int> &value) const;
    };

template<class T, class ... U>
inline std::ostream& operator<<(std::ostream& stream, NDArrayView<T, U...> &arr)
{
    stream<<NDArray<T>(arr);
    return stream;
}

}
