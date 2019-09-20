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
        TemplateArray();  
        TemplateArray(const std::string &other);

        template<class ... U>
        inline void resize(int axis1, U ... args);
        inline void resize(int axis1);

        void resize(const TemplateArray<int> &axisArray);        
    
        inline int shapeSize() const;

        int size() const;
        int itemsCount() const;
        
        TemplateArray<int> shape() const;
        int shape(int axis) const;

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

        template<class ... U> inline T &operator()(U ... args);
        template<class ... U> const inline T &operator()(U ... args) const;
        template<class U> inline T &operator()(TemplateArray<U> axisArray);

        template<class U> inline const TemplateArray<T> operator+=(const TemplateArray<U> &other);
        template<class U> inline TemplateArray<T> operator+(const TemplateArray<U> &other) const;

        template<class U> inline const TemplateArray<T> operator-=(const TemplateArray<U> &other);
        template<class U> inline TemplateArray<T> operator-(const TemplateArray<U> &other) const;

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