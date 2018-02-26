#include "pyramid.h"
#include "triangle.h"
#include "utils.h"

Pyramid::Pyramid() :
    Cell(), _baseLength(10.0)
{
    _initialized = init();
}

Pyramid::Pyramid(float bl) :
    Cell(), _baseLength(bl)
{
    _initialized = init();
}

float Pyramid::getBaseLength() {
    return _baseLength;
}

bool Pyramid::init() {
    if(_baseLength <= 0) {
        return false;
    }

    std::vector<Triangle> base;

    base = Utils::createSquare(_baseLength);

    // Base
    _facets.insert(_facets.end(), base.begin(), base.end());

    // Lateral face 1
    Triangle face1(glm::vec3(0.0,0.0,0.0), glm::vec3(_baseLength, 0.0, 0.0), glm::vec3(_baseLength/2.0, _baseLength/2.0, _baseLength));
    _facets.push_back(face1);

    // Lateral face 2
    Triangle face2(glm::vec3(0.0,_baseLength,0.0), glm::vec3(_baseLength/2.0, _baseLength/2.0, _baseLength), glm::vec3(_baseLength, _baseLength, 0.0));
    _facets.push_back(face2);

    // Lateral face 3
    Triangle face3(glm::vec3(0.0,0.0,0.0), glm::vec3(_baseLength/2.0, _baseLength/2.0, _baseLength), glm::vec3(0.0, _baseLength, 0.0));
    _facets.push_back(face3);

    // Lateral face 4
    Triangle face4(glm::vec3(_baseLength,0.0,0.0), glm::vec3(_baseLength, _baseLength, 0.0), glm::vec3(_baseLength/2.0, _baseLength/2.0, _baseLength));
    _facets.push_back(face4);

    // Calculate the boundaries
    calculateBounds();

    return true;
}
