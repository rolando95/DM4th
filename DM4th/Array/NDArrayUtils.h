#pragma once
#include "NDArray.h"

namespace DM4th
{

    namespace NDArrayUtils
    {

        template <class T>
        inline T mul(const NDArray<T> &arr)
        {
            T result = 1;
            int size = arr.data_size();
            for (int j = 0; j < size; ++j)
            {
                result *= arr.data_item(j);
            }
            return result;
        }

        template <class T>
        inline T add(const NDArray<T> &arr)
        {
            T result = 0;
            int size = arr.data_size();
            for (int j = 0; j < size; ++j)
            {
                result += arr.data_item(j);
            }
            return result;
        }

        template <class T>
        inline T min(const NDArray<T> &arr)
        {
            T result = INF;
            int size = arr.data_size();
            for (int j = 0; j < size; ++j)
            {
                if (arr.data_item(j) < result)
                {
                    result = arr.data_item(j);
                }
            }
            return result;
        }

        template <class T>
        inline T max(const NDArray<T> &arr)
        {
            T result = -INF;
            int size = arr.data_size();
            for (int j = 0; j < size; ++j)
            {
                if (arr.data_item(j) > result)
                {
                    result = arr.data_item(j);
                }
            }
            return result;
        }

        template <class T>
        inline int count(const NDArray<T> &arr) { return arr.data_size(); }

    } // namespace NDArrayUtils

    template <class T, class... U>
    inline NDArray<T> items(T first, U... args)
    {
        NDArray<T> result;
        int size = DM4thUtils::count(first, args...);
        result._resizeEmpty(size);
        int idx = 0;
        for (const T &item : {first, T(args)...})
        {
            result.data_item(idx++) = item;
        }
        return result;
    }

    template <class T, class... U>
    inline NDArray<T> repeat(T value, U... axisSize)
    {
        NDArray<T> result;
        unsigned int size = (unsigned int)DM4thUtils::mul(axisSize...);
        result._resizeEmpty(axisSize...);

        for (unsigned int j = 0; j < size; ++j)
        {
            result.data_item(j) = value;
        }

        return result;
    }

    template <class T, class... U>
    inline NDArray<T> zeros(U... axisSize)
    {
        return repeat<T>(0, axisSize...);
    }

    template <class T, class... U>
    inline NDArray<T> empty(U... axisSize)
    {
        NDArray<T> result;
        result._resizeEmpty(axisSize...);
        return result;
    }

    template <class T, class... U>
    inline NDArray<T> ones(U... axisSize)
    {
        return repeat<T>(1, axisSize...);
    }

    template <class T, class... U>
    inline NDArray<T> identity(int axis0, U... axisSize)
    {
        NDArray<T> result;
        if (DM4thUtils::count(axis0, axisSize...) > 1)
        {
            result = zeros<T>(axis0, axisSize...);
            //result._resizeEmpty(axisSize...);

            NDArray<T> axis = items<T>(axis0, axisSize...);
            int size = DM4th::NDArrayUtils::min<T>(axis);
            int disp = result._getAxisDisplacement(0) + 1;
            for (int j = 0, idx = 0; j < size; ++j, idx += disp)
            {
                result.data_item(idx) = 1;
            }
        }
        else
        {
            result = zeros<T>(axis0, axis0);
            for (int j = 0; j < axis0; ++j)
            {
                result(j, j) = 1;
            }
        }

        return result;
    }

    template <class T>
    inline NDArray<T> sort(NDArray<T> arr, bool reverse = false)
    {
        NDArray<T> result = arr.getCopy();
        result.sort(reverse);
        return result;
    }

    template <class T = number>
    class range
    {
        T _begin;
        T _end;
        T _step;
        int _size;

    public:
        friend class iterator;

        range(T end) : _begin(0), _end(end), _step(1)
        {
            if (this->_begin > this->_end)
            {
                this->_step = -1;
            }
            this->_size = this->_setSize();
        };

        range(T begin, T end) : _begin(begin), _end(end), _step(1)
        {
            if (this->_begin > this->_end)
            {
                this->_step = -1;
            }
            this->_size = this->_setSize();
        };

        range(T begin, T end, T step) : _begin(begin), _end(end), _step(step)
        {
            DM4thAssert((end >= begin && step > 0) || (end <= begin && step < 0));
            this->_size = this->_setSize();
        };

        int size() const { return this->_size; }

        operator NDArray<T>()
        {
            int size = this->_size;
            NDArray<T> result;
            T j = this->_begin;
            result._resizeEmpty(size);
            int idx = 0;

            while (idx < size)
            {
                result.item(idx) = j;
                j += this->_step;
                ++idx;
            }

            return result;
        }

        class iterator
        {
        private:
            const range<T> _data;
            T _ptr;

        public:
            iterator(const range<T> &data, T ptr = 0) : _data(data), _ptr(ptr){};
            bool operator==(iterator other) const { return (this->_ptr == other._ptr); }
            bool operator!=(iterator other) const { return !(*this == other); }
            iterator &operator++()
            {
                this->_ptr += _data._step;
                return *this;
            }
            iterator operator++(int)
            {
                iterator result(this->_data, this->_ptr);
                this->_ptr += _data._step;
                return result;
            }
            const T &operator*() { return this->_ptr; }
        };

        iterator begin() const { return iterator(*this, this->_begin); }
        iterator end() const { return iterator(*this, this->_end); }

        T beginValue() const { return this->_begin; }
        T endValue() const { return this->_end; }
        T stepValue() const { return this->_step; }

    private:
        int _setSize()
        {
            int size = 0;
            T j = this->_begin;
            if (this->_step > 0)
            {
                while (j < this->_end)
                {
                    ++size;
                    j += this->_step;
                }
            }
            else
            {
                while (j > this->_end)
                {
                    ++size;
                    j += this->_step;
                }
            }

            this->_end = j;
            return size;
        }
    };

    /*
    
*/
    class slice
    {
        int _begin;
        int _end;
        int _step;

    public:
        slice() : _begin(BEGIN), _end(END), _step(1){};
        slice(const int &end) : _begin(BEGIN), _end(end), _step(1)
        {
            if (end == ALL)
            {
                this->_end = END;
            }
        };
        slice(const int &begin, const int &end) : _begin(begin), _end(end), _step(1){};
        slice(const int &begin, const int &end, const int &step) : _begin(begin), _end(end), _step(step){};

        template <class T>
        const int beginValue(const NDArray<T> &arr, const int &axis = 0) const { return this->_begin; }
        template <class T>
        const int endValue(const NDArray<T> &arr, const int &axis = 0) const
        {
            return this->_end == END ? arr.shape(axis) : this->_end;
        }

        template <class T>
        const int stepValue(const NDArray<T> &arr, const int &axis = 0) const { return this->_step; }

        template <class T>
        const int size(const NDArray<T> &arr, const int &axis = 0) const
        {
            if (this->_step != 1)
            {
                const float end = this->endValue(arr, axis);
                return std::ceil((end - this->_begin) / this->_step);
            }
            return this->endValue(arr, axis) - this->_begin;
        }
    };

    template <class T, class... U>
    NDArray<T> map(std::function<T(T)> f, T first, U... args)
    {
        NDArray<T> result;
        int size = DM4thUtils::count(first, args...);
        result._resizeEmpty(size);
        //_map(f, result, 0, first, args...);
        int idx = 0;
        for (const T &item : {first, (T)args...})
        {
            result.data_item(idx++) = f(item);
        }
        return result;
    }

    template <class T>
    NDArray<T> map(std::function<T(T)> f, NDArray<T> args)
    {
        NDArray<T> result;
        result._resizeEmpty(args.data_size());
        for (int j = 0; j < args.data_size(); ++j)
        {
            result.data_item(j) = f(args.data_item(j));
        }
        return result;
    }

    template <class T, class U>
    NDArray<U> map(std::function<U(T)> f, NDArray<T> args)
    {
        NDArray<U> result;
        result._resizeEmpty(args.data_size());
        for (int j = 0; j < args.data_size(); ++j)
        {
            result.data_item(j) = f(args.data_item(j));
        }
        return result;
    }

    template <class T>
    NDArray<T> linspace(T begin, T end, number num, bool endPoint = true)
    {
        int size = (int)num;
        DM4thAssert(size > 0);
        T step = (T)((end - begin) / (num - (endPoint ? 1 : 0)));
        NDArray<T> result;
        result._resizeEmpty(size);

        T iter = begin;
        for (int j = 0; j < size; ++j)
        {
            result(j) = iter;
            iter += step;
        }
        return result;
    }
} // namespace DM4th