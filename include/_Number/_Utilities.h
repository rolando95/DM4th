#include "_Array.h"

template<class T>
struct range{
    private:
        T _begin;
        T _end;
        T _step;
        bool _isInverse=false;
    public:
        range(): _begin(0), _end(0), _step(1) {}

        range(T end){
            _end = end;
            if(end<0){
                _isInverse = true;
                _step = -1;
            }
        }
        range(T begin, T end){
            _begin = begin;
            _end = end;
            _step = 1;
            if(begin>end){
                _isInverse = true;
                _step = -1;
            }
        }
        range(T begin, T end, T step){
            _begin = begin;
            _end = end;
            _step = step;
            assert(
                (begin<end && step>0) ||
                (begin>end && step<0)
            );
        }
        operator Array<T>(){
            int count=0;
            {
                T j=_begin;
                if(!_isInverse){
                    while(j<_end){
                        ++count;
                        j+=_step;
                    }
                }else{
                    while(j>_end){
                        ++count;
                        j+=_step;
                    }
                }
            }
            
            Array<T> result;
            result.resize(count);

            {
                int idx=0;
                T j=_begin;
                while(idx<count){
                    result(idx) = j;
                    j+=_step;
                    ++idx;
                }
            }
            
            return result;
        }

};
