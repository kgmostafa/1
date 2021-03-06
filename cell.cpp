#include "cell.h"
#include <iostream>

#define EPSILON std::numeric_limits<float>::epsilon()

Cell::Cell() :
    _initialized(false)
{
}

std::vector<Triangle> Cell::getFacets()
{
    return _facets;
}

void Cell::scale(float x, float y, float z)
{
    glm::vec3 tmpMin = _min;
    moveToOrigin();
    for(std::vector<Triangle>::iterator it = _facets.begin() ; it != _facets.end(); ++it) {
        it->scale(x, y, z);
    }
    translate(tmpMin.x, tmpMin.y, tmpMin.z);
    calculateBounds();
}

void Cell::rotate(glm::vec3 angles)
{
    rotate(angles.x, angles.y, angles.z);
}

void Cell::rotate(float x, float y, float z)
{
    rotateX(x);
    rotateY(y);
    rotateZ(z);
}

void Cell::rotateX(float angle)
{
    if(angle < EPSILON) {
        return;
    }
    for(std::vector<Triangle>::iterator it = _facets.begin() ; it != _facets.end(); ++it) {
        it->rotateX(angle);
    }
    calculateBounds();
}

void Cell::rotateY(float angle)
{
    if(angle < EPSILON) {
        return;
    }
    for(std::vector<Triangle>::iterator it = _facets.begin() ; it != _facets.end(); ++it) {
        it->rotateY(angle);
    }
    calculateBounds();
}

void Cell::rotateZ(float angle)
{
    if(angle < EPSILON) {
        return;
    }
    for(std::vector<Triangle>::iterator it = _facets.begin() ; it != _facets.end(); ++it) {
        it->rotateZ(angle);
    }
    calculateBounds();
}

void Cell::translate(float x, float y, float z)
{
    for(std::vector<Triangle>::iterator it = _facets.begin() ; it != _facets.end(); ++it) {
        it->translate(x, y, z);
    }
    calculateBounds();
}

void Cell::resize(glm::vec3 size)
{
    resize(size.x, size.y, size.z);
}

void Cell::resize(float x, float y, float z)
{
    calculateBounds();
    float factorX = x/_maxXLength;
    float factorY = y/_maxYLength;
    float factorZ = z/_maxZLength;
    scale(factorX, factorY, factorZ);
    calculateBounds();
}

void Cell::resizeX(float size)
{
    float factor = size/_maxXLength;
    scale(factor, 1.0, 1.0);
    calculateBounds();
}

void Cell::resizeY(float size)
{
    float factor = size/_maxYLength;
    scale(1.0, factor, 1.0);
    calculateBounds();
}

void Cell::resizeZ(float size)
{
    float factor = size/_maxZLength;
    scale(1.0, 1.0, factor);
    calculateBounds();
}

void Cell::place(glm::vec3 pos)
{
    place(pos.x, pos.y, pos.z);
}

void Cell::place(float x, float y, float z)
{
    moveToOrigin();
    for (std::vector<Triangle>::iterator it = _facets.begin() ; it != _facets.end(); ++it) {
        it->translate(x, y, z);
    }
    calculateBounds();
}

void Cell::moveToOrigin()
{
    for (std::vector<Triangle>::iterator it = _facets.begin() ; it != _facets.end(); ++it) {
        it->translate(-_min.x, -_min.y, -_min.z);
    }
    calculateBounds();
}

bool Cell::isInitialized()
{
    return _initialized;
}

void Cell::calculateBounds()
{
    const float minFloat = std::numeric_limits<float>::lowest();
    const float maxFloat = std::numeric_limits<float>::max();
    glm::vec3 min(maxFloat, maxFloat, maxFloat);
    glm::vec3 max(minFloat, minFloat, minFloat);

    for (std::vector<Triangle>::iterator it = _facets.begin() ; it != _facets.end(); ++it) {
        glm::vec3 tmpMin = it->getMin();
        glm::vec3 tmpMax = it->getMax();

        // Check if is lower
        if(tmpMin.x < min.x) {
            min.x = tmpMin.x;
        }
        if(tmpMin.y < min.y) {
            min.y = tmpMin.y;
        }
        if(tmpMin.z < min.z) {
            min.z = tmpMin.z;
        }
        // Check if is higher
        if(tmpMax.x > max.x) {
            max.x = tmpMax.x;
        }
        if(tmpMax.y > max.y) {
            max.y = tmpMax.y;
        }
        if(tmpMax.z > max.z) {
            max.z = tmpMax.z;
        }
    }
    _min = min;
    _max = max;

    _maxXLength = _max.x - _min.x;
    _maxYLength = _max.y - _min.y;
    _maxZLength = _max.z - _min.z;

    _maxLength = _maxXLength;
    if(_maxYLength > _maxLength) {
        _maxLength = _maxYLength;
    }
    if(_maxZLength > _maxLength) {
        _maxLength = _maxZLength;
    }
}
