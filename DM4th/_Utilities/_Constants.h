#pragma once

#ifndef __CONSTANTS_H__
#define __CONSTANTS_H__

#define _USE_MATH_DEFINES
#include <cmath>
#include <limits>

namespace DM4th
{

#ifndef M_PI
#define M_PI    3.14159265358979323846
#endif

#ifndef M_E
#define M_E     2.7182818284590452353602875
#endif
constexpr double INF = std::numeric_limits<double>::infinity();
constexpr double pi = M_PI;
constexpr double e  = M_E;
constexpr double phi = 1.6180339887498948482045; // phi = (1+sqrt(5.0f))/2

}
#endif