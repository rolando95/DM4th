#ifndef __T_ARRAY_H__
#define __T_ARRAY_H__

#include "_BaseArray.h"
#include <queue>

////////////////////////////////////// FIX THIS
template<class T>
class TemplateArray;

template<class T, class U, class ... V>
void _items(TemplateArray<T> &arr, int axis, U first, V ... args)
{
    arr.c_arr()[axis] = (T)first;
    _items(arr, axis+1, args...);
}

template<class T>
void _items(TemplateArray<T> &arr, int axis){}

template<class T, class ... U>
TemplateArray<T> items(T first, U ... args)
{
    TemplateArray<T> result;
    int size = count(first, args...);
    result.resize(size);
    _items(result, 0, first, args...);
    return result;
}
////////////////////////////////////// END FIX THIS

template<class T>
class TemplateArray: public _ArrayDataManager<T>
{
    typedef _ArrayDataManager<T> super;
    public:
        inline void _resize1DArray(int size)
        {
            //assert(this->shapeSize()<=1); // Can be 0 || 1
            super::_data->array.resize(size);
            super::_data->shape.resize(1);
            super::_data->shape(0) = size;
        }
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
                    super::_data->array[newDispCount+newDisp.item(axis)*j] = oldArray[oldDispCount+oldDisp.item(axis)*j];
                }
            }
        }

        void _reshape(int axis, int last)
        {
            super::_data->shape.set(axis, last);
        }

        template<class ... U>
        void _reshape(int axis, int first, U ... args)
        {
            super::_data->shape.set(axis, first);
            this->_reshape(axis+1, args...);
        }

        template<class ... U>
        int _item(int axis, int pos, int idx, U ... args) const
        {
            pos = pos*super::_data->shape.get(axis) + idx;
            return _item(axis+1, pos, args ...);
        }

        int _item(int axis, int pos, int idx) const
        {
            assert(axis+1 == super::_data->shape.size());
            pos = pos*super::_data->shape.get(axis) + idx;
            return pos;
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
                super::_data->shape.set(j,axisArray.c_arr()[j]);
            }
            return oldArray;
        }

        void _ostream(std::ostream& stream, int shapeIdx, int& c_idx,  int ident) const
        {
            for(int j=0; j<shapeIdx; ++j)
            {
                for(int k=0; k<ident; ++k) stream<<" ";
            }
            stream << "[";
            if(this->shapeSize()>shapeIdx+1) 
            {
                stream<<"\n";
                for(int j=0; j<this->shape(shapeIdx); ++j)
                {
                    
                    if(j!=0) stream<<",\n";
                    this->_ostream(stream, shapeIdx+1,c_idx, ident);
                }
                stream<<"\n";
                for(int j=0; j<shapeIdx; ++j)
                {
                    for(int k=0; k<ident; ++k) stream<<" ";
                }
            }else
            {
                for(int j=0; j<this->shape(shapeIdx); ++j, ++c_idx)
                {
                    if(j!=0) stream<<", ";
                    stream<<this->c_arr()[c_idx];
                }
            }
            stream << "]";
        }

        void _istream(std::istream& stream, std::queue<T> &values, int shapeIdx, int& c_size, bool &shapeAllocated)
        {
            int size=0;
            _handleIstreamSpacesAndNewLines(stream);
            if(stream.peek()=='[')
            {
                while (true)
                {
                    assert(stream.peek()=='['); stream.get();

                    _handleIstreamSpacesAndNewLines(stream);
                    if(stream.peek()==']') break; //This dim is empty

                    this->_istream(stream, values, shapeIdx+1, c_size, shapeAllocated);
                    size+=1;
                    
                    assert(stream.peek()==']'); stream.get();

                    if(stream.peek()==']'){ break; }
                    else if(stream.peek()==',') { stream.get(); }
                    else assert(false);
                }
            }else
            {
                T value;
                while (true)
                {
                    _handleIstreamSpacesAndNewLines(stream);
                    if(stream.peek()==']') break; //This dim is empty
                    
                    stream>>value;
                    values.push(value);
                    size += 1;
                    c_size += 1;
                    
                    if(stream.peek()==']'){ break; }
                    else if(stream.peek()==',') { stream.get(); }
                    else assert(false);
                }

                if(!shapeAllocated)
                {
                    for(int j=0; j<super::_data->shape.size(); ++j)
                    {
                        super::_data->shape.set(j, 0);
                    }
                    super::_data->shape.resize(shapeIdx+1);
                    shapeAllocated = true;
                }
            }

            assert(
                size > 0  && 
                (
                    super::_data->shape.get(shapeIdx) == 0 ||
                    super::_data->shape.get(shapeIdx) == size
                )
            );
            super::_data->shape.set(shapeIdx, size);
            //std::cout<<size<<" "<<shapeIdx+1<<std::endl;      
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
            if(this->shapeSize()<=1) this->_resize1DArray(axis1); // 0 || 1 dim to 1 dim
            else
            { // N dim to 1 dim
                int disp = this->_getAxisDisplacement(0);
                int end = _min(axis1, this->shape(0));
                T* old = super::_data->array._allocAndReturnOldArray(axis1);
                super::_data->shape.resize(1);
                super::_data->shape.set(0, axis1);
                int oldj=0; int newj=0;
                for(; newj<end; ++newj, oldj+=disp)
                {
                    super::_data->array[newj] = old[oldj];
                }
                delete[] old;
            }
        }

        inline int shapeSize() const { return super::_data->shape.size(); }

        int size() const { return super::_data->shape.get(0); }

        TemplateArray<int> shape() const
        {
            TemplateArray<int> result;
            result._resize1DArray(super::_data->shape.size());
            for(int j=0; j<super::_data->shape.size(); ++j)
            {
                result.item(j) = super::_data->shape.get(j);
            }
            return result;
        }

        int shape(int axis) const 
        {
            return super::_data->shape(axis);
        }

        template<class ... U>
        void reshape(int axis1, U ... args)
        {
            //int oldShapeMult = mult(this->shape().c_arr(), this->shapeSize());
            int oldShapeMult = mult(super::_data->shape.c_arr(), this->shapeSize());
            int newShapeMult = mult(axis1,args...);
            assert(oldShapeMult==newShapeMult);
            
            super::_data->shape.resize(count(axis1,args...));
            this->_reshape(0, axis1, args...);
        }

        void reshape(TemplateArray<int> newShape)
        {
            int oldShapeMult = mult(super::_data->shape.c_arr(), this->shapeSize());
            int newShapeMult = mult(newShape.c_arr(), newShape.size());     
            assert(newShape.shapeSize()==1);    
            assert(oldShapeMult==newShapeMult);

            super::_data->shape.resize(newShape.size());
            for(int j=0; j<newShape.size(); ++j)
            {
                super::_data->shape.set(j, newShape.item(j));
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
                disp *= super::_data->shape.get(j);
            }

            return result;
        }

        int _getAxisDisplacement(int axis) const
        {
            int disp = 1;
            for(int j=super::_data->shape.size()-1; j>axis; --j)
            {
                disp *= super::_data->shape.get(j);
            }
            return disp;
        }

        template<class ... U>
        T &item(int x, U ... args) const
        { 
            const int pos = this->_item(1,x,args ...); 
            return super::_data->array(pos);
        }

        T &item(int x) const
        {
            assert(super::_data->shape.size()==1);
            assert(x<super::_data->array.size());
            assert( super::_data->shape.size()==1 && x<super::_data->array.size() );
            return super::_data->array[x];
        }

        T &item(const TemplateArray<int> &axisArray)
        {
            assert(axisArray.shapeSize()==1);
            assert(axisArray.size()==this->shapeSize());

            int pos = axisArray.c_arr()[0];
            for(int j=1; j<this->shapeSize(); ++j)
            {
                pos = pos*super::_data->shape.get(j) + axisArray.c_arr()[j];
            }

            // int *iter = axisArray.c_arr(); 
            // int pos = *iter;
            // for(int j=1; j<this->shapeSize(); ++j, ++iter)
            // {
            //     pos = pos*super::_data->shape(j) + *iter;
            // }
            return super::_data->array[pos];            
        }

        TemplateArray<T> copy() const
        {
            TemplateArray<T> result;
            result.resize(this->shape());
            for(int j=0; j<this->c_arr_size(); ++j)
            {
                result.c_arr_item(j) = this->c_arr_item(j);
            }
            return result;
        }

        template<class ... U>
        inline T &operator()(U ... args){ return this->item(args...); }
        template<class ... U>
        const inline T &operator()(U ... args) const { return this->item(args...); }

        inline T &operator()(TemplateArray<int> axisArray){ this->item(axisArray); }

        template<class U>
        TemplateArray<T> operator+(const TemplateArray<U> &other) const
        {
            TemplateArray<T> result = this->copy();
            result += other;
            return result;
        }

        template<class U>
        const TemplateArray<T> operator+=(const TemplateArray<U> &other)
        {
            assert(super::_data->shape==other._arrayData()->shape);
            for(int j=0; j<this->c_arr_size(); ++j)
            {
                this->c_arr_item(j) += other.c_arr_item(j);
            }
            return *this;
        }

        template<class U>
        TemplateArray<T> operator-(const TemplateArray<U> &other) const
        {
            TemplateArray<T> result = this->copy();
            result -= other;
            return result;
        }

        template<class U>
        const TemplateArray<T> operator-=(const TemplateArray<U> &other)
        {
            assert(super::_data->shape==other._arrayData()->shape);
            for(int j=0; j<this->c_arr_size(); ++j)
            {
                this->c_arr_item(j) -= other.c_arr_item(j);
            }
            return *this;
        }

        template<class U>
        bool operator==(const TemplateArray<U> &other)
        {
            return super::_data->shape==other._arrayData()->shape && other._arrayData()->array==super::_data->array;
        }

        template<class U>
        inline bool operator!=(const TemplateArray<U> &other){ return !(*this==other); }

        template<class U>
        bool operator>(const TemplateArray<U> &other)
        {
            const int sizeArr = this->c_arr_size();
            const int oSizeArr = other.c_arr_size();

            int size = _min(sizeArr,oSizeArr); 

            const T* c_arr = this->c_arr();
            const U* oC_arr = other.c_arr();

            for(int j=0; j<size; ++j)
            {
                if(c_arr[j]>oC_arr[j]) return true;
                if(c_arr[j]<oC_arr[j]) return false;
            }            

            if(oSizeArr>=sizeArr) return false;
            return true;
        }

        template<class U>
        inline bool operator<=(const TemplateArray<U> &other){ return !(*this>other); }

        template<class U>
        bool operator>=(const TemplateArray<U> &other)
        {
            const int sizeArr = this->c_arr_size();
            const int oSizeArr = other.c_arr_size();

            int size = _min(sizeArr,oSizeArr); 

            T* c_arr = this->c_arr();
            const U* oC_arr = other.c_arr();

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

        std::ostream& ostream(std::ostream& stream, int ident=4) const
        {
            int c_idx = 0;          
            this->_ostream(stream, 0, c_idx, ident);
            return stream;
        }

        std::istream& istream(std::istream& stream)
        {
            int c_size = 0;
            std::queue<T> values;
            bool shapeAllocated = false;
            _handleIstreamSpacesAndNewLines(stream);

            assert(stream.peek()=='['); stream.get();
            
            this->_istream(stream, values, 0, c_size, shapeAllocated);
            _handleIstreamSpacesAndNewLines(stream);

            assert(stream.peek()==']'); stream.get();

            super::_data->array.resize(c_size);
            for(int j=0; j<c_size; ++j)
            {
                assert(!values.empty());
                this->c_arr()[j] = values.front(); 
                values.pop();
            }
            return stream;
        }

        inline T *c_arr(){ return &super::_data->array[0]; }
        inline const T *c_arr() const { return &super::_data->array[0]; }
        inline const int c_arr_size() const { return super::_data->array.size(); }
        inline T &c_arr_item(int idx) { return super::_data->array[idx]; }
        inline const T c_arr_item(int idx) const { return super::_data->array.get(idx); }
};

template<class T>
inline std::ostream& operator<<(std::ostream& stream, const TemplateArray<T> &arr)
{
    return arr.ostream(stream,4);
}

template<class T>
inline std::istream& operator>>(std::istream& stream, TemplateArray<T> &arr)
{
    return arr.istream(stream);
}
#endif