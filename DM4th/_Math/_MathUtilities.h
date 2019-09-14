#pragma once

#include "../_Array/_Array.h"
#include "../_Number/_Number.h"

namespace DM4th
{
    
typedef Number (* Function)(Number x);

#define FUNCTION(name) Number name(Number x)

}