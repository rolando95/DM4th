#pragma once

#include "_BaseArray_impl.h"
#include "../_Utilities/_Utilities.h"

namespace DM4th
{

template<class T>
class TemplateArray: public DM4thInternal::_ArrayDataManager<T>
{
    typedef DM4thInternal::_ArrayDataManager<T> super;

    public:
        class iterator;
        class iterator_const;

        TemplateArray();
        template<class ... U> TemplateArray(T *data, U ... args);
        TemplateArray(T *data, const TemplateArray<int> &axisArray);
        TemplateArray(const std::string &other);

        template<class ... U>
        inline void resize(int axis1, U ... args);
        inline void resize(int axis1);

        void resize(const TemplateArray<int> &axisArray);

        inline int shapeSize() const;

        int size() const;
        //int itemsCount() const;

        TemplateArray<int> shape() const;
        inline int shape(int axis) const;

        template<class ... U>
        const TemplateArray<T> & reshape(int axis1, U ... args);
        const TemplateArray<T> & reshape(TemplateArray<int> newShape);

        TemplateArray<int> _getAxisDisplacement() const;
        int _getAxisDisplacement(int axis) const;

        template<class AXIS, class ... U> T &item(AXIS x, U ... args) const;
        template<class AXIS> T &item(AXIS x) const;
        template<class AXIS> T &item(const TemplateArray<AXIS> &axisArray);

        TemplateArray<T> getCopy() const;

        template<class U>
        void push(const U &value, const int idx=END);
        template<class U>
        void pushArray(const TemplateArray<U> &other, const int idx=END);

        T pop(const int idx=END);
        TemplateArray<T> popArray(const int idx=END);

        // template<class U>
        // inline explicit operator U() { return (U)this->data_item(0); }

        template<class U>
        explicit operator TemplateArray<U>(){
            TemplateArray<U> result;
            result.resize(this->shape());
            for(int j=0; j<this->data_size(); ++j)
            {
                result.data_item(j) = (U)this->data_item(j);
            }
            return result;
        }
        template<class ... U> inline T &operator()(U ... args);
        template<class ... U> const inline T &operator()(U ... args) const;
        template<class U> inline T &operator()(TemplateArray<U> axisArray);

        template<class U> inline const TemplateArray<T> operator+=(const TemplateArray<U> &other);
        template<class U> inline TemplateArray<T> operator+(const TemplateArray<U> &other) const;
        inline const TemplateArray<T>  operator+=(const T &other);
        inline const TemplateArray<T> operator+(const T &other) const;

        template<class U> inline const TemplateArray<T> operator-=(const TemplateArray<U> &other);
        template<class U> inline TemplateArray<T> operator-(const TemplateArray<U> &other) const;
        inline const TemplateArray<T>  operator-=(const T &other);
        inline const TemplateArray<T> operator-(const T &other) const;

        template<class U> const TemplateArray<T> operator*=(const TemplateArray<U> &other);
        template<class U> inline TemplateArray<T> operator*(const TemplateArray<U> &other) const;
        inline const TemplateArray<T>  operator*=(const T &other);
        inline TemplateArray<T> operator*(const T &other) const;

        inline const TemplateArray<T> operator/=(const T &other);
        inline TemplateArray<T> operator/(const T &other) const;

        inline const TemplateArray<T> operator%=(const T &other);
        inline TemplateArray<T> operator%(const T &other);

        template<class U> inline bool operator==(const TemplateArray<U> &other);
        template<class U> inline bool operator!=(const TemplateArray<U> &other);
        template<class U> bool operator>(const TemplateArray<U> &other);
        template<class U> inline bool operator<=(const TemplateArray<U> &other);
        template<class U> bool operator>=(const TemplateArray<U> &other);
        template<class U> inline bool operator<(TemplateArray<U> &other);

        std::ostream& ostream(std::ostream& stream, int ident=2, bool quotes=false) const;
        std::istream& istream(std::istream& stream);

        void loadFile(std::string path);
        void saveFile(std::string path);

        //const TemplateArray<T> &sort(bool reverse=false, int lo=0, int hi=END);
        void sort(bool reverse=false, int lo=0, int hi=END);

        template<class U, class V>
        inline void swap(U idx1, V idx2);

        inline void _resize1DArray(int size);
        inline T *data();
        inline const T *data() const;
        inline const int data_size() const;
        inline T &data_item(int idx);
        inline const T data_item(int idx) const;

        iterator begin(){ return iterator(*this); }
        iterator end(){ return iterator(*this, this->data_size()); }
        iterator_const begin() const{ return iterator(*this); }
        iterator_const end() const{ return iterator(*this, this->data_size()); }

        class iterator
        {
        private:
            TemplateArray<T> &_data;
            int _ptr;
        public:
            iterator(TemplateArray<T> &data, int idx=0) : _data(data), _ptr(idx) {};
            bool operator==(iterator other){ return (this->_ptr == other._ptr); }
            bool operator!=(iterator other){ return !(*this==other); }
            const T &operator=(const T value){ return this->_data.data_item(this->_ptr) = value; }
            iterator &operator++(){ ++this->_ptr; return *this; }
            iterator operator++(int){ iterator result(this->_data, this->_ptr); ++this->_ptr; return result; }
            T &operator*(){ return this->_data.data_item(this->_ptr); }
        };

        class iterator_const
        {
        private:
            const TemplateArray<T> &_data;
            int _ptr;
        public:
            iterator_const(const TemplateArray<T> &data, int idx=0) : _data(data), _ptr(idx) {};
            bool operator==(iterator_const other) const { return (this->_ptr == other._ptr); }
            bool operator!=(iterator_const other) const { return !(*this==other); }
            const T &operator=(const T value) const { return this->_data.data_item(this->_ptr) = value; }
            iterator_const &operator++(){ ++this->_ptr; return *this; }
            iterator_const operator++(int){ iterator_const result(this->_data, this->_ptr); ++this->_ptr; return result; }
            const T &operator*()  { return this->_data.data_item(this->_ptr); }
        };


        class SubArray
        {
            DM4thInternal::_BaseArray<DM4thInternal::_BaseArray<int>> _idxs;
            TemplateArray<T> &_data;
            int _totalSize;
        public:
            SubArray(TemplateArray<T> &data) : _data(data), _totalSize(0) {};

            template<class ... U>
            void setIdxs(U ... args){
                this->_idxs.resize(this->_data.shapeSize());
                this->_setIdxs(0, args...);
            }

            operator TemplateArray<T>()
            {
                TemplateArray<T> result;

                TemplateArray<int> oldShape = this->_data.shape();
                TemplateArray<int> oldDisp = this->_data._getAxisDisplacement();

                TemplateArray<int> newShape;
                int realSize=0;
                newShape.resize(this->_idxs.size());
                for(int j=0; j<this->_idxs.size();++j)
                {
                    newShape(j) = this->_idxs(j).size();
                    if(newShape(j)>1)
                    {
                        ++realSize;
                    }
                }

                result.resize(newShape);
                TemplateArray<int> newDisp = result._getAxisDisplacement();

                for( int j=0; j<this->_idxs(0).size(); ++j )
                {
                    this->_slider(
                        1,
                        oldDisp.item(0)*this->_idxs(0)(j),
                        newDisp.item(0)*j,
                        oldDisp, newDisp,
                        result
                    );
                }

                TemplateArray<int> realNewShape;
                realNewShape.resize(realSize);
                realSize=0;
                for(int j=0; j<this->_idxs.size(); ++j)
                {
                    if(this->_idxs(j).size()>1)
                    {
                        realNewShape(realSize) = this->_idxs(j).size();
                        ++realSize;
                    }
                }

                result.reshape(realNewShape);
                return result;
            }

            // const SubArray &operator=(const SubArray &other)
            // {
            //     if(this!=&other)
            //     {
            //         if(other._totalSize==this->_totalSize)
            //         {

            //         }else if(other._totalSize == 1)
            //         {

            //         }else
            //         {
            //             DM4thAssert(false);
            //         }
            //     }
            //     return *this;
            // }

        private:

            void _slider(
                int axis,
                int oldDispCount, int newDispCount,
                TemplateArray<int> oldDisp, TemplateArray<int> newDisp,
                TemplateArray<T> &result
            )
            {
                if(axis<this->_idxs.size()-1)
                {
                    for(int j=0; j<this->_idxs(axis).size(); ++j)
                    {
                        this->_slider(axis+1,
                            oldDispCount+oldDisp.item(axis)*this->_idxs(axis)(j),
                            newDispCount+newDisp.item(axis)*j,
                            oldDisp, newDisp,
                            result
                        );
                    }
                }else{
                    for(int j=0; j<this->_idxs(axis).size(); ++j)
                    {
                        int to = newDispCount+newDisp.item(axis)*j;
                        int from = oldDispCount+oldDisp.item(axis)*this->_idxs(axis)(j);
                        result.data_item(to) = this->_data.data_item(from);
                    }
                }
            }

            template<class U, class ... V>
            void _setIdxs(int idx, U first, V ... args)
            {
                TemplateArray<int>(first)._arrayData()->array.copyReferenceTo(this->_idxs(idx));
                this->_totalSize += this->_idxs(idx).size();
                this->_setIdxs(idx+1, args...);
            }
            void _setIdxs(int idx){
                if(idx<this->_data.shapeSize())
                {
                    TemplateArray<int> result;
                    result.resize(this->_data.shape(idx));
                    for(int j=0; j<this->_data.shape(idx); ++j)
                    {
                        result(j) = j;
                    }
                    this->_setIdxs(idx, result);
                }
            }

        };

        template<class ...U>
        SubArray subArr(U ... args)
        {
            SubArray result(*this);
            result.setIdxs(args ...);
            return result;
        }

    private:
        int _partition(bool reverse, const int lo, const int hi);

        void _resize(int axis, int oldDispCount, int newDispCount,
            TemplateArray<int> &oldDisp,  TemplateArray<int> &newDisp,
            TemplateArray<int> &oldShape,  TemplateArray<int> &newShape,
            const DM4thInternal::_BaseArray<T> &oldArray);

        template<class ... U>
        void _reshape(int axis, int first, U ... args);
        void _reshape(int axis, int last);

        template<class ... U>
        int _item(int axis, int pos, int idx, U ... args) const;
        int _item(int axis, int pos, int idx) const;

        DM4thInternal::_BaseArray<T> _allocZeros(const TemplateArray<int> &axisArray);

        void _ostream(std::ostream& stream, int shapeIdx, int& c_idx, int ident, bool quotes) const;
        void _istream(std::istream& stream, std::queue<T> &values, int shapeIdx, int& c_size, bool &shapeAllocated);
};

template<class T>
inline std::ostream& operator<<(std::ostream& stream, const TemplateArray<T> &arr);
template<class T>
inline std::istream& operator>>(std::istream& stream, TemplateArray<T> &arr);

}