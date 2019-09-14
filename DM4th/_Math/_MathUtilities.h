#pragma once

#include "../_Array/_Array.h"
#include "../_Number/_Number.h"

namespace DM4th
{
    
typedef number (* Function)(number x);

#define FUNCTION(name) number name(number x)

}