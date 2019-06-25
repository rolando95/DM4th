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
        //     assert(super::_data.shape.size());
        //     return super::_data[0];
        // }
};

template<class T=int>
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