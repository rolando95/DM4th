#include "N.h"
#include <vector>

class V{
    int count = 0;
public:
    V();
    std::vector<N> data;
    N push(const N&,N=-1);
    V push(const V&,N=-1);
    N pop(const N=-1);
    N length();
    void resize(const N&);
};