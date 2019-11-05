#include "_Array.h"

namespace DM4th {

template<class T=number>
class range {
    T _begin;
    T _end;
    T _step;
    int _size;
public:

    friend class iterator;

    range(T end) : _begin(0), _end(end), _step(1) 
    {
        if(this->_begin>this->_end)
        {
            this->_step = -1;
        }
        this->_size = this->_setSize();
    };

    range(T begin, T end) : _begin(begin), _end(end), _step(1) 
    {
        if(this->_begin>this->_end)
        {
            this->_step = -1;
        }
        this->_size = this->_setSize();
    };
    
    range(T begin, T end, T step) : _begin(begin), _end(end), _step(step)  
    {
        DM4thAssert( (end>=begin && step>0) || (end<=begin && step<0));
        this->_size = this->_setSize();
    };

    int size() { return this->_size; }

    operator NDArray<T>()
    {
        int size = this->_size;
        TemplateArray<T> result;
        T j = this->_begin;
        result.resize(size);
        int idx=0;
        
        while(idx<size)
        {
            result.item(idx) = j;
            j+=this->_step;
            ++idx;
        }

        return result;
    }

    class iterator
    {
        private:
            range<T> _data;
            T _ptr;
        public:
            iterator(range<T> &data, T ptr=0) : _data(data), _ptr(ptr) {};
            bool operator==(iterator other){ return (this->_ptr == other._ptr); }
            bool operator!=(iterator other){ return !(*this==other); }
            iterator &operator++(){ this->_ptr+=_data._step; return *this; }
            iterator operator++(int){ iterator result(this->_data, this->_ptr); this->_ptr+=_data._step; return result; }
            const T &operator*(){ return this->_ptr; }
    };

    iterator begin(){ return iterator(*this, this->_begin); }
    iterator end(){ return iterator(*this, this->_end); }


private:
    int _setSize() 
    { 
        int size = 0;
        T j = this->_begin; 
        if(this->_step>0)
        {
            while(j<this->_end)
            {
                ++size;
                j += this->_step;
            }
        }else
        {
            while(j>this->_end)
            {
                ++size;
                j += this->_step;
            }
        }

        this->_end = j;
        return size; 
    }
};

typedef range<int> slice;

template<class T, class U, class ... V>
void _map(std::function<T(T)> f, NDArray<T> &arr, int axis, U first, V ... args)
{
    arr.data_item(axis) = (T)f(first);
    _map(f, arr, axis+1, args...);
}

template<class T>
void _map(std::function<T(T)> f, NDArray<T> &arr, int axis){}

template<class T, class ... U>
NDArray<T> map(std::function<T(T)> f, T first, U ... args)
{
    NDArray<T> result;
    int size = DM4thUtils::count(first, args ...);
    result.resize(size);
    _map(f, result, 0, first, args...);
    return result;
}

template<class T>
NDArray<T> map(std::function<T(T)> f, NDArray<T> args)
{
    NDArray<T> result;
    result.resize(args.data_size());
    for(int j=0; j<args.data_size(); ++j)
    {
        result(j) = f(args(j));
    }
    return result;
}

template<class T, class U>
NDArray<U> map(std::function<U(T)> f, NDArray<T> args)
{
    NDArray<U> result;
    result.resize(args.data_size());
    for(int j=0; j<args.data_size(); ++j)
    {
        result(j) = f(args(j));
    }
    return result;
}

}