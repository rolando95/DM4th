#pragma once

#include "_BaseArray_impl.h"
#include <queue>

template<class T>
class TemplateArray: public _ArrayDataManager<T>
{
    typedef _ArrayDataManager<T> super;

    public:
        TemplateArray();  
        TemplateArray(range<T> &other);
        TemplateArray(const std::string &other);

        template<class ... U>
        inline void resize(int axis1, U ... args);
        inline void resize(int axis1);

        void resize(const TemplateArray<int> &axisArray);        
    
        inline int shapeSize() const;

        int size() const;

        TemplateArray<int> shape() const;
        int shape(int axis) const;

        template<class ... U>
        void reshape(int axis1, U ... args);
        void reshape(TemplateArray<int> newShape);

        TemplateArray<int> _getAxisDisplacement() const;
        int _getAxisDisplacement(int axis) const;

        template<class ... U>
        T &item(int x, U ... args) const;
        T &item(int x) const;
        T &item(const TemplateArray<int> &axisArray);

        TemplateArray<T> getCopy() const;

        template<class U>
        void push(const U &value, const int idx=END);
        template<class U>
        void pushArray(const TemplateArray<U> &other, const int idx=END);
        
        T pop(const int idx=END);
        TemplateArray<T> popArray(const int idx=END);

        template<class ... U> inline T &operator()(U ... args);
        template<class ... U> const inline T &operator()(U ... args) const;
        inline T &operator()(TemplateArray<int> axisArray);

        template<class U> const TemplateArray<T> operator+=(const TemplateArray<U> &other);
        template<class U> TemplateArray<T> operator+(const TemplateArray<U> &other) const;

        template<class U> const TemplateArray<T> operator-=(const TemplateArray<U> &other);
        template<class U> TemplateArray<T> operator-(const TemplateArray<U> &other) const;

        template<class U> bool operator==(const TemplateArray<U> &other);
        template<class U> inline bool operator!=(const TemplateArray<U> &other);
        template<class U> bool operator>(const TemplateArray<U> &other);
        template<class U> inline bool operator<=(const TemplateArray<U> &other);
        template<class U> bool operator>=(const TemplateArray<U> &other);
        template<class U> inline bool operator<(TemplateArray<U> &other);

        std::ostream& ostream(std::ostream& stream, int ident=2, bool quotes=false) const;
        std::istream& istream(std::istream& stream);

        inline void _resize1DArray(int size);
        inline T *c_arr();
        inline const T *c_arr() const;
        inline const int c_arr_size() const;
        inline T &c_arr_item(int idx);
        inline const T c_arr_item(int idx) const;

    private:
        void _resize(int axis, int oldDispCount, int newDispCount, 
            TemplateArray<int> &oldDisp,  TemplateArray<int> &newDisp, 
            TemplateArray<int> &oldShape,  TemplateArray<int> &newShape,
            T* oldArray);

        template<class ... U>
        void _reshape(int axis, int first, U ... args);
        void _reshape(int axis, int last);

        template<class ... U>
        int _item(int axis, int pos, int idx, U ... args) const;
        int _item(int axis, int pos, int idx) const;

        T* _allocZeros(const TemplateArray<int> &axisArray);

        void _ostream(std::ostream& stream, int shapeIdx, int& c_idx, int ident, bool quotes) const;
        void _istream(std::istream& stream, std::queue<T> &values, int shapeIdx, int& c_size, bool &shapeAllocated);
};

template<class T>
inline std::ostream& operator<<(std::ostream& stream, const TemplateArray<T> &arr);
template<class T>
inline std::istream& operator>>(std::istream& stream, TemplateArray<T> &arr);