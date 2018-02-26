#include "icosphere.h"

Icosphere::Icosphere() :
    Cell(), _radius(10.0), _recursionLevel(2)
{
    _initialized = init();
}

Icosphere::Icosphere(float r) :
    Cell(), _radius(r), _recursionLevel(2)
{
    _initialized = init();
}

Icosphere::Icosphere(float r, quint8 rl) :
    Cell(), _radius(r), _recursionLevel(rl)
{
    _initialized = init();
}

float Icosphere::getRadius() {
    return _radius;
}

// Based on: http://blog.andreaskahler.com/2009/06/creating-icosphere-mesh-in-code.html
bool Icosphere::init() {
    // create 12 vertices of a icosahedron
    float t = (1.0 + sqrt(5.0)) / 2.0;

    glm::vec3 v0 = putOverUnitSphere(glm::vec3(-1, t,  0));
    glm::vec3 v1 = putOverUnitSphere(glm::vec3(1, t,  0));
    glm::vec3 v2 = putOverUnitSphere(glm::vec3(-1, -t,  0));
    glm::vec3 v3 = putOverUnitSphere(glm::vec3(1, -t,  0));

    glm::vec3 v4 = putOverUnitSphere(glm::vec3(0, -1, t));
    glm::vec3 v5 = putOverUnitSphere(glm::vec3(0, 1, t));
    glm::vec3 v6 = putOverUnitSphere(glm::vec3(0, -1, -t));
    glm::vec3 v7 = putOverUnitSphere(glm::vec3(0, 1, -t));

    glm::vec3 v8 = putOverUnitSphere(glm::vec3(t, 0, -1));
    glm::vec3 v9 = putOverUnitSphere(glm::vec3(t, 0, 1));
    glm::vec3 v10 = putOverUnitSphere(glm::vec3(-t, 0, -1));
    glm::vec3 v11 = putOverUnitSphere(glm::vec3(-t, 0, 1));


    // create 20 triangles of the icosahedron
//    std::vector<Triangle> faces;

    // 5 faces around point 0
    _facets.push_back(Triangle(v0, v11, v5));
    _facets.push_back(Triangle(v0, v5, v1));
    _facets.push_back(Triangle(v0, v1, v7));
    _facets.push_back(Triangle(v0, v7, v10));
    _facets.push_back(Triangle(v0, v10, v11));

    // 5 adjacent faces
    _facets.push_back(Triangle(v1, v5, v9));
    _facets.push_back(Triangle(v5, v11, v4));
    _facets.push_back(Triangle(v11, v10, v2));
    _facets.push_back(Triangle(v10, v7, v6));
    _facets.push_back(Triangle(v7, v1, v8));

    // 5 faces around point 3
    _facets.push_back(Triangle(v3, v9, v4));
    _facets.push_back(Triangle(v3, v4, v2));
    _facets.push_back(Triangle(v3, v2, v6));
    _facets.push_back(Triangle(v3, v6, v8));
    _facets.push_back(Triangle(v3, v8, v9));

    // 5 adjacent faces
    _facets.push_back(Triangle(v4, v9, v5));
    _facets.push_back(Triangle(v2, v4, v11));
    _facets.push_back(Triangle(v6, v2, v10));
    _facets.push_back(Triangle(v8, v6, v7));
    _facets.push_back(Triangle(v9, v8, v1));

    // refine triangles
    for (quint8 i = 0; i < _recursionLevel; i++) {
      std::vector<Triangle> faces;
      for (std::vector<Triangle>::iterator it = _facets.begin() ; it != _facets.end(); ++it) {
          // replace triangle by 4 triangles
          glm::vec3 a = getMiddlePoint(it->getV1(), it->getV2());
          glm::vec3 b = getMiddlePoint(it->getV2(), it->getV3());
          glm::vec3 c = getMiddlePoint(it->getV3(), it->getV1());

          faces.push_back(Triangle(it->getV1(), a, c));
          faces.push_back(Triangle(it->getV2(), b, a));
          faces.push_back(Triangle(it->getV3(), c, b));
          faces.push_back(Triangle(a, b, c));
      }
      _facets = faces;
    }

    translate(1.0, 1.0, 1.0);
    scale(_radius/2.0,_radius/2.0,_radius/2.0);

    // Calculate the boundaries
    calculateBounds();

    return true;
}

glm::vec3 Icosphere::getMiddlePoint(glm::vec3 v1, glm::vec3 v2) {
    glm::vec3 middle((v1.x + v2.x) / 2.0,
                     (v1.y + v2.y) / 2.0,
                     (v1.z + v2.z) / 2.0);

    return putOverUnitSphere(middle);
}

glm::vec3 Icosphere::putOverUnitSphere(glm::vec3 v) {
    double length = sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
    return glm::vec3(v.x/length, v.y/length, v.z/length);
}
