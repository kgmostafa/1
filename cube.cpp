#include "cube.h"
#include "utils.h"

Cube::Cube() :
    Cell(), _edgeLength(10.0)
{
    _initialized = init();
}

Cube::Cube(float el) :
    Cell(), _edgeLength(el)
{
    _initialized = init();
}

float Cube::getEdgeLength() {
    return _edgeLength;
}

bool Cube::init() {
    if(_edgeLength <= 0) {
        return false;
    }

    std::vector<Triangle> square[6];
    for(int i = 0; i < 6; i++) {
        square[i] = Utils::createSquare(_edgeLength);
    }

    // Square 0
    _facets.insert(_facets.end(), square[0].begin(), square[0].end());

    // Square 1
    Utils::rotateX(square[1], glm::radians(180.0));
    Utils::translate(square[1], 0.0, _edgeLength, _edgeLength);
    _facets.insert(_facets.end(), square[1].begin(), square[1].end());

    // Square 2
    Utils::rotateY(square[2], glm::radians(90.0));
    Utils::translate(square[2], 0.0, 0.0, _edgeLength);
    _facets.insert(_facets.end(), square[2].begin(), square[2].end());

    // Square 3
    Utils::rotateY(square[3], glm::radians(-90.0));
    Utils::translate(square[3], _edgeLength, 0.0, 0.0);
    _facets.insert(_facets.end(), square[3].begin(), square[3].end());

    // Square 4
    Utils::rotateX(square[4], glm::radians(-90.0));
    Utils::translate(square[4], 0.0, 0.0, _edgeLength);
    _facets.insert(_facets.end(), square[4].begin(), square[4].end());

    // Square 5
    Utils::rotateX(square[5], glm::radians(90.0));
    Utils::translate(square[5], 0.0, _edgeLength, 0.0);
    _facets.insert(_facets.end(), square[5].begin(), square[5].end());

    // Calculate the boundaries
    calculateBounds();

    return true;
}
