#ifndef __ARRAY_H__
#define __ARRAY_H__

#include "_ArrayBase.h"

template<class T>
class TemplateArray: public _ArrayDataManager<T>
{
    typedef _ArrayDataManager<T> super;
    private:
        void _resize(int axis, int oldDispCount, int newDispCount, 
         TemplateArray<int> &oldDisp,  TemplateArray<int> &newDisp, 
         TemplateArray<int> &oldShape,  TemplateArray<int> &newShape,
         T* oldArray){
            int end = _min(oldShape.item(axis), newShape.item(axis));
            if(axis<oldShape.size()-1 && axis<newShape.size()-1){
                for(int j=0; j<end; ++j){
                    this->_resize(
                        axis+1, 
                        oldDispCount+oldDisp.item(axis)*j, newDispCount+newDisp.item(axis)*j,
                        oldDisp, newDisp,
                        oldShape, newShape,
                        oldArray
                    );
                }
            }else{
                for(int j=0; j<end; ++j){
                    this->_data->array[newDispCount+newDisp.item(axis)*j] = oldArray[oldDispCount+oldDisp.item(axis)*j];
                }
            }
        }
    public:
        // template<class ... U>
        // void resize(int axis1, U ... args){
        //     super::_resize(1, axis1, args ... );
        //     super::_data->shape.setAxisIdx(0, axis1);
        // }

        template<class ... U>
        void resize(int axis1, U ... args){
            TemplateArray<int> oldShape = this->shape();
            TemplateArray<int> oldDisp = this->_getAxisDisplacement();
            for(int j=0; j<oldShape.size(); ++j){
                   std::cout<<oldShape.item(j)<<" "<<std::endl;
            }

            T* oldArray = super::_allocZeros(1, axis1, args ...);
            super::_data->shape.setAxisIdx(0, axis1);
            TemplateArray<int> newShape = this->shape();
            TemplateArray<int> newDisp = this->_getAxisDisplacement();

            for(int j=0; j<newShape.size(); ++j){
                std::cout<<newShape.item(j)<<" "<<std::endl;
            }

            if(oldArray==nullptr) return;

            int end = _min(oldShape.item(0), newShape.item(0));
            for(int j=0; j<end; ++j){
                this->_resize(
                    1, 
                    oldDisp.item(0)*j, newDisp.item(0)*j, 
                    oldDisp, newDisp,
                    oldShape, newShape, 
                    oldArray
                );
            }

            delete[] oldArray;
        }

        inline void resize(int axis1){
            super::_resize1DArray(axis1);
        }

        int shapeSize(){
            return super::_data->shape.size();

        }

        int size(){
            return super::_data->shape.getAxisIdx(0);
        }

        TemplateArray<int> shape(){
            TemplateArray<int> result;
            result._resize1DArray(super::_data->shape.size());
            for(int j=0; j<super::_data->shape.size(); ++j){
                result.item(j) = super::_data->shape.getAxisIdx(j);
            }
            return result;
        }

        TemplateArray<int> _getAxisDisplacement(){
            TemplateArray<int> result;
            result._resize1DArray(super::_data->shape.size());
            int count = 1;
            for(int j=super::_data->shape.size()-1; j>=0; --j){
                result.item(j) = count;
                count *= super::_data->shape.getAxisIdx(j);
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
        Array(){}
        Array(const super &other){ static_cast<super&>(*this) = other; }
};

template<>
class Array<bool>: public TemplateArray<bool>
{
    typedef TemplateArray super;
    public:
        Array(){}
        Array(const super &other){ static_cast<super&>(*this) = other; }
};
#endif