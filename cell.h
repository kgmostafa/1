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
    void resize(glm::vec3 size);
    void resize(float x, float y, float z);
    void resizeX(float size);
    void resizeY(float size);
    void resizeZ(float size);

    void place(glm::vec3 pos);
    void place(float x, float y, float z);
    void moveToOrigin();

    bool isInitialized();


    float _maxXLength;
    float _maxYLength;
    float _maxZLength;
    float _maxLength;

protected:
    virtual bool init() = 0;
    void calculateBounds();

    bool _initialized;
    std::vector<Triangle> _facets;

    glm::vec3 _min;
    glm::vec3 _max;
};

#endif // CELL_H
