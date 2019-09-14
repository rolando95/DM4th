#pragma once

#include "_Tree.h"

template<class T>
inline T &TemplateTree<T>::node() const
{
    return super::_data->node;
}

template<class T>
inline T &TemplateTree<T>::item() const
{
    return super::_data->node;
}

template<class T> 
inline TemplateTree<T> &TemplateTree<T>::child(Number idx) const
{
    return super::_data->array[(int)idx];
}

template<class T> 
inline TemplateTree<T> &TemplateTree<T>::child(int idx) const
{
    return super::_data->array[(int)idx];
}

template<class T> template<class ... U>
TemplateTree<T> &TemplateTree<T>::child(Number idx, U ... args) const
{
    return super::_data->array[(int)idx].child(args ...);
}

template<class T> template<class ... U>
TemplateTree<T> &TemplateTree<T>::child(int idx, U ... args) const
{
    return super::_data->array[(int)idx].child(args ...);
}

template<class T> template<class U>
TemplateTree<T> &TemplateTree<T>::child(const TemplateArray<U> &axis, int level) const
{
    return this->child((NDArray<U>)axis, level);
}

template<class T> template<class U>
TemplateTree<T> &TemplateTree<T>::child(const NDArray<U> &axis, int level) const
{
    assert(axis.shapeSize()==1 && axis.size()>0);
    if(level<axis.size()-1)
    {
        return super::_data->array[(int)axis.item(level)].child(axis, level+1);
    }
    return super::_data->array[(int)axis.item(level)];
}

template<class T> template<class U>
inline TemplateTree<T> &TemplateTree<T>::operator()(U axis)
{
    return this->child(axis);
}


template<class T> template<class ... U>
inline TemplateTree<T> &TemplateTree<T>::operator()(U ... args)
{
    return this->child(args ...);
}
template<class T>
inline int TemplateTree<T>::size(){
    return this->_data->array.size();
}



template<class T> 
inline void TemplateTree<T>::resize(int size)
{
    super::_data->array.resize(size);
} 

template<class T> 
inline TemplateTree<T> &TemplateTree<T>::left()
{
    if(this->size()<1) this->resize(1);
    return super::_data->array[0];
}

template<class T> 
inline TemplateTree<T> &TemplateTree<T>::right()
{
    if(this->size()<2) this->resize(2);
    return super::_data->array[1];
}

template<class T>
void TemplateTree<T>::_ostream(std::ostream& stream, int shapeIdx, int& c_idx,  int ident, bool quotes) const       
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
            this->_ostream(stream, shapeIdx+1,c_idx, ident, quotes);
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
            if(quotes) stream<<"\"";
            stream<<this->c_arr()[c_idx];
            if(quotes) stream<<"\"";
        }
    }
    stream << "]";
}

template<class T>
void TemplateTree<T>::_istream(std::istream& stream, std::queue<T> &values, int shapeIdx, int& c_size, bool &shapeAllocated)
{
    int size=0;
    _handleIstreamSpacesAndNewLines(stream);
    if(stream.peek()=='[')
    {
        while (true)
        {
            _handleIstreamSpacesAndNewLines(stream);
            assert(stream.peek()=='['); stream.get();

            _handleIstreamSpacesAndNewLines(stream);
            if(stream.peek()==']') break; //This dim is empty

            this->_istream(stream, values, shapeIdx+1, c_size, shapeAllocated);
            size+=1;
            
            assert(stream.peek()==']'); stream.get();

            _handleIstreamSpacesAndNewLines(stream);
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
            
            _handleIstreamSpacesAndNewLines(stream);
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

template<class T>
std::ostream& TemplateTree<T>::ostream(std::ostream& stream, int ident, bool quotes) const
{
    // int c_idx = 0;          
    // this->_ostream(stream, 0, c_idx, ident, quotes);
    // return stream;
    return stream;
}

template<class T>
std::istream& TemplateTree<T>::istream(std::istream& stream)
{
    // int c_size = 0;
    // std::queue<T> values;
    // bool shapeAllocated = false;
    // _handleIstreamSpacesAndNewLines(stream);

    // assert(stream.peek()=='['); stream.get();
    
    // this->_istream(stream, values, 0, c_size, shapeAllocated);
    // _handleIstreamSpacesAndNewLines(stream);

    // assert(stream.peek()==']'); stream.get();

    // super::_data->array.resize(c_size);
    // for(int j=0; j<c_size; ++j)
    // {
    //     assert(!values.empty());
    //     this->c_arr()[j] = values.front(); 
    //     values.pop();
    // }
    return stream;
}

template<class T>
inline std::ostream& operator<<(std::ostream& stream, const TemplateTree<T> &tree)
{
    return tree.ostream(stream,4);
}

template<class T>
inline std::istream& operator>>(std::istream& stream, TemplateTree<T> &tree)
{
    return tree.istream(stream);
}