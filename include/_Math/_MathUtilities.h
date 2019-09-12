#pragma once

#include "../_Array/_Array.h"
#include "../_Number/_Number.h"

typedef Number (* Function)(Number x);

#define FUNCTION(name) Number name(Number x)