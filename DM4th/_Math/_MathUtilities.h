#pragma once

#include "../_Array/_Array.h"
#include "../_Number/_Number.h"
#include <functional>

namespace DM4th
{
    
//typedef number (* Function)(number x);
typedef std::function<number(number)> Function;

}