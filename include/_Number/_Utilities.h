#include "_Array.h"

template<class T=int>
struct range{
    private:
        T _begin;
        T _end;
        T _step;
        bool _isInverse=false;
    public:
        range();
        range(T end);
        range(T begin, T end);
        range(T begin, T end, T step);
        operator Array<T>();
};
