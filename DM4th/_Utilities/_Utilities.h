#pragma once

#include "_Constants.h"
#include "../_Exceptions/_Exceptions.h"

#include <istream>
#include <iostream>
#include <limits>
#include <queue>
#include <sstream>
#include <fstream>

namespace DM4th
{

constexpr int BEGIN = 0;
constexpr int END = std::numeric_limits<int>::max();
constexpr int ALL = std::numeric_limits<int>::max();

template<class T>
T mult(T last){
    return last;
}
template<class T, class ... U>
T mult(T first, U ... args){
    return first*mult(args...);
}


template<class T>
T sum(T last){
    return last;
}
template<class T, class ... U>
T sum(T first, U ... args){
    return first+sum(args...);
}

template<class T>
int count(T last){
    return 1;
}
template<class T, class ... U>
int count(T first, U ... args){
    return 1+count(args...);
}

void _handleIstreamSpacesAndNewLines(std::istream &stream);

void _handleStringInQuotes(std::istream &stream, std::string &value);

}