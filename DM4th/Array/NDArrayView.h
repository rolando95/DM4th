#include "NDArray_impl.h"

namespace DM4th
{

template <class T, class... U>
class NDArrayView
{
    NDArray<T> _ptr;
    std::tuple<U...> _view;

public:
    NDArrayView(NDArray<T> &data, U... view) : _ptr(data), _view(std::tuple<U...>(view...)) {}

    operator NDArray<T>() const;

    inline const NDArrayView<T, U...> &operator=(NDArrayView<T, U...> &other);

    template<class V>
    inline typename std::enable_if< std::is_convertible<V,T>::value, const NDArrayView<T, U...>>::type 
    &operator=(const V &other);

    inline const NDArrayView<T, U...> &operator=(const NDArray<T> &other);

    template <class... V>
    inline const NDArrayView<T, U...> &operator=(NDArrayView<T, V...> &other);

    inline void iterateOverNDArrayView(const std::function<void(const int &, T &)> &f);
    inline void iterateOverNDArrayView(const std::function<void(const int &, const T &)> &f) const;

    inline int getDataSize() const ;

private:
    template <int axis>
    inline typename std::enable_if<(axis < std::tuple_size<std::tuple<U...>>::value), void>::type
    _iterateOverNDArrayView(int &idx, const int &disp, const std::function<void(const int &, T &)> &f)
    {
        const int ldisp = this->_ptr._getAxisDisplacement(axis);
        iterateOverAxisIdxs<axis>(std::get<axis>(this->_view), [&](const int &j) {
            _iterateOverNDArrayView<axis + 1>(idx, disp + ldisp * j, f);
        });
    }

    template <int axis>
    inline typename std::enable_if<(axis == std::tuple_size<std::tuple<U...>>::value), void>::type
    _iterateOverNDArrayView(int &idx, const int &disp, const std::function<void(const int &, T &)> &f)
    {
        const int size = this->_ptr._getAxisDisplacement(axis - 1);
        for (int j = 0; j < size; ++j)
        {
            f(idx, this->_ptr.data_item(disp + j));
            ++idx;
        }
    }

    template <int axis>
    inline typename std::enable_if<(axis < std::tuple_size<std::tuple<U...>>::value), void>::type
    _iterateOverNDArrayView(int &idx, const int &disp, const std::function<void(const int &, const T &)> &f) const 
    {
        const int ldisp = this->_ptr._getAxisDisplacement(axis);
        iterateOverAxisIdxs<axis>(std::get<axis>(this->_view), [&](const int &j) {
            _iterateOverNDArrayView<axis + 1>(idx, disp + ldisp * j, f);
        });
    }

    template <int axis>
    inline typename std::enable_if<(axis == std::tuple_size<std::tuple<U...>>::value), void>::type
    _iterateOverNDArrayView(int &idx, const int &disp, const std::function<void(const int &, const T &)> &f) const
    {
        const int size = this->_ptr._getAxisDisplacement(axis - 1);
        for (int j = 0; j < size; ++j)
        {
            f(idx, this->_ptr.data_item(disp + j));
            ++idx;
        }
    }

    // int
    template <int axis>
    inline void iterateOverAxisIdxs(const int &iter, const std::function<void(int)> &f) const
    {
        switch (iter)
        {
        case ALL:
            for (int j = 0; j < this->_ptr.shape(axis); ++j)
                f(j);
            break;
        case END:
            f(this->_ptr.shape(axis) - 1);
            break;
        default:
            f(iter);
            break;
        }
    }

    // NDArray<int>
    template <int axis>
    inline void iterateOverAxisIdxs(const NDArray<int> &iter, const std::function<void(int)> &f) const
    {
        for (int j = 0; j < iter.data_size(); ++j)
            f(iter.data_item(j));
    }

    // NDArray<bool>
    template <int axis>
    inline void iterateOverAxisIdxs(const NDArray<bool> &iter, const std::function<void(int)> &f) const
    {
        for (int j = 0; j < iter.data_size(); ++j)
            if (iter.data_item(j))
                f(j);
    }

    // range
    template <int axis>
    inline void iterateOverAxisIdxs(const range<int> &iter, const std::function<void(int)> &f) const
    {
        for (int j = iter.beginValue(); j < iter.endValue(); j += iter.stepValue())
            f(j);
    }

    // slice
    template <int axis>
    inline void iterateOverAxisIdxs(const slice &iter, const std::function<void(int)> &f) const
    {
        const int begin = iter.beginValue(this->_ptr, axis);
        const int end = iter.endValue(this->_ptr, axis);
        const int step = iter.stepValue(this->_ptr, axis);

        for (int j = begin; j < end; j += step)
            f(j);
    }

    template <int axis>
    inline typename std::enable_if<(axis < std::tuple_size<std::tuple<U...>>::value - 1), int>::type
    getStrideAxis() const
    {
        const int size = this->queryAxisSize<axis + 1>(std::get<axis + 1>(this->_view));
        return size * this->getStrideAxis<axis + 1>();
    }

    template <int axis>
    inline typename std::enable_if<(axis == std::tuple_size<std::tuple<U...>>::value - 1), int>::type
    getStrideAxis() const
    {
        return this->_ptr._getAxisDisplacement(axis);
    }

    template <int axis>
    inline typename std::enable_if<(axis < std::tuple_size<std::tuple<U...>>::value), void>::type
    setShape(NDArray<T> &result, const int &rank) const
    {
        const int size = queryAxisSize<axis>(std::get<axis>(this->_view));
        if (size > 1)
        {
            setShape<axis + 1>(result, rank + 1);
            result._data->shape(rank) = size;
        }
        else
        {
            setShape<axis + 1>(result, rank);
        }
    }

    template <int axis>
    inline typename std::enable_if<(axis == std::tuple_size<std::tuple<U...>>::value), void>::type
    setShape(NDArray<T> &result, const int &rank) const
    {
        result._data->shape.resize(rank + this->_ptr.rank() - axis);

        int k = rank;
        for (int j = axis; j < this->_ptr.rank(); ++j)
        {
            if (this->_ptr.shape(j) > 1)
            {
                result._data->shape(k) = this->_ptr.shape(j);
                ++k;
            }
        }

        result._data->shape.resize(k);
    }

    template <int axis>
    inline int queryAxisSize(const int &value) const;
    template <int axis>
    inline int queryAxisSize(const NDArray<int> &value) const;
    template <int axis>
    inline int queryAxisSize(const NDArray<bool> &value) const;
    template <int axis>
    inline int queryAxisSize(const range<int> &value) const;
    template <int axis>
    inline int queryAxisSize(const slice &value) const;
};

template<class T>
class NDArrayView<T, NDArray<bool>>
{
    NDArray<T> _ptr;
    NDArray<bool> _view;

    public:
        NDArrayView(NDArray<T> &data, const NDArray<bool> &view) : _ptr(data), _view(view) {}

        operator NDArray<T>() const {
            NDArray<T> result;

            if(this->_ptr.data_size()==this->_view.data_size())
            {
                result.resize(this->_ptr.shape());
                int size = this->queryAxisSize();
                result._data->shape(0) -= (result.shape(0) - size);
                result._data->array.resize(DM4th::NDArrayUtils::mul(result.shape()));
                iterateOverNDArrayView([&](const int &j, const T& item){
                    result.data_item(j) = item;
                });

            }else{
                NDArray<T> r = this->_ptr;
                result = NDArrayView<T, NDArray<bool>, int>(r, this->_view, ALL);
            }
            return result;
        };

        inline const NDArrayView<T, NDArray<bool>> &operator=(NDArrayView<T, NDArray<bool>> &other)
        {
            if(this->_ptr.data_size()==this->_view.data_size())
            {
                int size = queryAxisSize();
                
                NDArray<T> tmp = other;

                if(tmp.data_size()==size)
                {
                    iterateOverNDArrayView([&](const int &j, T& item){
                        item = tmp.data_item(j);
                    });
                }else{
                    iterateOverNDArrayView([&](const int &j, T& item){
                        item = tmp.data_item(j%tmp.data_size());
                    });
                }


            }else
            {
                NDArray<T> r = this->_ptr;
                NDArrayView<T, NDArray<bool>, int>(r, this->_view, ALL) = other;
            }
            return *this;
        }

        template<class U>
        inline typename std::enable_if< std::is_convertible<U,T>::value, const NDArrayView<T, NDArray<bool>>>::type 
        &operator=(const U &other)
        {
            if(this->_ptr.data_size()==this->_view.data_size())
            {
                iterateOverNDArrayView([&](const int &j, T& item){
                    item = other;
                });
            }else
            {
                NDArray<T> r = this->_ptr;
                NDArrayView<T, NDArray<bool>, int>(r, this->_view, ALL) = other;
            }  
            return *this;  
        }

        inline const NDArrayView<T, NDArray<bool>> &operator=(const NDArray<T> &other)
        {
            if(this->_ptr.data_size()==this->_view.data_size())
            {
                int size = queryAxisSize();
                
                if(other.data_size()==size)
                {
                    iterateOverNDArrayView([&](const int &j, T& item){
                        item = other.data_item(j);
                    });
                }else{
                    iterateOverNDArrayView([&](const int &j, T& item){
                        item = other.data_item(j%other.data_size());
                    });
                }
            }else
            {
                NDArray<T> r = this->_ptr;
                NDArrayView<T, NDArray<bool>, int>(r, this->_view, ALL) = other;
            }
            return *this;            
        }

        template <class... V>
        inline const NDArrayView<T, NDArray<bool>> &operator=(NDArrayView<T, V...> &other)
        {
            if(this->_ptr.data_size()==this->_view.data_size())
            {
                int size = queryAxisSize();
                
                NDArray<T> tmp = other;

                if(tmp.data_size()==size)
                {
                    iterateOverNDArrayView([&](const int &j, T& item){
                        item = tmp.data_item(j);
                    });
                }else{
                    iterateOverNDArrayView([&](const int &j, T& item){
                        item = tmp.data_item(j%tmp.data_size());
                    });
                }
            }else
            {
                NDArray<T> r = this->_ptr;
                NDArrayView<T, NDArray<bool>, int>(r, this->_view, ALL) = other;
            }   
        }

        inline void iterateOverNDArrayView(const std::function<void(const int &, T &)> &f)
        {
            int idx = 0;
            for(int j=0; j<this->_view.size(); ++j)
            {
                if(_view.data_item(j)==true)
                {
                    f(idx, this->_ptr.data_item(j));
                    ++idx;
                }
            }
        }
        inline void iterateOverNDArrayView(const std::function<void(const int &, const T &)> &f) const
        {
            int idx = 0;
            for(int j=0; j<this->_view.size(); ++j)
            {
                if(_view.data_item(j)==true)
                {
                    f(idx, this->_ptr.data_item(j));
                    ++idx;
                }
            }
        }

    private:

        inline int queryAxisSize() const
        {
            int size = 0;
            for(int j=0; j<_view.data_size(); ++j)
            {
                if(_view.data_item(j)==true) ++size;
            }
            return size;
        }
};

template <class T, class... U>
inline std::ostream &operator<<(std::ostream &stream, const NDArrayView<T, U...> &arr)
{
    stream << NDArray<T>(arr);
    return stream;
}

} // namespace DM4th


