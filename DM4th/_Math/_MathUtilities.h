#pragma once

#include "../Array.h"
#include "../Number.h"

namespace DM4th
{
    
//typedef number (* Function)(number x);
typedef std::function<number(number)> Function;

}