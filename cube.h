#ifndef CUBE_H
#define CUBE_H

#include "cell.h"

class Cube : public Cell {
public:
    Cube();
    Cube(float el);

    float getEdgeLength();

protected:
    bool init();
    float _edgeLength;
};

#endif // CUBE_H
