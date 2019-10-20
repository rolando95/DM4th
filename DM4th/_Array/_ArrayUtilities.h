#include "_Array.h"

namespace DM4th {

template<class T=number>
class range {
    T _begin;
    T _end;
    T _step;
    int _size;
public:
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

    T begin() { return this->_begin; }
    T end() { return this->_end; }
    T step() { return this->_step; }
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

        return size; 
    }
};

}