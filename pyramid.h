#ifndef PYRAMID_H
#define PYRAMID_H

#include "cell.h"

class Pyramid : public Cell {
public:
    Pyramid();
    Pyramid(float bl);

    float getBaseLength();

protected:
    bool init();
    float _baseLength;
};

#endif // PYRAMID_H
