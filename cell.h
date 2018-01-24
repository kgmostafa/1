#ifndef CELL_H
#define CELL_H

#include <vector>

#include "triangle.h"

class Cell {
public:
    Cell();

    std::vector<Triangle> getFacets();

    void scale(float x, float y, float z);
    void rotateX(float angle);
    void rotateY(float angle);
    void rotateZ(float angle);
    void translate(float x, float y, float z);

    void place(float x, float y, float z);

    bool isInitialized();

    float _maxXLength;
    float _maxYLength;
    float _maxZLength;
    float _maxLength;

protected:
    virtual bool init() = 0;

    bool _initialized;
    std::vector<Triangle> _facets;
};

#endif // CELL_H
