// #include "../include/_Number/_Utilities.h"

// //Range class
// template class range<int>;
// template class range<float>;
// template class range<double>;

// template<class T> range<T>::range(): _begin(0), _end(0), _step(1) {}

// template<class T> range<T>::range(T end){
//     _end = end;
//     if(end<0){
//         _isInverse = true;
//         _step = -1;
//     }
// }

// template<class T> range<T>::range(T begin, T end){
//     _begin = begin;
//     _end = end;
//     if(begin>end){
//         _isInverse = true;
//         _step = -1;
//     }
// }

// template<class T> range<T>::range(T begin, T end, T step){
//     _begin = begin;
//     _end = end;
//     _step = step;
//     assert(
//         (begin>end && step>0) ||
//         (begin<end && step<0)
//     );
// }

