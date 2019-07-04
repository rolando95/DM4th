#ifndef __ARRAY_H__
#define __ARRAY_H__

#include "_ArrayBase.h"

template<class T>
class TemplateArray: public _ArrayDataManager<T>
{
    typedef _ArrayDataManager<T> super;
    public:
        template<class ... U>
        void resize(int axis1, U ... args){
            super::_resize(1, axis1, args ... );
            super::_data->shape.setAxisIdx(0, axis1);
        }

        inline void resize(int axis1){
            super::_resize1DArray(axis1);
        }

        int shapeSize(){
            return super::_data->shape.size();

        }
        TemplateArray<int> shape(){
            TemplateArray<int> result;
            result._resize1DArray(super::_data->shape.size());
            for(int j=0; j<super::_data->shape.size(); j++){
                result.item(j) = super::_data->shape.getAxisIdx(j);
            }
            return result;
        }

        int shape(int axis){
            return super::_data->shape.getAxisIdx(axis);
        }
        
        template<class ... U>
        T &item(int x, U ... args){
            return super::_item(1,x,args ...);
        }

        T &item(int x){
            assert(
                super::_data->shape.size()==1 &&
                x<super::_data->array.size()
            );
            return super::_data->array[x];
        }

        template<class ...U>
        T &operator()(U ... args){
            return this->item(args...);
        }
};

template<class T=float>
class Array: public TemplateArray<T>
{
    typedef TemplateArray<T> super;
    public:
        Array();
        Array(const super &other){ static_cast<super&>(*this) = other; }
};

template<>
class Array<bool>: public TemplateArray<bool>
{
    typedef TemplateArray super;
    public:
        Array();
        Array(const super &other){ static_cast<super&>(*this) = other; }
};

#endif