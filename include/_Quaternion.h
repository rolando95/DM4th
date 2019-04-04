#ifndef __QUATERNION_H__
#define __QUATERNION_H__
#include "_Matrix.h"

class Quaternion: protected _ArrayManager<Number>{
public:
    using _ArrayManager::operator=;
    
    Quaternion();
    Quaternion(const Quaternion&);
    Quaternion(Vector v);
    Quaternion(Number v1, Number v2, Number v3, Number v4);

};

#endif