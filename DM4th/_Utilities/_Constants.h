#pragma once

#ifndef __CONSTANTS_H__
#define __CONSTANTS_H__

#define _USE_MATH_DEFINES
#include <cmath>
#include <limits>

namespace DM4th
{

constexpr double INF = std::numeric_limits<double>::infinity();
constexpr double pi = M_PI;
constexpr double e  = M_E;
constexpr double phi = 1.6180339887498948482045; // phi = (1+sqrt(5.0f))/2

}
#endif