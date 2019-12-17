#pragma once

#include "MathUtils.h"

namespace DM4th
{

inline  number exp(const  number &x);
inline fnumber exp(const fnumber &x);

inline  number gamma(const  number &z, const  number &tolerance=1e-7);
inline fnumber gamma(const fnumber &z, const fnumber &tolerance=1e-7);
inline  number gamma(const  double &z, const  number &tolerance=1e-7);

inline  number PI(const  number &z, const  number &tolerance=1e-7);
inline fnumber PI(const fnumber &z, const fnumber &tolerance=1e-7);
inline  number PI(const  double &z, const  number &tolerance=1e-7);

inline  number derivative(const std::function< number( number)> &f, const  number x0,  number order=1,  number h=1e-2);
inline fnumber derivative(const std::function<fnumber(fnumber)> &f, const fnumber x0, fnumber order=1, fnumber h=1e-2);
inline  double derivative(const std::function< double( double)> &f, const  double x0,  double order=1,  double h=1e-2);

inline NDArray< number> diff(NDArray< number> v,  number iter=1);  
inline NDArray<fnumber> diff(NDArray<fnumber> v, fnumber iter=1);
inline NDArray< double> diff(NDArray< double> v,  double iter=1);

inline  number integral(const std::function< number( number)> &f, const  number& a, const  number& b,  number subintervals=1000);
inline fnumber integral(const std::function<fnumber(fnumber)> &f, const fnumber& a, const fnumber& b, fnumber subintervals=1000);
inline  double integral(const std::function< double( double)> &f, const  double& a, const  double& b,  double subintervals=1000);

inline  number RK4(const std::function< number( number, number)> &fd,  number t0,  number w,  number tn, const  number &iter=100);
inline fnumber RK4(const std::function<fnumber(fnumber,fnumber)> &fd, fnumber t0, fnumber w, fnumber tn, const fnumber &iter=100);
inline  double RK4(const std::function< double( double, double)> &fd,  double t0,  double w,  double tn, const  double &iter=100);

}