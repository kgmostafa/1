#include "cube.h"
#include "utils.h"

Cube::Cube() :
    Cell(), _edgeLength(10.0f)
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

//    std::vector<Triangle> square[6];
//    for(int i = 0; i < 6; i++) {
//        square[i] = Utils::createSquare(_edgeLength);
//    }

    Vertex v0(0.0f, 0.0f, 0.0f);
    Vertex v1(_edgeLength, 0.0f, 0.0f);
    Vertex v2(0.0f, _edgeLength, 0.0f);
    Vertex v3(_edgeLength, _edgeLength, 0.0f);
    Vertex v4(0.0f, 0.0f, _edgeLength);
    Vertex v5(_edgeLength, 0.0f, _edgeLength);
    Vertex v6(0.0f, _edgeLength, _edgeLength);
    Vertex v7(_edgeLength, _edgeLength, _edgeLength);

    // Square 0
    _facets.push_back(Triangle(v0, v2, v1));
    _facets.push_back(Triangle(v1, v2, v3));

    // Square 1
    _facets.push_back(Triangle(v4, v5, v6));
    _facets.push_back(Triangle(v5, v7, v6));

    // Square 2
    _facets.push_back(Triangle(v0, v4, v2));
    _facets.push_back(Triangle(v2, v4, v6));

    // Square 3
    _facets.push_back(Triangle(v1, v7, v5));
    _facets.push_back(Triangle(v1, v3, v7));

    // Square 4
    _facets.push_back(Triangle(v0, v5, v4));
    _facets.push_back(Triangle(v0, v1, v5));

    // Square 5
    _facets.push_back(Triangle(v2, v6, v3));
    _facets.push_back(Triangle(v3, v6, v7));

    // Calculate the boundaries
    calculateBounds();

    return true;
}
