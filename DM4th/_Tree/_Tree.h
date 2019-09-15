#pragma once

#include "_TemplateTree_impl.h"

namespace DM4th
{

template<class T=float>
class Tree: public TemplateTree<T>
{
    typedef TemplateTree<T> super;
    public:
        Tree(){}
        Tree(const super &other){ static_cast<super&>(*this) = other; }
        Tree(const std::string &other){ static_cast<super&>(*this) = other; };
        Tree(const char *other){ static_cast<super&>(*this) = std::string(other); };
};

template<>
class Tree<bool>: public TemplateTree<bool>
{
    typedef TemplateTree<bool> super;
    public:
        Tree(){}
        Tree(const super &other){ static_cast<super&>(*this) = other; }
        Tree(const std::string &other){ static_cast<super&>(*this) = other; };
        Tree(const char *other){ static_cast<super&>(*this) = std::string(other); };
};

}
