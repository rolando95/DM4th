#ifndef __ARRAY_H__
#define __ARRAY_H__

#include "_ArrayBase.h"

template<class T>
class TemplateArray: public _ArrayDataManager<T>
{
    typedef _ArrayDataManager<T> super;
    public:
        void resize(int x, int y=0){
            assert(x>0 && y>=0);
            
            if(y>0){
                super::_data->array.resize(x*y);
                super::_data->shape.resize(2);
                super::_data->shape.setAxisIdx(0,x);
                super::_data->shape.setAxisIdx(1,y);
            }else{
                super::_data->array.resize(x);
                super::_data->shape.resize(1);
                super::_data->shape.setAxisIdx(0,x);
            }
           
        }

        TemplateArray<int> shape(){
            TemplateArray<int> result;
            result.resize(super::_data->shape.size());
            for(int j=0; j<super::_data->shape.size(); j++){
                result(j) = super::_data->shape.getAxisIdx(j);
            }
            return result;
        }

        int shape(int axis){
            return super::_data->shape.getAxisIdx(axis);
        }

        // operator T(){
        //     assert(super::_data->array.size()==1);
        //     return super::_data->array[0];
        // }
        
        // T &operator()(int idx)
        // {
        //     assert(idx<super::_data->array.size());
        //     return super::_data->array[idx];
        // }

        T &operator()(int x){
            assert(
                super::_data->shape.size()==1 &&
                x<super::_data->array.size()
            );
            return super::_data->array[x];
        }

        T &operator()(int x, int y){
            assert(
                super::_data->shape.size()==2 &&
                x<super::_data->shape.getAxisIdx(0) &&
                y<super::_data->shape.getAxisIdx(1)
            );
            return super::_data->array[x*super::_data->shape.getAxisIdx(0) + y];
        }
};


template<class T=float>
class Array: public TemplateArray<T>
{
    typedef TemplateArray<T> super;
    public:
};

template<>
class Array<bool>: public TemplateArray<bool>
{
    typedef TemplateArray super;
    public:

    //bool any()
    //bool all()
};

#endif