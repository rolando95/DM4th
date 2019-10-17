#pragma once

#include "_TemplateTree_impl.h"

namespace DM4th
{

template<class T=float>
class DTree: public TemplateTree<T>
{
    typedef TemplateTree<T> super;
    public:
        DTree(){}
        DTree(const super &other){ static_cast<super&>(*this) = other; }
        explicit DTree(const std::string &other){ static_cast<super&>(*this) = other; };
        explicit DTree(const char *other){ static_cast<super&>(*this) = std::string(other); };
};

template<>
class DTree<bool>: public TemplateTree<bool>
{
    typedef TemplateTree<bool> super;
    public:
        DTree(){}
        DTree(const super &other){ static_cast<super&>(*this) = other; }
        explicit DTree(const std::string &other){ static_cast<super&>(*this) = other; };
        explicit DTree(const char *other){ static_cast<super&>(*this) = std::string(other); };
};

}
