#ifndef __T_ARRAY_H__
#define __T_ARRAY_H__

#include "_BaseArray.h"


////////////////////////////////////// FIX THIS
template<class T>
class TemplateArray;

template<class T, class ... U>
void _items(TemplateArray<T> &arr, int axis, T first, U ... args)
{
    arr.c_arr()[axis] = first;
    _items(arr, axis+1, args...);
}

template<class T>
void _items(TemplateArray<T> &arr, int axis){}

template<class T, class ... U>
TemplateArray<T> items(T first, U ... args)
{
    TemplateArray<T> result;
    int size = count(first, args...);
    result._resize1DArray(size);
    _items(result, 0, first, args...);
    return result;
}
////////////////////////////////////// END FIX THIS

template<class T>
class TemplateArray: public _ArrayDataManager<T>
{
    typedef _ArrayDataManager<T> super;
    public:

    private:

        void _resize(int axis, int oldDispCount, int newDispCount, 
            TemplateArray<int> &oldDisp,  TemplateArray<int> &newDisp, 
            TemplateArray<int> &oldShape,  TemplateArray<int> &newShape,
            T* oldArray)
        {
            int end = _min(oldShape.item(axis), newShape.item(axis));
            if(axis<oldShape.size()-1 && axis<newShape.size()-1){
                for(int j=0; j<end; ++j)
                {
                    this->_resize(
                        axis+1, 
                        oldDispCount+oldDisp.item(axis)*j, newDispCount+newDisp.item(axis)*j,
                        oldDisp, newDisp,
                        oldShape, newShape,
                        oldArray
                    );
                }
            }else{
                for(int j=0; j<end; ++j)
                {
                    this->_data->array[newDispCount+newDisp.item(axis)*j] = oldArray[oldDispCount+oldDisp.item(axis)*j];
                }
            }
        }

        void _reshape(int axis, int last)
        {
            super::_data->shape.setAxisIdx(axis, last);
        }

        template<class ... U>
        void _reshape(int axis, int first, U ... args)
        {
            super::_data->shape.setAxisIdx(axis, first);
            this->_reshape(axis+1, args...);
        }

        template<class ... U>
        T &_item(int axis, int pos, int idx, U ... args)
        {
            pos = pos*super::_data->shape.getAxisIdx(axis) + idx;
            return _item(axis+1, pos, args ...);
        }

        T &_item(int axis, int pos, int idx)
        {
            assert(axis+1 == super::_data->shape.size());
            pos = pos*super::_data->shape.getAxisIdx(axis) + idx;
            return super::_data->array[pos];
        }

        template<class ... U>
        T* _allocZeros(int axis, int count, int idx, U ... args)
        {
             count *= idx;
            T* oldArray = _allocZeros(axis+1, count, args ...);
            super::_data->shape.setAxisIdx(axis, idx);
            return oldArray;
        }

        T*  _allocZeros(int axis, int count, int idx)
        {
            count*=idx;
            T* oldArray = super::_data->array._allocAndReturnOldArray(count);
            super::_data->shape.resize(axis+1);
            super::_data->shape.setAxisIdx(axis, idx);
            return oldArray;
        }

        T* _allocZeros(const TemplateArray<int> &axisArray)
        {
            int count = 1;
            for(int j=0; j<axisArray.size(); ++j)
            {
                count*= axisArray.c_arr()[j];
            }
            T* oldArray = super::_data->array._allocAndReturnOldArray(count);
            super::_data->shape.resize(axisArray.size());
            for(int j=0; j<axisArray.size(); ++j)
            {
                super::_data->shape.setAxisIdx(j, axisArray.c_arr()[j]);
            }
            return oldArray;
        }

    public:

        TemplateArray(){}
        
        TemplateArray(range<T> &other)
        {
            int count = other.count();
            this->_resize1DArray(count);
            T j=other.begin();
            int idx=0;
            while(idx<count)
            {
                super::_data->array[idx] = j;
                j+=other.step();
                ++idx;
            }
        }

        template<class ... U>
        inline void resize(int axis1, U ... args)
        {
            TemplateArray<int> axisArray = items<int>(axis1, args...);
            this->resize(axisArray);
        }
        //template<class ... U>
        void resize(const TemplateArray<int> &axisArray)
        {
            assert(axisArray.shapeSize()==1);

            if(this->shapeSize()==1)
            { //1 dim to N dim
                int oldShape = this->shape(0);

                T* oldArray = this->_allocZeros(axisArray);

                int newDisp = this->_getAxisDisplacement(0);
                int end = _min(oldShape, this->shape(0));
                int newj = 0;
                for(int oldj=0; oldj<end; ++oldj, newj+=newDisp)
                {
                    super::_data->array[newj] = oldArray[oldj];
                }
                delete[] oldArray;
            }else
            { //N dim to M dim
                TemplateArray<int> oldShape = this->shape();
                TemplateArray<int> oldDisp = this->_getAxisDisplacement();

                T* oldArray = this->_allocZeros(axisArray);

                TemplateArray<int> newShape = this->shape();
                TemplateArray<int> newDisp = this->_getAxisDisplacement();

                if(oldArray==nullptr) return;

                int end = _min(oldShape.item(0), newShape.item(0));
                for(int j=0; j<end; ++j)
                {
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
        }

        inline void resize(int axis1)
        {
            if(this->shapeSize()==1) this->_resize1DArray(axis1); // 1 dim to 1 dim
            else
            { // N dim to 1 dim
                int disp = this->_getAxisDisplacement(0);
                int end = _min(axis1, this->shape(0));
                T* old = this->_data->array._allocAndReturnOldArray(axis1);
                super::_data->shape.resize(1);
                super::_data->shape.setAxisIdx(0, axis1);
                int oldj=0; int newj=0;
                for(; newj<end; ++newj, oldj+=disp)
                {
                    super::_data->array[newj] = old[oldj];
                }
                delete[] old;
            }
        }

        int shapeSize() const { return super::_data->shape.size(); }

        int size() const { return super::_data->shape.getAxisIdx(0); }

        TemplateArray<int> shape() const
        {
            TemplateArray<int> result;
            result._resize1DArray(super::_data->shape.size());
            for(int j=0; j<super::_data->shape.size(); ++j)
            {
                result.item(j) = super::_data->shape.getAxisIdx(j);
            }
            return result;
        }

        int shape(int axis) const 
        {
            return super::_data->shape.getAxisIdx(axis);
        }

        template<class ... U>
        void reshape(int axis1, U ... args)
        {
            int oldShapeMult = mult(this->shape().c_arr(), this->shapeSize());
            int newShapeMult = mult(axis1,args...);
            assert(oldShapeMult==newShapeMult);
            
            super::_data->shape.resize(count(axis1,args...));
            this->_reshape(0, axis1, args...);
        }

        void reshape(TemplateArray<int> newShape)
        {
            int oldShapeMult = mult(this->shape().c_arr(), this->shapeSize());
            int newShapeMult = mult(newShape.c_arr(), newShape.size());     
            assert(newShape.shapeSize()==1);    
            assert(oldShapeMult==newShapeMult);

            this->_data->shape.resize(newShape.size());
            for(int j=0; j<newShape.size(); ++j)
            {
                this->_data->shape.setAxisIdx(j,newShape.item(j));
            }
        }

        TemplateArray<int> _getAxisDisplacement() const
        {
            TemplateArray<int> result;
            result._resize1DArray(super::_data->shape.size());
            int disp = 1;
            for(int j=super::_data->shape.size()-1; j>=0; --j)
            {
                result.item(j) = disp;
                disp *= super::_data->shape.getAxisIdx(j);
            }

            return result;
        }

        int _getAxisDisplacement(int axis) const
        {
            int disp = 1;
            for(int j=super::_data->shape.size()-1; j>axis; --j)
            {
                disp *= super::_data->shape.getAxisIdx(j);
            }
            return disp;
        }

        template<class ... U>
        T &item(int x, U ... args){ return this->_item(1,x,args ...); }

        T &item(int x)
        {
            assert(super::_data->shape.size()==1);
            assert(x<super::_data->array.size());
            assert( super::_data->shape.size()==1 && x<super::_data->array.size() );
            return super::_data->array[x];
        }

        T &item(TemplateArray<int> axisArray)
        {
            assert(axisArray.shapeSize()==1);
            assert(axisArray.size()==this->shapeSize());

            int pos = axisArray.c_arr()[0];
            for(int j=1; j<this->shapeSize(); ++j)
            {
                pos = pos*this->_data->shape.getAxisIdx(j) + axisArray.c_arr()[j];
            }
            return this->_data->array[pos];            
        }

        template<class ... U>
        T &operator()(U ... args){ return this->item(args...); }

        inline T &operator()(TemplateArray<int> axisArray){ this->item(axisArray); }

        template<class U>
        bool operator==(TemplateArray<U> &other)
        {
            // Check if arrays have the same shape
            // int size = this->shapeSize();
            // int oSize = other.shapeSize();

            // if(size!=oSize) return false;

            // TemplateArray<T> tmp2 = other.shape(); 
            // int* shape = tmp2.c_arr();
            // TemplateArray<T> tmp = other.shape(); 
            // int* oShape = tmp.c_arr();
        
            // for(int j=0; j<size; ++j){
            //     std::cout<<shape[j]<<" "<<oShape[j]<<std::endl;
            //     if(shape[j]!=oShape[j]) return false;
            // }

            int sizeArr = this->c_arr_size();
            int oSizeArr = other.c_arr_size();

            if(sizeArr != oSizeArr) return false;

            T* c_arr = this->c_arr();
            U* oC_arr = other.c_arr();

            for(int j=0; j<sizeArr; ++j)
            {
                if(c_arr[j]!=oC_arr[j]) return false;
            }            

            return true;

            
        }

        template<class U>
        bool operator!=(TemplateArray<U> &other){ return !(*this==other); }

        template<class U>
        bool operator>(TemplateArray<U> &other)
        {
            int sizeArr = this->c_arr_size();
            int oSizeArr = other.c_arr_size();

            int size = _min(sizeArr,oSizeArr); 

            T* c_arr = this->c_arr();
            U* oC_arr = other.c_arr();

            for(int j=0; j<size; ++j)
            {
                if(c_arr[j]>oC_arr[j]) return true;
                if(c_arr[j]<oC_arr[j]) return false;
            }            

            if(oSizeArr>=sizeArr) return false;
            return true;
        }

        template<class U>
        bool operator<=(TemplateArray<U> &other){ return !(*this>other); }

        template<class U>
        bool operator>=(TemplateArray<U> &other)
        {
            int sizeArr = this->c_arr_size();
            int oSizeArr = other.c_arr_size();

            int size = _min(sizeArr,oSizeArr); 

            T* c_arr = this->c_arr();
            U* oC_arr = other.c_arr();

            for(int j=0; j<size; ++j)
            {
                if(c_arr[j]>oC_arr[j]) return true;
                if(c_arr[j]<oC_arr[j]) return false;
            }            

            if(oSizeArr>sizeArr) return false;
            return true;
        }

        template<class U>
        bool operator<(TemplateArray<U> &other){ return !(*this>=other); }

        inline T *c_arr(){ return &super::_data->array[0]; }
        inline const T *c_arr()const { return &super::_data->array[0]; }
        inline int c_arr_size() { return super::_data->array.size(); }
        inline T &c_arr_item(int idx) { return super::_data->array[idx]; }
        inline void _resize1DArray(int size)
        {
            assert(this->shapeSize()<=1); // Can be 0 || 1
            this->_data->array.resize(size);
            this->_data->shape.resize(1);
            this->_data->shape.setAxisIdx(0, size);
        }
};
#endif